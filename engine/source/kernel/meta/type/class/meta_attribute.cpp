//------------------------------------------------------------------------------------------------//
/// @file kernel/meta/type/class/meta_attribute.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "kernel/meta/type/class/meta_attribute.h"
#include "kernel/basic/container/basic_containers.h"
#include "kernel/basic/alpha/basic_alpha.h"
#include "kernel/meta/param/meta_params.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
namespace meta
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Attribute::Attribute() :
        _Name(COFFEE_New(basic::String)),
        _Type(NULL),
        _Param(NULL),
        _Offset(0),
        _ItIsPointer(false),
        _ItIsArray(false),
        _ItIsWeak(false)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Attribute::~Attribute()
    {
        COFFEE_Delete(_Name);
        if (_Param!=NULL)
            COFFEE_Delete(_Param);
    }

}
}
//------------------------------------------------------------------------------------------------//
