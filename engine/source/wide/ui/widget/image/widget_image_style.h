#ifndef _COFFEE_UI_WIDGET_IMAGE_STYLE_H_
#define _COFFEE_UI_WIDGET_IMAGE_STYLE_H_

#include "coffee_includes.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Image styles
    //--------------------------------------------------------------------------------------------//
    enum IMAGE_STYLE
    {
        IMAGE_STYLE_Default = 1 << 0,
        IMAGE_STYLE_AutoSize = 1 << 1,
        IMAGE_STYLE_DrawFrame = 1 << 2,
        IMAGE_STYLE_NoBorders = 1 << 3
    };
}
}
}
#endif
