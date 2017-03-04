//------------------------------------------------------------------------------------------------//
/// @file kernel/meta/type/meta_type_templates.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "kernel/meta/type/meta_type_templates.h"
#include "kernel/meta/meta_object.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
namespace meta
{
    //-OPERATIONS---------------------------------------------------------------------------------//

    template<>
    Type& TYPE< bool >::Get()
    {
        return SCALAR_FORMAT_GetType(SCALAR_FORMAT_Bool);
    }

    //--------------------------------------------------------------------------------------------//

    template<>
    Type& TYPE< int8 >::Get()
    {
        return SCALAR_FORMAT_GetType(SCALAR_FORMAT_Int8);
    }

    //--------------------------------------------------------------------------------------------//

    template<>
    Type& TYPE< uint8 >::Get()
    {
        return SCALAR_FORMAT_GetType(SCALAR_FORMAT_UInt8);
    }

    //--------------------------------------------------------------------------------------------//

    template<>
    Type& TYPE< int16 >::Get()
    {
        return SCALAR_FORMAT_GetType(SCALAR_FORMAT_Int16);
    }

    //--------------------------------------------------------------------------------------------//

    template<>
    Type& TYPE< uint16 >::Get()
    {
        return SCALAR_FORMAT_GetType(SCALAR_FORMAT_UInt16);
    }

    //--------------------------------------------------------------------------------------------//

    template<>
    Type& TYPE< int32 >::Get()
    {
        return SCALAR_FORMAT_GetType(SCALAR_FORMAT_Int32);
    }

    //--------------------------------------------------------------------------------------------//

    template<>
    Type& TYPE< uint32 >::Get()
    {
        return SCALAR_FORMAT_GetType(SCALAR_FORMAT_UInt32);
    }

    //--------------------------------------------------------------------------------------------//

    template<>
    Type& TYPE< real >::Get()
    {
        return SCALAR_FORMAT_GetType(SCALAR_FORMAT_Real);
    }

}
}
//------------------------------------------------------------------------------------------------//
