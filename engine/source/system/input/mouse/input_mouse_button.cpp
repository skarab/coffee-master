#include "system/input/mouse/input_mouse_button.h"
#include "system/input/mouse/input_mouse_button_windows.hpp"
#include "system/input/mouse/input_mouse_button_unix.hpp"

namespace coffee
{
namespace input
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    MouseButton::MouseButton(const BUTTON& code) :
        _Code(code)
    {
    }

    //--------------------------------------------------------------------------------------------//

    MouseButton::~MouseButton()
    {
    }

}
}
