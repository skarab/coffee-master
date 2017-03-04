#ifndef _COFFEE_UI_LAYOUT_STYLE_H_
#define _COFFEE_UI_LAYOUT_STYLE_H_

#include "coffee_includes.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Layout styles
    ///
    /// Used by the layout system to know which operations are needed to rearrange
    /// windows hierarchy.
    ///
    /// @see coffee::ui::LayoutCanvas, coffee::ui::Layout
    //--------------------------------------------------------------------------------------------//
    enum LAYOUT_STYLE
    {
        LAYOUT_STYLE_Default = 1 << 0,             ///< layout is inactive
        LAYOUT_STYLE_VerticalCanvas = 1 << 1,      ///< children are vertically ordered
        LAYOUT_STYLE_HorizontalCanvas = 1 << 2,    ///< children are horizontally ordered
        LAYOUT_STYLE_StickChildren = 1 << 3,       ///< children are stick by indices depending of canvas type
        LAYOUT_STYLE_HorizontalShrink = 1 << 4,    ///< resize window to horizontal content
        LAYOUT_STYLE_VerticalShrink = 1 << 5,      ///< resize window to vertical content
        LAYOUT_STYLE_HorizontalExpand = 1 << 6,    ///< resize window horizontally to parent client
        LAYOUT_STYLE_VerticalExpand = 1 << 7,      ///< resize window vertically to parent client
        LAYOUT_STYLE_Sort = 1 << 8,                ///< use the ui::Window::Sort method when generating indices

        LAYOUT_STYLE_Shrink = LAYOUT_STYLE_HorizontalShrink | LAYOUT_STYLE_VerticalShrink,
        LAYOUT_STYLE_Expand = LAYOUT_STYLE_HorizontalExpand | LAYOUT_STYLE_VerticalExpand
    };
}
}
#endif
