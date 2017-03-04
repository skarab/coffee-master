#ifndef _COFFEE_UI_PROPERTY_TEXT_H_
#define _COFFEE_UI_PROPERTY_TEXT_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/property/ui_property_manager.h"
#include "wide/ui/widget/widgets.h"
#include "wide/ui/property/basic/text/ui_property_text_dialog.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Text property
    ///
    /// It links the property to the text editor dialog.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PropertyText : public Property
    {
        COFFEE_PropertyInterface(PropertyText, "basic::Text", "", false);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyText();
        virtual ~PropertyText();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void CreateContent();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(PropertyText);
        COFFEE_Event bool OnEdit(shell::Event& event);
        COFFEE_Event bool OnClose(shell::Event& event);

        COFFEE_DeclareExternEventHandler(PropertyText, OnCloseEditDialog);
        COFFEE_DeclareExternEventHandler(PropertyText, OnTextChanged);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        widget::Button* _EditButton;
        PropertyTextDialog* _EditDialog;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, PropertyText);
}
}
#endif
