#include "system/physics/rigid_body/chamfer_cylinder/physics_chamfer_cylinder.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(physics::ChamferCylinder);
        COFFEE_Ancestor(physics::RigidBodyShape);
        COFFEE_Attribute(real, _Radius, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
        COFFEE_Attribute(real, _Height, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
    COFFEE_EndType();

namespace physics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ChamferCylinder::ChamferCylinder() :
        _Radius(1.0f),
        _Height(2.0f)
    {
    }

    //--------------------------------------------------------------------------------------------//

    ChamferCylinder::~ChamferCylinder()
    {
    }

    //-HANDLERS-------------------------------------------------------------------------------//

    void ChamferCylinder::OnPropertyModified(const void* property)
    {
        if (property==&_Radius
            || property==&_Height)
        {
            Restart();
        }

        RigidBodyShape::OnPropertyModified(property);
    }
        
    //-OPERATIONS---------------------------------------------------------------------------------//

    NewtonCollision* ChamferCylinder::_CreateCollisionShape(NewtonWorld* world)
    {
        return NewtonCreateChamferCylinder(world, _Radius, _Height, _ShapeIndex++, NULL);
    }

}
}
