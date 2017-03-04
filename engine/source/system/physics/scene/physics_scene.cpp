#include "system/physics/physics_world.h"
#include "system/physics/scene/physics_scene.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(physics::Scene);
        COFFEE_Ancestor(physics::Component);
        COFFEE_Attribute(basic::Vector3, _Gravity, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace physics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Scene::Scene() :
        _Gravity(0.0f, -9.81f, 0.0f),
        _Stamp(0)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Scene::~Scene()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    uint32 _CurrentStamp;
    void Scene::Simulate(const basic::Time& time_step)
    {
        _CurrentStamp = _Stamp;
        // Double update rate for now to 60fps
        NewtonUpdate(_World, time_step.GetSecondCount()/2.0f);
        NewtonUpdate(_World, time_step.GetSecondCount()/2.0f);
        ++_Stamp;
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    void Scene::OnStart()
    {
        _Initialize();
        World::Get().OnRegisterScene(this);
    }
    
    //--------------------------------------------------------------------------------------------//

    void Scene::OnStop()
    {
        World::Get().OnUnregisterScene(this);
        _Finalize();
    }

    //--------------------------------------------------------------------------------------------//

    void Scene::OnUpdate(const basic::Time& time_step)
    {
        _UpdateMaterials();
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    int32 Scene::_RegisterMaterial(Material& material)
    {
        int32 material_id = NONE;
        for (uint32 i=0 ; i<_Materials.GetSize() ; ++i)
        {
            if (material.GetFilePath()==_Materials[i]->GetFilePath())
            {
                material_id = i;
                break;
            }
        }

        if (material_id==NONE)
        {
            Material* mat = COFFEE_New(Material);
            *mat = material;
            _Materials.AddItem(mat);
            resource::Handler<Material>* handler = COFFEE_New(resource::Handler<Material>, mat);
            _MaterialHandlers.AddItem(handler);
            material_id = NewtonMaterialCreateGroupID(_World);
            COFFEE_Assert(material_id==_Materials.GetSize(), core::ERROR_CODE_Unexpected,
                "Material ID is incorrect");
        }
        else
        {
            ++material_id;
        }
        return material_id;
    }

    //-FUNCTIONS----------------------------------------------------------------------------------//

    int32 Scene::_OnCollide(const NewtonMaterial* material, const NewtonBody* body0,
        const NewtonBody* body1, int32 threadIndex)
    {
        RigidBody* rigid_body0 = static_cast<RigidBody*>(NewtonBodyGetUserData(body0));
        RigidBody* rigid_body1 = static_cast<RigidBody*>(NewtonBodyGetUserData(body1));
        
        Collision collision;
        collision.NodeBody = rigid_body0;
        collision.OtherBody = rigid_body1;
        
        uint32 index0 = rigid_body0->GetCollisions().FindItem(collision);
        uint32 index1 = rigid_body1->GetCollisions().FindItem(collision);
        
        // TODO: check why this happens
        if ((index0==NONE)!=(index1==NONE))
            return 0;

        COFFEE_Assert((index0==NONE)==(index1==NONE), core::ERROR_CODE_Unexpected, "Physics collision unexpected error");

        if (index0==NONE)
        {
            collision.Stamp = _CurrentStamp;
            collision.ItIsFirstTime = true;
            collision.ItIsLastTime = false;
            rigid_body0->GetCollisions().AddItem(collision);
            collision.NodeBody = rigid_body1;
            collision.OtherBody = rigid_body0;  
            rigid_body1->GetCollisions().AddItem(collision);
        }
        else if (_CurrentStamp!=rigid_body0->GetCollisions()[index0].Stamp
            || _CurrentStamp!=rigid_body1->GetCollisions()[index1].Stamp)
        {
            rigid_body0->GetCollisions()[index0].Stamp = _CurrentStamp;
            rigid_body0->GetCollisions()[index0].ItIsFirstTime = false;
            rigid_body0->GetCollisions()[index0].ItIsLastTime = false;
            rigid_body1->GetCollisions()[index1].Stamp = _CurrentStamp;
            rigid_body1->GetCollisions()[index1].ItIsFirstTime = false;
            rigid_body1->GetCollisions()[index1].ItIsLastTime = false;
        }
        return 1;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Scene::_Initialize()
    {
        _World = NewtonCreate();

        // use the standard x86 floating point model  
        NewtonSetPlatformArchitecture(_World, 0);

        // set world size
        basic::Vector3 minimum(-900000.0f, -900000.0f, -900000.0f);
        basic::Vector3 maximum(900000.0f, 900000.0f, 900000.0f);
        NewtonSetWorldSize(_World, &minimum.X, &maximum.X);
    
        // fast and accurate enough for games
	    NewtonSetSolverModel(_World, 1);
    }

    //--------------------------------------------------------------------------------------------//

    void Scene::_Finalize()
    {
        NewtonDestroy(_World);
    }

    //--------------------------------------------------------------------------------------------//

    void Scene::_UpdateMaterials()
    {
        for (uint32 j=0 ; j<_MaterialHandlers.GetSize() ; ++j)
        {
            if (_MaterialHandlers[j]->Update()==resource::HANDLER_STATE_EndLoading)
            {
                int32 material_id = j+1;
                Material* mat(_Materials[j]);
                for (uint32 i=0 ; i<_Materials.GetSize() ; ++i)
                {
                    if (_Materials[i]->IsAvailable())
                    {
                        real elasticity = Maximum(mat->GetElasticity(), _Materials[i]->GetElasticity());
                        NewtonMaterialSetDefaultElasticity(_World, material_id, i+1, elasticity);
                        
                        real softness = Maximum(mat->GetSoftness(), _Materials[i]->GetSoftness());
                        NewtonMaterialSetDefaultSoftness(_World, material_id, i+1, softness);
                        
                        real static_friction = Maximum(mat->GetStaticFriction(), _Materials[i]->GetStaticFriction());
                        real kinetic_friction = Maximum(mat->GetKineticFriction(), _Materials[i]->GetKineticFriction());
                        NewtonMaterialSetDefaultFriction(_World, material_id, i+1, static_friction, kinetic_friction);
                        
                        int32 collidable = (!mat->IsCollidable() || !_Materials[i]->IsCollidable())?0:1;
                        NewtonMaterialSetDefaultCollidable(_World, material_id, i+1, collidable);
                        
                        // NewtonMaterialSetSurfaceThickness

                        NewtonMaterialSetCollisionCallback(_World, material_id, i+1, NULL, &_OnCollide, NULL);
                    }
                }
            }
        }
    }

}
}
