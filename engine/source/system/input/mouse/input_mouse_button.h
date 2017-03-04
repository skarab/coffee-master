#ifndef _COFFEE_INPUT_MOUSE_BUTTON_H_
#define _COFFEE_INPUT_MOUSE_BUTTON_H_

#include "coffee_includes.h"
#include "system/input/input_device_button.h"
#include "system/input/mouse/input_mouse_button_code.h"

namespace coffee
{
namespace input
{
    //--------------------------------------------------------------------------------------------//
    /// Mouse button
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API MouseButton : public DeviceButton
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        MouseButton(const BUTTON& code);
        ~MouseButton();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Update(const basic::Time& time_step);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        BUTTON _Code;
    };
}
}
#endif
