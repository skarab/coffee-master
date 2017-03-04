#ifndef _COFFEE_PHYSICS_BOX_H_
#define _COFFEE_PHYSICS_BOX_H_

#include "coffee_includes.h"
#include "system/physics/rigid_body/physics_rigid_body_shape.h"

namespace coffee
{
namespace physics
{
    //--------------------------------------------------------------------------------------------//
    /// Box rigid body
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Box : public RigidBodyShape
    {
        COFFEE_Component(Box, "Box", "Physics/");

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Box();
        ~Box();

        //-HANDLERS-------------------------------------------------------------------------------//

        void OnPropertyModified(const void* property);
        
    protected:

        //-OPERATIONS-----------------------------------------------------------------------------//

        NewtonCollision* _CreateCollisionShape(NewtonWorld* world);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Vector3 _Size;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Box);
}
}
#endif