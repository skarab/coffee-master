#ifndef _COFFEE_UI_WIDGET_BUTTON_STYLE_H_
#define _COFFEE_UI_WIDGET_BUTTON_STYLE_H_

#include "coffee_includes.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Button styles
    //--------------------------------------------------------------------------------------------//
    enum BUTTON_STYLE
    {
        BUTTON_STYLE_Default = 1 << 0,
        BUTTON_STYLE_PushLike = 1 << 1,
        BUTTON_STYLE_HideFrame = 1 << 2
    };
}
}
}
#endif
