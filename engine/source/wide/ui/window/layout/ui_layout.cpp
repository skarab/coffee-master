#include "wide/ui/window/layout/ui_layout.h"
#include "wide/ui/window/ui_window.h"
#include "wide/ui/widget/widget.h"

namespace coffee
{
namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Layout::Layout() :
        _Window(NULL),
        _Style(LAYOUT_STYLE_Default),
        _Index(NONE),
        _Size(0.0f),
        _ItIsPercentage(false),
        _ItIsValid(false)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Layout::~Layout()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Layout::SetWindow(Window& window)
    {
        _Window = &window;
    }

    //--------------------------------------------------------------------------------------------//

    const Window& Layout::GetWindow() const
    {
        return *_Window;
    }

    //--------------------------------------------------------------------------------------------//

    Window& Layout::GetWindow()
    {
        return *_Window;
    }

    //--------------------------------------------------------------------------------------------//

    void Layout::SetStyle(uint32 style)
    {
        _Style = style;
    }

    //--------------------------------------------------------------------------------------------//

    uint32 Layout::GetStyle() const
    {
        return _Style;
    }

    //--------------------------------------------------------------------------------------------//

    bool Layout::HasStyle(const LAYOUT_STYLE& style) const
    {
        return ((_Style & (uint32)style) > 0);
    }

    //--------------------------------------------------------------------------------------------//

