#ifndef _COFFEE_UI_WIDGET_DIALOG_STYLE_H_
#define _COFFEE_UI_WIDGET_DIALOG_STYLE_H_

#include "coffee_includes.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Dialog styles
    //--------------------------------------------------------------------------------------------//
    enum DIALOG_STYLE
    {
        DIALOG_STYLE_None = 0,
        DIALOG_STYLE_CloseButton = 1 << 0
    };
}
}
}
#endif
