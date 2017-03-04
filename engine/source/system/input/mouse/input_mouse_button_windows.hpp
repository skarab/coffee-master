#ifdef COFFEE_OS_WINDOWS

#include "system/input/mouse/input_mouse.h"
#include "wide/application/application.h"

namespace coffee
{
namespace input
{
    //-OPERATIONS---------------------------------------------------------------------------------//

    void MouseButton::Update(const basic::Time& time_step)
    {
        if (_Code<=BUTTON_Middle)
        {
            BUTTON code(_Code);

            if (Mouse::Get().IsSwapped())
            {
                if(_Code==BUTTON_Left)
                {
                    code = BUTTON_Right;
                }
                else if(_Code==BUTTON_Right)
                {
                    code = BUTTON_Left;
                }
            }

            _ItWasPressed = _ItIsPressed;
            _ItIsPressed = Application::IsInstantiated()
                && Application::Get().HasFocus()
                && GetAsyncKeyState(code)!=0;
        }
        else
        {
            int32 scroll = Mouse::Get().GetScrollValue();

            _ItWasPressed = _ItIsPressed;

            _ItIsPressed = Application::IsInstantiated()
                && Application::Get().HasFocus()
                && ((scroll>0 && _Code==BUTTON_ScrollUp)
                || (scroll<0 && _Code==BUTTON_ScrollDown));
        }
    }

}
}
#endif
