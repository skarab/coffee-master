#ifndef _COFFEE_UI_SKIN_DEFAULT_VIEW_CONTAINER_H_
#define _COFFEE_UI_SKIN_DEFAULT_VIEW_CONTAINER_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/widget/widgets.h"
#include "wide/ui/skin/ui_skin_widget.h"

namespace coffee
{ 
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// ViewContainer skin
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API SkinViewContainer : public SkinWidget
    {
        //-META-----------------------------------------------------------------------------------//
        
        COFFEE_Type(SkinViewContainer);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SkinViewContainer();
        ~SkinViewContainer();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void ApplyTheme(SkinTheme& theme);
        void Render(Window& window, const SkinContext& paint_context);
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, SkinViewContainer);
}
}
#endif
