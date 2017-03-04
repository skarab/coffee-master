#include "system/physics/rigid_body/sphere/physics_sphere.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(physics::Sphere);
        COFFEE_Ancestor(physics::RigidBodyShape);
        COFFEE_Attribute(real, _Radius, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
    COFFEE_EndType();

namespace physics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Sphere::Sphere() :
        _Radius(1.0f)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Sphere::~Sphere()
    {
    }

    //-HANDLERS-------------------------------------------------------------------------------//

    void Sphere::OnPropertyModified(const void* property)
    {
        if (property==&_Radius)
        {
            Restart();
        }

        RigidBodyShape::OnPropertyModified(property);
    }
     
    //-OPERATIONS---------------------------------------------------------------------------------//

    NewtonCollision* Sphere::_CreateCollisionShape(NewtonWorld* world)
    {
        return NewtonCreateSphere(world, _Radius, _Radius, _Radius, _ShapeIndex++, NULL);
    }

}
}
