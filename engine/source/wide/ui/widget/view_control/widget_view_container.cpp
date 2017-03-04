#include "wide/ui/widget/view_control/widget_view_container.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::widget::ViewContainer);
        COFFEE_Ancestor(ui::Window);
    COFFEE_EndType();

namespace ui
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ViewContainer::ViewContainer()
    {
    }

    //--------------------------------------------------------------------------------------------//

    ViewContainer::~ViewContainer()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ViewContainer::Create(Window* parent, const basic::Vector2i& position,
        const basic::Vector2i& size, uint32 style)
    {
        Window::Create(parent, basic::Vector2i(), basic::Vector2i(),
            WINDOW_STYLE_Focusable);
        GetLayout().SetStyle(LAYOUT_STYLE_VerticalCanvas
            | LAYOUT_STYLE_Shrink
            | LAYOUT_STYLE_StickChildren);
    }

}
}
}
