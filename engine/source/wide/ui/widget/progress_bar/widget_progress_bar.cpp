//------------------------------------------------------------------------------------------------//
/// @file wide/ui/widget/progress_bar/widget_progress_bar.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "wide/ui/widget/progress_bar/widget_progress_bar.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::widget::ProgressBar);
        COFFEE_Ancestor(ui::widget::Widget);
    COFFEE_EndType();

namespace ui
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ProgressBar::ProgressBar() :
        _Percentage(0.0f)
    {
    }

    //--------------------------------------------------------------------------------------------//

    ProgressBar::~ProgressBar()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void ProgressBar::SetPercentage(real percentage)
    {
        _Percentage = percentage;
        Clamp(_Percentage, 0.0f, 1.0f);
    }

    //--------------------------------------------------------------------------------------------//

    real ProgressBar::GetPercentage() const
    {
        return _Percentage;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ProgressBar::Create(Window* parent, const basic::Vector2i& position,
        const basic::Vector2i& size, uint32 style)
    {
        Window::Create(parent, position, size,
            WINDOW_STYLE_DrawFrame | WINDOW_STYLE_DrawClientSunken);
        SetExtendedStyle(style);
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(ProgressBar, Widget)
    COFFEE_EndEventHandler()

}
}
}
//------------------------------------------------------------------------------------------------//
