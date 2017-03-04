#ifndef _COFFEE_UI_SKIN_DEFAULT_VIEW_CONTROL_H_
#define _COFFEE_UI_SKIN_DEFAULT_VIEW_CONTROL_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/widget/widgets.h"
#include "wide/ui/skin/ui_skin_widget.h"

namespace coffee
{ 
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// ViewControl skin
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API SkinViewControl : public SkinWidget
    {
        //-META-----------------------------------------------------------------------------------//
        
        COFFEE_Type(SkinViewControl);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SkinViewControl();
        ~SkinViewControl();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void ApplyTheme(SkinTheme& theme);
        void Render(Window& window, const SkinContext& paint_context);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//
        
        SkinWidgetState _StateDisabled;
        SkinWidgetState _StateEnabled;
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, SkinViewControl);
}
}
#endif
