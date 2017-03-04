#ifndef _COFFEE_UI_PROPERTY_INT8_H_
#define _COFFEE_UI_PROPERTY_INT8_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/property/ui_property_manager.h"
#include "wide/ui/property/scalar/ui_property_scalar.h"
#include "wide/ui/widget/widgets.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// int8 property widget
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PropertyInt8 : public PropertyScalar< int8, meta::ParamScalarInt8 >
    {
        //-META-----------------------------------------------------------------------------------//

        COFFEE_PropertyInterface(PropertyInt8, "int8", "", false);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyInt8();
        ~PropertyInt8();

    protected:

        //-QUERIES--------------------------------------------------------------------------------//

        basic::String _GetTextFromValue(int8 value) const;
        int8 _GetValueFromText(const basic::String& text) const;
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, PropertyInt8);
}
}
#endif
