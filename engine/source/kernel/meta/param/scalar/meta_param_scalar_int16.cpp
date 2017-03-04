//------------------------------------------------------------------------------------------------//
/// @file kernel/meta/param/scalar/meta_param_scalar_int16.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "kernel/meta/param/scalar/meta_param_scalar_int16.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(meta::ParamScalarInt16);
        COFFEE_Ancestor(meta::Param);
    COFFEE_EndType();

namespace meta
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ParamScalarInt16::ParamScalarInt16()
    {
    }

    //--------------------------------------------------------------------------------------------//

    ParamScalarInt16::ParamScalarInt16(uint32 mode, int16 minimum_value, int16 maximum_value) :
        ParamScalar< int16 >(mode, minimum_value, maximum_value)
    {
    }

    //--------------------------------------------------------------------------------------------//

    ParamScalarInt16::~ParamScalarInt16()
    {
    }
}
}
//------------------------------------------------------------------------------------------------//
