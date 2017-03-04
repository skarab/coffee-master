#ifndef _COFFEE_UI_WIDGET_EVENT_H_
#define _COFFEE_UI_WIDGET_EVENT_H_

#include "coffee_includes.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Widget events
    //--------------------------------------------------------------------------------------------//
    enum EVENT
    {
        EVENT_Pressed,              ///< it has been pressed
        EVENT_PressedCanceled,      ///< it has been released outside the widget
        EVENT_Scroll,               ///< scroll up/down event
        EVENT_Select,               ///< item has been selected
        EVENT_Activate,             ///< item has been activated (double clicked)
        EVENT_ContextMenu,          ///< right mouse click on the item
        EVENT_Changed,              ///< item value has changed
        EVENT_Edit,                 ///< just edited the item
        EVENT_MayEdit               ///< query if edit is available on the item
    };
}
}
}
#endif
