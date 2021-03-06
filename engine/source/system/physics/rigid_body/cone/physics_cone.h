#ifndef _COFFEE_PHYSICS_CONE_H_
#define _COFFEE_PHYSICS_CONE_H_

#include "coffee_includes.h"
#include "system/physics/rigid_body/physics_rigid_body_shape.h"

namespace coffee
{
namespace physics
{
    //--------------------------------------------------------------------------------------------//
    /// Cone rigid body
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Cone : public RigidBodyShape
    {
        COFFEE_Component(Cone, "Cone", "Physics/");

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Cone();
        ~Cone();

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

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Cone);
}
}
#endif
