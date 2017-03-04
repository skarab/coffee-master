#include "system/physics/physics_component.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(physics::Component);
        COFFEE_Ancestor(scene::Component);
    COFFEE_EndType();

namespace physics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Component::Component()
    {
    }

    //--------------------------------------------------------------------------------------------//

    Component::~Component()
    {
    }

}
}
