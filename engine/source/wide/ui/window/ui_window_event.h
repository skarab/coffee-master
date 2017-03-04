#ifndef _COFFEE_UI_WINDOW_EVENT_H_
#define _COFFEE_UI_WINDOW_EVENT_H_

#include "coffee_includes.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Window events
    //--------------------------------------------------------------------------------------------//
    enum WINDOW_EVENT
    {
        WINDOW_EVENT_Show,
        WINDOW_EVENT_Move,
        WINDOW_EVENT_Resize,
        WINDOW_EVENT_Activate,
        WINDOW_EVENT_Deactivate,
        WINDOW_EVENT_SetFocus,
        WINDOW_EVENT_KillFocus,
        WINDOW_EVENT_BeginCursorOver,
        WINDOW_EVENT_EndCursorOver,
        WINDOW_EVENT_ScrollUp,
        WINDOW_EVENT_ScrollDown,
        WINDOW_EVENT_QueryDrag,
        WINDOW_EVENT_QueryDrop,
        WINDOW_EVENT_Drop
    };
}
}
#endif
