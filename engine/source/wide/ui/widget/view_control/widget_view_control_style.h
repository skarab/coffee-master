#ifndef _COFFEE_UI_WIDGET_VIEW_CONTROL_STYLE_H_
#define _COFFEE_UI_WIDGET_VIEW_CONTROL_STYLE_H_

#include "coffee_includes.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// ViewControl styles
    //--------------------------------------------------------------------------------------------//
    enum VIEW_CONTROL_STYLE
    {
        VIEW_CONTROL_STYLE_Default = 1 << 0,                ///< no custom styles
        VIEW_CONTROL_STYLE_AlwaysShowHScrollBar = 1 << 1,   ///< always show horizontal scroll bar
        VIEW_CONTROL_STYLE_AlwaysShowVScrollBar = 1 << 2,   ///< always show vertical scroll bar
        VIEW_CONTROL_STYLE_SortAscending = 1 << 3,          ///< sort items by ascending name
        VIEW_CONTROL_STYLE_SortDescending = 1 << 4,         ///< sort items by descending name
        VIEW_CONTROL_STYLE_ShowCheckBoxes = 1 << 5,         ///< show checkboxes next to each item
        VIEW_CONTROL_STYLE_FollowCursorOnAdd = 1 << 6,      ///< automatically scroll down when adding items

        VIEW_CONTROL_STYLE_AlwaysShowScrollBars = VIEW_CONTROL_STYLE_AlwaysShowHScrollBar
            | VIEW_CONTROL_STYLE_AlwaysShowVScrollBar
    };
}
}
}
#endif
