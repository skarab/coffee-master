#include "system/input/command/input_command.h"
#include "system/input/input.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(input::Command);
        COFFEE_Attribute(basic::String, _Name, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_ReadOnly);
        COFFEE_Attribute(basic::String, _Description, meta::MODE_Serializeable | meta::MODE_Editable | meta::MODE_ReadOnly);
        COFFEE_Attribute(input::KEY, _FirstKey, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(input::KEY, _SecondKey, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(input::KEY, _ThirdKey, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(input::BUTTON, _Mouse, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace input
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Command::Command() :
        _FirstKey(KEY_None),
        _SecondKey(KEY_None),
        _ThirdKey(KEY_None),
        _Mouse(BUTTON_None)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Command::Command(const Command& command) :
        _Name(command._Name),
        _Description(command._Description),
        _FirstKey(command._FirstKey),
        _SecondKey(command._SecondKey),
        _ThirdKey(command._ThirdKey),
        _Mouse(command._Mouse)
    {
    }
    
    //--------------------------------------------------------------------------------------------//

    Command::Command(basic::String name, basic::String description, KEY first_key,
        KEY second_key, KEY third_key, BUTTON mouse_button):
        _Name(name),
        _Description(description),
        _FirstKey(first_key),
        _SecondKey(second_key),
        _ThirdKey(third_key),
        _Mouse(mouse_button)
    {
    }
    
    //--------------------------------------------------------------------------------------------//

    Command::~Command()
    {
    }

    //-OPERATORS------------------------------------------------------------------------------//

    Command& Command::operator=(const Command& command)
    {
        _Name = command._Name;
        _Description = command._Description;
        _FirstKey = command._FirstKey;
        _SecondKey = command._SecondKey;
        _ThirdKey = command._ThirdKey;
        _Mouse = command._Mouse;
        return *this;
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Command::SetName(basic::String name)
    {
        _Name = name;
    }
        
    //--------------------------------------------------------------------------------------------//

    const basic::String& Command::GetName() const
    {
        return _Name;
    }

    //--------------------------------------------------------------------------------------------//

    void Command::SetDescription(basic::String description)
    {
        _Description = description;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::String& Command::GetDescription() const
    {
        return _Description;
    }

    //--------------------------------------------------------------------------------------------//

    KEY Command::GetFirstKey() const
    {
        return _FirstKey;
    }

    //--------------------------------------------------------------------------------------------//

    KEY Command::GetSecondKey() const
    {
        return _SecondKey;
    }

    //--------------------------------------------------------------------------------------------//

    KEY Command::GetThirdKey() const
    {
        return _ThirdKey;
    }

    //--------------------------------------------------------------------------------------------//

    BUTTON Command::GetMouse() const
    {
        return _Mouse;
    }

    //-QUERIES--------------------------------------------------------------------------------//

    uint32 Command::GetControlCount() const
    {
        uint32 control_count=0;
        if (_FirstKey!=KEY_None) ++control_count;
        if (_SecondKey!=KEY_None) ++control_count;
        if (_ThirdKey!=KEY_None) ++control_count;
        if (_Mouse!=BUTTON_None) ++control_count;
        return control_count;
    }

    //--------------------------------------------------------------------------------------------//

    basic::String Command::GetControlString() const
    {
        basic::String controls;
        meta::Enum* enum_type = (meta::Enum*)meta::Types::Get().FindType("input::KEY");
            
        if (_FirstKey!=KEY_None)
            controls = enum_type->GetName((uint32)_FirstKey);
        
        if (_SecondKey!=KEY_None)
        {
            if (!controls.IsEmpty()) controls += "+";
            controls += enum_type->GetName((uint32)_SecondKey);
        }

        if (_ThirdKey!=KEY_None)
        {
            if (!controls.IsEmpty()) controls += "+";
            controls += enum_type->GetName((uint32)_ThirdKey);
        }

        if (_Mouse!=BUTTON_None)
        {
            enum_type = (meta::Enum*)meta::Types::Get().FindType("input::BUTTON");
            if (!controls.IsEmpty()) controls += "+Mouse";
            controls += enum_type->GetName((uint32)_Mouse);
        }
        return controls;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//
    
    bool Command::Update()
    {
        if (input::Keyboard::IsAvailable())
        {
            uint32 control_count=GetControlCount();
            uint32 pressed_count=0;
            uint32 just_pressed_count=0;

            if (_FirstKey!=KEY_None)
            {
                if (input::Keyboard::Get().IsButtonPressed(_FirstKey)) ++pressed_count;
                if (input::Keyboard::Get().IsJustButtonPressed(_FirstKey)) ++just_pressed_count;
            }

            if (_SecondKey!=KEY_None)
            {
                if (input::Keyboard::Get().IsButtonPressed(_SecondKey)) ++pressed_count;
                if (input::Keyboard::Get().IsJustButtonPressed(_SecondKey)) ++just_pressed_count;
            }

            if (_ThirdKey!=KEY_None)
            {
                if (input::Keyboard::Get().IsButtonPressed(_ThirdKey)) ++pressed_count;
                if (input::Keyboard::Get().IsJustButtonPressed(_ThirdKey)) ++just_pressed_count;
            }

            if (_Mouse!=BUTTON_None)
            {
                if (input::Mouse::Get().IsButtonPressed(_Mouse)) ++pressed_count;
                if (input::Mouse::Get().IsJustButtonPressed(_Mouse)) ++just_pressed_count;
            }

            if ((pressed_count==control_count) && (just_pressed_count!=0))
            {
                shell::EventCode event_code((uint32)EVENT_Command, Handler::GetClassMetaType());
                shell::EventParameters event_parameters((void*)this);
                shell::Event shell_event;
                shell_event.Set(event_code, event_parameters,
                    shell::EVENT_FLAG_StopWhenHandled|shell::EVENT_FLAG_ForwardToChildren);
                Module::Get().GetSystem().SendImmediateEvent(shell_event);
                return true;
            }
        }
        return false;
    }

}
}
