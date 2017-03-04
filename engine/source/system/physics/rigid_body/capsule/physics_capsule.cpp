#include "system/physics/rigid_body/capsule/physics_capsule.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(physics::Capsule);
        COFFEE_Ancestor(physics::RigidBodyShape);
        COFFEE_Attribute(real, _Radius, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
        COFFEE_Attribute(real, _Height, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
    COFFEE_EndType();

namespace physics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Capsule::Capsule() :
        _Radius(1.0f),
        _Height(2.0f)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Capsule::~Capsule()
    {
    }

    //-HANDLERS-------------------------------------------------------------------------------//

    void Capsule::OnPropertyModified(const void* property)
    {
        if (property==&_Radius
            || property==&_Height)
        {
            Restart();
        }

        RigidBodyShape::OnPropertyModified(property);
    }
 
    //-OPERATIONS---------------------------------------------------------------------------------//

    NewtonCollision* Capsule::_CreateCollisionShape(NewtonWorld* world)
    {
        return NewtonCreateCapsule(world, _Radius, _Height, _ShapeIndex++, NULL);
    }

}
}
