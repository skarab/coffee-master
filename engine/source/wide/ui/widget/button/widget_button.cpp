#include "wide/ui/widget/button/widget_button.h"
#include "wide/ui/widget/tool_tip/widget_tool_tip.h"
#include "wide/ui/skin/ui_skin.h"
#include "wide/ui/window/ui_window_manager.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::widget::Button);
        COFFEE_Ancestor(ui::widget::Widget);
    COFFEE_EndType();

namespace ui
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Button::Button() :
        _State(BUTTON_STATE_Off),
        _ItHasToOverwriteColor(false),
        _Image(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Button::~Button()
    {
        if(WindowManager::IsAvailable())
            WindowManager::Get().SetNoToolTipWindow(this);
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Button::SetState(const BUTTON_STATE& state)
    {
        _State = state;
    }

    //--------------------------------------------------------------------------------------------//

    const BUTTON_STATE& Button::GetState()
    {
        return _State;
    }

    //--------------------------------------------------------------------------------------------//

    void Button::SetText(const basic::String& text)
    {
        _Text = text;
        SetNoImage();
    }

    //--------------------------------------------------------------------------------------------//

    const basic::String& Button::GetText() const
    {
        return _Text;
    }

    //--------------------------------------------------------------------------------------------//

    void Button::SetColor(const basic::Color& color)
    {
        _Color = color;
        _ItHasToOverwriteColor = true;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Color& Button::GetColor() const
    {
        return _Color;
    }

    //--------------------------------------------------------------------------------------------//

    bool Button::HasToOverwriteColor() const
    {
        return _ItHasToOverwriteColor;
    }

    //--------------------------------------------------------------------------------------------//

    void Button::SetImage(graphics::Texture texture_instance)
    {
        if (_Image==NULL)
        {
            _Image = COFFEE_New(Image);
            _Image->Create(this, basic::Vector2i(), GetClientRect().Size, IMAGE_STYLE_NoBorders);
            _Image->GetLayout().SetStyle(LAYOUT_STYLE_Default);
        }
        
        _Image->SetImage(texture_instance);
    }

    //--------------------------------------------------------------------------------------------//

    void Button::SetImage(storage::Path texture_path)
    {
        if (_Image==NULL)
        {
            _Image = COFFEE_New(Image);
            _Image->Create(this, basic::Vector2i(), GetClientRect().Size, IMAGE_STYLE_NoBorders);
            _Image->GetLayout().SetStyle(LAYOUT_STYLE_Default);
        }

        _Image->SetImage(texture_path);
    }

    //--------------------------------------------------------------------------------------------//

    void Button::SetImage(const SKIN_ICON& icon)
    {
        if (_Image==NULL)
        {
            _Image = COFFEE_New(Image);
            _Image->Create(this, basic::Vector2i(), GetClientRect().Size, IMAGE_STYLE_NoBorders);
            _Image->GetLayout().SetStyle(LAYOUT_STYLE_Default);
        }

        _Image->SetImage(icon);
    }

    //--------------------------------------------------------------------------------------------//

    void Button::SetNoImage()
    {
        _DestroyImage();
    }

    //--------------------------------------------------------------------------------------------//

    void Button::SetHelpText(const basic::String& help_text)
    {
        _HelpText = help_text;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool Button::HasImage() const
    {
        return (_Image!=NULL);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Button::Create(Window* parent, const basic::Vector2i& position,
        const basic::Vector2i& size, uint32 style)
    {
        Window::Create(parent, position, size, WINDOW_STYLE_Focusable);
        SetExtendedStyle(style);
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(Button, Widget)
        COFFEE_RegisterEventHandler(WINDOW_EVENT_BeginCursorOver, Window, OnBeginCursorOver)
        COFFEE_RegisterEventHandler(WINDOW_EVENT_EndCursorOver, Window, OnEndCursorOver)
        COFFEE_RegisterEventHandler(input::EVENT_MouseLeftButtonPressed, input::Handler, OnMouseLeftButtonPressed)
        COFFEE_RegisterEventHandler(input::EVENT_MouseLeftButtonReleased, input::Handler, OnMouseLeftButtonReleased)
        COFFEE_RegisterEventHandler(input::EVENT_MouseRightButtonReleased, input::Handler, OnMouseRightButtonReleased)
        COFFEE_RegisterEventHandler(input::EVENT_MouseDoubleClick, input::Handler, OnMouseDoubleClick)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool Button::OnBeginCursorOver(shell::Event& event)
    {
        if(_HelpText.GetLength()>0 && WindowManager::IsAvailable())
        {
            ToolTip* bullet;

            bullet = COFFEE_New(ToolTip);

            bullet->Create(_HelpText, basic::Vector2i(
                (int32) input::Mouse::Get().GetPosition().X,
                (int32) input::Mouse::Get().GetPosition().Y + 25), this);

            WindowManager::Get().SetToolTipWindow(bullet);
        }

        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Button::OnEndCursorOver(shell::Event& event)
    {
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Button::OnMouseLeftButtonPressed(shell::Event& event)
    {
        if (IsEnabled())
        {
            if (HasExtendedStyle(BUTTON_STYLE_Default))
                _State = BUTTON_STATE_On;
            _UpdateClientArea();
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Button::OnMouseLeftButtonReleased(shell::Event& event)
    {
        if (IsEnabled())
        {
            input::EventMouse* mouse_parameter = (input::EventMouse*)event.GetParameters().GetCustomParameter();
            bool it_is_inside = GetParentWindow().HitTest(mouse_parameter->Position, WINDOW_STYLE_Focusable)==this;

            if (HasExtendedStyle(BUTTON_STYLE_Default))
            {
                _State = BUTTON_STATE_Off;
            }
            else if (it_is_inside)
            {                
                if(_State==BUTTON_STATE_Off)
                {
                    _State = BUTTON_STATE_On;
                }
                else
                {
                    _State = BUTTON_STATE_Off;
                }
            }

            if (it_is_inside)
            {
                SendEvent(EVENT_Pressed);
            }
            else
            {
                SendEvent(EVENT_PressedCanceled);
            }
            _UpdateClientArea();
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Button::OnMouseRightButtonReleased(shell::Event& event)
    {
        if (IsEnabled())
        {
            input::EventMouse* mouse_parameter = (input::EventMouse*)event.GetParameters().GetCustomParameter();
            bool it_is_inside = GetParentWindow().HitTest(mouse_parameter->Position, WINDOW_STYLE_Focusable)==this;
            if (it_is_inside)
                SendEvent(EVENT_ContextMenu);
        }
        return false;
    }
        
    //--------------------------------------------------------------------------------------------//

    bool Button::OnMouseDoubleClick(shell::Event& event)
    {
        if (IsEnabled())
            SendEvent(EVENT_Pressed);
        return false;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Button::_DestroyImage()
    {
        if (_Image!=NULL)
        {
            ui::widget::Image* image = _Image;
            _Image = NULL;
            image->Destroy();
        }
    }
    
    //--------------------------------------------------------------------------------------------//

    void Button::_UpdateClientArea()
    {
        Window::_UpdateClientArea();

        if (HasImage())
        {
            if (_State==BUTTON_STATE_On)
            {
                _Image->SetPosition(basic::Vector2i(1, 1));
            }
            else
            {
                _Image->SetPosition(basic::Vector2i(0, 0));
            }

            _Image->SetSize(GetClientRect().Size);
        }
    }

}
}
}
