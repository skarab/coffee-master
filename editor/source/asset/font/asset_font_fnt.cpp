#include "asset/font/asset_font_fnt.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(asset::FontFNT);
        COFFEE_Ancestor(asset::Importer);
    //    COFFEE_Attribute(bool, _PreserveTexCoords, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace asset
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

	FontFNT::FontFNT()
    {
    }

    //--------------------------------------------------------------------------------------------//

    FontFNT::~FontFNT()
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool FontFNT::IsSupporting(const basic::String& file_extension)
    {
        return file_extension=="fnt";
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool FontFNT::Import()
    {
        storage::Data* file_data = storage::System::Get().GetFileData(GetAssetPath());
        if (file_data==NULL)
            return false;
        if (file_data->GetSize()==0)
        {
            COFFEE_Delete(file_data);
            return false;
        }

        storage::Stream data;
        data.SetData(file_data);
        
        storage::Path file_path = Manager::Get().GetResourcePath(GetAssetPath())
            + "/" + GetAssetPath().GetFileNameWithoutExtension() + ".font";
            
        graphics::Font* font = COFFEE_New(graphics::Font);
        
        uint16 font_height;
        uint8 first_character_code;
        uint8 last_character_code;
        uint16 width_bytes;
        uint32 glyph_index;
        uint32* character_parameter_array;
        uint32 glyph_count;
        uint16 max_width;

        data.Seek(88);
        data.Pop(&font_height, sizeof(uint16));

        data.Seek(95);
        data.Pop(&first_character_code, sizeof(uint8));

        data.Seek(96);
        data.Pop(&last_character_code, sizeof(uint8));

        data.Seek(93);
        data.Pop(&max_width, sizeof(uint16));

        width_bytes = max_width / 8 + 2;

        glyph_count = last_character_code - first_character_code + 1;

        data.Seek(118);
        character_parameter_array = (uint32 *) malloc(sizeof(uint32) * glyph_count);
        data.Pop(character_parameter_array, sizeof(uint32) * glyph_count);

        uint32 width_glyph_count, height_glyph_count;
        uint32 image_width, image_height;

        width_glyph_count = (uint32) sqrtf((real) glyph_count) + 1;
        height_glyph_count = (uint32) sqrtf((real) glyph_count) + 1;

        image_width = width_glyph_count * max_width;
        image_height = height_glyph_count * font_height;

        image_width = (uint32) pow(2, ceil(log((real) image_width) / log(2.0f)));
        image_height = (uint32) pow(2, ceil(log((real) image_height) / log(2.0f)));

        font->SetHeight(font_height);
        font->SetFirstCharacterCode(first_character_code);
        font->SetLastCharacterCode(last_character_code);
        font->GrabGlyphImage().Create(image_width, image_height, 1, meta::SCALAR_FORMAT_UInt8, 4);

        uint8* font_data = (uint8*)COFFEE_Allocate(width_bytes*font_height);

        for (glyph_index=0 ; glyph_index<glyph_count ; ++glyph_index)
        {
            SetProgress((real)glyph_index/(glyph_count-1.0f));

            graphics::FontGlyph* glyph;
            uint16 width;
            uint16 offset;
            uint32 glyph_pos_x, glyph_pos_y;

            width = *(((uint16 *) character_parameter_array) + glyph_index * 2 + 0);
            offset = *(((uint16 *) character_parameter_array) + glyph_index * 2 + 1);

            glyph_pos_x = glyph_index % width_glyph_count;
            glyph_pos_y = glyph_index / width_glyph_count;

            glyph = COFFEE_New(graphics::FontGlyph);
            glyph->SetPosition(basic::Vector2i(glyph_pos_x * max_width, glyph_pos_y * font_height));
            glyph->SetSize(basic::Vector2i(width, font_height));
            font->GrabGlyphArray().AddItem(glyph);

            data.Seek(offset);
            data.Pop(font_data, sizeof(uint8) * width_bytes * font_height);

            for(uint32 y=0 ; y<font_height ; y++)
                for(uint32 x=0 ; x<width ; x++)
                {
                    uint32 pos = (glyph_pos_x * max_width + x) + (glyph_pos_y * font_height + y) * image_width;

                    int _x = x / 8;
                    int _b = x % 8;

                    uint8 value;

                    value = ((font_data[ _x * font_height + y ] & (128 >> _b)) != 0) ? 1 : 0;
                    value *= 255;

                    ((uint8*)font->GetGlyphImage().GetData())[pos*4+0] = 255;
                    ((uint8*)font->GetGlyphImage().GetData())[pos*4+1] = 255;
                    ((uint8*)font->GetGlyphImage().GetData())[pos*4+2] = 255;
                    ((uint8*)font->GetGlyphImage().GetData())[pos*4+3] = value;
                }
        }

        COFFEE_Free(font_data);

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
