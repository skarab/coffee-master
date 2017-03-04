#ifndef _COFFEE_INPUT_MOUSE_BUTTON_CODES_H_
#define _COFFEE_INPUT_MOUSE_BUTTON_CODES_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_enum.h"

//-CONSTANTS--------------------------------------------------------------------------------------//
#ifndef COFFEE_InputMouseButtonCodeStart
    #define COFFEE_InputMouseButtonCodeStart   0x01
    #define COFFEE_InputMouseButtonCodeEnd     0x09
#endif
//------------------------------------------------------------------------------------------------//

namespace coffee
{
namespace input
{
    //--------------------------------------------------------------------------------------------//
    /// @enum BUTTON
    /// @brief Mouse Button Codes
    ///
    /// Button codes used by the input handler for notifications.
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(coffee::input, BUTTON, "MouseButton", SingleNone)
        COFFEE_EnumValue(BUTTON, Left, 0x01)
        COFFEE_EnumValue(BUTTON, Right, 0x02)
        COFFEE_EnumValue(BUTTON, Middle, 0x04)
        COFFEE_EnumValue(BUTTON, ScrollUp, 0x06)
        COFFEE_EnumValue(BUTTON, ScrollDown, 0x08)
    COFFEE_EndEnum(COFFEE_API, COFFEE_EXPORT_STATICS, BUTTON)
}
}
#endif
