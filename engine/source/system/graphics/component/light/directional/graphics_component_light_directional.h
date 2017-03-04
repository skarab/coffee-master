#ifndef _COFFEE_GRAPHICS_COMPONENT_LIGHT_DIRECTIONAL_H_
#define _COFFEE_GRAPHICS_COMPONENT_LIGHT_DIRECTIONAL_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/component/light/graphics_component_light.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Graphics directional light
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ComponentLightDirectional : public ComponentLight
    {
        COFFEE_Component(ComponentLightDirectional, "Directional Light", "Graphics/");

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ComponentLightDirectional();
        ~ComponentLightDirectional();

        //-HANDLERS-------------------------------------------------------------------------------//

        void OnStart();

    protected:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _UpdateBounding();
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ComponentLightDirectional);
}
}
#endif
