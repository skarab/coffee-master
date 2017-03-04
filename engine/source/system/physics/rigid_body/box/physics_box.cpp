#include "system/physics/rigid_body/box/physics_box.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(physics::Box);
        COFFEE_Ancestor(physics::RigidBodyShape);
        COFFEE_Attribute(basic::Vector3, _Size, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
    COFFEE_EndType();

namespace physics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Box::Box() :
        _Size(1.0f, 1.0f, 1.0f)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Box::~Box()
    {
    }

    //-HANDLERS-------------------------------------------------------------------------------//

    void Box::OnPropertyModified(const void* property)
    {
        if (property==&_Size)
            Restart();

        RigidBodyShape::OnPropertyModified(property);
    }
        
    //-OPERATIONS---------------------------------------------------------------------------------//

    NewtonCollision* Box::_CreateCollisionShape(NewtonWorld* world)
    {
        return NewtonCreateBox(world, _Size.X, _Size.Y, _Size.Z, _ShapeIndex++, NULL);
    }

}
}
