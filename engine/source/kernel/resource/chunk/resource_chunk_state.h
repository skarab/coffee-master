#ifndef _COFFEE_RESOURCE_CHUNK_STATE_H_
#define _COFFEE_RESOURCE_CHUNK_STATE_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_enum.h"

namespace coffee
{
namespace resource
{
    //--------------------------------------------------------------------------------------------//
    /// Resource chunk status
    ///
    /// @see coffee::resource::Chunk
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(coffee::resource, CHUNK_STATE, "State", Single)
        COFFEE_EnumValue(CHUNK_STATE, Unused, 0)     ///< the chunk is unused
        COFFEE_EnumValue(CHUNK_STATE, Invalid, 1)    ///< the chunk is invalid
        COFFEE_EnumValue(CHUNK_STATE, Loading, 2)    ///< the chunk is loading
        COFFEE_EnumValue(CHUNK_STATE, Loaded, 3)     ///< the chunk is loaded
    COFFEE_EndEnum(COFFEE_API, COFFEE_EXPORT_STATICS, CHUNK_STATE)
}
}
#endif
