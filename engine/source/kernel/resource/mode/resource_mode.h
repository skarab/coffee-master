#ifndef _COFFEE_RESOURCE_MODE_H_
#define _COFFEE_RESOURCE_MODE_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_enum.h"

namespace coffee
{
namespace resource
{
    //--------------------------------------------------------------------------------------------//
    /// Resource modes
    ///
    /// @see coffee::resource::Object
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(coffee::resource, MODE, "Mode", Multi)
        COFFEE_EnumValue(MODE, LevelOfDetail, 1 << 0)       ///< the resource uses the LOD system
        COFFEE_EnumValue(MODE, ImmediateLoad, 1 << 1)       ///< stall all when loading, useful when all assumes its already loaded (ie GUI skin)
    COFFEE_EndEnum(COFFEE_API, COFFEE_EXPORT_STATICS, MODE)
}
}
#endif
