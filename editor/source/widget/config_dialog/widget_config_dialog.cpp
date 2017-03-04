#include "widget/config_dialog/widget_config_dialog.h"
#include "widget/config_dialog/widget_config_general.h"
#include "widget/config_dialog/widget_config_graphics.h"
#include "widget/config_dialog/widget_config_audio.h"
#include "widget/config_dialog/widget_config_shortcuts.h"

namespace coffee_editor
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ConfigDialog::ConfigDialog() :
        _TabControl(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    ConfigDialog::~ConfigDialog()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ConfigDialog::Create()
    {
        ui::widget::Dialog::Create(
            NULL,
            basic::Vector2i(),
            basic::Vector2i(410, 353));

        SetTitleBarText("Editor Settings");

        _TabControl = COFFEE_New(ui::widget::TabControl);
        _TabControl->Create(this, basic::Vector2i(), basic::Vector2i());
        _TabControl->GetLayout().SetStyle(_TabControl->GetLayout().GetStyle()
            | ui::LAYOUT_STYLE_Expand);
        
        _TabControl->AddTab("General");
        _TabControl->AddTab("Graphics");
        _TabControl->AddTab("Audio");
        _TabControl->AddTab("Shortcuts");
        _TabControl->ActivateTab("General");
        PositionToCenter();
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(ConfigDialog, ui::widget::Dialog)
        COFFEE_RegisterEventHandler(ui::widget::TAB_CONTROL_EVENT_Activate, ui::widget::TabControl, OnActivateTab)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool ConfigDialog::OnActivateTab(shell::Event& event)
    {
        if (_TabControl->GetActiveTab()=="General")
            (COFFEE_New(ConfigGeneral))->Create(&_TabControl->GetClientWindow());
        else if (_TabControl->GetActiveTab()=="Graphics")
            (COFFEE_New(ConfigGraphics))->Create(&_TabControl->GetClientWindow());
        else if (_TabControl->GetActiveTab()=="Audio")
            (COFFEE_New(ConfigAudio))->Create(&_TabControl->GetClientWindow());
        else if (_TabControl->GetActiveTab()=="Shortcuts")
            (COFFEE_New(ConfigShortcuts))->Create(&_TabControl->GetClientWindow());

        return true;
    }

}
}
