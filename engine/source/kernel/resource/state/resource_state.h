#ifndef _COFFEE_RESOURCE_STATE_H_
#define _COFFEE_RESOURCE_STATE_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_enum.h"

namespace coffee
{
namespace resource
{
    //--------------------------------------------------------------------------------------------//
    /// Resource states
    ///
    /// @see coffee::resource::Object
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(coffee::resource, STATE, "State", Single)
        COFFEE_EnumValue(STATE, Unused, 0)         ///< the resource is unused
        COFFEE_EnumValue(STATE, Invalid, 1)        ///< the resource is not valid
        COFFEE_EnumValue(STATE, Streamed, 3)       ///< the resource needs preparing
        COFFEE_EnumValue(STATE, Available, 5)      ///< the resource is ready
        COFFEE_EnumValue(STATE, Instantiated, 6)   ///< the resource has been instantiated
    COFFEE_EndEnum(COFFEE_API, COFFEE_EXPORT_STATICS, STATE)
}
}
#endif
