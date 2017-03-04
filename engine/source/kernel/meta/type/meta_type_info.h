#ifndef _COFFEE_META_TYPE_INFO_H_
#define _COFFEE_META_TYPE_INFO_H_

#include "coffee_includes.h"

namespace coffee
{
namespace meta
{
    //--------------------------------------------------------------------------------------------//
    /// Meta type information
    ///
    /// Used to know if an object comes from class or scalar type.
    //--------------------------------------------------------------------------------------------//
    enum TYPE_INFO
    {
        TYPE_INFO_Scalar,
        TYPE_INFO_Class,
        TYPE_INFO_Count,
        TYPE_INFO_None = -1
    };
}
}
#endif
