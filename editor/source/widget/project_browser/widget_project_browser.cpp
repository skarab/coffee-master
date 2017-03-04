#include "coffee_editor.h"
#include "widget/project_browser/widget_project_browser.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(widget::ProjectBrowser);
    COFFEE_Ancestor(ui::Window);
    COFFEE_EndType();

namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ProjectBrowser::ProjectBrowser() :
        _ProjectList(NULL),
        _WelcomeScreen(NULL),
        _ProjectDialog(NULL),
        _ProjectName(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    ProjectBrowser::~ProjectBrowser()
    {
    }

    //-OPERATIONS-----------------------------------------------------------------------------//

    void ProjectBrowser::Create()
    {
        ui::Window::Create(NULL, basic::Vector2i(), basic::Vector2i(),
            ui::WINDOW_STYLE_DrawFrame | ui::WINDOW_STYLE_DrawClientSunken
            | ui::WINDOW_STYLE_Activable | ui::WINDOW_STYLE_Focusable);
        GetLayout().SetStyle(ui::LAYOUT_STYLE_Expand | ui::LAYOUT_STYLE_VerticalCanvas
            | ui::LAYOUT_STYLE_StickChildren);

        ui::Window* border = COFFEE_New(ui::Window);
        border->Create(this, basic::Vector2i(), basic::Vector2i(1, 150),
            ui::WINDOW_STYLE_DrawFrame);
        border->GetLayout().SetStyle(ui::LAYOUT_STYLE_HorizontalExpand);
        border->GetLayout().SetCanvas(150, false);

        ui::widget::Image* image = COFFEE_New(ui::widget::Image);
        image->Create(border, basic::Vector2i(), basic::Vector2i(300, 150),
            ui::widget::IMAGE_STYLE_AutoSize);
        image->SetImage("/coffee/import/editor/logo.texture");

        ui::Window* frame = COFFEE_New(ui::Window);
        frame->Create(this, basic::Vector2i(), basic::Vector2i(), ui::WINDOW_STYLE_None);
        frame->GetLayout().SetCanvas(100, true);
        frame->GetLayout().SetStyle(ui::LAYOUT_STYLE_HorizontalExpand | ui::LAYOUT_STYLE_HorizontalCanvas
            | ui::LAYOUT_STYLE_StickChildren);
        
        ui::Window* panel = COFFEE_New(ui::Window);
        panel->Create(frame, basic::Vector2i(), basic::Vector2i(),
            ui::WINDOW_STYLE_DrawFrame | ui::WINDOW_STYLE_DrawClientSunken);
        panel->GetLayout().SetCanvas(20, true);
        panel->GetLayout().SetStyle(ui::LAYOUT_STYLE_VerticalExpand
            | ui::LAYOUT_STYLE_VerticalCanvas
            | ui::LAYOUT_STYLE_StickChildren);
        
        ui::widget::ToolBar* project_toolbar = COFFEE_New(ui::widget::ToolBar);
        project_toolbar->Create(panel, 30);
        COFFEE_RegisterExternEventHandler(
            ui::widget::EVENT_Pressed,
            ui::widget::Widget::GetClassMetaType(),
            *project_toolbar->AddButton("New Project...", ui::SKIN_ICON_New), OnAskProjectName);

        _ProjectList = COFFEE_New(ui::widget::ListView);
        _ProjectList->Create(panel, basic::Vector2i(), basic::Vector2i());
        _ProjectList->GetLayout().SetStyle(ui::LAYOUT_STYLE_Expand);

        _WelcomeScreen = COFFEE_New(ui::widget::TextBox);
        _WelcomeScreen->Create(frame, basic::Vector2i(), basic::Vector2i(50, 50));
        _WelcomeScreen->GetLayout().SetCanvas(80, true);
        _WelcomeScreen->GetLayout().SetStyle(_WelcomeScreen->GetLayout().GetStyle()
            | ui::LAYOUT_STYLE_VerticalExpand);
        
        basic::Text text;
        text.AddLine("Welcome!");
        _WelcomeScreen->SetText(text);
        _WelcomeScreen->Enable(false);
        _UpdateContent();
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(ProjectBrowser, ui::Window)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Activate, ui::widget::Widget, _ProjectList, OnOpenProject)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool ProjectBrowser::OnAskProjectName(shell::Event& event)
    {
        _ProjectDialog = COFFEE_New(ui::widget::Dialog);
        _ProjectDialog->Create(NULL, basic::Vector2i(), basic::Vector2i(300, 80));
        _ProjectDialog->SetTitleBarText("Create Project");
        
        _ProjectName = COFFEE_New(ui::widget::EditBox);
        _ProjectName->Create(_ProjectDialog, basic::Vector2i(40, 16), 160);
        _ProjectName->SetText("new_project");

        ui::widget::Button* ok = COFFEE_New(ui::widget::Button);
        ok->Create(_ProjectDialog, basic::Vector2i(205, 16), basic::Vector2i(35, 20));
        ok->SetText("Ok");
        COFFEE_RegisterExternEventHandler(ui::widget::EVENT_Pressed,
            ui::widget::Widget::GetClassMetaType(), *ok, OnCreateProject);

        _ProjectDialog->PositionToCenter();
        if (_ProjectDialog->DoModal())
        {
            _ProjectDialog->Destroy();
            Destroy();
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool ProjectBrowser::OnCreateProject(shell::Event& event)
    {
        if (!storage::PhysicalSystem::Get().IsValidName(_ProjectName->GetText()))
        {
            ui::DoMessageBox("Warning", "Project name is invalid.");
            return true;
        }
        
        storage::Path project_path = basic::String("/projects/") + _ProjectName->GetText();
        if (storage::PhysicalSystem::Get().IsFolder(storage::System::Get().GetRootPath() + project_path))
        {
            ui::DoMessageBox("Warning", "Project already exists");
            return true;
        }

        Application::Get().GetProject().SetPath(project_path);
        ui::WindowManager::Get().AcceptModalWindow();
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool ProjectBrowser::OnOpenProject(shell::Event& event)
    {
        Application::Get().GetProject().SetPath(
            basic::String("/projects/")+
            ((storage::PhysicalPath*)_ProjectList->GetItemData(_ProjectList->GetSelectedIndex()))->GetFileName());
        Destroy();
        return true;
    }

    //-OPERATIONS-----------------------------------------------------------------------------//

    void ProjectBrowser::_UpdateContent()
    {
        _ProjectList->RemoveItems();
        storage::PhysicalPath projects_path = storage::System::Get().GetRootPath()
            + "/projects";
        if (!storage::PhysicalSystem::Get().IsFolder(projects_path))
            storage::PhysicalSystem::Get().CreateFolder(projects_path);
        storage::PhysicalSystem::Get().List(_Projects, projects_path, true, false);
        for (uint32 index=0 ; index<_Projects.GetSize() ; ++index)
            _ProjectList->AddItem(_Projects[index]->GetFileName(), _Projects[index]);
    }

}
}
