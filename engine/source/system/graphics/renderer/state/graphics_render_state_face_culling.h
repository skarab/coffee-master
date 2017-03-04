#ifndef _COFFEE_GRAPHICS_RENDER_STATE_FACE_CULLING_H_
#define _COFFEE_GRAPHICS_RENDER_STATE_FACE_CULLING_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_enum.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// @enum RENDER_STATE_FACE_CULLING
    /// @brief Graphic Render State Face Culling
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(coffee::graphics, RENDER_STATE_FACE_CULLING, "Face culling", SingleNone)
    COFFEE_EnumValue(RENDER_STATE_FACE_CULLING, Back, 0)
    COFFEE_EnumValue(RENDER_STATE_FACE_CULLING, Front, 1)
    COFFEE_EndEnum(COFFEE_API, COFFEE_EXPORT_STATICS, RENDER_STATE_FACE_CULLING)
}
}
#endif
