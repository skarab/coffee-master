#include "system/graphics/texture/2d/graphics_texture_2d.h"
#include "system/graphics/device/graphics_device.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginResource(graphics, Texture2D, "RAW Texture", "texture", 0);
        COFFEE_Ancestor(graphics::Texture);
        COFFEE_ResourceProperty(basic::Image*, _Image, meta::MODE_Serializeable | meta::MODE_Editable, 0);
        COFFEE_ResourceProperty(uint32, _Index, meta::MODE_None, 0);
    COFFEE_EndResource();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Texture2D::Texture2D() :
        _Image(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Texture2D::~Texture2D()
    {
        DestroyImage();
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Texture2D::SetImage(basic::Image& image)
    {
        DestroyImage();
        _Image.Set(&image);
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Image& Texture2D::GetImage() const
    {
        return *_Image.Get();
    }

    //--------------------------------------------------------------------------------------------//

    basic::Image& Texture2D::GrabImage()
    {
        return *_Image.Get();
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool Texture2D::HasImage() const
    {
        return (_Image.Get() != NULL);
    }

    //--------------------------------------------------------------------------------------------//

    bool Texture2D::IsValid() const
    {
        return HasImage() && !_Image.Get()->IsEmpty() && _Image.Get()->GetDepth()==1;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool Texture2D::Initialize()
    {
        COFFEE_GRAPHICS_Debug();

        if (!HasImage())
            _Image.Set(COFFEE_New(basic::Image));

        if (!IsValid())
            return true;

        COFFEE_GRAPHICS_Debug();
        glGenTextures(1, &_Index.Grab());
        COFFEE_GRAPHICS_Debug();
        glBindTexture(GL_TEXTURE_2D, _Index.Get());

        COFFEE_GRAPHICS_Debug();
        if (IsParameterEnabled(TEXTURE_PARAMETER_AnisotropicFiltering))
        {
            real aniso = (real)Device::Get().GetConfig().GetState(CONFIG_STATE_Anisotropic);
            if (aniso<1.0f)
                aniso = 1.0f;
            glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, aniso);
        }

        COFFEE_GRAPHICS_Debug();
        if (IsParameterEnabled(TEXTURE_PARAMETER_BilinearFiltering))
        {
            if (IsParameterEnabled(TEXTURE_PARAMETER_MipMapping))
            {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            }
            else
            {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            }
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
        else
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }

        COFFEE_GRAPHICS_Debug();

        if (IsParameterEnabled(TEXTURE_PARAMETER_Clamp))
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        }

        COFFEE_GRAPHICS_Debug();

        if (IsParameterEnabled(TEXTURE_PARAMETER_Modulate))
            glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        COFFEE_GRAPHICS_Debug();

        if (IsParameterEnabled(TEXTURE_PARAMETER_MipMapping))
        {
            gluBuild2DMipmaps(GL_TEXTURE_2D, _GetInternalFormat(), _Image.Get()->GetWidth(),
                _Image.Get()->GetHeight(), _GetInternalType(), _GetInternalComponentType(), _Image.Get()->GetData());
        }
        else
        {
            glTexImage2D(GL_TEXTURE_2D, 0, _GetInternalFormat(), _Image.Get()->GetWidth(),
                _Image.Get()->GetHeight(), 0, _GetInternalType(), _GetInternalComponentType(), _Image.Get()->GetData());
        }
        COFFEE_GRAPHICS_Debug();
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Texture2D::Finalize()
    {
        if (IsValid())
            glDeleteTextures(1, &_Index.Grab());
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    void Texture2D::Bind(uint32 multi_texture_index)
    {
        if (IsValid())
        {
            glActiveTexture(GL_TEXTURE0 + multi_texture_index);
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, _Index.Get());
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Texture2D::UnBind(uint32 multi_texture_index)
    {
        if (IsValid())
        {
            glActiveTexture(GL_TEXTURE0 + multi_texture_index);
            glBindTexture(GL_TEXTURE_2D, 0);
            glDisable(GL_TEXTURE_2D);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Texture2D::DestroyImage()
    {
        if (_Image.GrabValue()!=NULL)
        {
            COFFEE_Delete(_Image.GrabValue());
            _Image.SetValue(NULL);
        }
    }

    //-QUERIES------------------------------------------------------------------------------------//

    uint32 Texture2D::_GetInternalType() const
    {
        switch(_Image.Get()->GetComponentCount())
        {
            case 1: return GL_LUMINANCE;
            case 2: return GL_LUMINANCE_ALPHA;
            case 3: if (_Image.Get()->IsBGR()) return GL_BGR; else return GL_RGB;
            case 4: if (_Image.Get()->IsBGR()) return GL_BGRA; else return GL_RGBA;

            default:
                COFFEE_Error(core::ERROR_CODE_GraphicsSystem, "Texture format unsupported.");
        }
        return 0;
    }

    //--------------------------------------------------------------------------------------------//

    uint32 Texture2D::_GetInternalFormat() const
    {
        switch(_Image.Get()->GetComponentCount())
        {
            case 1:
                switch(_Image.Get()->GetComponentType())
                {
                    case meta::SCALAR_FORMAT_UInt8: return IsParameterEnabled(TEXTURE_PARAMETER_LinearSpace)?GL_LUMINANCE8:GL_SLUMINANCE8_EXT;
                    case meta::SCALAR_FORMAT_UInt16: return GL_LUMINANCE16;
                    case meta::SCALAR_FORMAT_Real: return GL_LUMINANCE32F_ARB;
                    default: COFFEE_Error(core::ERROR_CODE_GraphicsSystem, "Texture format unsupported.");
                }                
            case 2:
                switch(_Image.Get()->GetComponentType())
                {
                    case meta::SCALAR_FORMAT_UInt8: return IsParameterEnabled(TEXTURE_PARAMETER_LinearSpace)?GL_LUMINANCE8_ALPHA8:GL_SLUMINANCE8_ALPHA8_EXT;
                    case meta::SCALAR_FORMAT_UInt16: return GL_LUMINANCE16_ALPHA16;
                    case meta::SCALAR_FORMAT_Real: return GL_LUMINANCE_ALPHA32F_ARB;
                    default: COFFEE_Error(core::ERROR_CODE_GraphicsSystem, "Texture format unsupported.");
                }
                
            case 3:
                switch(_Image.Get()->GetComponentType())
                {
                    case meta::SCALAR_FORMAT_UInt8: return IsParameterEnabled(TEXTURE_PARAMETER_LinearSpace)?GL_RGB8:GL_SRGB8_EXT;
                    case meta::SCALAR_FORMAT_UInt16: return GL_RGB16;
                    case meta::SCALAR_FORMAT_Real: return GL_RGB32F_ARB;
                    default: COFFEE_Error(core::ERROR_CODE_GraphicsSystem, "Texture format unsupported.");
                }
                
            case 4:
                switch(_Image.Get()->GetComponentType())
                {
                    case meta::SCALAR_FORMAT_UInt8: return IsParameterEnabled(TEXTURE_PARAMETER_LinearSpace)?GL_RGBA8:GL_SRGB8_ALPHA8_EXT;
                    case meta::SCALAR_FORMAT_UInt16: return GL_RGBA16;
                    case meta::SCALAR_FORMAT_Real: return GL_RGBA32F_ARB;
                    default: COFFEE_Error(core::ERROR_CODE_GraphicsSystem, "Texture format unsupported.");
                }                

            default:
                COFFEE_Error(core::ERROR_CODE_GraphicsSystem, "Texture format unsupported.");
        }
        return 0;
    }

    //--------------------------------------------------------------------------------------------//

    uint32 Texture2D::_GetInternalComponentType() const
    {
        switch(_Image.Get()->GetComponentType())
        {
            case meta::SCALAR_FORMAT_UInt8: return GL_UNSIGNED_BYTE;
            case meta::SCALAR_FORMAT_UInt16: return GL_UNSIGNED_SHORT;
            case meta::SCALAR_FORMAT_Real: return GL_FLOAT;
            default: COFFEE_Error(core::ERROR_CODE_GraphicsSystem, "Texture format unsupported.");
        }
        return 0;
    }

}
}
