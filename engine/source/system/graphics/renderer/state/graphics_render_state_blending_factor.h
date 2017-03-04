#ifndef _COFFEE_GRAPHICS_RENDER_STATE_BLENDING_FACTOR_H_
#define _COFFEE_GRAPHICS_RENDER_STATE_BLENDING_FACTOR_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_enum.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// @enum RENDER_STATE_BLENDING_FACTOR
    /// @brief Graphic Render State Blending Factor
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(coffee::graphics, RENDER_STATE_BLENDING_FACTOR, "Blending factor", Single)
    COFFEE_EnumValue(RENDER_STATE_BLENDING_FACTOR, Zero, 0)
    COFFEE_EnumValue(RENDER_STATE_BLENDING_FACTOR, One, 1)
    COFFEE_EnumValue(RENDER_STATE_BLENDING_FACTOR, SourceColor, 2)
    COFFEE_EnumValue(RENDER_STATE_BLENDING_FACTOR, SourceColorInversed, 3)
    COFFEE_EnumValue(RENDER_STATE_BLENDING_FACTOR, SourceAlpha, 4)
    COFFEE_EnumValue(RENDER_STATE_BLENDING_FACTOR, SourceAlphaInversed, 5)
    COFFEE_EnumValue(RENDER_STATE_BLENDING_FACTOR, SourceAlphaSatured, 6)
    COFFEE_EnumValue(RENDER_STATE_BLENDING_FACTOR, DestinationColor, 7)
    COFFEE_EnumValue(RENDER_STATE_BLENDING_FACTOR, DestinationColorInversed, 8)
    COFFEE_EnumValue(RENDER_STATE_BLENDING_FACTOR, DestinationAlpha, 9)
    COFFEE_EnumValue(RENDER_STATE_BLENDING_FACTOR, DestinationAlphaInversed, 10)
    COFFEE_EnumValue(RENDER_STATE_BLENDING_FACTOR, ConstantColor, 11)
    COFFEE_EnumValue(RENDER_STATE_BLENDING_FACTOR, ConstantColorInversed, 12)
    COFFEE_EnumValue(RENDER_STATE_BLENDING_FACTOR, ConstantAlpha, 13)
    COFFEE_EnumValue(RENDER_STATE_BLENDING_FACTOR, ConstantAlphaInversed, 14)
    COFFEE_EndEnum(COFFEE_API, COFFEE_EXPORT_STATICS, RENDER_STATE_BLENDING_FACTOR)
}
}
#endif
