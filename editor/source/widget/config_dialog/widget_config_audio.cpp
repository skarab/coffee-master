#include "widget/config_dialog/widget_config_audio.h"
#include "coffee_editor.h"

namespace coffee_editor
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ConfigAudio::ConfigAudio()
    {
    }

    //--------------------------------------------------------------------------------------------//

    ConfigAudio::~ConfigAudio()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ConfigAudio::Create(ui::Window* tab_client)
    {
        ui::Window::Create(
            tab_client,
            basic::Vector2i(),
            basic::Vector2i(), 0);
        GetLayout().SetStyle(tab_client->GetLayout().GetStyle());
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(ConfigAudio, ui::Window)
    COFFEE_EndEventHandler()

}
}
