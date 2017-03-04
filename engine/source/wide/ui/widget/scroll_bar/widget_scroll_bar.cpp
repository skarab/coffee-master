#include "wide/ui/widget/scroll_bar/widget_scroll_bar.h"
#include "wide/ui/window/ui_window_manager.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::widget::ScrollBar);
        COFFEE_Ancestor(ui::widget::Widget);
    COFFEE_EndType();

namespace ui
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ScrollBar::ScrollBar() :
        _Minimum(0),
        _Maximum(255),
        _ScrollPosition(128),
        _ItIsSliding(false),
        _StepSize(0.0f),
        _ControlSize(1),
        _ItIsReversed(true),
        _IncreaseButton(NULL),
        _DecreaseButton(NULL),
        _SlideButton(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    ScrollBar::~ScrollBar()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    uint32 ScrollBar::GetScrollPosition() const
    {
        return _ScrollPosition;
    }

    //--------------------------------------------------------------------------------------------//

    void ScrollBar::SetControlSize(uint32 control_size)
    {
        _ControlSize = control_size;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ScrollBar::Create(Window* parent, const basic::Vector2i& position,
        const basic::Vector2i& size, uint32 style)
    {
        basic::Vector2i real_size(size);

        if(HasExtendedStyle(SCROLL_BAR_STYLE_Horizontal))
            real_size.Y=GetRealScrollSize()+GetBorders().Y*2;
        else if(HasExtendedStyle(SCROLL_BAR_STYLE_Vertical))
            real_size.X=GetRealScrollSize()+GetBorders().X*2;

        Window::Create(parent, position, real_size,
            WINDOW_STYLE_Focusable | WINDOW_STYLE_DrawFrame
            | WINDOW_STYLE_DrawClientSunken);

        SetExtendedStyle(style);

        _IncreaseButton = COFFEE_New(Button);
        _IncreaseButton->Create(this, _MakePosition(
            basic::Vector2i(0, _MakeY(real_size) - _MakeX(real_size))),
            basic::Vector2i(GetScrollSize(), GetScrollSize()), BUTTON_STYLE_Default);
        
        _DecreaseButton = COFFEE_New(Button);
        _DecreaseButton->Create(this, _MakePosition(basic::Vector2i(0, 0)),
            basic::Vector2i(GetScrollSize(), GetScrollSize()), BUTTON_STYLE_Default);
        
        if(HasExtendedStyle(SCROLL_BAR_STYLE_Horizontal))
        {
            _IncreaseButton->SetImage(SKIN_ICON_Right);
            _DecreaseButton->SetImage(SKIN_ICON_Left);
        }
        else
        {
            _IncreaseButton->SetImage(SKIN_ICON_Down);
            _DecreaseButton->SetImage(SKIN_ICON_Up);
        }

        _SlideButton = COFFEE_New(Button);
        _SlideButton->Create(this, _MakePosition(basic::Vector2i(0, _MakeX(real_size))),
            _MakePosition(basic::Vector2i(_MakeX(real_size - GetBorders() * 2),
            _MakeY(real_size - GetBorders() * 2) - _MakeX(real_size))), BUTTON_STYLE_Default);
        
        _UpdateSlider();
    }

    //--------------------------------------------------------------------------------------------//

    void ScrollBar::SetScrollRange(uint32 minimum, uint32 maximum)
    {
        if(maximum < minimum)
            maximum = minimum;

        _Minimum = minimum;
        _Maximum = maximum;
        Clamp(_ScrollPosition, _Minimum, _Maximum);
        _UpdateSlider();
    }

    //--------------------------------------------------------------------------------------------//

    void ScrollBar::SetScrollPosition(uint32 position, bool it_has_to_notify,
        bool it_has_to_update_slider)
    {
        uint32 old_position = _ScrollPosition;

        _ScrollPosition = position;
        Clamp(_ScrollPosition, _Minimum, _Maximum);

        if(it_has_to_update_slider)
            _UpdateSlider(true);

        if(it_has_to_notify && _ScrollPosition!=old_position)
            SendEvent(EVENT_Scroll);
    }

    //--------------------------------------------------------------------------------------------//

    void ScrollBar::Update()
    {
        if(_SlideButton!=NULL && _SlideButton->GetState()==BUTTON_STATE_On)
        {
            if(_ItIsSliding)
            {
                real slide_position;

                if(_StepSize>0.0f)
                {
                    slide_position = (float) _MakePosition(
                        input::Mouse::Get().GetPosition()).Y
                        - _MouseOffset - _MakeX(GetSize());
                    slide_position /= _StepSize;

                    if(!_ItIsReversed)
                        slide_position = _Maximum - slide_position;

                    ClampMinimum(slide_position, 0.0f);
                    SetScrollPosition((uint32) slide_position, true);
                }
            }
            else
            {
                _ItIsSliding = true;
                _MouseOffset = _MakePosition(
                    input::Mouse::Get().GetPosition()).Y
                    - _MakeY(_SlideButton->GetPosition());
            }
        }
        else if(_ItIsSliding)
        {
            _ItIsSliding = false;
        }

        Window::Update();
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(ScrollBar, Widget)
        COFFEE_RegisterEventHandler(input::EVENT_MouseLeftButtonPressed, input::Handler, OnMouseLeftButtonPressed)
        COFFEE_RegisterTargetEventHandler(EVENT_Pressed, Widget, _IncreaseButton, OnIncrease)
        COFFEE_RegisterTargetEventHandler(EVENT_Pressed, Widget, _DecreaseButton, OnDecrease)
        COFFEE_RegisterEventHandler(WINDOW_EVENT_ScrollUp, Window, OnScrollUp)
        COFFEE_RegisterEventHandler(WINDOW_EVENT_ScrollDown, Window, OnScrollDown)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool ScrollBar::OnMouseLeftButtonPressed(shell::Event& event)
    {
        input::EventMouse* parameter = (input::EventMouse*)
            event.GetParameters().GetCustomParameter();

        WindowContext context;
        basic::Vector2i mouse_position;

        context.Create(this);
        mouse_position = parameter->Position-context.GetDesktopWindowRect().GetMinimum();

        if (_MakeX(mouse_position)>=0 && _MakeX(mouse_position)<=_MakeX(GetSize()))
        {
            if (_MakeY(mouse_position)>=_MakeX(GetSize())
                && _MakeY(mouse_position)<=_MakeY(_SlideButton->GetPosition()))
            {
                int32 step;
                int32 new_position;

                step = (_Maximum - _Minimum) / 5;
                ClampMinimum(step, 2);

                if(_ItIsReversed) new_position = _ScrollPosition - step;
                else new_position = _ScrollPosition + step;

                Clamp(new_position, (int32) _Minimum, (int32) _Maximum);
                SetScrollPosition(new_position, true);
            }
            else if (_MakeY(mouse_position)>=_MakeY(_SlideButton->GetPosition())
                + _MakeY(_SlideButton->GetSize())
                && _MakeY(mouse_position)<=_MakeY(GetSize()) - _MakeX(GetSize()))
            {
                int32 step = (_Maximum - _Minimum) / 5;
                int32 new_position = _ScrollPosition + step;

                step = (_Maximum - _Minimum) / 5;
                ClampMinimum(step, 2);

                if (_ItIsReversed) new_position = _ScrollPosition + step;
                else new_position = _ScrollPosition - step;

                Clamp(new_position, (int32) _Minimum, (int32) _Maximum);
                SetScrollPosition(new_position, true);
            }
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool ScrollBar::OnIncrease(shell::Event& event)
    {
        uint32 scroll(1);

        if(_ControlSize == 1)
        {
            scroll = (_Maximum - _Minimum) / 40;
            scroll = Maximum(scroll, (uint32)1);
        }

        if(_ItIsReversed) SetScrollPosition(_ScrollPosition + scroll, true);
        else if(_ScrollPosition >= scroll) SetScrollPosition(_ScrollPosition - scroll, true);
        else SetScrollPosition(0, true);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool ScrollBar::OnDecrease(shell::Event& event)
    {
        uint32 scroll(1);

        if(_ControlSize == 1)
        {
            scroll = (_Maximum - _Minimum) / 40;
            scroll = Maximum(scroll, (uint32)1);
        }

        if(!_ItIsReversed) SetScrollPosition(_ScrollPosition + scroll, true);
        else if(_ScrollPosition >= scroll) SetScrollPosition(_ScrollPosition - scroll, true);
        else SetScrollPosition(0, true);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool ScrollBar::OnScrollUp(shell::Event& event)
    {
        uint32 scroll;

        scroll = (_Maximum - _Minimum) / 20;
        scroll = Maximum(scroll, (uint32)1);

        if(_ScrollPosition >= scroll) SetScrollPosition(_ScrollPosition - scroll, true);
        else SetScrollPosition(0, true);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool ScrollBar::OnScrollDown(shell::Event & event)
    {
        uint32 scroll;

        scroll = (_Maximum - _Minimum) / 20;
        scroll = Maximum(scroll, (uint32)1);

        SetScrollPosition(_ScrollPosition + scroll, true);
        return true;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    int32 ScrollBar::_MakeX(const basic::Vector2i& position) const
    {
        if(HasExtendedStyle(SCROLL_BAR_STYLE_Horizontal))
            return position.Y;
        return position.X;
    }

    //--------------------------------------------------------------------------------------------//

    int32 ScrollBar::_MakeY(const basic::Vector2i& position) const
    {
        if(HasExtendedStyle(SCROLL_BAR_STYLE_Horizontal))
            return position.X;
        return position.Y;
    }

    //--------------------------------------------------------------------------------------------//

    basic::Vector2i ScrollBar::_MakePosition(const basic::Vector2i& position) const
    {
        if(HasExtendedStyle(SCROLL_BAR_STYLE_Horizontal))
            return basic::Vector2i(position.Y, position.X);
        return position;
    }

    //--------------------------------------------------------------------------------------------//

    basic::Vector2 ScrollBar::_MakePosition(const basic::Vector2& position) const
    {
        if(HasExtendedStyle(SCROLL_BAR_STYLE_Horizontal))
            return basic::Vector2(position.Y, position.X);
        return position;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ScrollBar::_UpdateSlider(bool it_comes_from_set_scroll_pos, bool it_has_to_set_position)
    {
        basic::Vector2i slider_position;
        basic::Vector2i slider_size;
        int32 scroll_position;

        if(_SlideButton == NULL)
            return;

        if(_ItIsReversed) scroll_position = _ScrollPosition;
        else scroll_position = _Maximum - _ScrollPosition;

        if(_Maximum>_Minimum)
        {
            _StepSize = (_MakeY(GetSize()) * (GetScrollSize() + GetBorders().X * 2.0f + 1.0f))
                / ((_Maximum - _Minimum) * _ControlSize);
            if (_StepSize > (_MakeY(GetSize()) - _MakeX(GetSize()) * 2.0f) * 0.8f)
                _StepSize = (_MakeY(GetSize()) - _MakeX(GetSize()) * 2.0f) * 0.8f;
            slider_size=(_MakePosition(basic::Vector2i(_MakeX(GetSize() - GetBorders() * 2),
                (uint32) Maximum(5.0f, _StepSize))));
            _StepSize = (_MakeY(GetSize()) - _MakeX(GetSize()) * 2.0f - _MakeY(slider_size))
                / ((float) _Maximum - _Minimum);
            slider_position=(_MakePosition(basic::Vector2i(0, (uint32)(_MakeX(GetSize())
                + scroll_position * _StepSize - 1))));
        }
        else
        {
            slider_position=(_MakePosition(basic::Vector2i(0, _MakeX(GetSize()))));
            slider_size=(_MakePosition(basic::Vector2i(_MakeX(GetSize() - GetBorders() * 2),
                _MakeY(GetSize() - GetBorders() * 2) - _MakeX(GetSize()) * 2)));
        }

        if(it_has_to_set_position
            && (_MakeY(slider_position) < _MakeY(_DecreaseButton->GetPosition())
            + _MakeY(_DecreaseButton->GetSize()) + 1))
        {
            SetScrollPosition(0, !it_comes_from_set_scroll_pos, !it_comes_from_set_scroll_pos);
        }

        _SlideButton->SetPosition(slider_position);
        _SlideButton->SetSize(slider_size);
    }

    //--------------------------------------------------------------------------------------------//

    void ScrollBar::_UpdateClientArea()
    {
        Window::_UpdateClientArea();

        if(_IncreaseButton != NULL)
        {
            _IncreaseButton->SetPosition(_MakePosition(
                basic::Vector2i(0, _MakeY(GetSize()) - _MakeX(GetSize()))));
            _IncreaseButton->SetSize(basic::Vector2i(GetScrollSize(), GetScrollSize()));
        }

        if(_DecreaseButton != NULL)
        {
            _DecreaseButton->SetPosition(_MakePosition(basic::Vector2i(0, 0)));
            _DecreaseButton->SetSize(basic::Vector2i(GetScrollSize(), GetScrollSize()));
        }

        _UpdateSlider(true, false);
    }

}
}
}
