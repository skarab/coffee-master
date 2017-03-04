#ifndef _COFFEE_UI_SKIN_DEFAULT_BUTTON_H_
#define _COFFEE_UI_SKIN_DEFAULT_BUTTON_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/widget/widgets.h"
#include "wide/ui/skin/ui_skin_widget.h"

namespace coffee
{ 
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Button skin
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API SkinButton : public SkinWidget
    {
        COFFEE_Type(SkinButton);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SkinButton();
        ~SkinButton();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void ApplyTheme(SkinTheme& theme);
        void Render(Window& window, const SkinContext& paint_context);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//
        
        SkinWidgetState _StateDisabled;
        SkinWidgetState _StatePressed;
        SkinWidgetState _StateReleased;
        SkinWidgetState _StateCursorOver;
        SkinWidgetState _StatePressedImage;
        SkinWidgetState _StateCursorOverImage;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, SkinButton);
}
}
#endif
