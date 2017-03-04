#include "wide/ui/widget/check_box/widget_check_box.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::widget::CheckBox);
        COFFEE_Ancestor(ui::widget::Widget);
    COFFEE_EndType();

namespace ui
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    CheckBox::CheckBox() :
        _State(CHECK_BOX_STATE_UnChecked)
    {
    }

    //--------------------------------------------------------------------------------------------//

    CheckBox::~CheckBox()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void CheckBox::SetState(const CHECK_BOX_STATE& state)
    {
        _State = state;
    }

    //--------------------------------------------------------------------------------------------//

    const CHECK_BOX_STATE& CheckBox::GetState()
    {
        return _State;
    }

    //--------------------------------------------------------------------------------------------//

    void CheckBox::SetText(const basic::String& text)
    {
        _Text = text;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::String& CheckBox::GetText() const
    {
        return _Text;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void CheckBox::Create(Window* parent, const basic::Vector2i& position,
        const basic::Vector2i& size, uint32 style)
    {
        Window::Create(parent, position, size, WINDOW_STYLE_Focusable);
        SetExtendedStyle(style);
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(CheckBox, Widget)
        COFFEE_RegisterEventHandler(input::EVENT_MouseLeftButtonReleased, input::Handler, OnMouseLeftButtonReleased)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool CheckBox::OnMouseLeftButtonReleased(shell::Event& event)
    {
        if (IsEnabled())
        {
            if (_State==CHECK_BOX_STATE_UnChecked)
            {
                _State = CHECK_BOX_STATE_Checked;
            }
            else
            {
                if (HasExtendedStyle(CHECK_BOX_STYLE_ThreeStates)
                    && _State==CHECK_BOX_STATE_Checked)
                {
                    _State = CHECK_BOX_STATE_AlternateChecked;
                }
                else
                {
                    _State = CHECK_BOX_STATE_UnChecked;
                }
            }
            SendEvent(EVENT_Pressed);
        }

        return false;
    }

}
}
}
