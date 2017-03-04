#ifndef _COFFEE_UI_STRING_BOX_H_
#define _COFFEE_UI_STRING_BOX_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/widget/widgets.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Query a string using a modal dialog, coffee::ui::StringBox.
    //--------------------------------------------------------------------------------------------//
    basic::String COFFEE_API DoStringBox(basic::String caption, basic::String message,
        basic::String default_string="", basic::String accept_button="Ok");

    //--------------------------------------------------------------------------------------------//
    /// Modal dialog used to ask for a string
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API StringBox : public widget::Dialog
    {
        COFFEE_Type(StringBox);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        StringBox();
        ~StringBox();

        //-QUERIES--------------------------------------------------------------------------------//

        const basic::String& GetValue() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(basic::String caption, basic::String message, basic::String default_string="",
            basic::String accept_button="Ok");

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(StringBox);
        COFFEE_Event bool OnAccept(shell::Event& event);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        widget::Label* _MessageText;
        widget::EditBox* _EditBox;
        widget::Button* _AcceptButton;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, StringBox);
}
}
#endif
