#ifndef _COFFEE_GRAPHICS_RENDER_STATE_SHADE_MODEL_H_
#define _COFFEE_GRAPHICS_RENDER_STATE_SHADE_MODEL_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_enum.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// @enum RENDER_STATE_SHADE_MODEL
    /// @brief Graphic Render State Shade Model
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(coffee::graphics, RENDER_STATE_SHADE_MODEL, "Shade model", Single)
    COFFEE_EnumValue(RENDER_STATE_SHADE_MODEL, Flat, 0)
    COFFEE_EnumValue(RENDER_STATE_SHADE_MODEL, Smooth, 1)
    COFFEE_EndEnum(COFFEE_API, COFFEE_EXPORT_STATICS, RENDER_STATE_SHADE_MODEL)
}
}
#endif
