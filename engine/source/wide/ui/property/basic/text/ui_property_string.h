#ifndef _COFFEE_UI_PROPERTY_STRING_H_
#define _COFFEE_UI_PROPERTY_STRING_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/property/ui_property_manager.h"
#include "wide/ui/widget/widgets.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// String property
    ///
    /// Property for basic::String edition.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PropertyString : public Property
    {
        COFFEE_PropertyInterface(PropertyString, "basic::String", "", false);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyString();
        virtual ~PropertyString();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void CreateContent();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(PropertyString);
        COFFEE_Event bool OnTextChanged(shell::Event& event);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        widget::Label* _Text;
        widget::EditBox* _EditBox;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, PropertyString);
}
}
#endif
