#ifndef _COFFEE_PHYSICS_SPHERE_H_
#define _COFFEE_PHYSICS_SPHERE_H_

#include "coffee_includes.h"
#include "system/physics/rigid_body/physics_rigid_body_shape.h"

namespace coffee
{
namespace physics
{
    //--------------------------------------------------------------------------------------------//
    /// Sphere rigid body
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Sphere : public RigidBodyShape
    {
        COFFEE_Component(Sphere, "Sphere", "Physics/");

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Sphere();
        ~Sphere();

        //-HANDLERS-------------------------------------------------------------------------------//

        void OnPropertyModified(const void* property);
                        
    protected:

        //-OPERATIONS-----------------------------------------------------------------------------//

        NewtonCollision* _CreateCollisionShape(NewtonWorld* world);
        
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        real _Radius;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Sphere);
}
}
#endif
