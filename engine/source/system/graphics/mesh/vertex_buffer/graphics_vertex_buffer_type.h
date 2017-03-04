#ifndef _COFFEE_GRAPHICS_VERTEX_BUFFER_TYPE_H_
#define _COFFEE_GRAPHICS_VERTEX_BUFFER_TYPE_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_enum.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// @enum VERTEX_BUFFER_TYPE
    /// @brief Vertex Buffer Type
    ///
    /// @see coffee::graphics::VertexBuffer
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(coffee::graphics, VERTEX_BUFFER_TYPE, "Type", Single)
        COFFEE_EnumValue(VERTEX_BUFFER_TYPE, Index, 0)
        COFFEE_EnumValue(VERTEX_BUFFER_TYPE, Position, 1)
        COFFEE_EnumValue(VERTEX_BUFFER_TYPE, Color, 2)
        COFFEE_EnumValue(VERTEX_BUFFER_TYPE, Normal, 3)
        COFFEE_EnumValue(VERTEX_BUFFER_TYPE, STangent, 4)
        COFFEE_EnumValue(VERTEX_BUFFER_TYPE, TTangent, 5)
        COFFEE_EnumValue(VERTEX_BUFFER_TYPE, TexCoord, 6)
        COFFEE_EnumValue(VERTEX_BUFFER_TYPE, Adjacency, 7)
    COFFEE_EndEnum(COFFEE_API, COFFEE_EXPORT_STATICS, VERTEX_BUFFER_TYPE)
}
}
#endif
