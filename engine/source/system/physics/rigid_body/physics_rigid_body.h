#ifndef _COFFEE_PHYSICS_RIGID_BODY_H_
#define _COFFEE_PHYSICS_RIGID_BODY_H_

#include "coffee_includes.h"
#include "system/physics/physics_component.h"
#include "system/physics/scene/physics_scene.h"
#include "system/physics/material/physics_material.h"
#include "system/physics/physics_collision.h"

namespace coffee
{
namespace physics
{
    //--------------------------------------------------------------------------------------------//
    /// Rigid body component base
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API RigidBody : public Component
    {
        COFFEE_Component(RigidBody, "RigidBody", "Physics/");

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        RigidBody();
        virtual ~RigidBody();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetMass(real mass);
        real GetMass() const { return _Mass; }
        void SetHasToApplyGravity(bool it_has_to_apply_gravity) { _ItHasToApplyGravity = it_has_to_apply_gravity; }
        bool HasToApplyGravity() const { return _ItHasToApplyGravity; }
        void SetIsHandlingRotation(bool it_is_handling_rotation) { _ItIsHandlingRotation = it_is_handling_rotation; }
        bool IsHandlingRotation() const { return _ItIsHandlingRotation; }
        void SetOffset(const basic::Vector3& offset);
        const basic::Vector3& GetOffset() const { return _Offset; }
        const basic::Array<Collision>& GetCollisions() const { return _Collisions; }
        basic::Array<Collision>& GetCollisions() { return _Collisions; }
    
        //-QUERIES--------------------------------------------------------------------------------//

        bool IsDynamic() const;
        
        //-OPERATIONS-----------------------------------------------------------------------------//

        void AddForce(const basic::Vector3& force);
        void AddTorque(const basic::Vector3& torque);
        void SetVelocity(const basic::Vector3& velocity);
        basic::Vector3 GetVelocity() const;
        void SetOmega(const basic::Vector3& omega);
        basic::Vector3 GetOmega() const;

        //-HANDLERS-------------------------------------------------------------------------------//

        void OnStart();
        void OnStop();
        virtual void OnFixedUpdate(const basic::Time& time_step);
        void OnTransform();
        void OnPropertyModified(const void* prop);
        
    protected:

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void _Initialize(Scene& scene);
        virtual void _Finalize(Scene& scene);
        virtual void _UpdateBasicProperties();
        virtual void _UpdateMatrix();
        virtual void _ApplyMatrix();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        bool _ItIsUpToDate;
        NewtonBody* _Body;
    
    protected:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _ForwardCollisions();

        //-FUNCTIONS----------------------------------------------------------------------------------//

        static void _ApplyForceAndTorqueCallback(const NewtonBody* body, real timestep, int threadIndex);
        static void _OnTransformCallback(const NewtonBody* body, const real* matrix, int threadIndex);
      
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        real _Mass;
        bool _ItHasToApplyGravity;
        bool _ItIsHandlingRotation;
        basic::Vector3 _Offset;
        basic::Vector<basic::Vector3> _Forces;
        basic::Vector<basic::Vector3> _Torques;
        Material _Material;
        basic::Array<Collision> _Collisions;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, RigidBody);
}
}
#endif
