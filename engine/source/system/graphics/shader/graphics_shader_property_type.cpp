#include "system/graphics/shader/graphics_shader_property_type.h"
#undef _COFFEE_GRAPHICS_SHADER_PROPERTY_TYPE_H_
#include "kernel/meta/macros/meta_macros_enum_cpp.h"
#include "system/graphics/shader/graphics_shader_property_type.h"
#include "kernel/meta/macros/meta_macros_enum_h.h"

namespace coffee
{
namespace graphics
{
    //-FUNCTIONS----------------------------------------------------------------------------------//

    basic::String SHADER_PROPERTY_TYPE_GetTypeName(const SHADER_PROPERTY_TYPE& property_type)
    {
        static const char property_type_string_array[SHADER_PROPERTY_TYPE_Count][24] = \
        {
            "graphics::Texture",   \
            "real",                \
            "bool",                \
            "int32",               \
            "basic::Vector2",     \
            "basic::Vector3",     \
            "basic::Color",    \
            "basic::Matrix"       \
        };

        return property_type_string_array[(uint32)property_type];
    }

}
}
