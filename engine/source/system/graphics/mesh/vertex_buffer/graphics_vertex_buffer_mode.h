#ifndef _COFFEE_GRAPHICS_VERTEX_BUFFER_MODE_H_
#define _COFFEE_GRAPHICS_VERTEX_BUFFER_MODE_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_enum.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// @enum VERTEX_BUFFER_MODE
    /// @brief Vertex Buffer Mode
    ///
    /// @see coffee::graphics::VertexBuffer
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(coffee::graphics, VERTEX_BUFFER_MODE, "Mode", Multi)
        COFFEE_EnumValue(VERTEX_BUFFER_MODE, Read, 1 << 0)
        COFFEE_EnumValue(VERTEX_BUFFER_MODE, Write, 1 << 1)
    COFFEE_EndEnum(COFFEE_API, COFFEE_EXPORT_STATICS, VERTEX_BUFFER_MODE)
}
}
#endif
