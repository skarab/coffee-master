#ifndef _COFFEE_META_PARAM_ARRAY_COMBO_H_
#define _COFFEE_META_PARAM_ARRAY_COMBO_H_

#include "coffee_includes.h"
#include "kernel/meta/param/meta_param_array.h"

namespace coffee
{
namespace meta
{
    //--------------------------------------------------------------------------------------------//
    /// Custom edition of array using combo box
    ///
    /// Tell the GUI system the specified array is edited using a single element approach, where
    /// item index is selectable using a combo box, binded either on an attribute of the type or
    /// either on an enum meta type.
    ///
    /// @see coffee::meta::ParamArray
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ParamArrayCombo : public ParamArray
    {
        COFFEE_Type(ParamArrayCombo);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ParamArrayCombo();
        ParamArrayCombo(uint32 mode, basic::String attribute_name);
        virtual ~ParamArrayCombo();
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ParamArrayCombo);
}
}
#endif
