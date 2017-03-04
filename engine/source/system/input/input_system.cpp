#include "system/input/input_system.h"
#include "system/input/input.h"

#define COFFEE_INPUT_SYSTEM_DoubleClickTimeThreshold    0.3f

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(input::System);
        COFFEE_Ancestor(input::Handler);
    COFFEE_EndType();

namespace input
{
    COFFEE_ImplementSingleton(System);
    
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    System::System()
    {
        COFFEE_CreateSingleton(System);
    }

    //--------------------------------------------------------------------------------------------//

    System::~System()
    {
        COFFEE_DestroySingleton(System);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void System::RegisterCommand(Command* command)
    {
        uint32 best_index=NONE;
        uint32 control_count=command->GetControlCount();
        for (uint32 index=0 ; index<_CommandArray.GetSize() ; ++index)
        {
            if (command->GetName()==_CommandArray[index]->GetName())
                COFFEE_Error(core::ERROR_CODE_IncorrectUsage, "Trying to register already existing command");
            
            if (control_count>_CommandArray[index]->GetControlCount())
                best_index=index;
        }

        _CommandArray.AddItem(command, best_index);
    }

    //--------------------------------------------------------------------------------------------//

    void System::UnregisterCommand(Command* command)
    {
        uint32 index = _CommandArray.FindItem(command);
        if (index!=NONE)
        {
            _CommandArray[index] = NULL;
            _CommandArray.Remove(index);
        }
    }

    //--------------------------------------------------------------------------------------------//
    
    void System::Update(const basic::Time& time_step)
    {
        for (uint32 index=0 ; index<_CommandArray.GetSize() ; ++index)
        {
            if (_CommandArray[index]->Update())
                break;
        }
        
        static real time = 0.0f;
        time += time_step.GetSecondCount();
        if (Mouse::Get().IsJustButtonPressed(BUTTON_Left))
        {
            static real last_time = 0.0f;
        
            if (time-last_time<=COFFEE_INPUT_SYSTEM_DoubleClickTimeThreshold)
            {
                SendEvent(EVENT_MouseDoubleClick, (void*)COFFEE_New(EventMouse, _MousePosition));
            }
            else
            {
                SendEvent(EVENT_MouseLeftButtonPressed, (void*)COFFEE_New(EventMouse, _MousePosition));
            }

            last_time = time;
        }
        
        if (Mouse::Get().IsJustButtonReleased(BUTTON_Left))
            SendEvent(EVENT_MouseLeftButtonReleased, (void*)COFFEE_New(EventMouse, _MousePosition));
        
        if (Mouse::Get().IsJustButtonPressed(BUTTON_Right))
            SendEvent(EVENT_MouseRightButtonPressed, (void*)COFFEE_New(EventMouse, _MousePosition));
        
        if (Mouse::Get().IsJustButtonReleased(BUTTON_Right))
            SendEvent(EVENT_MouseRightButtonReleased, (void*)COFFEE_New(EventMouse, _MousePosition));
        
        if (Mouse::Get().IsJustButtonPressed(BUTTON_Middle))
            SendEvent(EVENT_MouseMiddleButtonPressed, (void*)COFFEE_New(EventMouse, _MousePosition));
        
        if (Mouse::Get().IsJustButtonReleased(BUTTON_Middle))
            SendEvent(EVENT_MouseMiddleButtonReleased, (void*)COFFEE_New(EventMouse, _MousePosition));
        
        basic::Vector2i new_position(
            (int32) Mouse::Get().GetPosition().X,
            (int32) Mouse::Get().GetPosition().Y);

        if (new_position!=_MousePosition || Mouse::Get().IsCapturing())
        {
            SendEvent(EVENT_MouseMove, (void*)COFFEE_New(EventMouse, new_position));
            _MousePosition = new_position;
        }

        shell::EventHandler::Update();
    }

    //--------------------------------------------------------------------------------------------//
    
    void System::SendEvent(const EVENT& event, void* parameters)
    {
        SendEvent(event, parameters, *this);
    }

    //--------------------------------------------------------------------------------------------//
    
    void System::SendEvent(const EVENT& event, void* parameters, input::Handler& target)
    {
        shell::EventCode event_code((uint32) event, Handler::GetClassMetaType());
        shell::EventParameters event_parameters(parameters);
        shell::Event shell_event;
        shell_event.Set(event_code, event_parameters,
            shell::EVENT_FLAG_StopWhenHandled|shell::EVENT_FLAG_ForwardToChildren);
        target.SendImmediateEvent(shell_event);
    }
        
}
}
#undef COFFEE_INPUT_SYSTEM_DoubleClickTimeThreshold
