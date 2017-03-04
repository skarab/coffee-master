#ifndef _COFFEE_UI_PROPERTY_UINT16_H_
#define _COFFEE_UI_PROPERTY_UINT16_H_

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
    /// uint16 property widget
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PropertyUInt16 : public PropertyScalar< uint16, meta::ParamScalarUInt16 >
    {
        //-META-----------------------------------------------------------------------------------//

        COFFEE_PropertyInterface(PropertyUInt16, "uint16", "", false);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyUInt16();
        ~PropertyUInt16();

    protected:

        //-QUERIES--------------------------------------------------------------------------------//

        basic::String _GetTextFromValue(uint16 value) const;
        uint16 _GetValueFromText(const basic::String& text) const;
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, PropertyUInt16);
}
}
#endif
