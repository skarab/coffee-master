#include "widget/config_dialog/widget_config_general.h"
#include "coffee_editor.h"

namespace coffee_editor
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ConfigGeneral::ConfigGeneral()
    {
    }

    //--------------------------------------------------------------------------------------------//

    ConfigGeneral::~ConfigGeneral()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ConfigGeneral::Create(ui::Window* tab_client)
    {
        ui::Window::Create(
            tab_client,
            basic::Vector2i(),
            basic::Vector2i(), 0);
        GetLayout().SetStyle(tab_client->GetLayout().GetStyle());
        
        ui::PropertyList* properties = COFFEE_New(ui::PropertyList);
        properties->Create(coffee_editor::Application::Get().GetConfig(),
            basic::Vector2i(), GetSize(), this, false);
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(ConfigGeneral, ui::Window)
    COFFEE_EndEventHandler()

}
}
