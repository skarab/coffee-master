#include "system/physics/rigid_body/character/physics_character.h"
#include "system/scene/node/scene_node.h"
#include "system/physics/scene/physics_scene.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(physics::Character);
        COFFEE_Ancestor(physics::RigidBody);
        COFFEE_Attribute(real, _Height, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
        COFFEE_Attribute(real, _Radius, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
    COFFEE_EndType();

namespace physics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Character::Character() :
        _CharacterBody(NULL),
        _Height(1.8f),
        _Radius(0.7f),
        _Move(0.0f),
        _Strafe(0.0f),
        _Jump(0.0f)
    {
        SetOffset(basic::Vector3(0.0f, _Height*0.9f, 0.0f));
    }

    //--------------------------------------------------------------------------------------------//

    Character::~Character()
    {
    }

    //-ACCESSORS------------------------------------------------------------------------------//

    void Character::Set(real move, real strafe, real jump)
    {
        _Move = move;
        _Strafe = strafe;

        if (_Jump==0.0f)
            _Jump = jump;
    }

    //-HANDLERS-------------------------------------------------------------------------------//

    void Character::OnFixedUpdate(const basic::Time& time_step)
    {
        SetHasToApplyGravity(true);
        SetIsHandlingRotation(false);

        RigidBody::OnFixedUpdate(time_step);

        Scene* scene = GetNode().GetRoot().FindComponent<Scene>();
        if (scene!=NULL && _CharacterBody!=NULL && GetNode().HasTransform())
        {
            dVector gravity(scene->GetGravity().X, scene->GetGravity().Y, scene->GetGravity().Z, 0.0f);

            basic::Euler rotation(
                GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World).GetRotation());

            if (_CharacterBody->IsJumping())
                _Jump = 0.0f;

            _CharacterBody->SetPlayerVelocity(_Move, _Strafe, _Jump,
                rotation.Y.Get(), gravity, time_step.GetSecondCount());
            _Jump = 0.0f;
            _CharacterBody->PostUpdate(time_step.GetSecondCount(), 0);
            _ItIsUpToDate = false;
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Character::OnPropertyModified(const void* prop)
    {
        if (IsRunning() && (prop==&_Height || prop==&_Radius || prop==&_Mass))
        {
            if (prop==&_Height)
                SetOffset(basic::Vector3(0.0f, _Height*0.9f, 0.0f));

           Restart();
        }
        else if (prop==&_ItHasToApplyGravity || prop==&_ItIsHandlingRotation)
        {
            _ItHasToApplyGravity = false;
            _ItIsHandlingRotation = false;
        }
        else
        {
            RigidBody::OnPropertyModified(prop);
        }
    }
     
    //-OPERATIONS----------------------------------------------------------------------------------//

    void Character::_Initialize(physics::Scene& scene)
    {
        dMatrix playerAxis;
        playerAxis[0] = dVector (0.0f, 1.0f, 0.0f, 0.0f);
        playerAxis[1] = dVector (0.0f, 0.0f, 1.0f, 0.0f);
        playerAxis[2] = playerAxis[0] * playerAxis[1];
        playerAxis[3] = dVector (0.0f, 0.0f, 0.0f, 1.0f);

        _CharacterBody = COFFEE_New(CharacterBody);
        _CharacterBody->m_world = scene.GetWorld();
        _CharacterBody->Init(GetMass(), _Radius, _Radius, _Height, _Height*0.33f, playerAxis);
        _CharacterBody->SetRestrainingDistance(0.1f);
        _CharacterBody->_Controller->OnCollide = &scene._OnCollide;
        _Body = _CharacterBody->m_body;
        
        RigidBody::_Initialize(scene);
    }

    //--------------------------------------------------------------------------------------------//

    void Character::_Finalize(physics::Scene& scene)
    {
        RigidBody::_Finalize(scene);
        
        if (_CharacterBody!=NULL)
        {
            COFFEE_Delete(_CharacterBody);
            _CharacterBody = NULL;
            _Body = NULL;
        }
    }

}
}
