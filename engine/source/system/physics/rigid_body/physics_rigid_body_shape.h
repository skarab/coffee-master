#ifndef _COFFEE_PHYSICS_RIGID_BODY_SHAPE_H_
#define _COFFEE_PHYSICS_RIGID_BODY_SHAPE_H_

#include "coffee_includes.h"
#include "system/physics/rigid_body/physics_rigid_body.h"

namespace coffee
{
namespace physics
{
    //--------------------------------------------------------------------------------------------//
    /// Rigid body shape component base
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API RigidBodyShape : public RigidBody
    {
        COFFEE_Component(RigidBodyShape, "RigidBodyShape", "Physics/");

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        RigidBodyShape();
        virtual ~RigidBodyShape();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetIsTrigger(bool it_is_trigger);
        bool IsTrigger() const { return _ItIsTrigger; }
        
        //-HANDLERS-------------------------------------------------------------------------------//

        void OnPropertyModified(const void* prop);
       
    protected:

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void _Initialize(Scene& scene);
        virtual void _Finalize(Scene& scene);
        virtual void _UpdateBasicProperties();
        virtual void _UpdateMatrix();
        virtual NewtonCollision* _CreateCollisionShape(NewtonWorld* world) { return NULL; }

        //-VARIABLES----------------------------------------------------------------------------------//

        static uint32 _ShapeIndex;
    
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        bool _ItIsTrigger;
        NewtonCollision* _Shape;
        basic::Vector3 _Inertia;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, RigidBodyShape);
}
}
#endif
