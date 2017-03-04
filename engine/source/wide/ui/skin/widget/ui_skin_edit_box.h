#ifndef _COFFEE_UI_SKIN_DEFAULT_EDIT_BOX_H_
#define _COFFEE_UI_SKIN_DEFAULT_EDIT_BOX_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/widget/widgets.h"
#include "wide/ui/skin/ui_skin_widget.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// EditBox skin
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API SkinEditBox : public SkinWidget
    {
        COFFEE_Type(SkinEditBox);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SkinEditBox();
        ~SkinEditBox();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void ApplyTheme(SkinTheme& theme);
        void Render(Window& window, const SkinContext& paint_context);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//
        
        SkinWidgetState _StateDisabled;
        SkinWidgetState _StateEnabled;
        SkinWidgetState _StateCursorOver;
        SkinWidgetState _StateSelection;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, SkinEditBox);
}
}
#endif
