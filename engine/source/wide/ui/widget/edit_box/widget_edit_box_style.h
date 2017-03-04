#ifndef _COFFEE_UI_WIDGET_EDIT_BOX_STYLE_H_
#define _COFFEE_UI_WIDGET_EDIT_BOX_STYLE_H_

#include "coffee_includes.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// EditBox Styles
    //--------------------------------------------------------------------------------------------//
    enum EDIT_BOX_STYLE
    {
        EDIT_BOX_STYLE_Default = 1 << 0,
        EDIT_BOX_STYLE_ReadOnly = 1 << 1,
        EDIT_BOX_STYLE_NoBorders = 1 << 2,
        EDIT_BOX_STYLE_FitToContent = 1 << 3,
        EDIT_BOX_STYLE_NoClipBoard = 1 << 4,
        EDIT_BOX_STYLE_NoFrame = 1 << 5
    };
}
}
}
#endif
