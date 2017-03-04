#include "kernel/meta/param/meta_param_enum_multi.h"
#include "kernel/basic/alpha/string/basic_string.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(meta::ParamEnumMulti);
        COFFEE_Ancestor(meta::Param);
    COFFEE_EndType();

namespace meta
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ParamEnumMulti::ParamEnumMulti() :
        _EnumName(COFFEE_New(basic::String))
    {
    }

    //--------------------------------------------------------------------------------------------//

    ParamEnumMulti::ParamEnumMulti(uint32 mode, basic::String enum_name) :
        Param(mode),
        _EnumName(COFFEE_New(basic::String, enum_name))
    {
    }

    //--------------------------------------------------------------------------------------------//

    ParamEnumMulti::~ParamEnumMulti()
    {
        COFFEE_Delete(_EnumName);
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void ParamEnumMulti::SetEnumName(const basic::String & enum_name)
    {
        *_EnumName = enum_name;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::String & ParamEnumMulti::GetEnumName() const
    {
        return *_EnumName;
    }

}
}
