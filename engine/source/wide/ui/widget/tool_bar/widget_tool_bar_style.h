#ifndef _COFFEE_UI_WIDGET_TOOL_BAR_STYLE_H_
#define _COFFEE_UI_WIDGET_TOOL_BAR_STYLE_H_

#include "coffee_includes.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// ToolBar widget style
    /// @see coffee::ui::widget::ToolBar
    //--------------------------------------------------------------------------------------------//
    enum TOOL_BAR_STYLE
    {
        TOOL_BAR_STYLE_Default = 1 << 0,
        TOOL_BAR_STYLE_DrawFrame = 1 << 1,
        TOOL_BAR_STYLE_DrawButtons = 1 << 2,
        TOOL_BAR_STYLE_Vertical = 1 << 3
    };
}
}
}
#endif
