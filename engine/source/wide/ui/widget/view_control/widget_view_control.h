#ifndef _COFFEE_UI_WIDGET_VIEW_CONTROL_H_
#define _COFFEE_UI_WIDGET_VIEW_CONTROL_H_

#include "coffee_includes.h"
#include "wide/ui/widget/widget.h"
#include "wide/ui/widget/scroll_bar/widget_scroll_bar.h"
#include "wide/ui/widget/view_control/widget_view_container.h"
#include "wide/ui/widget/view_control/widget_view_control_style.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// ViewControl widget
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ViewControl : public Widget
    {
        COFFEE_Type(ViewControl);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ViewControl();
        virtual ~ViewControl();

        //-ACCESSORS------------------------------------------------------------------------------//

        const ViewContainer& GetContainer() const;
        ViewContainer& GetContainer();

        //-QUERIES--------------------------------------------------------------------------------//

        bool HasContainer() const;
        
        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void Create(Window* parent, const basic::Vector2i& position,
            const basic::Vector2i& size, uint32 style=VIEW_CONTROL_STYLE_Default);
        void ResetContainer();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(ViewControl);
        COFFEE_Event bool OnHorizontalScroll(shell::Event& event);
        COFFEE_Event bool OnVerticalScroll(shell::Event& event);

    protected:

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void _UpdateClientArea();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _UpdateScrollBars();
        void _RepositionScrollBars();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        ViewContainer* _Container;
        ScrollBar* _VerticalScrollBar;
        ScrollBar* _HorizontalScrollBar;
        basic::Vector2i _ScrollPosition;
        uint32 _ScrollBarSize;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ViewControl);
}
}
}
#endif
