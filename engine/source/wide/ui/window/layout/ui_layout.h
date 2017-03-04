#ifndef _COFFEE_UI_LAYOUT_H_
#define _COFFEE_UI_LAYOUT_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "wide/ui/window/layout/ui_layout_style.h"

namespace coffee
{
namespace ui
{
    //-FORWARDS-----------------------------------------------------------------------------------//

    class Window;

    //--------------------------------------------------------------------------------------------//
    /// Window Layout class
    ///
    /// Each window own his own Layout instance. Disabled by default, it can automatically sort
    /// and move/resize window or children depending of the flags set. Performing various
    /// operation as Shrink to content, Expand, sort and stick children ...
    ///
    /// @see coffee::ui::LAYOUT_STYLE, coffee::ui::LayoutCanvas
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Layout
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Layout();
        ~Layout();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetWindow(Window& window);
        const Window& GetWindow() const;
        Window& GetWindow();
        void SetStyle(uint32 style);
        uint32 GetStyle() const;
        bool HasStyle(const LAYOUT_STYLE& style) const;
        void SetMinimumSize(const basic::Vector2i& minimum_size);
        const basic::Vector2i& GetMinimumSize() const;
        void SetCanvas(real canvas_size, bool it_is_in_percentage);
        void SetCanvas(int32 canvas_size, bool it_is_in_percentage);
        
        //-QUERIES--------------------------------------------------------------------------------//

        basic::Vector2i ComputeWindowSize() const;
        basic::Vector2i GetValidSize(const basic::Vector2i& size) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Update();
        
        //-HANDLERS-------------------------------------------------------------------------------//

        void OnShow(bool it_is_visible);

    private:

        //-QUERIES--------------------------------------------------------------------------------//

        bool _IsWindowUsed() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _AdjustSize();
        void _AdjustCanvas();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Window* _Window;
        uint32 _Style;
        basic::Vector2i _MinimumSize;
        uint32 _Index;
        real _Size;
        bool _ItIsPercentage;
        bool _ItIsValid;
    };
}
}
#endif
