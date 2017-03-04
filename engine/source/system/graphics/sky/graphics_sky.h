#ifndef _COFFEE_GRAPHICS_SKY_H_
#define _COFFEE_GRAPHICS_SKY_H_

#include "coffee_includes.h"
#include "system/graphics/texture/graphics_texture.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Sky based on lightprobes
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Sky : public resource::Object
    {
        COFFEE_Resource(Sky);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Sky();
        ~Sky();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetIntensity(real intensity) { _Intensity.Set(intensity); }
        real GetIntensity() const { return _Intensity.Get(); }
        void SetLightProbe(Texture light_probe) { _LightProbe.Set(light_probe); }
        const Texture& GetLightProbe() const { return _LightProbe.Get(); }
        Texture& GrabLightProbe() { return _LightProbe.Grab(); }
        const basic::Vector< Texture >& GetMipmaps() const { return _Mipmaps.Get(); }
        basic::Vector< Texture >& GrabMipmaps() { return _Mipmaps.Grab(); }
        
        //-QUERIES--------------------------------------------------------------------------------//

        bool IsReady() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Bind(bool it_is_ambient_pass=false);
        void UnBind(bool it_is_ambient_pass=false);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        resource::Property< real > _Intensity;
        resource::Property< Texture > _LightProbe;
        resource::Property< basic::Vector< Texture > > _Mipmaps;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Sky);
}
}
#endif
