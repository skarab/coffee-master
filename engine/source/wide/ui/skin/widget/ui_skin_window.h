#ifndef _COFFEE_UI_SKIN_DEFAULT_WINDOW_H_
#define _COFFEE_UI_SKIN_DEFAULT_WINDOW_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/widget/widgets.h"
#include "wide/ui/skin/ui_skin_widget.h"

namespace coffee
{ 
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Window skin
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API SkinWindow : public SkinWidget
    {
        COFFEE_Type(SkinWindow);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SkinWindow();
        ~SkinWindow();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void ApplyTheme(SkinTheme& theme);
        void Render(Window& window, const SkinContext& paint_context);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _RenderShadows(Window& window, const SkinContext& paint_context);
        void _RenderBump(Window& window, const SkinContext& paint_context);

        //-ATTRIBUTES-----------------------------------------------------------------------------//
        
        SkinWidgetState _WindowArea;
        SkinWidgetState _WindowClientRaised;
        SkinWidgetState _WindowClientSunken;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, SkinWindow);
}
}
#endif
