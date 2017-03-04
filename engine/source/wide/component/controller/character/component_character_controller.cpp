#include "wide/component/controller/character/component_character_controller.h"
#include "system/scene/node/scene_node.h"
#include "system/physics/physics.h"
#include "system/input/keyboard/input_keyboard.h"
#include "wide/ui/window/ui_window_manager.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(component::CharacterController);
        COFFEE_Ancestor(component::Controller);
        COFFEE_Attribute(real, _MoveSpeed, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
        COFFEE_Attribute(real, _RollSpeed, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
        COFFEE_Attribute(real, _JumpSpeed, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_Undoable);
    COFFEE_EndType();

namespace component
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    CharacterController::CharacterController() :
        _MoveSpeed(2.0f),
        _RollSpeed(1.0f),
        _JumpSpeed(8.0f),
        _ItHasMovedMouse(false)
    {
    }

    //--------------------------------------------------------------------------------------------//

    CharacterController::~CharacterController()
    {
    }

    //-HANDLERS-------------------------------------------------------------------------------//

    bool CharacterController::OnInputEvent(const input::EVENT& event, const void* parameters)
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
                
                if (parameter->Key==input::KEY_W) { _KeyArray[input::KEY_Up-input::KEY_Left] = true; return true; }
                if (parameter->Key==input::KEY_S) { _KeyArray[input::KEY_Down-input::KEY_Left] = true; return true; }
                if (parameter->Key==input::KEY_A) { _KeyArray[input::KEY_Left-input::KEY_Left] = true; return true; }
                if (parameter->Key==input::KEY_D) { _KeyArray[input::KEY_Right-input::KEY_Left] = true; return true; }
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
            
            if (parameter->Key==input::KEY_W) { _KeyArray[input::KEY_Up-input::KEY_Left] = false; return true; }
            if (parameter->Key==input::KEY_S) { _KeyArray[input::KEY_Down-input::KEY_Left] = false; return true; }
            if (parameter->Key==input::KEY_A) { _KeyArray[input::KEY_Left-input::KEY_Left] = false; return true; }
            if (parameter->Key==input::KEY_D) { _KeyArray[input::KEY_Right-input::KEY_Left] = false; return true; }
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

    void CharacterController::OnStart()
    {
        for (uint32 index=0 ; index<4 ; ++index)
            _KeyArray[index] = false;
    
        if (ui::WindowManager::IsAvailable())
            ui::WindowManager::Get().GetCursor().BeginCapture();
    }
    
    //--------------------------------------------------------------------------------------------//

    void CharacterController::OnStop()
    {
        if (ui::WindowManager::IsAvailable())
            ui::WindowManager::Get().GetCursor().EndCapture();
    }

    //--------------------------------------------------------------------------------------------//

    void CharacterController::OnUpdate(const basic::Time& time_step)
    {
        physics::Character* character = GetNode().FindComponent<physics::Character>();
        if (character!=NULL)
            character->Set(0.0f, 0.0f, 0.0f);

        if (GetNode().HasTransform())
        {
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

            real move(0.0f);
            real strafe(0.0f);

            if (_KeyArray[input::KEY_Up-input::KEY_Left]) move += _MoveSpeed;
            if (_KeyArray[input::KEY_Down-input::KEY_Left]) move -= _MoveSpeed;
            
            if (_KeyArray[input::KEY_Right-input::KEY_Left]) strafe -= _MoveSpeed;
            if (_KeyArray[input::KEY_Left-input::KEY_Left]) strafe += _MoveSpeed;
        
            real mag = move*move+strafe*strafe;
	        if (mag>RealPrecision)
            {
		        real imag = _MoveSpeed/dSqrt(mag);
		        move *= imag;
		        strafe *= imag;
	        }

            if (character!=NULL)
            {
                real jump = 0.0f;
                if (input::Mouse::Get().IsJustButtonPressed(input::BUTTON_Right))
                    jump = _JumpSpeed;

                character->Set(move, strafe, jump);
            }

            local_to_world.SetFromLookAt(position, target, basic::Vector3::YAxis);
            GetNode().GetTransform().SetRotation(local_to_world.GetRotation());
        }
    }

}
}
