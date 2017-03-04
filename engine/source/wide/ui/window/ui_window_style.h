#ifndef _COFFEE_UI_WINDOW_STYLE_H_
#define _COFFEE_UI_WINDOW_STYLE_H_

#include "coffee_includes.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Window styles defining visual styles and behaviors
    //--------------------------------------------------------------------------------------------//
    enum WINDOW_STYLE
    {
        WINDOW_STYLE_None = 0,
        WINDOW_STYLE_Draggable = 1 << 0,
        WINDOW_STYLE_Focusable = 1 << 1,
        WINDOW_STYLE_Activable = 1 << 2,
        WINDOW_STYLE_ResizeableTop = 1 << 3,
        WINDOW_STYLE_ResizeableBottom = 1 << 4,
        WINDOW_STYLE_ResizeableLeft = 1 << 5,
        WINDOW_STYLE_ResizeableRight = 1 << 6,
        WINDOW_STYLE_DrawFrame = 1 << 7,
        WINDOW_STYLE_DrawClientRaised = 1 << 8,
        WINDOW_STYLE_DrawClientSunken = 1 << 9,
        WINDOW_STYLE_NoParentClientClip = 1 << 10,  ///< the parent doesnt clip this window using client area but
                                                    /// it uses whole window area instead when hittesting
                                                    /// (only works for parent->child hittesting for now)
        WINDOW_STYLE_NoParentClip = 1 << 11,        ///< the parent isnt used to clip this window when hittesting
        WINDOW_STYLE_TopMost = 1 << 12,
        WINDOW_STYLE_BottomMost = 1 << 13,
        WINDOW_STYLE_ForwardsInput = 1 << 14,       ///< Cursor doesnt stop input events
        WINDOW_STYLE_All = 0xFFFFFFFF,

        WINDOW_STYLE_Resizeable = WINDOW_STYLE_ResizeableTop
            | WINDOW_STYLE_ResizeableBottom
            | WINDOW_STYLE_ResizeableLeft
            | WINDOW_STYLE_ResizeableRight
    };
}
}
#endif
