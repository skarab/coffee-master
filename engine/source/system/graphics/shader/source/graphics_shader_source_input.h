#ifndef _COFFEE_GRAPHICS_SHADER_SOURCE_INPUT_H_
#define _COFFEE_GRAPHICS_SHADER_SOURCE_INPUT_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_enum.h"
#include "kernel/basic/basic.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Geometry shader input type
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(coffee::graphics, SHADER_SOURCE_INPUT, "Geometry Input", Single)
        COFFEE_EnumValue(SHADER_SOURCE_INPUT, Points, 0)
        COFFEE_EnumValue(SHADER_SOURCE_INPUT, Lines, 1)
        COFFEE_EnumValue(SHADER_SOURCE_INPUT, LineStrip, 2)
        COFFEE_EnumValue(SHADER_SOURCE_INPUT, LinesAdjacency, 3)
        COFFEE_EnumValue(SHADER_SOURCE_INPUT, LineStripAdjacency, 4)
        COFFEE_EnumValue(SHADER_SOURCE_INPUT, Triangles, 5)
        COFFEE_EnumValue(SHADER_SOURCE_INPUT, TriangleStrip, 6)
        COFFEE_EnumValue(SHADER_SOURCE_INPUT, TriangleFan, 7)
        COFFEE_EnumValue(SHADER_SOURCE_INPUT, TrianglesAdjacency, 8)
        COFFEE_EnumValue(SHADER_SOURCE_INPUT, TriangleStripAdjacency, 9)
    COFFEE_EndEnum(COFFEE_API, COFFEE_EXPORT_STATICS, SHADER_SOURCE_INPUT)
}
}
#endif
