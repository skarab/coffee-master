#include "system/physics/rigid_body/mesh/physics_mesh.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(physics::Mesh);
        COFFEE_Ancestor(physics::RigidBodyShape);
    COFFEE_EndType();

namespace physics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Mesh::Mesh()
    {
    }

    //--------------------------------------------------------------------------------------------//

    Mesh::~Mesh()
    {
    }

    //-HANDLERS-------------------------------------------------------------------------------//

    void Mesh::OnPropertyModified(const void* property)
    {
        /*
        if (property==&_Radius
            || property==&_Height)
        {
            Stop();
            Start();
        }*/

        RigidBodyShape::OnPropertyModified(property);
    }
       
    //-OPERATIONS---------------------------------------------------------------------------------//

    NewtonCollision* Mesh::_CreateCollisionShape(NewtonWorld* world)
    {
        return NULL; //NewtonCreateCone(world, _Radius, _Height, _ShapeIndex++, NULL);
    }

}
}
