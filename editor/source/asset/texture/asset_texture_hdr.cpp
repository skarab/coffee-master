#include "asset/texture/asset_texture_hdr.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(asset::TextureHDR);
        COFFEE_Ancestor(asset::Importer);
        COFFEE_Attribute(real, _Intensity, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(graphics::TEXTURE_PARAMETER, _Parameters, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(uint32, _SkyMip, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace asset
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    TextureHDR::TextureHDR() :
        _Intensity(100000.0f),
        _Parameters(
            graphics::TEXTURE_PARAMETER_BilinearFiltering
            | graphics::TEXTURE_PARAMETER_AnisotropicFiltering
            | graphics::TEXTURE_PARAMETER_LinearSpace),
        _SkyMip(0)
    {
    }

    //--------------------------------------------------------------------------------------------//

    TextureHDR::~TextureHDR()
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool TextureHDR::IsSupporting(const basic::String& file_extension)
    {
        return file_extension=="hdr";
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    static basic::Color _RGBEtoColor(const uint8* rgbe)
    {
        if (rgbe[3]!=0)
        {
            real f = ldexp(1.0f, (int32)rgbe[3]-(int32)(128+8));
            return basic::Color(rgbe[0]*f, rgbe[1]*f, rgbe[2]*f, 0.0f);
        }
        return basic::Color();
    }

    //--------------------------------------------------------------------------------------------//

    static void ColorToRGBE(uint8* rgbe, const basic::Color& color)
    {
        real v = Maximum(Maximum(color.R, color.G), color.B);
        if (v<1e-32)
        {
            rgbe[0] = rgbe[1] = rgbe[2] = rgbe[3] = 0;
        }
        else 
        {
            int32 e;
            v = frexp(v, &e)*256.0f/v;
            rgbe[0] = (uint8)(color.R*v);
            rgbe[1] = (uint8)(color.G*v);
            rgbe[2] = (uint8)(color.B*v);
            rgbe[3] = (uint8)(e+128);
        }
    }

    //--------------------------------------------------------------------------------------------//

    bool TextureHDR::Import()
    {
        HDRLoaderResult result;
        result.cols = NULL;

        if (!HDRLoader::load(storage::System::Get().GetPhysicalFilePath(GetAssetPath()).GetBuffer(), result))
        {
            if (result.cols!=NULL)
                delete result.cols;
            return false;
        }
        
        storage::Path sky_file_path = Manager::Get().GetResourcePath(GetAssetPath())
            + "/" + GetAssetPath().GetFileNameWithoutExtension() + ".sky";
    
        Clamp(_SkyMip, (uint32)0, (uint32)3);
        basic::String index("_mip%d", _SkyMip);
        storage::Path probe_file_path = Manager::Get().GetResourcePath(GetAssetPath())
            + "/" + GetAssetPath().GetFileNameWithoutExtension() + index + ".texture";
    
        uint32 width = GetPowerOfTwo(result.width);
        uint32 height = GetPowerOfTwo(result.height);

        basic::Image* image = COFFEE_New(basic::Image);
        image->Create(width, height, 1, meta::SCALAR_FORMAT_UInt8, 4);
        uint8* output = (uint8*)image->GetData();
        for (uint32 j=0 ; j<height ; ++j)
        for (uint32 i=0 ; i<width ; ++i)
        {
            uint32 x = i*(result.width-1)/(width-1);
            uint32 y = j*(result.height-1)/(height-1);
            memcpy(output+(j*width+i)*4, result.cols+(y*result.width+x)*4, 4);
        }
        delete result.cols;

        DeleteImportedResources();
        AddThumbnail(Manager::Get().GenerateThumbnail(GetImportPath(), *image));
        AddThumbnail(Manager::Get().GenerateThumbnail(sky_file_path, *image));

        // TODO: maybe move that into basic::Image if useful..

        float flevel = log10((float)width)/log10(2.0f);
		uint32 lodw = static_cast<int>(flevel);
		if (fabs(flevel-floor((float)lodw))!=0.0f)
			++lodw;
        
        flevel = log10((float)height)/log10(2.0f);
		uint32 lodh = static_cast<int>(flevel);
		if (fabs(flevel-floor((float)lodh))!=0.0f)
			++lodh;

        graphics::Sky* sky;
        sky = COFFEE_New(graphics::Sky);
        sky->SetIntensity(_Intensity);
        sky->GrabMipmaps().Resize(4);

        basic::Image* source_image = image;

        for (uint32 i=0 ; i<4 ; ++i)
        {
            uint32 w = (uint32)pow(2.0f, (float)lodw-(i*lodw/4.0f));
            if (w<2) w=2;
            uint32 h = (uint32)pow(2.0f, (float)lodh-(i*lodh/4.0f));
            if (h<2) h=2;
            image = _GenerateMipmap(*sky, image, i, w, h);
        }

        COFFEE_Delete(source_image);

        sky->SetLightProbe(resource::Manager::Get().Load(probe_file_path));
        sky->Initialize();
        sky->PreCreateLOD(0);
        resource::Chunk* resource_chunk = resource::Manager::Get().Create(sky_file_path);
        resource_chunk->AddLOD(*sky);        
        AddImportedResource(resource_chunk);
        return true;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    basic::Image* TextureHDR::_GenerateMipmap(graphics::Sky& sky, const basic::Image* input, uint32 id, uint32 width, uint32 height)
    {
        basic::String index("_mip%d", id);
        storage::Path file_path = Manager::Get().GetResourcePath(GetAssetPath())
            + "/" + GetAssetPath().GetFileNameWithoutExtension() + index + ".texture";
    
        sky.GrabMipmaps()[id] = resource::Manager::Get().Load(file_path);

        basic::Image* image = COFFEE_New(basic::Image);
        image->Create(width, height, 1, meta::SCALAR_FORMAT_UInt8, 4);
        const uint8* src = (const uint8*)input->GetData();
        uint8* output = (uint8*)image->GetData();
        for (uint32 j=0 ; j<height ; ++j)
        for (uint32 i=0 ; i<width ; ++i)
        {
            int32 x = i*(input->GetWidth()-1)/(width-1);
            int32 y = j*(input->GetHeight()-1)/(height-1);

            basic::Color color;
            if (id==0)
            {
                color = _RGBEtoColor(src+(y*input->GetWidth()+x)*4);
            }
            else
            {
                // Apply simple blur..

                real count(0.0f);
                for (int32 b=-1 ; b<=1 ; ++b)
                {
                    if (y+b>=0 && y+b<(int32)input->GetHeight())
                    for (int32 a=-1 ; a<=1 ; ++a)
                    {
                        if (x+a>=0 && x+a<(int32)input->GetWidth())
                        {
                            color += _RGBEtoColor(src+((y+b)*input->GetWidth()+x+a)*4);
                            count += 1.0f;
                        }
                    }
                }
                color /= count;
            }
            
            ColorToRGBE(output+(j*width+i)*4+0, color);
        }
        
        AddThumbnail(Manager::Get().GenerateThumbnail(file_path, *image));

        graphics::Texture2D* texture;
        texture = COFFEE_New(graphics::Texture2D);
        texture->SetImage(*image);
        texture->SetParameters(
            graphics::TEXTURE_PARAMETER_BilinearFiltering
            | graphics::TEXTURE_PARAMETER_AnisotropicFiltering
            | graphics::TEXTURE_PARAMETER_LinearSpace);
        texture->Initialize();
        texture->PreCreateLOD(0);
        resource::Chunk* resource_chunk;
        resource_chunk = resource::Manager::Get().Create(file_path);
        resource_chunk->AddLOD(*texture);
        
        AddImportedResource(resource_chunk);
        return image;
    }

}
}
