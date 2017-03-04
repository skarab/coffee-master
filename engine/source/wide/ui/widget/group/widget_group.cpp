//------------------------------------------------------------------------------------------------//
/// @file wide/ui/widget/group/widget_group.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "wide/ui/widget/group/widget_group.h"
#include "wide/ui/window/ui_window_context.h"
#include "wide/ui/window/ui_window_manager.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::widget::Group);
        COFFEE_Ancestor(ui::widget::Widget);
    COFFEE_EndType();

namespace ui
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Group::Group() :
        _Button(NULL),
        _Height(0),
        _ItIsOpen(true),
        _ItIsSliding(false),
        _SlideTime(0.1f)
    {
        _TitleBarHeight = 12;
    }

    //--------------------------------------------------------------------------------------------//

    Group::~Group()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Group::SetTitleBarText(const basic::String& title_bar_text)
    {
        _TitleBarText = title_bar_text;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::String& Group::GetTitleBarText()
    {
        return _TitleBarText;
    }

    //--------------------------------------------------------------------------------------------//

    int32 Group::GetTitleBarHeight() const
    {
        return _TitleBarHeight;
    }

    //--------------------------------------------------------------------------------------------//

    const Button& Group::GetGrooveButton() const
    {
        return *_Button;
    }

    //--------------------------------------------------------------------------------------------//

    Button& Group::GetGrooveButton()
    {
        return *_Button;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Group::Create(Window* parent, const basic::Vector2i& position,
        const basic::Vector2i& size, uint32 style)
    {
        _Height = size.Y;

        Window::Create(parent, position, size,
            WINDOW_STYLE_Activable | WINDOW_STYLE_DrawFrame
            | WINDOW_STYLE_DrawClientSunken);

        SetExtendedStyle(style);

        if(HasExtendedStyle(GROUP_STYLE_VerticalShrink))
        {
            GetLayout().SetStyle(LAYOUT_STYLE_VerticalCanvas
                | LAYOUT_STYLE_VerticalShrink
                | LAYOUT_STYLE_StickChildren
                | LAYOUT_STYLE_HorizontalExpand);
        }
        else
        {
            GetLayout().SetStyle(LAYOUT_STYLE_VerticalCanvas
                | LAYOUT_STYLE_StickChildren
                | LAYOUT_STYLE_HorizontalExpand);
        }

        SetTitleBarText(basic::String("Groove"));

        _Button = COFFEE_New(Button);
        _Button->Create(this, basic::Vector2i(),
            basic::Vector2i(_TitleBarHeight, _TitleBarHeight), BUTTON_STYLE_Default);
        _Button->SetStyle(_Button->GetStyle()
            | (uint32) WINDOW_STYLE_NoParentClientClip);
        _Button->SetImage(SKIN_ICON_GroupOn);
        _Button->SetHelpText(basic::String("Show/hide"));
    }

    //--------------------------------------------------------------------------------------------//

    void Group::Update()
    {
        if(_ItIsSliding)
        {
            basic::Rectangle rect;
            int32 real_height;
            real translation;
            int32 height;

            if(HasExtendedStyle(GROUP_STYLE_VerticalShrink))
            {
                GetLayout().SetStyle(LAYOUT_STYLE_VerticalCanvas
                    | LAYOUT_STYLE_VerticalShrink
                    | LAYOUT_STYLE_StickChildren
                    | LAYOUT_STYLE_HorizontalExpand);
                real_height = GetLayout().ComputeWindowSize().Y;
                GetLayout().SetStyle(LAYOUT_STYLE_VerticalCanvas
                    | LAYOUT_STYLE_HorizontalExpand);
            }
            else
            {
                real_height = _Height;
            }

            translation = input::Module::Get().GetTimeStep().GetSecondCount()
                * real_height / _SlideTime.GetSecondCount();
            
            if(_ItIsOpen)
            {
                _AnimatedHeight += translation;
                height = (int32) _AnimatedHeight;

                if(height >= real_height)
                {
                    height = real_height;
                    _ItIsSliding = false;
                    _Button->SetImage(SKIN_ICON_GroupOn);

                    if(HasExtendedStyle(GROUP_STYLE_VerticalShrink))
                    {
                        GetLayout().SetStyle(LAYOUT_STYLE_VerticalCanvas
                            | LAYOUT_STYLE_VerticalShrink
                            | LAYOUT_STYLE_StickChildren
                            | LAYOUT_STYLE_HorizontalExpand);
                    }
                }
            }
            else
            {
                _AnimatedHeight -= translation;
                height = (int32) _AnimatedHeight;

                if(height <= (int32)(_TitleBarHeight + 2 * GetBorders().Y))
                {
                    height = (int32)(_TitleBarHeight + 2 * GetBorders().Y);
                    _ItIsSliding = false;
                    _Button->SetImage(SKIN_ICON_GroupOff);
                }
            }

            SetSize(basic::Vector2i(GetSize().X, height));
        }

        Window::Update();
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(Group, Widget)
        COFFEE_RegisterTargetEventHandler(EVENT_Pressed, Widget, _Button, OnGroove)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool Group::OnGroove(shell::Event& event)
    {
        if(!_ItIsSliding)
        {
            if(HasExtendedStyle(GROUP_STYLE_VerticalShrink))
            {
                GetLayout().SetStyle(LAYOUT_STYLE_VerticalCanvas
                    | LAYOUT_STYLE_HorizontalExpand);
            }

            _ItIsOpen = !_ItIsOpen;
            _ItIsSliding = true;
            _AnimatedHeight = (real) GetRect().Size.Y;
        }

        return true;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Group::_UpdateClientArea()
    {
        basic::Rectangle client_rect;

        Window::_UpdateClientArea();

        client_rect = GetClientRect();

        client_rect.Position = basic::Vector2i(
            client_rect.Position.X,
            client_rect.Position.Y + _TitleBarHeight + GetBorders().Y);
        client_rect.Size = basic::Vector2i(
            client_rect.Size.X,
            client_rect.Size.Y - _TitleBarHeight - GetBorders().Y);

        if (_Button != NULL)
        {
            _Button->SetPosition(basic::Vector2i(
                client_rect.Size.X - _TitleBarHeight + GetBorders().X / 2,
                - _TitleBarHeight - GetBorders().Y));
        }

        _SetClientRect(client_rect);
    }

}
}
}
//------------------------------------------------------------------------------------------------//
