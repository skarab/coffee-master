#ifndef _COFFEE_GRAPHICS_RENDER_STATE_POLYGON_MODE_H_
#define _COFFEE_GRAPHICS_RENDER_STATE_POLYGON_MODE_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_enum.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// @enum RENDER_STATE_POLYGON_MODE
    /// @brief Graphic Render State Polygon Mode
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(coffee::graphics, RENDER_STATE_POLYGON_MODE, "Polygon mode", Single)
    COFFEE_EnumValue(RENDER_STATE_POLYGON_MODE, Point, 0)
    COFFEE_EnumValue(RENDER_STATE_POLYGON_MODE, Line, 1)
    COFFEE_EnumValue(RENDER_STATE_POLYGON_MODE, Fill, 2)
    COFFEE_EndEnum(COFFEE_API, COFFEE_EXPORT_STATICS, RENDER_STATE_POLYGON_MODE)
}
}
#endif
