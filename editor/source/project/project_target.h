#ifndef _EDITOR_PROJECT_TARGET_H_
#define _EDITOR_PROJECT_TARGET_H_

#include "coffee_editor_includes.h"
#include "kernel/meta/meta_enum.h"

namespace coffee_editor
{
    //--------------------------------------------------------------------------------------------//
    /// Deployment target
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(coffee_editor, PROJECT_TARGET, "Target", Single)
        COFFEE_EnumValue(PROJECT_TARGET, Package, 0)
        COFFEE_EnumValue(PROJECT_TARGET, Desktop, 1)
        COFFEE_EnumValue(PROJECT_TARGET, Web, 2)
    COFFEE_EndEnum(COFFEE_EDITOR_API, COFFEE_EDITOR_EXPORT_STATICS, PROJECT_TARGET)

}
#endif
