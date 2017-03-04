#include "wide/ui/widget/dialog/widget_dialog.h"
#include "wide/ui/window/ui_window_context.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::widget::Dialog);
        COFFEE_Ancestor(ui::widget::Widget);
    COFFEE_EndType();

namespace ui
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Dialog::Dialog():
        _CloseButton(NULL)
    {
        _TitleBarHeight = GetButtonSize();
    }

    //--------------------------------------------------------------------------------------------//

    Dialog::~Dialog()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Dialog::SetTitleBarText(const basic::String& title_bar_text)
    {
        _TitleBarText = title_bar_text;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::String& Dialog::GetTitleBarText()
    {
        return _TitleBarText;
    }

    //--------------------------------------------------------------------------------------------//

    int32 Dialog::GetTitleBarHeight() const
    {
        return _TitleBarHeight;
    }

    //--------------------------------------------------------------------------------------------//

    const Button& Dialog::GetCloseButton() const
    {
        return *_CloseButton;
    }

    //--------------------------------------------------------------------------------------------//

    Button& Dialog::GetCloseButton()
    {
        return *_CloseButton;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Dialog::Create(Window* parent, const basic::Vector2i& position,
        const basic::Vector2i& size, uint32 style)
    {
        Window::Create(parent, position, size,
            WINDOW_STYLE_Draggable | WINDOW_STYLE_Activable
            | WINDOW_STYLE_Resizeable | WINDOW_STYLE_DrawFrame
            | WINDOW_STYLE_DrawClientRaised);

        SetExtendedStyle(style);
        SetTitleBarText("Dialog");

        if (HasExtendedStyle(DIALOG_STYLE_CloseButton))
        {
            _CloseButton = COFFEE_New(Button);
            _CloseButton->Create(this, basic::Vector2i(),
                basic::Vector2i(_TitleBarHeight, _TitleBarHeight), BUTTON_STYLE_Default);
            _CloseButton->SetStyle(_CloseButton->GetStyle()
                | (uint32) WINDOW_STYLE_NoParentClientClip);
            _CloseButton->SetImage(SKIN_ICON_Close);
            _CloseButton->SetHelpText("Close");
        }
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(Dialog, Widget)
        COFFEE_RegisterTargetEventHandler(EVENT_Pressed, Widget, _CloseButton, OnClose)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool Dialog::OnClose(shell::Event& event)
    {
        Destroy();
        return true;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Dialog::_UpdateClientArea()
    {
        basic::Rectangle client_rect;

        GetLayout().SetMinimumSize(basic::Vector2i(
            40 + 2 * GetBorders().X,
            _TitleBarHeight + 2 * GetBorders().Y));

        Window::_UpdateClientArea();

        client_rect = GetClientRect();

        client_rect.Position = basic::Vector2i(
            client_rect.Position.X,
            client_rect.Position.Y + _TitleBarHeight + GetBorders().Y);

        client_rect.Size = basic::Vector2i(
            client_rect.Size.X,
            client_rect.Size.Y - _TitleBarHeight - GetBorders().Y);

        if (_CloseButton!=NULL)
        {
            _CloseButton->SetPosition(basic::Vector2i(
                GetSize().X - _TitleBarHeight - GetBorders().X * 2 + 1,
                - _TitleBarHeight - GetBorders().Y));
        }

        _SetClientRect(client_rect);
    }

}
}
}
