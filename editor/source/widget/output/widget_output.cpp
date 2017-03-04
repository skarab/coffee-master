#include "widget/output/widget_output.h"
#include "widget/output/widget_output_bar.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(widget::Output);
    COFFEE_Ancestor(ui::Window);
    COFFEE_EndType();

namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Output::Output() :
        _OutputBar(NULL),
        _View(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Output::~Output()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Output::Create(OutputBar* output_bar)
    {
        _OutputBar = output_bar;
        
        ui::WindowContext context;
        context.Create(_OutputBar);
        
        basic::Vector2i size(
            context.GetDesktopWindowRect().Size.X,
            context.GetDesktopWindowRect().Size.X/2);
        ui::Window::Create(NULL, context.GetDesktopWindowRect().Position
            - basic::Vector2i(0, size.Y), size, ui::WINDOW_STYLE_Activable
            | ui::WINDOW_STYLE_DrawFrame);
        Activate();

        _View = COFFEE_New(ui::widget::ListView);
        _View->Create(this, basic::Vector2i(), basic::Vector2i(), ui::widget::VIEW_CONTROL_STYLE_FollowCursorOnAdd);
        _View->GetLayout().SetStyle(ui::LAYOUT_STYLE_Expand);
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(Output, ui::Window)
        COFFEE_RegisterEventHandler(ui::WINDOW_EVENT_Deactivate, ui::Window, OnDeactivate)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool Output::OnDeactivate(shell::Event& event)
    {
        Destroy();
        return false;
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    void Output::OnLog(core::Log::Type type, const char* message)
    {
        _View->AddOutput(basic::String("%s\n", message));
    }

}
}
