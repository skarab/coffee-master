#ifndef _EDITOR_DEBUGGER_PASS_TYPE_H_
#define _EDITOR_DEBUGGER_PASS_TYPE_H_

#include "coffee_editor_includes.h"
#include "kernel/meta/meta_enum.h"

namespace coffee_editor
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// @enum DEBUGGER_PASS_TYPE
    /// @brief Debugger pass/layer type
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(coffee_editor::widget, DEBUGGER_PASS_TYPE, "Type", SingleNone)
        COFFEE_EnumValue(DEBUGGER_PASS_TYPE, Depth, 0)
        COFFEE_EnumValue(DEBUGGER_PASS_TYPE, LinearDepth, 1)
        COFFEE_EnumValue(DEBUGGER_PASS_TYPE, Normal, 2)
        COFFEE_EnumValue(DEBUGGER_PASS_TYPE, Color, 3)
        COFFEE_EnumValue(DEBUGGER_PASS_TYPE, Material, 4)
        COFFEE_EnumValue(DEBUGGER_PASS_TYPE, Lightning, 5)
        COFFEE_EnumValue(DEBUGGER_PASS_TYPE, DetectNAN, 6)
    COFFEE_EndEnum(COFFEE_EDITOR_API, COFFEE_EDITOR_EXPORT_STATICS, DEBUGGER_PASS_TYPE)

}
}
#endif
