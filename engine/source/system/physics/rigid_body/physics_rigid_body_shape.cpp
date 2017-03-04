#include "system/physics/rigid_body/physics_rigid_body_shape.h"
#include "system/physics/physics_world.h"
#include "system/scene/scene_resource.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(physics::RigidBodyShape);
        COFFEE_Ancestor(physics::RigidBody);
        COFFEE_Attribute(bool, _ItIsTrigger, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
    COFFEE_EndType();

namespace physics
{
    //-VARIABLES----------------------------------------------------------------------------------//

    uint32 RigidBodyShape::_ShapeIndex = 0;
    
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    RigidBodyShape::RigidBodyShape() :
        _ItIsTrigger(false),
        _Shape(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    RigidBodyShape::~RigidBodyShape()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void RigidBodyShape::SetIsTrigger(bool it_is_trigger)
    {
        _ItIsTrigger = it_is_trigger;
        _UpdateBasicProperties();
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    void RigidBodyShape::OnPropertyModified(const void* prop)
    {
        if (prop==&_ItIsTrigger)
            SetIsTrigger(_ItIsTrigger);
        
        RigidBody::OnPropertyModified(prop);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void RigidBodyShape::_Initialize(Scene& scene)
    {
        NewtonCollision* shape = _CreateCollisionShape(scene.GetWorld());
        if (shape==NULL)
        {
            _Body = NULL;
            return;
        }

        NewtonCollisionSetAsTriggerVolume(shape, _ItIsTrigger);
        _Shape = NewtonCreateConvexHullModifier(scene.GetWorld(), shape, _ShapeIndex++);
        NewtonCollisionSetAsTriggerVolume(_Shape, _ItIsTrigger);
        
        basic::Vector3 origin;
        const basic::Matrix& local_to_world = GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World);
        basic::Matrix matrix;
        matrix.Set(local_to_world.GetTranslation(), local_to_world.GetRotation());

        basic::Matrix modifier = matrix;
        modifier.Invert();
        modifier = local_to_world*modifier;
        NewtonConvexHullModifierSetMatrix(_Shape, modifier.GetData());
            
        NewtonConvexCollisionCalculateInertialMatrix (_Shape, &_Inertia[0], &origin[0]);
        
        _Body = NewtonCreateBody(scene.GetWorld(), _Shape, matrix.GetData());
        NewtonReleaseCollision(scene.GetWorld(), shape);
    
        NewtonBodySetCentreOfMass(_Body, &origin[0]);
        RigidBody::_Initialize(scene);
    }

    //--------------------------------------------------------------------------------------------//

    void RigidBodyShape::_Finalize(Scene& scene)
    {
        if (_Shape!=NULL)
        {
            NewtonReleaseCollision(scene.GetWorld(), _Shape);
            _Shape = NULL;
        }
        
        RigidBody::_Finalize(scene);
    }

    //--------------------------------------------------------------------------------------------//

    void RigidBodyShape::_UpdateBasicProperties()
    {
        RigidBody::_UpdateBasicProperties();
    
        if (_Body!=NULL)
        {
            NewtonBodySetMassMatrix(_Body, GetMass(),
                GetMass()*_Inertia.X, GetMass()*_Inertia.Y, GetMass()*_Inertia.Z);
    
            if (_Shape!=NULL)
                NewtonCollisionSetAsTriggerVolume(_Shape, _ItIsTrigger);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void RigidBodyShape::_UpdateMatrix()
    {
        RigidBody::_UpdateMatrix();

        if (_Body!=NULL && _Shape!=NULL)
        {
            const basic::Matrix& local_to_world = GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World);
            basic::Matrix matrix;
            matrix.Set(local_to_world.GetTranslation(), local_to_world.GetRotation());
            matrix.Invert();
            basic::Matrix modifier = local_to_world;
            modifier *= matrix;
            NewtonConvexHullModifierSetMatrix(_Shape, modifier.GetData());
        }
    }

}
}
