#ifndef _COFFEE_UI_WINDOW_STATE_H_
#define _COFFEE_UI_WINDOW_STATE_H_

#include "coffee_includes.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Window states
    //--------------------------------------------------------------------------------------------//
    enum WINDOW_STATE
    {
        WINDOW_STATE_None = 0,
        WINDOW_STATE_Visible = 1 << 0,
        WINDOW_STATE_MouseLeftButtonPressed = 1 << 1,
        WINDOW_STATE_MouseRightButtonPressed = 1 << 2,
        WINDOW_STATE_All = 0xFFFF
    };
}
}
#endif
