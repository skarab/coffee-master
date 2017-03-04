#ifndef _COFFEE_PHYSICS_COMPONENT_H_
#define _COFFEE_PHYSICS_COMPONENT_H_

#include "coffee_includes.h"
#include "system/scene/component/scene_component.h"

namespace coffee
{
namespace physics
{
    //--------------------------------------------------------------------------------------------//
    /// Physics component class
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Component : public scene::Component
    {
        COFFEE_Type(Component);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Component();
        virtual ~Component();

        //-HANDLERS-------------------------------------------------------------------------------//

        virtual void OnTransform() {}
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Component);
}
}
#endif
