#ifndef _COFFEE_UI_PROPERTY_BOOL_H_
#define _COFFEE_UI_PROPERTY_BOOL_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/property/ui_property_manager.h"
#include "wide/ui/widget/widgets.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Boolean property widget
    ///
    /// @see coffee::ui::PropertyManager
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PropertyBool : public Property
    {
        //-META-----------------------------------------------------------------------------------//

        COFFEE_PropertyInterface(PropertyBool, "bool", "", false);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyBool();
        virtual ~PropertyBool();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void CreateContent();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(PropertyBool);
        COFFEE_Event bool OnCheck(shell::Event& event);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        widget::CheckBox* _CheckBox;
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, PropertyBool);
}
}
#endif
