#ifndef _COFFEE_UI_SKIN_DEFAULT_TREE_CONTROL_ITEM_H_
#define _COFFEE_UI_SKIN_DEFAULT_TREE_CONTROL_ITEM_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/widget/widgets.h"
#include "wide/ui/skin/ui_skin_widget.h"

namespace coffee
{ 
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// TreeControlItem skin
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API SkinTreeControlItem : public SkinWidget
    {
        //-META-----------------------------------------------------------------------------------//
        
        COFFEE_Type(SkinTreeControlItem);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SkinTreeControlItem();
        ~SkinTreeControlItem();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void ApplyTheme(SkinTheme& theme);
        void Render(Window& window, const SkinContext& paint_context);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//
        
        SkinWidgetState _StateDisabled;
        SkinWidgetState _StateEnabled;
        SkinWidgetState _StateActive;
        SkinWidgetState _StateCursorOver;
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, SkinTreeControlItem);
}
}
#endif
