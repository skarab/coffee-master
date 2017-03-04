#ifndef _COFFEE_GRAPHICS_SHADER_SOURCE_OUTPUT_H_
#define _COFFEE_GRAPHICS_SHADER_SOURCE_OUTPUT_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_enum.h"
#include "kernel/basic/basic.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Geometry shader output type
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(coffee::graphics, SHADER_SOURCE_OUTPUT, "Geometry Output", Single)
        COFFEE_EnumValue(SHADER_SOURCE_OUTPUT, Points, 0)
        COFFEE_EnumValue(SHADER_SOURCE_OUTPUT, LineStrip, 1)
        COFFEE_EnumValue(SHADER_SOURCE_OUTPUT, TriangleStrip, 2)
    COFFEE_EndEnum(COFFEE_API, COFFEE_EXPORT_STATICS, SHADER_SOURCE_OUTPUT)
}
}
#endif
