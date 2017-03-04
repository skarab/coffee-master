#include "kernel/meta/param/meta_param_array_combo.h"
#include "kernel/basic/alpha/string/basic_string.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(meta::ParamArrayCombo);
        COFFEE_Ancestor(meta::ParamArray);
    COFFEE_EndType();

namespace meta
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ParamArrayCombo::ParamArrayCombo()
    {
    }

    //--------------------------------------------------------------------------------------------//

    ParamArrayCombo::ParamArrayCombo(uint32 mode, basic::String attribute_name) :
        ParamArray(mode, attribute_name)
    {
    }

    //--------------------------------------------------------------------------------------------//

    ParamArrayCombo::~ParamArrayCombo()
    {
    }

}
}
