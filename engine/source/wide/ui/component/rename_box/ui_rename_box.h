#ifndef _COFFEE_UI_RENAME_BOX_H_
#define _COFFEE_UI_RENAME_BOX_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/widget/edit_box/widget_edit_box.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Simple rename item helper
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API RenameBox : public widget::EditBox
    {
        COFFEE_Type(RenameBox);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        RenameBox();
        ~RenameBox();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(Window* item, basic::String text);

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(RenameBox);
        COFFEE_Event bool OnKeyReleased(shell::Event& event);
        COFFEE_Event bool OnKillFocus(shell::Event& event);
        COFFEE_Event bool OnChanged(shell::Event& event);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        bool _ItHasToSkipChanges;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, RenameBox);
}
}
#endif
