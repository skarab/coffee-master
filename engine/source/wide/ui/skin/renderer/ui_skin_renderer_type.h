#ifndef _COFFEE_UI_SKIN_RENDERER_TYPE_H_
#define _COFFEE_UI_SKIN_RENDERER_TYPE_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_enum.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Renderer types
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(coffee::ui, SKIN_RENDERER_TYPE, "Renderer", Single)
        COFFEE_EnumValue(SKIN_RENDERER_TYPE, Basic, 0)
        COFFEE_EnumValue(SKIN_RENDERER_TYPE, Rounded, 1)
    COFFEE_EndEnum(COFFEE_API, COFFEE_EXPORT_STATICS, SKIN_RENDERER_TYPE)
}
}
#endif
