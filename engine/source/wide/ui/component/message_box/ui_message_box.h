#ifndef _COFFEE_UI_MESSAGE_BOX_H_
#define _COFFEE_UI_MESSAGE_BOX_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/widget/widgets.h"
#include "wide/ui/component/message_box/ui_message_box_flag.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Open a modal Message box
    //--------------------------------------------------------------------------------------------//
    bool COFFEE_API DoMessageBox(basic::String caption, basic::String message,
        uint32 flags = MESSAGE_BOX_FLAG_Ok);

    //--------------------------------------------------------------------------------------------//
    /// Simple modal message box
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API MessageBox : public widget::Dialog
    {
        COFFEE_Type(MessageBox);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        MessageBox();
        ~MessageBox();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(basic::String caption, basic::String message,
            uint32 flags = MESSAGE_BOX_FLAG_None);

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(MessageBox);
        COFFEE_Event bool OnOk(shell::Event& event);
        COFFEE_Event bool OnCancel(shell::Event& event);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        uint32 _Flags;
        widget::Label* _MessageText;
        widget::Button* _OkButton;
        widget::Button* _CancelButton;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, MessageBox);
}
}
#endif
