#include "widget/project_manager/widget_project_general.h"
#include "coffee_editor.h"

namespace coffee_editor
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ProjectGeneral::ProjectGeneral() :
        _Properties(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    ProjectGeneral::~ProjectGeneral()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ProjectGeneral::Create(ui::Window* tab_client)
    {
        ui::Window::Create(
            tab_client,
            basic::Vector2i(),
            basic::Vector2i(), 0);
        GetLayout().SetStyle(tab_client->GetLayout().GetStyle());
        _UpdateProperties();
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(ProjectGeneral, ui::Window)
        //COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _ApplyButton, OnApply)
    COFFEE_EndEventHandler()

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ProjectGeneral::_UpdateProperties()
    {
        if (_Properties!=NULL)
            _Properties->Destroy();

        _Properties = COFFEE_New(ui::PropertyList);
        _Properties->Create(
            coffee_editor::Application::Get().GetProject(),
            basic::Vector2i(), GetSize(), this, false);
    }

}
}
