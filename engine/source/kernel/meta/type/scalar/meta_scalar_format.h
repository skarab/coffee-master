#ifndef _COFFEE_META_SCALAR_FORMAT_H_
#define _COFFEE_META_SCALAR_FORMAT_H_

#include "coffee_includes.h"

namespace coffee
{
namespace basic
{
    class String;
}

namespace meta
{
    class Type;

    //--------------------------------------------------------------------------------------------//
    /// Serializable scalar formats
    //--------------------------------------------------------------------------------------------//
    enum SCALAR_FORMAT
    {
        SCALAR_FORMAT_Bool,
        SCALAR_FORMAT_Int8,
        SCALAR_FORMAT_UInt8,
        SCALAR_FORMAT_Int16,
        SCALAR_FORMAT_UInt16,
        SCALAR_FORMAT_Int32,
        SCALAR_FORMAT_UInt32,
        SCALAR_FORMAT_Real,
        SCALAR_FORMAT_Enum,
        SCALAR_FORMAT_Count,
        SCALAR_FORMAT_None = -1
    };

    /// Used internally to register scalar types.
    void SCALAR_FORMAT_Register();

    /// Get scalar format from a type name
    COFFEE_API SCALAR_FORMAT SCALAR_FORMAT_GetFormat(const basic::String& type_name);

    /// Get size of a scalar format
    COFFEE_API ulong SCALAR_FORMAT_GetFormatSize(SCALAR_FORMAT format);

    /// Get name of a scalar format
    COFFEE_API const char* SCALAR_FORMAT_GetFormatName(SCALAR_FORMAT format);

    /// Get meta type of a scalar format
    COFFEE_API Type& SCALAR_FORMAT_GetType(SCALAR_FORMAT format);

}
}
#endif
