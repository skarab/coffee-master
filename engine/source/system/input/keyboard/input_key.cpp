#include "system/input/keyboard/input_key.h"
#include "system/input/input.h"
#include "system/input/keyboard/input_key_windows.hpp"
#include "system/input/keyboard/input_key_unix.hpp"

namespace coffee
{
namespace input
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Key::Key(const KEY& code) :
        _Code(code)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Key::~Key()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Key::Update(const basic::Time& time_step)
    {
        _PlatformUpdate();

        DeviceButton::Update(time_step);

        if( IsRepeatPressed())
        {
            Module::Get().GetSystem().SendEvent(EVENT_KeyPressed,
                (void*)COFFEE_New(EventKey, _Code, IsRepeating()));
        }
        else if (IsJustReleased())
        {
            Module::Get().GetSystem().SendEvent(EVENT_KeyReleased,
                (void*)COFFEE_New(EventKey, _Code, IsRepeating()));
        }
    }

}
}
