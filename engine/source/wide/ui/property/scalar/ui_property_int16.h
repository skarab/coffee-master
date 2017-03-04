#ifndef _COFFEE_UI_PROPERTY_INT16_H_
#define _COFFEE_UI_PROPERTY_INT16_H_

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
    /// int16 property widget
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PropertyInt16 : public PropertyScalar< int16, meta::ParamScalarInt16 >
    {
        //-META-----------------------------------------------------------------------------------//

        COFFEE_PropertyInterface(PropertyInt16, "int16", "", false);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyInt16();
        ~PropertyInt16();

    protected:

        //-QUERIES--------------------------------------------------------------------------------//

        basic::String _GetTextFromValue(int16 value) const;
        int16 _GetValueFromText(const basic::String& text) const;
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, PropertyInt16);
}
}
#endif
