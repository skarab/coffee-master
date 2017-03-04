#include "asset/texture/asset_texture_png.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(asset::TexturePNG);
        COFFEE_Ancestor(asset::Texture);
    COFFEE_EndType();

namespace asset
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    TexturePNG::TexturePNG()
    {
    }

    //--------------------------------------------------------------------------------------------//

    TexturePNG::~TexturePNG()
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool TexturePNG::IsSupporting(const basic::String& file_extension)
    {
        return file_extension=="png";
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    typedef struct
    {
        char name[256];
        unsigned char *data;
        long length;
        long offset;
    } file_buffer_t;

    //--------------------------------------------------------------------------------------------//

    void TEXTURE_PNG_Read(png_structp png_ptr, png_bytep data, png_size_t length)
    {
        file_buffer_t *src = (file_buffer_t *) png_get_io_ptr (png_ptr);
        COFFEE_Copy(data, src->data + src->offset, length);
        src->offset += (long) length;
    }

    //--------------------------------------------------------------------------------------------//

    bool TexturePNG::Import()
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
            + "/" + GetAssetPath().GetFileNameWithoutExtension() + ".texture";
        
        file_buffer_t file_buffer;
        png_structp png_ptr;
        png_infop info_ptr;
        png_bytep* row_pointers;
        int32 color_type, bit_depth;
        uint32 width, height;
        uint32 row_index;

        file_buffer.data = (unsigned char*) file_data->GetBuffer();
        file_buffer.offset = 0;
        file_buffer.length = file_data->GetSize();

        if (!png_check_sig(file_buffer.data, sizeof(png_byte)*8)
            || ((png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL)) == NULL)
            || ((info_ptr = png_create_info_struct(png_ptr)) == NULL)
            || (setjmp(png_jmpbuf(png_ptr))))
        {
            COFFEE_Delete(file_data);
            return false;
        }

        png_set_read_fn(png_ptr, (png_voidp *) &file_buffer, TEXTURE_PNG_Read);
        png_read_info(png_ptr, info_ptr);

        color_type = png_get_color_type(png_ptr, info_ptr);
        bit_depth = png_get_bit_depth(png_ptr, info_ptr);

        if (color_type == PNG_COLOR_TYPE_PALETTE)
            png_set_palette_to_rgb(png_ptr);

        if (bit_depth==16)
            png_set_strip_16(png_ptr);
        else if (bit_depth<8)
            png_set_packing(png_ptr);

        png_read_update_info(png_ptr, info_ptr);
        png_get_IHDR(png_ptr, info_ptr, (png_uint_32*)(&width),
            (png_uint_32 *)(&height), &bit_depth, &color_type,
            NULL, NULL, NULL);

        basic::Image* image = COFFEE_New(basic::Image);
        uint32 component_count = 0;

        switch (color_type)
        {
            case PNG_COLOR_TYPE_GRAY:           component_count = 1; break;
            case PNG_COLOR_TYPE_GRAY_ALPHA:     component_count = 2; break;
            case PNG_COLOR_TYPE_RGB:            component_count = 3; break;
            case PNG_COLOR_TYPE_RGB_ALPHA:      component_count = 4; break;

            default:
                COFFEE_Free(file_buffer.data);
                return false;
        }

        meta::SCALAR_FORMAT format = meta::SCALAR_FORMAT_None;

        switch (bit_depth)
        {
            case 8:     format = meta::SCALAR_FORMAT_UInt8; break;
            case 16:    format = meta::SCALAR_FORMAT_UInt16; break;
            case 32:    format = meta::SCALAR_FORMAT_UInt32; break;

            default:
                COFFEE_Delete(file_data);
                return false;
        }

        SetProgress(0.20f);

        image->Create(width, height, 1, format, component_count);
        row_pointers = (png_bytep *) COFFEE_Allocate(sizeof(png_bytep) * height);

        SetProgress(0.40f);

        for (row_index=0 ; row_index<height ; ++row_index)
        {
            row_pointers[row_index] = (png_bytep)(PtrToUlong(image->GetData()) + (
                row_index * width * image->GetComponentCount() * image->GetComponentSize()));
        }

        SetProgress(0.50f);

        png_read_image(png_ptr, row_pointers);
        COFFEE_Free(row_pointers);
        png_read_end(png_ptr, NULL);
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        COFFEE_Delete(file_data);

        SetProgress(0.70f);

        DeleteImportedResources();
        AddThumbnail(Manager::Get().GenerateThumbnail(GetImportPath(), *image));
        AddThumbnail(Manager::Get().GenerateThumbnail(file_path, *image));

        SetProgress(0.80f);

        graphics::Texture2D* texture;
        texture = COFFEE_New(graphics::Texture2D);
        texture->SetImage(*image);
        texture->SetParameters(_Parameters);
        texture->Initialize();
        texture->PreCreateLOD(0);
        resource::Chunk* resource_chunk;
        resource_chunk = resource::Manager::Get().Create(file_path);
        resource_chunk->AddLOD(*texture);
        
        AddImportedResource(resource_chunk);
        return true;
    }

}
}
