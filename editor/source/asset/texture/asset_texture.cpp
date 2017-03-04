#include "asset/texture/asset_texture.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(asset::Texture);
        COFFEE_Ancestor(asset::Importer);
        COFFEE_Attribute(graphics::TEXTURE_PARAMETER, _Parameters, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace asset
{
    struct SupportedFormat { const char* Extension; ILenum Format; };
    const SupportedFormat SUPPORTED_FORMATS[] = {
        { "bmp", IL_BMP },
        { "jpg", IL_JPG },
        { "pcx", IL_PCX },
        { "tga", IL_TGA },
        { "tif", IL_TIF }
    };

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Texture::Texture() :
        _Parameters(graphics::TEXTURE_PARAMETER_MipMapping
            | graphics::TEXTURE_PARAMETER_BilinearFiltering
            | graphics::TEXTURE_PARAMETER_AnisotropicFiltering)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Texture::~Texture()
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool Texture::IsSupporting(const basic::String& file_extension)
    {
        uint32 count = sizeof(SUPPORTED_FORMATS)/sizeof(SupportedFormat);
        for (uint32 i=0 ; i<count ; ++i)
        {
            if (file_extension==SUPPORTED_FORMATS[i].Extension)
                return true;
        }
        return false;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool Texture::Import()
    {
        storage::Data* file_data = storage::System::Get().GetFileData(GetAssetPath());
        if (file_data==NULL)
            return false;
        if (file_data->GetSize()==0)
        {
            COFFEE_Delete(file_data);
            return false;
        }

        basic::String extension = GetAssetPath().GetFileExtension();
        uint32 format_index = NONE;
        uint32 count = sizeof(SUPPORTED_FORMATS)/sizeof(SupportedFormat);
        for (uint32 i=0 ; i<count ; ++i)
        {
            if (extension==SUPPORTED_FORMATS[i].Extension)
            {
                format_index = i;
                break;
            }
        }
        COFFEE_Assert(format_index!=NONE, core::ERROR_CODE_Unexpected, "Texture format is not supported.");

        storage::Path file_path = Manager::Get().GetResourcePath(GetAssetPath())
            + "/" + GetAssetPath().GetFileNameWithoutExtension() + ".texture";

        ILuint image_name;
        ilGenImages(1, &image_name);
        ilBindImage(image_name);

        bool result = false;
        if (ilLoadL(SUPPORTED_FORMATS[format_index].Format, file_data->GetBuffer(), file_data->GetSize()))
        {
            uint32 width = ilGetInteger(IL_IMAGE_WIDTH);
            uint32 height = ilGetInteger(IL_IMAGE_HEIGHT);
            uint32 depth = ilGetInteger(IL_IMAGE_DEPTH);

            bool it_is_bgr = false;
            uint32 component_count;
            switch(ilGetInteger(IL_IMAGE_FORMAT))
            {
                case IL_ALPHA:
                case IL_LUMINANCE:          component_count = 1; break;
                case IL_LUMINANCE_ALPHA:    component_count = 2; break;
                case IL_BGR:                it_is_bgr = true;
                case IL_RGB:                component_count = 3; break;
                case IL_BGRA:               it_is_bgr = true;
                case IL_RGBA:               component_count = 4; break;
                default: component_count = 0;
            }

            meta::SCALAR_FORMAT component_type;
            switch(ilGetInteger(IL_IMAGE_TYPE))
            {
                case IL_BYTE:           component_type = meta::SCALAR_FORMAT_Int8; break;
                case IL_UNSIGNED_BYTE:  component_type = meta::SCALAR_FORMAT_UInt8; break;
                case IL_SHORT:          component_type = meta::SCALAR_FORMAT_Int16; break;
                case IL_UNSIGNED_SHORT: component_type = meta::SCALAR_FORMAT_UInt16; break;
                case IL_INT:            component_type = meta::SCALAR_FORMAT_Int32; break;
                case IL_UNSIGNED_INT:   component_type = meta::SCALAR_FORMAT_UInt32; break;
                case IL_FLOAT:          component_type = meta::SCALAR_FORMAT_Real; break;

                default:
                    component_type = meta::SCALAR_FORMAT_None;
            }

            if (depth==1 && component_count!=0 && component_type!=meta::SCALAR_FORMAT_None)
            {
                SetProgress(0.20f);

                basic::Image* image = COFFEE_New(basic::Image);
                image->Create(width, height, 1, component_type, component_count, it_is_bgr);
                ILubyte* data = ilGetData();
                COFFEE_Copy(image->GetData(), data, width*height*component_count*image->GetComponentSize());
                SetProgress(0.50f);

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
                result = true;
            }
        }

        COFFEE_Delete(file_data);
        ilDeleteImages(1, &image_name);
        return result;
    }

}
}
