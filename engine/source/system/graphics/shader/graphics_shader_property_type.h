#ifndef _COFFEE_GRAPHICS_SHADER_PROPERTY_TYPE_H_
#define _COFFEE_GRAPHICS_SHADER_PROPERTY_TYPE_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_enum.h"
#include "kernel/basic/basic.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// @enum SHADER_PROPERTY_TYPE
    /// @brief Material property type
    /// @see coffee::graphics::Material
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(coffee::graphics, SHADER_PROPERTY_TYPE, "Type", SingleNone)
        COFFEE_EnumValue(SHADER_PROPERTY_TYPE, Texture, 0)
        COFFEE_EnumValue(SHADER_PROPERTY_TYPE, Real, 1)
        COFFEE_EnumValue(SHADER_PROPERTY_TYPE, Boolean, 2)
        COFFEE_EnumValue(SHADER_PROPERTY_TYPE, Integer, 3)
        COFFEE_EnumValue(SHADER_PROPERTY_TYPE, Vector2, 4)
        COFFEE_EnumValue(SHADER_PROPERTY_TYPE, Vector3, 5)
        COFFEE_EnumValue(SHADER_PROPERTY_TYPE, Color, 6)
        COFFEE_EnumValue(SHADER_PROPERTY_TYPE, Matrix4x4, 7)
    COFFEE_EndEnum(COFFEE_API, COFFEE_EXPORT_STATICS, SHADER_PROPERTY_TYPE)

    /// Retrieve meta type name from property type
    COFFEE_API basic::String SHADER_PROPERTY_TYPE_GetTypeName(const SHADER_PROPERTY_TYPE& property_type);
}
}
#endif
