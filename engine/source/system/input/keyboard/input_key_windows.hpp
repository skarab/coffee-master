#ifdef COFFEE_OS_WINDOWS

#include "wide/application/application.h"

namespace coffee
{
namespace input
{
    //-OPERATIONS---------------------------------------------------------------------------------//

    void Key::_PlatformUpdate()
    {
        _ItWasPressed = _ItIsPressed;
        _ItIsPressed = Application::IsInstantiated()
            && Application::Get().HasFocus()
            && GetAsyncKeyState(_Code)&0x8000;
    }

}
}
#endif
