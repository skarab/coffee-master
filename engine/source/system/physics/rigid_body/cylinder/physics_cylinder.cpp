#include "system/physics/rigid_body/cylinder/physics_cylinder.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(physics::Cylinder);
        COFFEE_Ancestor(physics::RigidBodyShape);
        COFFEE_Attribute(real, _Radius, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
        COFFEE_Attribute(real, _Height, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
    COFFEE_EndType();

namespace physics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Cylinder::Cylinder() :
        _Radius(1.0f),
        _Height(2.0f)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Cylinder::~Cylinder()
    {
    }

    //-HANDLERS-------------------------------------------------------------------------------//

    void Cylinder::OnPropertyModified(const void* property)
    {
        if (property==&_Radius
            || property==&_Height)
        {
            Restart();
        }

        RigidBodyShape::OnPropertyModified(property);
    }
        
    //-OPERATIONS---------------------------------------------------------------------------------//

    NewtonCollision* Cylinder::_CreateCollisionShape(NewtonWorld* world)
    {
        return NewtonCreateCylinder(world, _Radius, _Height, _ShapeIndex++, NULL);
    }

}
}
