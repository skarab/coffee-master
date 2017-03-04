#ifndef _COFFEE_UI_WIDGET_SCROLL_BAR_STYLE_H_
#define _COFFEE_UI_WIDGET_SCROLL_BAR_STYLE_H_

#include "coffee_includes.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// ScrollBar styles
    //--------------------------------------------------------------------------------------------//
    enum SCROLL_BAR_STYLE
    {
        SCROLL_BAR_STYLE_Vertical = 1 << 0,
        SCROLL_BAR_STYLE_Horizontal = 1 << 1,

        SCROLL_BAR_STYLE_Default = SCROLL_BAR_STYLE_Vertical
    };
}
}
}
#endif
