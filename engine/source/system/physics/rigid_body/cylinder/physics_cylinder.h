#ifndef _COFFEE_PHYSICS_CYLINDER_H_
#define _COFFEE_PHYSICS_CYLINDER_H_

#include "coffee_includes.h"
#include "system/physics/rigid_body/physics_rigid_body_shape.h"

namespace coffee
{
namespace physics
{
    //--------------------------------------------------------------------------------------------//
    /// Cylinder rigid body
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Cylinder : public RigidBodyShape
    {
        COFFEE_Component(Cylinder, "Cylinder", "Physics/");

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Cylinder();
        ~Cylinder();

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

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Cylinder);
}
}
#endif
