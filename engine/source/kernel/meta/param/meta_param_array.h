#ifndef _COFFEE_META_PARAM_ARRAY_H_
#define _COFFEE_META_PARAM_ARRAY_H_

#include "coffee_includes.h"
#include "kernel/meta/param/meta_param.h"

namespace coffee
{
namespace meta
{
    //--------------------------------------------------------------------------------------------//
    /// Array meta type custom parameter base class
    ///
    /// Passing it to COFFEE_AttributeCustom, it allows to set custom parameters to meta type,
    /// edition parameters for instance.
    /// This class is set by default using COFFEE_Attribute, when array type is given.
    /// ex: COFFEE_Attribute(< uint32 >, MyArray, 0);
    /// Note that by using COFFEE_AttributeCustom with ParamArray, it is possible to
    /// specify the attribute used to display element name in the GUI.
    ///
    /// @see COFFEE_AttributeCustom, coffee::meta::Param
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ParamArray : public Param
    {
        COFFEE_Type(ParamArray);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ParamArray();
        ParamArray(uint32 mode, basic::String attribute_name);
        virtual ~ParamArray();

        //-ACCESSORS------------------------------------------------------------------------------//

        const basic::String & GetAttributeName() const;

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::String * _AttributeName;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ParamArray);
}
}
#endif
