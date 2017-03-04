#ifndef _COFFEE_UI_SKIN_ICON_H_
#define _COFFEE_UI_SKIN_ICON_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_enum.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Default skin icons
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(coffee::ui, SKIN_ICON, "Icon", Single)
        COFFEE_EnumValue(SKIN_ICON, CursorDefault, 0)
        COFFEE_EnumValue(SKIN_ICON, CursorMove, 1)
        COFFEE_EnumValue(SKIN_ICON, CursorResizeUp, 2)
        COFFEE_EnumValue(SKIN_ICON, CursorResizeDown, 3)
        COFFEE_EnumValue(SKIN_ICON, CursorResizeLeft, 4)
        COFFEE_EnumValue(SKIN_ICON, CursorResizeRight, 5)
        COFFEE_EnumValue(SKIN_ICON, CursorResizeUpLeft, 6)
        COFFEE_EnumValue(SKIN_ICON, CursorResizeUpRight, 7)
        COFFEE_EnumValue(SKIN_ICON, CursorResizeDownLeft, 8)
        COFFEE_EnumValue(SKIN_ICON, CursorResizeDownRight, 9)
        COFFEE_EnumValue(SKIN_ICON, CursorEditText, 10)
        COFFEE_EnumValue(SKIN_ICON, Close, 11)
        COFFEE_EnumValue(SKIN_ICON, New, 12)
        COFFEE_EnumValue(SKIN_ICON, Open, 13)
        COFFEE_EnumValue(SKIN_ICON, Save, 14)
        COFFEE_EnumValue(SKIN_ICON, Return, 15)
        COFFEE_EnumValue(SKIN_ICON, Left, 16)
        COFFEE_EnumValue(SKIN_ICON, Right, 17)
        COFFEE_EnumValue(SKIN_ICON, Down, 18)
        COFFEE_EnumValue(SKIN_ICON, Up, 19)
        COFFEE_EnumValue(SKIN_ICON, Combo, 20)
        COFFEE_EnumValue(SKIN_ICON, Separator, 21)
        COFFEE_EnumValue(SKIN_ICON, GroupOn, 22)
        COFFEE_EnumValue(SKIN_ICON, GroupOff, 23)
        COFFEE_EnumValue(SKIN_ICON, On, 24)
        COFFEE_EnumValue(SKIN_ICON, Off, 25)
        COFFEE_EnumValue(SKIN_ICON, Undo, 26)
        COFFEE_EnumValue(SKIN_ICON, Redo, 27)
        COFFEE_EnumValue(SKIN_ICON, Empty, 28)
        COFFEE_EnumValue(SKIN_ICON, DisplayLines, 29)
        COFFEE_EnumValue(SKIN_ICON, PlugOn, 30)
        COFFEE_EnumValue(SKIN_ICON, PlugOff, 31)
        COFFEE_EnumValue(SKIN_ICON, PlugFailed, 32)
        COFFEE_EnumValue(SKIN_ICON, Scroll, 33)
        COFFEE_EnumValue(SKIN_ICON, CursorDrop, 34)
        COFFEE_EnumValue(SKIN_ICON, CursorNoDrop, 35)        
    COFFEE_EndEnum(COFFEE_API, COFFEE_EXPORT_STATICS, SKIN_ICON)
}
}
#endif
