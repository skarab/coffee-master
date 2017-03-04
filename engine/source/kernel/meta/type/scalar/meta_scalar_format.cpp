//------------------------------------------------------------------------------------------------//
/// @file kernel/meta/type/scalar/meta_scalar_format.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "kernel/meta/type/scalar/meta_scalar_format.h"
#include "kernel/meta/meta_types.h"
#include "kernel/meta/type/scalar/meta_scalar.h"
#include "kernel/basic/container/basic_containers.h"
#include "kernel/basic/alpha/basic_alpha.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
namespace meta
{
    //-VARIABLES----------------------------------------------------------------------------------//

    static const char SCALAR_FORMAT_TypeNameArray[SCALAR_FORMAT_Count][8] =
    {
        "bool",
        "int8",
        "uint8",
        "int16",
        "uint16",
        "int32",
        "uint32",
        "real",
        "enum"
    };

    //--------------------------------------------------------------------------------------------//

    static ulong SCALAR_FORMAT_TypeSizeArray[SCALAR_FORMAT_Count] =
    {
        sizeof(bool),
        sizeof(int8),
        sizeof(uint8),
        sizeof(int16),
        sizeof(uint16),
        sizeof(int32),
        sizeof(uint32),
        sizeof(real),
        sizeof(uint32)
    };

    //--------------------------------------------------------------------------------------------//

    Type* SCALAR_FORMAT_TypeArray[SCALAR_FORMAT_Count];

    //-OPERATIONS---------------------------------------------------------------------------------//

    void SCALAR_FORMAT_Register()
    {
        for (uint32 index=0 ; index<SCALAR_FORMAT_Count ; ++index)
        {
            SCALAR_FORMAT_TypeArray[index] = COFFEE_New(Scalar, 
                SCALAR_FORMAT_TypeNameArray[index]);
            Types::Get()._RegisterType(*SCALAR_FORMAT_TypeArray[index]);
        }
    }

    //--------------------------------------------------------------------------------------------//

    SCALAR_FORMAT SCALAR_FORMAT_GetFormat(const basic::String& type_name)
    {
        for (uint32 index=0 ; index<SCALAR_FORMAT_Count ; ++index)
            if (type_name==SCALAR_FORMAT_TypeNameArray[index])
                return (SCALAR_FORMAT) index;
       return SCALAR_FORMAT_Enum;
    }

    //--------------------------------------------------------------------------------------------//

    ulong SCALAR_FORMAT_GetFormatSize(SCALAR_FORMAT format)
    {
        if (format==SCALAR_FORMAT_None)
            return 0;
        return SCALAR_FORMAT_TypeSizeArray[(uint32)format];
    }

    //--------------------------------------------------------------------------------------------//

    const char* SCALAR_FORMAT_GetFormatName(SCALAR_FORMAT format)
    {
        return SCALAR_FORMAT_TypeNameArray[(int32)format];
    }

    //--------------------------------------------------------------------------------------------//

    Type& SCALAR_FORMAT_GetType(SCALAR_FORMAT format)
    {
        COFFEE_Assert(format!=SCALAR_FORMAT_None, core::ERROR_CODE_IncorrectUsage,
            "Failed to retrieve scalar format");
        return *SCALAR_FORMAT_TypeArray[(int32)format];
    }

}
}
//------------------------------------------------------------------------------------------------//
