#include "asset/font/asset_font_ttf.h"
#include "ft2build.h"
#include FT_FREETYPE_H

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(asset::FontTTF);
        COFFEE_Ancestor(asset::Importer);
    //    COFFEE_Attribute(bool, _PreserveTexCoords, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace asset
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

	FontTTF::FontTTF()
    {
    }

    //--------------------------------------------------------------------------------------------//

    FontTTF::~FontTTF()
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool FontTTF::IsSupporting(const basic::String& file_extension)
    {
        return file_extension=="ttf";
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool FontTTF::Import()
    {
        storage::Data* file_data = storage::System::Get().GetFileData(GetAssetPath());
        if (file_data==NULL)
            return false;
        if (file_data->GetSize()==0)
        {
            COFFEE_Delete(file_data);
            return false;
        }
      
        storage::Path file_path = Manager::Get().GetResourcePath(GetAssetPath())
            + "/" + GetAssetPath().GetFileNameWithoutExtension() + ".font";
            
        graphics::Font* font = COFFEE_New(graphics::Font);
        
        FT_Library library;
        if (!FT_Init_FreeType(&library))
        {
            FT_Face face;
            if (!FT_New_Memory_Face(library, (const FT_Byte*)file_data->GetBuffer(),
                file_data->GetSize(), 0, &face)
                && !FT_Set_Pixel_Sizes(face,0,16))
            {
                uint32 max_w(0), max_h(0);
                for (uint32 glyph_index=0 ; glyph_index<255 ; ++glyph_index)
                {
                    FT_UInt gindex;
                    gindex = FT_Get_Char_Index(face, (char)glyph_index); 
                    if (!FT_Load_Glyph(face, gindex, FT_LOAD_DEFAULT)
                        && !FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL))
                    {
                        max_w = Maximum(max_w, (uint32)face->glyph->bitmap.width);
                        max_h = Maximum(max_h, (uint32)face->glyph->bitmap.rows);
                    }
                }

                uint32 width_glyph_count, height_glyph_count;
                uint32 image_width, image_height;
                width_glyph_count = (uint32)sqrtf(255.0f)+1;
                height_glyph_count = (uint32)sqrtf(255.0f)+1;
                image_width = width_glyph_count * max_w;
                image_height = height_glyph_count * max_h;
                image_width = (uint32) pow(2, ceil(log((real) image_width) / log(2.0f)));
                image_height = (uint32) pow(2, ceil(log((real) image_height) / log(2.0f)));

                font->SetColor(basic::Color(1.0f, 1.0f, 1.0f, 1.0f));
                font->SetHeight(max_h);
                font->SetFirstCharacterCode(0);
                font->SetLastCharacterCode(254);
                font->GrabGlyphImage().Create(image_width, image_height, 1, meta::SCALAR_FORMAT_UInt8, 4);

                for (uint32 glyph_index=0 ; glyph_index<255 ; ++glyph_index)
                {
                    SetProgress((real)glyph_index/254.0f);

                    FT_UInt gindex;
                    gindex = FT_Get_Char_Index(face, (char)glyph_index); 
                    bool exist;
                    exist = !FT_Load_Glyph(face, gindex, FT_LOAD_DEFAULT);
                    if (exist)
                        exist = !FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
                    
                    FT_GlyphSlot slot = face->glyph;
                    
                    if (slot->bitmap.buffer==NULL)
                        exist = false;

                    graphics::FontGlyph* glyph;
                    uint32 glyph_pos_x, glyph_pos_y;

                    glyph_pos_x = glyph_index%width_glyph_count;
                    glyph_pos_y = glyph_index/width_glyph_count;

                    glyph = COFFEE_New(graphics::FontGlyph);
                    glyph->SetPosition(basic::Vector2i(glyph_pos_x*max_w,
                        glyph_pos_y*max_h+(max_h-(int32)slot->bitmap.rows)));
                    glyph->SetSize(basic::Vector2i(exist?slot->bitmap.width:max_w/2, slot->bitmap.rows));
                    font->GrabGlyphArray().AddItem(glyph);

                    for (int32 y=0 ; y<(int32)max_h ; y++)
                    for (int32 x=0 ; x<(int32)max_w ; x++)
                    {
                        uint32 pos = (glyph_pos_x*max_w+x)
                            + (glyph_pos_y*max_h+y)*image_width;
                        
                        uint8 value;
                        if (exist && slot->bitmap.buffer!=NULL && x<slot->bitmap.width
                            && y>=(int32)max_h-slot->bitmap.rows)
                        {
                            value = slot->bitmap.buffer[(y-(max_h-(int32)slot->bitmap.rows))*slot->bitmap.width+x];
                        }
                        else
                        {
                            value = 0;
                        }

                        ((uint8*)font->GetGlyphImage().GetData())[pos*4+0] = value;
                        ((uint8*)font->GetGlyphImage().GetData())[pos*4+1] = value;
                        ((uint8*)font->GetGlyphImage().GetData())[pos*4+2] = value;
                        ((uint8*)font->GetGlyphImage().GetData())[pos*4+3] = value;
                    }
                }
                FT_Done_Face(face);
            }
            FT_Done_FreeType(library);
        }
        COFFEE_Delete(file_data);

        DeleteImportedResources();
        
        basic::Image glyph;
        if (font->ExtractGlyph(glyph, 'C'))
        {
            AddThumbnail(Manager::Get().GenerateThumbnail(GetImportPath(), glyph));
            AddThumbnail(Manager::Get().GenerateThumbnail(file_path, glyph));
        }

        font->Initialize();
        font->PreCreateLOD(0);
        resource::Chunk* resource_chunk;
        resource_chunk = resource::Manager::Get().Create(file_path);
        resource_chunk->AddLOD(*font);
        
        AddImportedResource(resource_chunk);
        return true;
    }

}
}
