#ifndef _COFFEE_GRAPHICS_TEXTURE_PARAMETER_H_
#define _COFFEE_GRAPHICS_TEXTURE_PARAMETER_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_enum.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Texture parameters
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(coffee::graphics, TEXTURE_PARAMETER, "Texture parameter", Multi)
        COFFEE_EnumValue(TEXTURE_PARAMETER, MipMapping, 1 << 0)
        COFFEE_EnumValue(TEXTURE_PARAMETER, BilinearFiltering, 1 << 1)
        COFFEE_EnumValue(TEXTURE_PARAMETER, AnisotropicFiltering, 1 << 2)
        COFFEE_EnumValue(TEXTURE_PARAMETER, Modulate, 1 << 3)
        COFFEE_EnumValue(TEXTURE_PARAMETER, Clamp, 1 << 4)
        COFFEE_EnumValue(TEXTURE_PARAMETER, LinearSpace, 1 << 5)
    COFFEE_EndEnum(COFFEE_API, COFFEE_EXPORT_STATICS, TEXTURE_PARAMETER)
}
}
#endif
