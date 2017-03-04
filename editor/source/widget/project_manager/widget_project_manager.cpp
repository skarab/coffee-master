#include "widget/project_manager/widget_project_manager.h"
#include "widget/project_manager/widget_project_general.h"
#include "widget/project_manager/widget_project_plugins.h"
#include "widget/project_manager/deploy/widget_deploy_package.h"
#include "widget/project_manager/deploy/widget_deploy_desktop.h"

namespace coffee_editor
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ProjectManager::ProjectManager() :
        _TabControl(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    ProjectManager::~ProjectManager()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ProjectManager::Create()
    {
        ui::widget::Dialog::Create(
            NULL,
            basic::Vector2i(),
            basic::Vector2i(410, 353));

        SetTitleBarText("Project Manager");

        _TabControl = COFFEE_New(ui::widget::TabControl);
        _TabControl->Create(this, basic::Vector2i(), basic::Vector2i());
        _TabControl->GetLayout().SetStyle(_TabControl->GetLayout().GetStyle()
            | ui::LAYOUT_STYLE_Expand);
        
        _TabControl->AddSeparator("Settings");
        _TabControl->AddTab("General");
        _TabControl->AddTab("Plugins");

        _TabControl->AddSeparator("Deployment");
        _TabControl->AddTab("Package");
        _TabControl->AddTab("Desktop");
        
        _TabControl->ActivateTab("General");
        PositionToCenter();
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(ProjectManager, ui::widget::Dialog)
        COFFEE_RegisterEventHandler(ui::widget::TAB_CONTROL_EVENT_Activate, ui::widget::TabControl, OnActivateTab)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool ProjectManager::OnActivateTab(shell::Event& event)
    {
        if (_TabControl->GetActiveTab()=="General")
            (COFFEE_New(ProjectGeneral))->Create(&_TabControl->GetClientWindow());
        else if (_TabControl->GetActiveTab()=="Plugins")
            (COFFEE_New(ProjectPlugins))->Create(&_TabControl->GetClientWindow());
        else if (_TabControl->GetActiveTab()=="Package")
            (COFFEE_New(DeployPackage))->Create(&_TabControl->GetClientWindow());
        else if (_TabControl->GetActiveTab()=="Desktop")
            (COFFEE_New(DeployDesktop))->Create(&_TabControl->GetClientWindow());
        return true;
    }

}
}
