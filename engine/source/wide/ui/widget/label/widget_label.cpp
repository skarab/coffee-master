#include "wide/ui/widget/label/widget_label.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::widget::Label);
        COFFEE_Ancestor(ui::widget::Widget);
    COFFEE_EndType();

namespace ui
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Label::Label()
    {
    }

    //--------------------------------------------------------------------------------------------//

    Label::~Label()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Label::SetText(const basic::String& text)
    {
        _Text = text;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::String& Label::GetText() const
    {
        return _Text;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Label::Create(Window* parent, const basic::Vector2i& position,
        const basic::Vector2i& size, uint32 style)
    {
        Window::Create(parent, position, size, WINDOW_STYLE_Focusable);
    }

    //--------------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(Label, Widget)
    COFFEE_EndEventHandler()

}
}
}
