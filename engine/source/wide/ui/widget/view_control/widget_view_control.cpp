#include "wide/ui/widget/view_control/widget_view_control.h"
#include "wide/ui/window/ui_window_manager.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::widget::ViewControl);
        COFFEE_Ancestor(ui::widget::Widget);
    COFFEE_EndType();

namespace ui
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ViewControl::ViewControl() :
        _Container(NULL),
        _HorizontalScrollBar(NULL),
        _VerticalScrollBar(NULL)
    {
        _ScrollBarSize = GetScrollSize() + 2;
    }

    //--------------------------------------------------------------------------------------------//

    ViewControl::~ViewControl()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const ViewContainer& ViewControl::GetContainer() const
    {
        return *_Container;
    }

    //--------------------------------------------------------------------------------------------//

    ViewContainer& ViewControl::GetContainer()
    {
        return *_Container;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool ViewControl::HasContainer() const
    {
        return _Container!=NULL;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ViewControl::Create(Window* parent, const basic::Vector2i& position,
        const basic::Vector2i& size, uint32 style)
    {
        Window::Create(parent, position, size, WINDOW_STYLE_Focusable);
        SetExtendedStyle(style);

        _VerticalScrollBar = COFFEE_New(ScrollBar);
        _VerticalScrollBar->Create(this, basic::Vector2i(), basic::Vector2i(),
            SCROLL_BAR_STYLE_Vertical);
        _VerticalScrollBar->SetStyle(_VerticalScrollBar->GetStyle()
            | (uint32) WINDOW_STYLE_NoParentClientClip);
        _VerticalScrollBar->SetScrollPosition(0);

        _HorizontalScrollBar = COFFEE_New(ScrollBar);
        _HorizontalScrollBar->Create(this, basic::Vector2i(), basic::Vector2i(),
            SCROLL_BAR_STYLE_Horizontal);
        _HorizontalScrollBar->SetStyle(_HorizontalScrollBar->GetStyle()
            | (uint32) WINDOW_STYLE_NoParentClientClip);
        _HorizontalScrollBar->SetScrollPosition(0);

        _ScrollPosition = 0;

        _Container = COFFEE_New(ViewContainer);
        _Container->Create(this, basic::Vector2i(), basic::Vector2i());

        _Container->GetLayout().SetStyle(LAYOUT_STYLE_VerticalCanvas
            | LAYOUT_STYLE_VerticalShrink
            | LAYOUT_STYLE_HorizontalExpand
            | LAYOUT_STYLE_StickChildren);

        if (HasExtendedStyle(VIEW_CONTROL_STYLE_SortAscending)
            || HasExtendedStyle(VIEW_CONTROL_STYLE_SortDescending))
        {
            _Container->GetLayout().SetStyle(_Container->GetLayout().GetStyle()|LAYOUT_STYLE_Sort);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void ViewControl::ResetContainer()
    {
        _Container->SetPosition(basic::Vector2i());
        _Container->SetSize(basic::Vector2i());
        _ScrollPosition = 0;
        _VerticalScrollBar->SetScrollPosition(0);
        _HorizontalScrollBar->SetScrollPosition(0);
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(ViewControl, Widget)
        COFFEE_RegisterTargetEventHandler(EVENT_Scroll, Widget, _HorizontalScrollBar, OnHorizontalScroll)
        COFFEE_RegisterTargetEventHandler(EVENT_Scroll, Widget, _VerticalScrollBar, OnVerticalScroll)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool ViewControl::OnHorizontalScroll(shell::Event& event)
    {
        _UpdateClientArea();
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool ViewControl::OnVerticalScroll(shell::Event& event)
    {
        _UpdateClientArea();
        return true;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ViewControl::_UpdateClientArea()
    {
        basic::Rectangle client_rect;
        basic::Vector2i offset(_ScrollBarSize, _ScrollBarSize);

        Window::_UpdateClientArea();
        _UpdateScrollBars();

        if (_HorizontalScrollBar==NULL || !_HorizontalScrollBar->IsVisible())
            offset.Y=0;

       if (_VerticalScrollBar==NULL || !_VerticalScrollBar->IsVisible())
            offset.X=0;

        client_rect = GetClientRect();
        client_rect.Position = basic::Vector2i(1, 1);

        client_rect.Size = basic::Vector2i(
            GetSize().X - offset.X - GetBorders().X * 2 - 1,
            GetSize().Y - offset.Y - GetBorders().Y * 2 - 1);

        _SetClientRect(client_rect);
        _RepositionScrollBars();
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ViewControl::_UpdateScrollBars()
    {
        if (_Container==NULL || _VerticalScrollBar==NULL || _HorizontalScrollBar==NULL)
            return;

        int32 client_size_x, client_size_y;
        client_size_y = _Container->GetSize().Y - (GetRect().Size.Y-GetBorders().Y*2);
        client_size_y = Maximum(client_size_y, 0);
        client_size_y = Maximum(client_size_y, _ScrollPosition.Y);

        client_size_x = _Container->GetSize().X - (GetRect().Size.X-GetBorders().X*2);
        client_size_x = Maximum(client_size_x, 0);
        client_size_x = Maximum(client_size_x, _ScrollPosition.X);

        if(client_size_x != 0)
        {
            client_size_y = _Container->GetSize().Y
                - (GetRect().Size.Y-GetBorders().Y*2-_ScrollBarSize);
            client_size_y = Maximum(client_size_y, 0);
            client_size_y = Maximum(client_size_y, _ScrollPosition.Y);
        }

        if(client_size_y != 0)
        {
            client_size_x = _Container->GetSize().X
                - (GetRect().Size.X-GetBorders().X*2-_ScrollBarSize);
            client_size_x = Maximum(client_size_x, 0);
            client_size_x = Maximum(client_size_x, _ScrollPosition.X);

            if(client_size_x != 0)
            {
                client_size_y = _Container->GetSize().Y
                    - (GetRect().Size.Y-GetBorders().Y*2-_ScrollBarSize);
                client_size_y = Maximum(client_size_y, 0);
                client_size_y = Maximum(client_size_y, _ScrollPosition.Y);
            }
        }

        _VerticalScrollBar->SetScrollRange(0, client_size_y);

        if(client_size_y == 0)
        {
            if(_VerticalScrollBar->IsEnabled())
            {
                _VerticalScrollBar->Enable(false);

                if(!HasExtendedStyle(VIEW_CONTROL_STYLE_AlwaysShowVScrollBar))
                    _VerticalScrollBar->Show(false);
            }
        }
        else
        {
            if(!_VerticalScrollBar->IsEnabled())
            {
                _VerticalScrollBar->Enable(true);
                if(!HasExtendedStyle(VIEW_CONTROL_STYLE_AlwaysShowVScrollBar))
                    _VerticalScrollBar->Show(true);
            }
        }

        _ScrollPosition.Y=_VerticalScrollBar->GetScrollPosition();

        _Container->SetPosition(basic::Vector2i(
            _Container->GetPosition().X, -_ScrollPosition.Y));
    
        _HorizontalScrollBar->SetScrollRange(0, client_size_x);

        if(client_size_x == 0)
        {
            if(_HorizontalScrollBar->IsEnabled())
            {
                _HorizontalScrollBar->Enable(false);

                if(!HasExtendedStyle(VIEW_CONTROL_STYLE_AlwaysShowHScrollBar))
                    _HorizontalScrollBar->Show(false);
            }
        }
        else
        {
            if(!_HorizontalScrollBar->IsEnabled())
            {
                _HorizontalScrollBar->Enable(true);
                if(!HasExtendedStyle(VIEW_CONTROL_STYLE_AlwaysShowHScrollBar))
                    _HorizontalScrollBar->Show(true);
            }
        }

        _ScrollPosition.X=(_HorizontalScrollBar->GetScrollPosition());

        _Container->SetPosition(basic::Vector2i(
            -_ScrollPosition.X, _Container->GetPosition().Y));
    }

    //--------------------------------------------------------------------------------------------//

    void ViewControl::_RepositionScrollBars()
    {
        if(_VerticalScrollBar!=NULL && _HorizontalScrollBar!=NULL)
        {
            _VerticalScrollBar->SetPosition(basic::Vector2i(GetClientRect().Size.X, 0));
            _VerticalScrollBar->SetSize(basic::Vector2i(
                _ScrollBarSize, GetClientRect().Size.Y));

            _HorizontalScrollBar->SetPosition(basic::Vector2i(0, GetClientRect().Size.Y));
            _HorizontalScrollBar->SetSize(basic::Vector2i(
                GetClientRect().Size.X, _ScrollBarSize));
        }
    }

}
}
}
