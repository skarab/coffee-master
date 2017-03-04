#ifndef _COFFEE_GRAPHICS_COMPONENT_LIGHT_SPOT_H_
#define _COFFEE_GRAPHICS_COMPONENT_LIGHT_SPOT_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/component/light/point/graphics_component_light_point.h"
#include "system/graphics/texture/graphics_texture.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Graphics spot light
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ComponentLightSpot : public ComponentLightPoint
    {
        COFFEE_Component(ComponentLightSpot, "Spot Light", "Graphics/");

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ComponentLightSpot();
        virtual ~ComponentLightSpot();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetApex(real apex);
        real GetApex() const { return _Apex; }
        
        //-HANDLERS-------------------------------------------------------------------------------//

        void OnStart();
        void OnPropertyModified(const void* prop);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        real _Apex;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ComponentLightSpot);
}
}
#endif
