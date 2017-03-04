#ifndef _COFFEE_UI_PROPERTY_UINT32_H_
#define _COFFEE_UI_PROPERTY_UINT32_H_

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
    /// uint32 property widget
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PropertyUInt32 : public PropertyScalar< uint32, meta::ParamScalarUInt32 >
    {
        //-META-----------------------------------------------------------------------------------//

        COFFEE_PropertyInterface(PropertyUInt32, "uint32", "", false);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyUInt32();
        ~PropertyUInt32();

    protected:

        //-QUERIES--------------------------------------------------------------------------------//

        basic::String _GetTextFromValue(uint32 value) const;
        uint32 _GetValueFromText(const basic::String& text) const;
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, PropertyUInt32);
}
}
#endif
