#ifndef _COFFEE_UI_SKIN_DEFAULT_GROUP_H_
#define _COFFEE_UI_SKIN_DEFAULT_GROUP_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/widget/widgets.h"
#include "wide/ui/skin/ui_skin_widget.h"

namespace coffee
{ 
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Group skin
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API SkinGroup : public SkinWidget
    {
        //-META-----------------------------------------------------------------------------------//

        COFFEE_Type(SkinGroup);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SkinGroup();
        ~SkinGroup();

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

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, SkinGroup);
}
}
#endif
