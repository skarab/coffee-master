#ifndef _COFFEE_GRAPHICS_RENDER_STATE_TEST_FUNCTION_H_
#define _COFFEE_GRAPHICS_RENDER_STATE_TEST_FUNCTION_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_enum.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// @enum RENDER_STATE_TEST_FUNCTION
    /// @brief Graphic Render State TestFunction
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(coffee::graphics, RENDER_STATE_TEST_FUNCTION, "Test function", Single)
    COFFEE_EnumValue(RENDER_STATE_TEST_FUNCTION, Never, 0)
    COFFEE_EnumValue(RENDER_STATE_TEST_FUNCTION, Less, 1)
    COFFEE_EnumValue(RENDER_STATE_TEST_FUNCTION, Equal, 2)
    COFFEE_EnumValue(RENDER_STATE_TEST_FUNCTION, LessOrEqual, 3)
    COFFEE_EnumValue(RENDER_STATE_TEST_FUNCTION, Greater, 4)
    COFFEE_EnumValue(RENDER_STATE_TEST_FUNCTION, NotEqual, 5)
    COFFEE_EnumValue(RENDER_STATE_TEST_FUNCTION, GreaterOrEqual, 6)
    COFFEE_EnumValue(RENDER_STATE_TEST_FUNCTION, Always, 7)
    COFFEE_EndEnum(COFFEE_API, COFFEE_EXPORT_STATICS, RENDER_STATE_TEST_FUNCTION)
}
}
#endif
