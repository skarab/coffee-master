#ifndef _COFFEE_GRAPHICS_COMPONENT_LIGHT_IES_H_
#define _COFFEE_GRAPHICS_COMPONENT_LIGHT_IES_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/component/light/spot/graphics_component_light_spot.h"
#include "system/graphics/texture/graphics_texture.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Graphics IES light
    ///
    /// Unactive for now, need to do proper importer.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ComponentLightIES : public ComponentLightSpot
    {
        COFFEE_Component(ComponentLightIES, "IES Light", "Graphics/");

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ComponentLightIES();
        ~ComponentLightIES();

        //-HANDLERS-------------------------------------------------------------------------------//

        void OnStart();
        
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ComponentLightIES);
}
}
#endif
