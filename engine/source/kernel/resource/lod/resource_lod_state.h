#ifndef _COFFEE_RESOURCE_LOD_STATE_H_
#define _COFFEE_RESOURCE_LOD_STATE_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_enum.h"

namespace coffee
{
namespace resource
{
    //--------------------------------------------------------------------------------------------//
    /// Resource lod status
    ///
    /// @see coffee::resource::LOD
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(coffee::resource, LOD_STATE, "State", Single)
        COFFEE_EnumValue(LOD_STATE, Unused, 0)     ///< the lod is unused - not loaded
        COFFEE_EnumValue(LOD_STATE, Invalid, 1)    ///< the lod is invalid
        COFFEE_EnumValue(LOD_STATE, Loaded, 2)     ///< the lod is loaded - ready
    COFFEE_EndEnum(COFFEE_API, COFFEE_EXPORT_STATICS, LOD_STATE)
}
}
#endif
