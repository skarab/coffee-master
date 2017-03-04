#ifndef _COFFEE_UI_PROPERTY_INT32_H_
#define _COFFEE_UI_PROPERTY_INT32_H_

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
    /// int32 property widget
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PropertyInt32 : public PropertyScalar< int32, meta::ParamScalarInt32 >
    {
        //-META-----------------------------------------------------------------------------------//

        COFFEE_PropertyInterface(PropertyInt32, "int32", "", false);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyInt32();
        ~PropertyInt32();

    protected:

        //-QUERIES--------------------------------------------------------------------------------//

        basic::String _GetTextFromValue(int32 value) const;
        int32 _GetValueFromText(const basic::String& text) const;
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, PropertyInt32);
}
}
#endif
