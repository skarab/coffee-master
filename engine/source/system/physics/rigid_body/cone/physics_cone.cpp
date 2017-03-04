#include "system/physics/rigid_body/cone/physics_cone.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(physics::Cone);
        COFFEE_Ancestor(physics::RigidBodyShape);
        COFFEE_Attribute(real, _Radius, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
        COFFEE_Attribute(real, _Height, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
    COFFEE_EndType();

namespace physics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Cone::Cone() :
        _Radius(1.0f),
        _Height(1.0f)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Cone::~Cone()
    {
    }

    //-HANDLERS-------------------------------------------------------------------------------//

    void Cone::OnPropertyModified(const void* property)
    {
        if (property==&_Radius
            || property==&_Height)
        {
            Restart();
        }

        RigidBodyShape::OnPropertyModified(property);
    }
       
    //-OPERATIONS---------------------------------------------------------------------------------//

    NewtonCollision* Cone::_CreateCollisionShape(NewtonWorld* world)
    {
        return NewtonCreateCone(world, _Radius, _Height, _ShapeIndex++, NULL);
    }

}
}
