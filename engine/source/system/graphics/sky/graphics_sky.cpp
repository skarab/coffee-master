#include "system/graphics/sky/graphics_sky.h"
#include "system/graphics/device/graphics_device.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginResource(graphics, Sky, "Sky", "sky", 0);
        COFFEE_Ancestor(resource::Object);
        COFFEE_ResourceProperty(real, _Intensity, meta::MODE_Serializeable | meta::MODE_Editable, resource::PROPERTY_FLAG_Instantiable);
        COFFEE_ResourceProperty(graphics::Texture, _LightProbe, meta::MODE_Serializeable | meta::MODE_Editable, 0);
        COFFEE_ResourceProperty(< graphics::Texture >, _Mipmaps, meta::MODE_Serializeable | meta::MODE_Editable, 0);
    COFFEE_EndResource();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Sky::Sky() :
        _Intensity(10000.0f)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Sky::~Sky()
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool Sky::IsReady() const
    {
        if (!IsAvailable() || !GetLightProbe().IsAvailable())
            return false;
        for (uint32 i=0 ; i<GetMipmaps().GetSize() ; ++i)
        {
            if (!GetMipmaps()[i].IsAvailable())
                return false;
        }
        return true;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Sky::Bind(bool it_is_ambient_pass)
    {
        COFFEE_GRAPHICS_Debug();

        if (it_is_ambient_pass)
        {
            for (uint32 i=0 ; i<GetMipmaps().GetSize() ; ++i)
                GrabMipmaps()[i].Bind(i+3);
        }
        else
        {
            GrabLightProbe().Bind(0);
        }

        COFFEE_GRAPHICS_Debug();
    }

    //--------------------------------------------------------------------------------------------//

    void Sky::UnBind(bool it_is_ambient_pass)
    {
        if (it_is_ambient_pass)
        {
            for (uint32 i=0 ; i<GetMipmaps().GetSize() ; ++i)
                GrabMipmaps()[i].UnBind(i+3);
        }
        else
        {
            GrabLightProbe().UnBind(0);
        }
    }

}
}
