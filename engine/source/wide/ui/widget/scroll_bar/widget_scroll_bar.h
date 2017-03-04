#ifndef _COFFEE_UI_WIDGET_SCROLL_BAR_H_
#define _COFFEE_UI_WIDGET_SCROLL_BAR_H_

#include "coffee_includes.h"
#include "wide/ui/widget/widget.h"
#include "wide/ui/widget/scroll_bar/widget_scroll_bar_style.h"
#include "wide/ui/widget/button/widget_button.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// ScrollBar widget
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ScrollBar : public Widget
    {
        COFFEE_Type(ScrollBar);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ScrollBar();
        ~ScrollBar();

        //-ACCESSORS------------------------------------------------------------------------------//

        uint32 GetScrollPosition() const;
        void SetControlSize(uint32 control_size);
        uint32 GetMinimum() const { return _Minimum; }
        uint32 GetMaximum() const { return _Maximum; }

        //-OPERATIONS-----------------------------------------------------------------------------//

        void SetScrollRange(uint32 minimum, uint32 maximum);
        void SetScrollPosition(uint32 position, bool it_has_to_notify=false,
            bool it_has_to_update_slider=true);
        void Create(Window* parent, const basic::Vector2i& position,
            const basic::Vector2i& size, uint32 style=SCROLL_BAR_STYLE_Default);
        void Update();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(ScrollBar);
        COFFEE_Event bool OnMouseLeftButtonPressed(shell::Event& event);
        COFFEE_Event bool OnIncrease(shell::Event& event);
        COFFEE_Event bool OnDecrease(shell::Event& event);
        COFFEE_Event bool OnScrollUp(shell::Event& event);
        COFFEE_Event bool OnScrollDown(shell::Event& event);
        
    private:

        //-QUERIES--------------------------------------------------------------------------------//

        int32 _MakeX(const basic::Vector2i& position) const;
        int32 _MakeY(const basic::Vector2i& position) const;
        basic::Vector2i _MakePosition(const basic::Vector2i& position) const;
        basic::Vector2 _MakePosition(const basic::Vector2& position) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _UpdateSlider(bool it_comes_from_set_scroll_pos=false,
            bool it_has_to_set_position=true);
        virtual void _UpdateClientArea();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Button* _IncreaseButton;
        Button* _DecreaseButton;
        Button* _SlideButton;
        uint32 _Minimum;
        uint32 _Maximum;
        uint32 _ScrollPosition;
        uint32 _ControlSize;
        bool _ItIsSliding;
        bool _ItIsReversed;
        real _MouseOffset;
        real _StepSize;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ScrollBar);
}
}
}
#endif
