#ifndef _COFFEE_UI_SKIN_DEFAULT_CHECK_BOX_H_
#define _COFFEE_UI_SKIN_DEFAULT_CHECK_BOX_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/widget/widgets.h"
#include "wide/ui/skin/ui_skin_widget.h"

namespace coffee
{ 
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// CheckBox skin
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API SkinCheckBox : public SkinWidget
    {
        //-META-----------------------------------------------------------------------------------//
        
        COFFEE_Type(SkinCheckBox);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SkinCheckBox();
        ~SkinCheckBox();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void ApplyTheme(SkinTheme& theme);
        void Render(Window& window, const SkinContext& paint_context);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//
        
        SkinWidgetState _StateDisabled;
        SkinWidgetState _StateEnabled;
        SkinWidgetState _StateChecked;
        SkinWidgetState _StateCursorOver;
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, SkinCheckBox);
}
}
#endif
