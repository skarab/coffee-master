#include "widget/config_dialog/widget_config_shortcuts.h"
#include "coffee_editor.h"

namespace coffee_editor
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ConfigShortcuts::ConfigShortcuts() :
        _Properties(NULL),
        _ApplyButton(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    ConfigShortcuts::~ConfigShortcuts()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ConfigShortcuts::Create(ui::Window* tab_client)
    {
        ui::Window::Create(
            tab_client,
            basic::Vector2i(),
            basic::Vector2i(), 0);
        GetLayout().SetStyle(tab_client->GetLayout().GetStyle());
        _UpdateProperties();

        _ApplyButton = COFFEE_New(ui::widget::Button);
        _ApplyButton->Create(this, basic::Vector2i(), basic::Vector2i(70, 20));
        _ApplyButton->SetText("Apply");
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(ConfigShortcuts, ui::Window)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _ApplyButton, OnApply)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool ConfigShortcuts::OnApply(shell::Event& event)
    {
        static_cast<input::Config&>(input::Module::Get().GetConfig()).Apply();
        _UpdateProperties();
        return true;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ConfigShortcuts::_UpdateProperties()
    {
        if (_Properties!=NULL)
            _Properties->Destroy();

        _Properties = COFFEE_New(ui::PropertyList);
        _Properties->Create(input::Module::Get().GetConfig(),
            basic::Vector2i(), GetSize(), this, false);
    }

}
}
