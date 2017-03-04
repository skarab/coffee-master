#ifndef _COFFEE_UI_SKIN_DEFAULT_DIALOG_H_
#define _COFFEE_UI_SKIN_DEFAULT_DIALOG_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/widget/widgets.h"
#include "wide/ui/skin/ui_skin_widget.h"

namespace coffee
{ 
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Dialog skin
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API SkinDialog : public SkinWidget
    {
        //-META-----------------------------------------------------------------------------------//
        
        COFFEE_Type(SkinDialog);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SkinDialog();
        ~SkinDialog();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void ApplyTheme(SkinTheme& theme);
        void Render(Window& window, const SkinContext& paint_context);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//
        
        SkinWidgetState _StateDisabled;
        SkinWidgetState _StateEnabled;
        SkinWidgetState _StateActive;
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, SkinDialog);
}
}
#endif
