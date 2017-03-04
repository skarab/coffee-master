#include "system/physics/rigid_body/physics_rigid_body.h"
#include "system/physics/physics_world.h"
#include "system/scene/scene_resource.h"
#include "wide/application/application.h"
#include "wide/plugins/component/plugins_component.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(physics::RigidBody);
        COFFEE_Ancestor(physics::Component);
        COFFEE_Attribute(physics::Material, _Material, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
        COFFEE_Attribute(real, _Mass, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
        COFFEE_Attribute(bool, _ItHasToApplyGravity, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
        COFFEE_Attribute(bool, _ItIsHandlingRotation, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
        COFFEE_Attribute(basic::Vector3, _Offset, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
    COFFEE_EndType();

namespace physics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    RigidBody::RigidBody() :
        _Mass(0.0f),
        _ItHasToApplyGravity(true),
        _ItIsHandlingRotation(true),
        _ItIsUpToDate(true),
        _Body(NULL)
    {
        SetIsStoppedInEditor(true);
    }

    //--------------------------------------------------------------------------------------------//

    RigidBody::~RigidBody()
    {
        for (uint32 i=0 ; i<_Collisions.GetSize() ; ++i)
        {
            uint32 index = _Collisions[i].OtherBody->GetCollisions().FindItem(_Collisions[i]);
            if (index!=NONE)
                _Collisions[i].OtherBody->GetCollisions().Remove(index);
        }
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void RigidBody::SetMass(real mass)
    {
        _Mass = mass;
        _UpdateBasicProperties();
    }

    //--------------------------------------------------------------------------------------------//

    void RigidBody::SetOffset(const basic::Vector3& offset)
    {
        _Offset = offset;
        _ItIsUpToDate = false;
    }
        
    //-QUERIES------------------------------------------------------------------------------------//

    bool RigidBody::IsDynamic() const
    {
        return _Mass!=0.0f;
    }
    
    //-OPERATIONS---------------------------------------------------------------------------------//

    void RigidBody::AddForce(const basic::Vector3& force)
    {
        if (IsRunning())
            _Forces.AddItem(force);
    }

    //--------------------------------------------------------------------------------------------//

    void RigidBody::AddTorque(const basic::Vector3& torque)
    {
        if (IsRunning() && IsHandlingRotation())
            _Torques.AddItem(torque);
    }

    //--------------------------------------------------------------------------------------------//

    void RigidBody::SetVelocity(const basic::Vector3& velocity)
    {
        if (_Body!=NULL)
            NewtonBodySetVelocity(_Body, &velocity.X);
    }

    //--------------------------------------------------------------------------------------------//

    basic::Vector3 RigidBody::GetVelocity() const
    {
        basic::Vector3 velocity;
        if (_Body!=NULL)
            NewtonBodyGetVelocity(_Body, &velocity.X);
        return velocity;
    }

    //--------------------------------------------------------------------------------------------//

    void RigidBody::SetOmega(const basic::Vector3& omega)
    {
        if (_Body!=NULL)
            NewtonBodySetOmega(_Body, &omega.X);
    }

    //--------------------------------------------------------------------------------------------//

    basic::Vector3 RigidBody::GetOmega() const
    {
        basic::Vector3 omega;
        if (_Body!=NULL)
            NewtonBodyGetOmega(_Body, &omega.X);
        return omega;
    }

    //-HANDLERS-------------------------------------------------------------------------------//

    void RigidBody::OnStart()
    {
        if (_Material.GetFilePath().IsEmpty())
            _Material = resource::Manager::Get().Load(storage::Path("/coffee/default.physics_material"));
        
        Scene* scene = GetNode().GetRoot().FindComponent<Scene>();
        if (scene!=NULL)
            _Initialize(*scene);
    }

    //--------------------------------------------------------------------------------------------//

    void RigidBody::OnStop()
    {
        Scene* scene = GetNode().GetRoot().FindComponent<Scene>();
        if (scene!=NULL)
            _Finalize(*scene);
    }

    //--------------------------------------------------------------------------------------------//

    void RigidBody::OnFixedUpdate(const basic::Time& time_step)
    {
        if (!_ItIsUpToDate)
            _ApplyMatrix();

        _ForwardCollisions();
    }

    //--------------------------------------------------------------------------------------------//

    void RigidBody::OnTransform()
    {
        Scene* scene = GetNode().GetRoot().FindComponent<Scene>();
        if (scene!=NULL)
            _UpdateMatrix();
    }

    //--------------------------------------------------------------------------------------------//

    void RigidBody::OnPropertyModified(const void* prop)
    {
        if (prop==&_Mass)
            SetMass(_Mass);
        else if (prop==&_Offset)
            _ItIsUpToDate = false;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//
    
    void RigidBody::_Initialize(Scene& scene)
    {
        COFFEE_Assert(_Body!=NULL, core::ERROR_CODE_IncorrectUsage, "You need to create the body.");

        const basic::Matrix& local_to_world = GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World);
        basic::Matrix matrix;
        matrix.Set(local_to_world.GetTranslation(), local_to_world.GetRotation());
        NewtonBodySetMatrix(_Body, matrix.GetData());
        
        _UpdateBasicProperties();
        NewtonBodySetUserData(_Body, this);
        NewtonBodySetForceAndTorqueCallback(_Body, _ApplyForceAndTorqueCallback);
        NewtonBodySetTransformCallback(_Body, _OnTransformCallback);

        int32 material_id = scene._RegisterMaterial(_Material);
        NewtonBodySetMaterialGroupID(_Body, material_id);
    }

    //--------------------------------------------------------------------------------------------//

    void RigidBody::_Finalize(Scene& scene)
    {
        if (_Body!=NULL)
        {
            NewtonDestroyBody(scene.GetWorld(), _Body);
            _Body = NULL;
        }
    }

    //--------------------------------------------------------------------------------------------//

    void RigidBody::_UpdateBasicProperties()
    {
    }

    //--------------------------------------------------------------------------------------------//

    void RigidBody::_UpdateMatrix()
    {
        if (_Body!=NULL)
        {
            const basic::Matrix& local_to_world = GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World);
            basic::Matrix matrix;
            matrix.Set(local_to_world.GetTranslation()-_Offset, local_to_world.GetRotation());
            NewtonBodySetMatrix(_Body, matrix.GetData());
        }
    }

    //--------------------------------------------------------------------------------------------//

    void RigidBody::_ApplyMatrix()
    {
        if (_Body!=NULL)
        {
            Scene* scene = GetNode().GetRoot().FindComponent<Scene>();
            if (scene!=NULL && GetNode().HasTransform())
            {
                basic::Matrix local_to_world;
                NewtonBodyGetMatrix(_Body, local_to_world.GetData());
                local_to_world *= GetNode().GetTransform().GetMatrix(
                    scene::TRS_World, scene::TRS_Parent);

                GetNode().GetTransform().OnPhysicsTransform(
                    local_to_world.GetTranslation()+_Offset,
                    local_to_world.GetRotation(),
                    IsHandlingRotation());

                _ItIsUpToDate = true;
            }
        }
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void RigidBody::_ForwardCollisions()
    {
        for (int32 i=0 ; i<(int32)_Collisions.GetSize() ; ++i)
        {
            if (_Collisions[i].ItIsLastTime)
            {
                for (uint32 index=0 ; index<GetNode().GetComponentCount() ; ++index)
                {
                    if (GetNode().GetComponent(index).IsRunning()
                        && GetNode().GetComponent(index).HandlePhysics())
                    {
                        GetNode().GetComponent(index).OnCollisionEnd(_Collisions[i]);
                    }
                }
                _Collisions.Remove(i--);
                continue;
            }

            if (_Collisions[i].ItIsFirstTime)
            {
                for (uint32 index=0 ; index<GetNode().GetComponentCount() ; ++index)
                {
                    if (GetNode().GetComponent(index).IsRunning()
                        && GetNode().GetComponent(index).HandlePhysics())
                    {
                        GetNode().GetComponent(index).OnCollisionBegin(_Collisions[i]);
                    }
                }
            }
            else
            {
                for (uint32 index=0 ; index<GetNode().GetComponentCount() ; ++index)
                {
                    if (GetNode().GetComponent(index).IsRunning()
                        && GetNode().GetComponent(index).HandlePhysics())
                    {
                        GetNode().GetComponent(index).OnCollision(_Collisions[i]);
                    }
                }
            }
            
            _Collisions[i].ItIsLastTime = true;
        }
    }

    //-FUNCTIONS----------------------------------------------------------------------------------//

    void RigidBody::_ApplyForceAndTorqueCallback(const NewtonBody* body, dFloat timestep, int threadIndex)
    {
        real factor = timestep/(1.0f/120.0f);

	    RigidBody* rigid_body = static_cast<RigidBody*>(NewtonBodyGetUserData(body));
        
        // newton bug fix: if there is only a torque applied it goes into sleep state!
        // so we make sure it doesn't sleep. (will require check when upgraded to latest newton version)
        //if (rigid_body->_Forces.GetSize()>0 || rigid_body->_Torques.GetSize()>0)
        NewtonBodySetAutoSleep(body, 0);

        if (rigid_body->HasToApplyGravity())
        {
            real ix, iy, iz, mass;
            basic::Vector3 gravity;        
            Scene* scene = rigid_body->GetNode().GetRoot().FindComponent<Scene>();
            if (scene!=NULL)
                gravity = scene->GetGravity();
            NewtonBodyGetMassMatrix(body, &mass, &ix, &iy, &iz);
            gravity *= mass*factor;
            basic::Vector4 gravityForce (gravity.X, gravity.Y, gravity.Z, 1.0f);
	        NewtonBodyAddForce(body, &gravityForce[0]);
        }

        uint32 index;
        for (index=0 ; index<rigid_body->_Forces.GetSize() ; ++index)
        {
            basic::Vector3 force(rigid_body->_Forces[index]*factor);
            NewtonBodyAddForce(body, &force.X);
        }
        for (index=0 ; index<rigid_body->_Torques.GetSize() ; ++index)
        {
            basic::Vector3 torque(rigid_body->_Torques[index]*factor);
            NewtonBodyAddTorque(body, &torque.X);
        }
        rigid_body->_Forces.Clear();
        rigid_body->_Torques.Clear();
    }

    //--------------------------------------------------------------------------------------------//

    void RigidBody::_OnTransformCallback(const NewtonBody* body, const dFloat* matrix, int threadIndex)
    {
	    RigidBody* rigid_body = static_cast<RigidBody*>(NewtonBodyGetUserData(body));
        rigid_body->_ItIsUpToDate = false;
    }

}
}
