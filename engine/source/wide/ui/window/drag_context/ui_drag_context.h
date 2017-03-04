#ifndef _COFFEE_UI_DRAG_CONTEXT_H_
#define _COFFEE_UI_DRAG_CONTEXT_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/window/ui_window.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// UI Cursor
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API DragContext
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        DragContext();
        DragContext(Window* window, const basic::Vector2i& position,
            const basic::Vector2i& window_position, const basic::Vector2i& window_size);
        ~DragContext();

        //-ACCESSORS------------------------------------------------------------------------------//

        const Window& GetWindow() const;
        Window& GetWindow();
        const basic::Vector2i& GetPosition() const;
        const basic::Vector2i& GetWindowPosition() const;
        const basic::Vector2i& GetWindowSize() const;

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Window* _Window;
        basic::Vector2i _Position;
        basic::Vector2i _WindowPosition;
        basic::Vector2i _WindowSize;
    };
}
}
#endif
