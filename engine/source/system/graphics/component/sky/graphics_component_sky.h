#ifndef _COFFEE_GRAPHICS_COMPONENT_SKY_H_
#define _COFFEE_GRAPHICS_COMPONENT_SKY_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/component/graphics_component.h"
#include "system/graphics/sky/graphics_sky.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Graphics sky component
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ComponentSky : public Component
    {
        COFFEE_Component(ComponentSky, "Sky", "Graphics/");

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ComponentSky();
        ~ComponentSky();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetSky(Sky sky) { _Sky = sky; }
        const Sky& GetSky() const { return _Sky; }
        Sky& GetSky() { return _Sky; }

        //-HANDLERS-------------------------------------------------------------------------------//

        void OnStart();
        
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Sky _Sky;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ComponentSky);
}
}
#endif
