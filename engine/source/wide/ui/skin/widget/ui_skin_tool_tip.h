#ifndef _COFFEE_UI_SKIN_DEFAULT_TOOL_TIP_H_
#define _COFFEE_UI_SKIN_DEFAULT_TOOL_TIP_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/widget/widgets.h"
#include "wide/ui/skin/ui_skin_widget.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// ToolTip skin
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API SkinToolTip : public SkinWidget
    {
        //-META-----------------------------------------------------------------------------------//

        COFFEE_Type(SkinToolTip);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SkinToolTip();
        ~SkinToolTip();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void ApplyTheme(SkinTheme& theme);
        void Render(Window& window, const SkinContext& paint_context);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//
            
        SkinWidgetState _StateEnabled;
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, SkinToolTip);
}
}
#endif
