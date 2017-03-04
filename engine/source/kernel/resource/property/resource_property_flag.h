#ifndef _COFFEE_RESOURCE_PROPERTY_FLAG_H_
#define _COFFEE_RESOURCE_PROPERTY_FLAG_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_enum.h"

namespace coffee
{
namespace resource
{
    //--------------------------------------------------------------------------------------------//
    /// Resource property flag
    ///
    /// @see coffee::resource::Property
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(coffee::resource, PROPERTY_FLAG, "Flag", Multi)
        COFFEE_EnumValue(PROPERTY_FLAG, Enabled, 1 << 0)        ///< internal flag for property validity
        COFFEE_EnumValue(PROPERTY_FLAG, Instantiable, 1 << 1)   ///< can be overwritten by instances
        COFFEE_EnumValue(PROPERTY_FLAG, LOD, 1 << 2)            ///< LOD is used on this property
        COFFEE_EnumValue(PROPERTY_FLAG, AutoInstantiate, 1 << 3)///< auto instantiate when loaded
    COFFEE_EndEnum(COFFEE_API, COFFEE_EXPORT_STATICS, PROPERTY_FLAG)
}
}
#endif
