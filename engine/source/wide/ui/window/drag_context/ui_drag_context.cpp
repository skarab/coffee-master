//------------------------------------------------------------------------------------------------//
/// @file wide/ui/window/drag_context/ui_drag_context.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "wide/ui/window/drag_context/ui_drag_context.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    DragContext::DragContext()
    {
    }

    //--------------------------------------------------------------------------------------------//

    DragContext::DragContext(Window* window, const basic::Vector2i& position,
        const basic::Vector2i& window_position, const basic::Vector2i& window_size) :
        _Window(window),
        _Position(position),
        _WindowPosition(window_position),
        _WindowSize(window_size)
    {
    }

    //--------------------------------------------------------------------------------------------//

    DragContext::~DragContext()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const Window& DragContext::GetWindow() const
    {
        return *_Window;
    }

    //--------------------------------------------------------------------------------------------//

    Window& DragContext::GetWindow()
    {
        return *_Window;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Vector2i& DragContext::GetPosition() const
    {
        return _Position;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Vector2i& DragContext::GetWindowPosition() const
    {
        return _WindowPosition;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Vector2i& DragContext::GetWindowSize() const
    {
        return _WindowSize;
    }

}
}
//------------------------------------------------------------------------------------------------//
