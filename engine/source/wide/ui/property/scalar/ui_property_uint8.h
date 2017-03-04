#ifndef _COFFEE_UI_PROPERTY_UINT8_H_
#define _COFFEE_UI_PROPERTY_UINT8_H_

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
    /// uint8 property widget
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PropertyUInt8 : public PropertyScalar< uint8, meta::ParamScalarUInt8 >
    {
        //-META-----------------------------------------------------------------------------------//

        COFFEE_PropertyInterface(PropertyUInt8, "uint8", "", false);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyUInt8();
        ~PropertyUInt8();

    protected:

        //-QUERIES--------------------------------------------------------------------------------//

        basic::String _GetTextFromValue(uint8 value) const;
        uint8 _GetValueFromText(const basic::String& text) const;
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, PropertyUInt8);
}
}
#endif
