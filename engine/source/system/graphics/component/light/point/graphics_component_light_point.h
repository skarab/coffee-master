#ifndef _COFFEE_GRAPHICS_COMPONENT_LIGHT_POINT_H_
#define _COFFEE_GRAPHICS_COMPONENT_LIGHT_POINT_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/component/light/graphics_component_light.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Graphics point light
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ComponentLightPoint : public ComponentLight
    {
        COFFEE_Component(ComponentLightPoint, "Point Light", "Graphics/");

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ComponentLightPoint();
        virtual ~ComponentLightPoint();

        //-ACCESSORS------------------------------------------------------------------------------//

        virtual real GetRadius() const { return _Radius; }

        //-HANDLERS-------------------------------------------------------------------------------//

        virtual void OnStart();

    protected:

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void _UpdateBounding();

    private:

        real _Radius;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ComponentLightPoint);
}
}
#endif
