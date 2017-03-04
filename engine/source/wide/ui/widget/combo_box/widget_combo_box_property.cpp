#include "wide/ui/widget/combo_box/widget_combo_box_property.h"
#include "wide/ui/widget/label/widget_label.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::widget::ComboBoxProperty);
        COFFEE_Ancestor(ui::widget::Widget);
    COFFEE_EndType();

namespace ui
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ComboBoxProperty::ComboBoxProperty():
        _ComboBox(NULL)
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const ComboBox& ComboBoxProperty::GetComboBox() const
    {
        return *_ComboBox;
    }

    //--------------------------------------------------------------------------------------------//

    ComboBox& ComboBoxProperty::GetComboBox()
    {
        return *_ComboBox;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ComboBoxProperty::Create(basic::String text, Window* parent,
        const basic::Vector2i& position, uint32 width)
    {
        Window::Create(parent, position, basic::Vector2i(width, 20), 
            WINDOW_STYLE_DrawFrame | WINDOW_STYLE_DrawClientSunken);

        GetLayout().SetStyle(
            LAYOUT_STYLE_HorizontalCanvas
            | LAYOUT_STYLE_StickChildren
            | LAYOUT_STYLE_VerticalShrink);
        
        Label* static_text = COFFEE_New(Label);
        static_text->Create(this, basic::Vector2i(), basic::Vector2i(84, 20));
        static_text->SetText(text);
        static_text->GetLayout().SetCanvas(40, true);

        _ComboBox = COFFEE_New(ComboBox);
        _ComboBox->Create(this, basic::Vector2i(88, 0), 108);
        _ComboBox->GetLayout().SetCanvas(100 - 40, true);
    }

}
}
}
