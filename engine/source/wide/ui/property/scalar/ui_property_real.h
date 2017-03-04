#ifndef _COFFEE_UI_PROPERTY_REAL_H_
#define _COFFEE_UI_PROPERTY_REAL_H_

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
    /// real property widget
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PropertyReal : public PropertyScalar< real, meta::ParamScalarReal >
    {
        //-META-----------------------------------------------------------------------------------//

        COFFEE_PropertyInterface(PropertyReal, "real", "", false);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyReal();
        ~PropertyReal();

    protected:

        //-QUERIES--------------------------------------------------------------------------------//

        basic::String _GetTextFromValue(real value) const;
        real _GetValueFromText(const basic::String& text) const;
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, PropertyReal);
}
}
#endif
