#ifndef _COFFEE_PHYSICS_MESH_H_
#define _COFFEE_PHYSICS_MESH_H_

#include "coffee_includes.h"
#include "system/physics/rigid_body/physics_rigid_body_shape.h"

namespace coffee
{
namespace physics
{
    //--------------------------------------------------------------------------------------------//
    /// Mesh rigid body
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Mesh : public RigidBodyShape
    {
        COFFEE_Component(Mesh, "Mesh", "Physics/");

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Mesh();
        ~Mesh();

        //-HANDLERS-------------------------------------------------------------------------------//

        void OnPropertyModified(const void* property);
            
    protected:

        //-OPERATIONS-----------------------------------------------------------------------------//

        NewtonCollision* _CreateCollisionShape(NewtonWorld* world);
        
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Mesh);
}
}
#endif
