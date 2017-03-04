#include "wide/component/controller/free/component_free_controller.h"
#include "system/input/input.h"
#include "system/scene/scene.h"
#include "system/physics/physics.h"
#include "wide/ui/window/ui_window_manager.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(component::FreeController);
        COFFEE_Ancestor(component::Controller);
        COFFEE_Attribute(real, _MoveSpeed, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
        COFFEE_Attribute(real, _RollSpeed, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
        COFFEE_Attribute(bool, _ItHasToFixVelocity, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
    COFFEE_EndType();

namespace component
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    FreeController::FreeController() :
        _MoveSpeed(2.0f),
        _RollSpeed(1.0f),
        _ItHasToFixVelocity(true),
        _ItHasMovedMouse(false)
    {
    }

    //--------------------------------------------------------------------------------------------//

    FreeController::~FreeController()
    {
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    bool FreeController::OnInputEvent(const input::EVENT& event, const void* parameters)
    {
        if (event==input::EVENT_KeyPressed)
        {
            const input::EventKey* parameter = (const input::EventKey*)parameters;

            if (!parameter->ItIsRepeating)
            {
                if (parameter->Key>=input::KEY_Left && parameter->Key<=input::KEY_Down)
                {
                    _KeyArray[parameter->Key-input::KEY_Left] = true;
                    return true;
                }
            }
        }
        else if (event==input::EVENT_KeyReleased)
        {
            const input::EventKey* parameter = (const input::EventKey*)parameters;

            if (parameter->Key>=input::KEY_Left && parameter->Key<=input::KEY_Down)
            {
                _KeyArray[parameter->Key-input::KEY_Left] = false;
                return true;
            }
        }
        else if (event==input::EVENT_MouseMove && !_ItHasMovedMouse)
        {
            _MouseMovement = input::Mouse::Get().GetMovementVector();
            _ItHasMovedMouse = true;
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    void FreeController::OnStart()
    {
        _Force = 0.0f;

        for (uint32 index=0 ; index<4 ; ++index)
            _KeyArray[index] = false;
    
        if (ui::WindowManager::IsAvailable())
            ui::WindowManager::Get().GetCursor().BeginCapture();
    }
    
    //--------------------------------------------------------------------------------------------//

    void FreeController::OnStop()
    {
        _Force = 0.0f;
        if (GetNode().HasRigidBody() && GetNode().GetRigidBody().IsRunning())
            GetNode().GetRigidBody().SetVelocity(basic::Vector3::Zero);
    
        if (ui::WindowManager::IsAvailable())
            ui::WindowManager::Get().GetCursor().EndCapture();
    }

    //--------------------------------------------------------------------------------------------//

    void FreeController::OnUpdate(const basic::Time& time_step)
    {
        _Force = 0.0f;

        basic::Matrix local_to_world = GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World);
        basic::Vector3 position(local_to_world.GetTranslation());
        basic::Vector3 target(local_to_world.GetTranslation()+basic::Vector3::ZAxis*local_to_world.GetRotation());
        
        if (_ItHasMovedMouse)
        {
            basic::Euler frame_rotation;
            basic::Vector3 frame_rotation_axis;
            basic::Quaternion axis_rotation;
            basic::Quaternion y_rotation;
            basic::Vector3 z_axis;

            z_axis = local_to_world.GetRotation().GetZAxis();      
            z_axis.Normalize();

            frame_rotation.Y = _MouseMovement.X*_RollSpeed/400.0f;
            frame_rotation.X = _MouseMovement.Y*_RollSpeed/400.0f;

            if (z_axis==basic::Vector3::YAxis || z_axis==-basic::Vector3::YAxis)
            {
                z_axis.X = 0.001f;
                z_axis.Z = 0.001f;
                z_axis.Normalize();
            }

            frame_rotation_axis = z_axis.GetCrossProduct(basic::Vector3::YAxis);
            frame_rotation_axis.Normalize();

            axis_rotation.SetFromAxisAndAngle(frame_rotation_axis, frame_rotation.X);
            y_rotation.SetFromAxisAndAngle(basic::Vector3::YAxis, frame_rotation.Y);

            // ToDo: move this elsewhere when needed

            basic::Segment3 segment;
            basic::Plane plane;
            basic::Vector3 temp_z_axis, plane_direction, intersection_point;

            plane_direction = z_axis;
            plane_direction.Y = 0.0f;
            plane_direction.Normalize();

            temp_z_axis = z_axis * axis_rotation;

            segment.Set(target, position+temp_z_axis);
            plane.Set(position, plane_direction);

            if (!plane.FindSegmentIntersection(intersection_point, segment))
                z_axis = temp_z_axis;

            // EndToDo

            z_axis *= y_rotation;
            z_axis.Normalize();
            target = position + z_axis;
            _ItHasMovedMouse = false;
        }

        real distance = _MoveSpeed*time_step.GetSecondCount()*8.0f;

        basic::Vector3 movement;
        if (_KeyArray[input::KEY_Up-input::KEY_Left]) movement += _ComputeMove(distance);
        if (_KeyArray[input::KEY_Down-input::KEY_Left]) movement += _ComputeMove(-distance);
        if (_KeyArray[input::KEY_Right-input::KEY_Left]) movement += _ComputeStrafe(-distance);
        if (_KeyArray[input::KEY_Left-input::KEY_Left]) movement += _ComputeStrafe(distance);
    
        position += movement;
        target += movement;

        local_to_world.SetFromLookAt(position, target, basic::Vector3::YAxis);

        if (GetNode().HasRigidBody() && GetNode().GetRigidBody().IsRunning())
        {
            _Force = (local_to_world.GetTranslation()-GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World).GetTranslation())
                / time_step.GetSecondCount();
            GetNode().GetTransform().SetRotation(local_to_world.GetRotation());
        }
        else
        {
            GetNode().GetTransform().SetPosition(
                local_to_world.GetTranslation(),
                local_to_world.GetRotation(),
                basic::Vector3::One);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void FreeController::OnFixedUpdate(const basic::Time& time_step)
    {
        if (GetNode().HasRigidBody() && GetNode().GetRigidBody().IsRunning())
        {
            if (_ItHasToFixVelocity)
            {
                basic::Vector3 force = ((_Force*40.0f-GetNode().GetRigidBody().GetVelocity()/time_step.GetSecondCount()));
                GetNode().GetRigidBody().AddForce(force);
                _Force = 0.0f;
            }
            else
            {
                GetNode().GetRigidBody().AddForce(_Force);
                _Force = 0.0f;
            }
        }
    }

    //-OPERATIONS-----------------------------------------------------------------------------//

    basic::Vector3 FreeController::_ComputeMove(real distance)
    {
        basic::Vector3 movement;
        movement = GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World).GetRotation().GetZAxis();
        movement *= distance;
        return movement;
    }

    //--------------------------------------------------------------------------------------------//

    basic::Vector3 FreeController::_ComputeStrafe(real distance)
    {
        basic::Vector3 movement;
        movement = (GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World).GetRotation().GetZAxis()).GetCrossProduct(basic::Vector3::YAxis);
        if (!movement.IsZero())
            movement.Normalize();
        movement *= distance;
        return movement;
    }

}
}
