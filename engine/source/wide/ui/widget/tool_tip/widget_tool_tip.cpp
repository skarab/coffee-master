//------------------------------------------------------------------------------------------------//
/// @file wide/ui/widget/tool_tip/widget_tool_tip.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "wide/ui/widget/tool_tip/widget_tool_tip.h"
#include "wide/ui/widget/label/widget_label.h"
#include "wide/ui/skin/ui_skin.h"
#include "wide/ui/window/ui_window_manager.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::widget::ToolTip);
        COFFEE_Ancestor(ui::widget::Widget);
    COFFEE_EndType();

namespace ui
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ToolTip::ToolTip() :
        _OverWindow(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    ToolTip::~ToolTip()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const basic::String& ToolTip::GetHelpText() const
    {
        return _HelpText;
    }

    //--------------------------------------------------------------------------------------------//

    const Window* ToolTip::GetOverWindow() const
    {
        return _OverWindow;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ToolTip::Create(const basic::String& help_text, const basic::Vector2i& position,
        Window* over_window)
    {
        _HelpText = help_text;
        _OverWindow = over_window;

        Window::Create(NULL, position, basic::Vector2i(), WINDOW_STYLE_None);

        SetSize(basic::Vector2i(
            GetSkinWidget().GetTextWidth(help_text) + GetSkinWidget().GetBorderSize().X * 2,
            GetSkinWidget().GetCharacterSize('A').Y + GetSkinWidget().GetBorderSize().Y * 2));
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(ToolTip, Widget)
    COFFEE_EndEventHandler()

}
}
}
//------------------------------------------------------------------------------------------------//