    void Layout::SetMinimumSize(const basic::Vector2i& minimum_size)
    {
        _MinimumSize = minimum_size;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Vector2i& Layout::GetMinimumSize() const
    {
        return _MinimumSize;
    }

    //--------------------------------------------------------------------------------------------//

    void Layout::SetCanvas(real canvas_size, bool it_is_in_percentage)
    {
        _Size = Maximum(canvas_size, 0.0f);
        _ItIsPercentage = it_is_in_percentage;
        _ItIsValid = true;
    }

    //--------------------------------------------------------------------------------------------//

    void Layout::SetCanvas(int32 canvas_size, bool it_is_in_percentage)
    {
        SetCanvas((real)canvas_size, it_is_in_percentage);
    }

    //-QUERIES------------------------------------------------------------------------------------//

    basic::Vector2i Layout::ComputeWindowSize() const
    {
        basic::Vector2i size;
        uint32 child_index;
        Window* child_window;
        basic::Vector2i borders(GetWindow().GetSize() - GetWindow().GetClientRect().Size);

        size.Set(Maximum(borders.X, _MinimumSize.X), Maximum(borders.Y, _MinimumSize.Y));

        if (HasStyle(LAYOUT_STYLE_Shrink))
        {
            for (child_index=0 ; child_index<GetWindow().GetChildCount() ; ++child_index)
            {
                child_window = (Window*)&GetWindow().GetChild(child_index);
                if (child_window->GetLayout()._IsWindowUsed())
                {
                    if (HasStyle(LAYOUT_STYLE_HorizontalShrink))
                        size.X=Maximum(size.X, child_window->GetPosition().X + child_window->GetSize().X + borders.X);

                    if (HasStyle(LAYOUT_STYLE_VerticalShrink))
                        size.Y=Maximum(size.Y, child_window->GetPosition().Y + child_window->GetSize().Y + borders.Y);
                }
            }
        }

        if (HasStyle(LAYOUT_STYLE_HorizontalExpand))
            size.X=Maximum(size.X, GetWindow().GetParentWindow().GetClientRect().Size.X - GetWindow().GetPosition().X);

        if (HasStyle(LAYOUT_STYLE_VerticalExpand))
            size.Y=Maximum(size.Y, GetWindow().GetParentWindow().GetClientRect().Size.Y - GetWindow().GetPosition().Y);

        return size;
    }

    //--------------------------------------------------------------------------------------------//

    basic::Vector2i Layout::GetValidSize(const basic::Vector2i& size) const
    {
        return basic::Vector2i(
            size.X<_MinimumSize.X?_MinimumSize.X:size.X,
            size.Y<_MinimumSize.Y?_MinimumSize.Y:size.Y);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Layout::Update()
    {
        if (HasStyle(LAYOUT_STYLE_StickChildren))
        {
            if (HasStyle(LAYOUT_STYLE_HorizontalCanvas)
                || HasStyle(LAYOUT_STYLE_VerticalCanvas))
            {
                _AdjustCanvas();
            }
        }

        _AdjustSize();
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    void Layout::OnShow(bool it_is_visible)
    {
        if (it_is_visible)
        {
            if (_Window->HasParent()
                && !_Window->HasStyle(ui::WINDOW_STYLE_NoParentClientClip)
                && !_Window->HasStyle(ui::WINDOW_STYLE_NoParentClip)
                && _Index==NONE)
            {
                uint32 unused_count=0;
                for (uint32 i=0 ; i<_Window->GetParentWindow().GetChildCount() ; ++i)
                {
                    const Window& child = _Window->GetParentWindow().GetChildWindow(i);
                    if (&child==_Window || !child.GetLayout()._IsWindowUsed())
                        ++unused_count;
                }
                _Index = _Window->GetParentWindow().GetChildCount()-unused_count;

                if (_Window->GetParentWindow().GetLayout().HasStyle(LAYOUT_STYLE_Sort))
                {
                    uint32 index = NONE;
                    for (uint32 i=0 ; i<_Window->GetParentWindow().GetChildCount() ; ++i)
                    {
                        const Window& child = _Window->GetParentWindow().GetChildWindow(i);                
                        if (&child!=_Window && child.GetLayout()._IsWindowUsed()
                            && index>child.GetLayout()._Index
                            && _Window->GetParentWindow().Sort(*_Window, child))
                        {
                            index = child.GetLayout()._Index;
                        }
                    }
                    if (index!=NONE)
                    {
                        _Index = index;
                        for (uint32 i=0 ; i<_Window->GetParentWindow().GetChildCount() ; ++i)
                        {
                            Window& child = _Window->GetParentWindow().GetChildWindow(i);                
                            if (&child!=_Window && child.GetLayout()._IsWindowUsed()
                                && child.GetLayout()._Index>=index)
                            {
                                ++child.GetLayout()._Index;
                            }
                        }
                    }
                }
            }
        }
        else
        {
            if (_Window->HasParent()
                && !_Window->HasStyle(ui::WINDOW_STYLE_NoParentClientClip)
                && !_Window->HasStyle(ui::WINDOW_STYLE_NoParentClip)
                && _Index!=NONE)
            {
                for (uint32 i=0 ; i<_Window->GetParentWindow().GetChildCount() ; ++i)
                {
                    Window& child = _Window->GetParentWindow().GetChildWindow(i);
                    if (child.GetLayout()._IsWindowUsed() && child.GetLayout()._Index>_Index)
                        --child.GetLayout()._Index;
                }
                _Index = NONE;
            }
        }
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool Layout::_IsWindowUsed() const
    {
        return !_Window->IsDestroyed()
            && !_Window->HasStyle(WINDOW_STYLE_NoParentClientClip)
            && !_Window->HasStyle(WINDOW_STYLE_NoParentClip)
            && _Index!=NONE;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Layout::_AdjustSize()
    {
        if (HasStyle(LAYOUT_STYLE_Shrink) || HasStyle(LAYOUT_STYLE_Expand))
        {
            basic::Vector2i window_size = _Window->GetSize();
            basic::Vector2i size = ComputeWindowSize();

            if (HasStyle(LAYOUT_STYLE_HorizontalShrink)
                || HasStyle(LAYOUT_STYLE_HorizontalExpand))
            {
                window_size.X = size.X;
            }

            if (HasStyle(LAYOUT_STYLE_VerticalShrink)
                || HasStyle(LAYOUT_STYLE_VerticalExpand))
            {
                window_size.Y = size.Y;
            }
    
            GetWindow().SetSize(window_size);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Layout::_AdjustCanvas()
    {
        // Sort children using canvas indices, and compute available size for percentage sizes...

        basic::Prow< Window* > sorted_windows;
        sorted_windows.Reserve(_Window->GetChildCount());
        uint32 unused = 0;
        int32 available_size = HasStyle(LAYOUT_STYLE_HorizontalCanvas)?
            _Window->GetClientRect().Size.X:_Window->GetClientRect().Size.Y;
        real total_percentage = 0.0f;

        for (uint32 i=0 ; i<_Window->GetChildCount() ; ++i)
        {
            Window* window(NULL);
            unused = 0;
            for (uint32 j=0 ; j<_Window->GetChildCount() ; ++j)
            {
                Window& child = _Window->GetChildWindow(j);
                if (child.GetLayout()._IsWindowUsed())
                {
                    if (child.GetLayout()._Index==i)
                    {
                        window = &child;
                        if (child.GetLayout()._ItIsValid)
                        {
                            if (child.GetLayout()._ItIsPercentage)
                            {
                                total_percentage += child.GetLayout()._Size;
                            }
                            else
                            {
                                available_size -= (int32)child.GetLayout()._Size;
                            }
                        }
                        else
                        {
                            available_size -= HasStyle(LAYOUT_STYLE_HorizontalCanvas)?
                                child.GetSize().X:child.GetSize().Y;
                        }
                        break;
                    }
                }
                else
                {
                    ++unused;
                }
            }
            if (i>=_Window->GetChildCount()-unused)
                break;

            COFFEE_Assert(window!=NULL, core::ERROR_CODE_WindowManager, "Broken layout detected!");
            sorted_windows.AddItem(window);
        }

        // Apply canvas sizes

        available_size = Maximum(available_size, 0);
        int32 position = 0;
        for (uint32 i=0 ; i<sorted_windows.GetSize() ; ++i)
        {
            Window& child = *sorted_windows[i];

            if (child.GetLayout()._ItIsValid)
            {
                int32 size = (int32)child.GetLayout()._Size;
                if (child.GetLayout()._ItIsPercentage)
                {
                    COFFEE_Assert(total_percentage>0.0f, core::ERROR_CODE_WindowManager, "Broken layout detected!");
                    size = (int32)(available_size*child.GetLayout()._Size/total_percentage);
                }
                
                if (size!=(HasStyle(LAYOUT_STYLE_HorizontalCanvas)?child.GetSize().X:child.GetSize().Y))
                {
                    child.SetSize(HasStyle(LAYOUT_STYLE_HorizontalCanvas)?
                        basic::Vector2i(size, child.GetSize().Y):
                        basic::Vector2i(child.GetSize().X, size));
                }
            }

            child.SetPosition(HasStyle(LAYOUT_STYLE_HorizontalCanvas)?
                basic::Vector2i(position, child.GetPosition().Y):
                basic::Vector2i(child.GetPosition().X, position));
            position += HasStyle(LAYOUT_STYLE_HorizontalCanvas)?
                child.GetSize().X+1:
                child.GetSize().Y+1;
        }
    }

}
}
