#ifndef _COFFEE_GRAPHICS_COMPONENT_FLAG_H_
#define _COFFEE_GRAPHICS_COMPONENT_FLAG_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_enum.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Flags defining graphics component behaviors
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(coffee::graphics, COMPONENT_FLAG, "Flags", Multi)
        COFFEE_EnumValue(COMPONENT_FLAG, Pickable, 1<<0)        ///< is pickable by FramePicker
        COFFEE_EnumValue(COMPONENT_FLAG, CastShadows, 1<<1)     ///< is casting & receiving shadows
    COFFEE_EndEnum(COFFEE_API, COFFEE_EXPORT_STATICS, COMPONENT_FLAG)
}
}
#endif
