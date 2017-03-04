#include "kernel/meta/param/meta_param_array.h"
#include "kernel/basic/alpha/string/basic_string.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(meta::ParamArray);
        COFFEE_Ancestor(meta::Param);
    COFFEE_EndType();

namespace meta
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ParamArray::ParamArray() :
        _AttributeName(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    ParamArray::ParamArray(uint32 mode, basic::String attribute_name) :
        Param(mode),
        _AttributeName(COFFEE_New(basic::String, attribute_name))
    {
    }

    //--------------------------------------------------------------------------------------------//

    ParamArray::~ParamArray()
    {
        if (_AttributeName!=NULL)
            COFFEE_Delete(_AttributeName);
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const basic::String & ParamArray::GetAttributeName() const
    {
        return *_AttributeName;
    }

}
}
