#ifndef _COFFEE_PHYSICS_CAPSULE_H_
#define _COFFEE_PHYSICS_CAPSULE_H_

#include "coffee_includes.h"
#include "system/physics/rigid_body/physics_rigid_body_shape.h"

namespace coffee
{
namespace physics
{
    //--------------------------------------------------------------------------------------------//
    /// Capsule rigid body
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Capsule : public RigidBodyShape
    {
        COFFEE_Component(Capsule, "Capsule", "Physics/");

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Capsule();
        ~Capsule();

        //-HANDLERS-------------------------------------------------------------------------------//

        void OnPropertyModified(const void* property);
                    
    protected:

        //-OPERATIONS-----------------------------------------------------------------------------//

        NewtonCollision* _CreateCollisionShape(NewtonWorld* world);
        
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        real _Radius;
        real _Height;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Capsule);
}
}
#endif
