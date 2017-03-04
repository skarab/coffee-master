#ifndef _EDITOR_ASSET_MODE_H_
#define _EDITOR_ASSET_MODE_H_

#include "coffee_editor_includes.h"
#include "kernel/meta/meta_enum.h"

namespace coffee_editor
{
namespace asset
{
    //--------------------------------------------------------------------------------------------//
    /// Asset synchronization mode
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(coffee_editor::asset, MODE, "Synchronization Mode", Single)
    COFFEE_EnumValue(MODE, Automatic, 0)
    COFFEE_EnumValue(MODE, Manual, 1)
    COFFEE_EndEnum(COFFEE_EDITOR_API, COFFEE_EDITOR_EXPORT_STATICS, MODE)
}
}
#endif
