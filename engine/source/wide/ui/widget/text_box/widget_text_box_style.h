#ifndef _COFFEE_UI_WIDGET_TEXT_BOX_STYLE_H_
#define _COFFEE_UI_WIDGET_TEXT_BOX_STYLE_H_

#include "coffee_includes.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// TextBox styles
    //--------------------------------------------------------------------------------------------//
    enum TEXT_BOX_STYLE
    {
        TEXT_BOX_STYLE_Default = 0,
        TEXT_BOX_STYLE_DrawLines = 1 << 0,
        TEXT_BOX_STYLE_DrawNumbers = 1 << 1
    };
}
}
}
#endif
