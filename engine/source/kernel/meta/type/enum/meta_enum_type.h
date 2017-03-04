#ifndef _COFFEE_META_ENUM_TYPE_H_
#define _COFFEE_META_ENUM_TYPE_H_

#include "coffee_includes.h"

namespace coffee
{
namespace meta
{
    //--------------------------------------------------------------------------------------------//
    /// Enum type used by GUI properties
    //--------------------------------------------------------------------------------------------//
    enum ENUM_TYPE
    {
        ENUM_TYPE_Single,       ///< only one enum value can be selected
        ENUM_TYPE_SingleNone,   ///< only one enum value can be selected, and NONE
        ENUM_TYPE_Multi         ///< multiple value can be selected (bitfield like)
    };
}
}
#endif
