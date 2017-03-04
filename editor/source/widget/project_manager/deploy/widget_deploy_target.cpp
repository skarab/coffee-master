#include "widget/project_manager/deploy/widget_deploy_target.h"
#include "coffee_editor.h"

namespace coffee_editor
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    DeployTarget::DeployTarget(PROJECT_TARGET target) :
        _Target(target),
        _DeployButton(NULL)
    {
    }
        
    //--------------------------------------------------------------------------------------------//

    DeployTarget::~DeployTarget()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void DeployTarget::Create(ui::Window* tab_client)
    {
        ui::Window::Create(
            tab_client,
            basic::Vector2i(),
            basic::Vector2i(), 0);
        GetLayout().SetStyle(tab_client->GetLayout().GetStyle()
            | ui::LAYOUT_STYLE_VerticalCanvas
            | ui::LAYOUT_STYLE_StickChildren);

        ui::Window* frame = COFFEE_New(ui::Window);
        frame->Create(this, basic::Vector2i(), basic::Vector2i(), ui::WINDOW_STYLE_DrawFrame
            | ui::WINDOW_STYLE_DrawClientSunken);
        frame->GetLayout().SetStyle(ui::LAYOUT_STYLE_HorizontalExpand);
        frame->GetLayout().SetCanvas(100, true);
        
        _BuildFilesList(frame);

        ui::Window* controls = COFFEE_New(ui::Window);
        controls->Create(this, basic::Vector2i(), basic::Vector2i(), ui::WINDOW_STYLE_None);
        controls->GetLayout().SetStyle(ui::LAYOUT_STYLE_HorizontalExpand
            | ui::LAYOUT_STYLE_HorizontalCanvas
            | ui::LAYOUT_STYLE_StickChildren);
        controls->GetLayout().SetCanvas(30, false);

        ui::Window* space = COFFEE_New(ui::Window);
        space->Create(controls, basic::Vector2i(), basic::Vector2i(30, 30), ui::WINDOW_STYLE_None);
        space->GetLayout().SetCanvas(100, true);
        
        _DeployButton = COFFEE_New(ui::widget::Button);
        _DeployButton->Create(controls, basic::Vector2i(), basic::Vector2i(60, 30));
        _DeployButton->SetText("Deploy");
        _DeployButton->GetLayout().SetCanvas(80, false);
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(DeployTarget, ui::Window)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _DeployButton, OnDeploy)
    COFFEE_EndEventHandler()
    
    //--------------------------------------------------------------------------------------------//

    bool DeployTarget::OnDeploy(shell::Event& event)
    {
        coffee_editor::Application::Get().SaveConfiguration(true);

        meta::Enum* type = static_cast<meta::Enum*>(meta::Types::Get().FindType("coffee_editor::PROJECT_TARGET"));
        storage::PhysicalPath deployment_root = Application::Get().GetProject().GetFullPath()
            + "/deploy";
        storage::PhysicalPath deployment_path = deployment_root + "/" + GetPackageName();
        basic::String project_name = Application::Get().GetProject().GetFullPath().GetFileName();

        // Create deployment folders
        if (storage::PhysicalSystem::Get().IsFolder(deployment_path)
            && !storage::PhysicalSystem::Get().RemoveFolder(deployment_path))
        {
            return false;
        }
        if (!storage::PhysicalSystem::Get().CreateFolder(deployment_path))
            return false;

        // Deploy project and internal data
        if (AreCoffeeFilesRequired() && !_CopyProjectData("coffee", deployment_path))
            return false;
        if (!_CopyProjectData(project_name, deployment_path))
            return false;

        // Deploy target specifics
        if (!OnDeploy(deployment_path))
            return false;

        // Create archive if required
        if (!GetArchiveName().IsEmpty())
        {
            // Deploy target specifics
            if (!OnDeployArchive(deployment_root))
                return false;

            if (!core::Platform::Get().Run(storage::System::Get().GetRootPath()+"/tools/7z/7z.exe "
                + basic::String("a ")+deployment_root+"/"+GetArchiveName()+" "+deployment_path, deployment_root))
            {
                return false;
            }
        }
        if (storage::PhysicalSystem::Get().IsFolder(deployment_path)
            && !storage::PhysicalSystem::Get().RemoveFolder(deployment_path))
        {
            return false;
        }
        return true;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool DeployTarget::_CopyProjectData(basic::String project_name, storage::PhysicalPath deployment_path)
    {
        storage::PhysicalPath project_path;
        storage::PhysicalPath output_path;

        if (project_name=="coffee")
        {
            project_path = storage::System::Get().GetRootPath()+"/internals";
            output_path = deployment_path+"/internals";
        }
        else
        {
            project_path = storage::System::Get().GetRootPath()+"/projects/"+project_name;
            output_path = deployment_path+"/projects/"+project_name;
        }

        // Copy resources folder

        if (!storage::PhysicalSystem::Get().CopyFolder(project_path+"/resources", output_path+"/resources", true,
            &_Filter, this))
        {
            return false;
        }

        storage::PhysicalSystem::Get().CopyFolder(project_path+"/others", output_path+"/others", true);

        // Copy assets or import

        basic::String source = IsDeployingAssetsOnly()?"/assets":"/import";
        if (!storage::PhysicalSystem::Get().CopyFolder(project_path+source, output_path+source, true,
            &_Filter, this))
        {
            return false;
        }

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    void DeployTarget::_BuildFilesList(ui::Window* parent)
    {
        _Files = COFFEE_New(ui::widget::TreeControl);
        _Files->Create(parent, basic::Vector2i(), basic::Vector2i(),
            ui::widget::VIEW_CONTROL_STYLE_SortAscending
            /*| ui::widget::VIEW_CONTROL_STYLE_ShowCheckBoxes*/);
        _Files->GetLayout().SetStyle(ui::LAYOUT_STYLE_Expand);
        
        basic::Prow<storage::Path*, true> files;
        storage::System::Get().List(files, "/", false, true, "*", true);
        for (uint32 i=0 ; i<files.GetSize() ; ++i)
        {
            if (files[i]->IsPrefixed("/root"))
                continue;

            if (!_Filter(this, storage::System::Get().GetPhysicalFilePath(*files[i])))
                continue;

            _Files->AddPath(*files[i]/*, true*/);
        }
    }

    //-FUNCTIONS----------------------------------------------------------------------------------//
        
    bool DeployTarget::_Filter(meta::Object* user, const storage::PhysicalPath& path)
    {
        DeployTarget* target = static_cast<DeployTarget*>(user);
        if (path.IsSuffixed("/resources/" COFFEE_ProjectConfigFile))
            return false;
        else if (!target->IsDeployingAssetsOnly())
        {
            if (path.IsContaining("/import/editor/") || path.IsContaining("/resources/editor/"))
                return false;
        }
        else
        {
            if (path.IsContaining(".plugin/binaries")
                || path.IsContaining(".plugin/workspace")
                || path.IsContaining(".plugin/build/temp"))
            {
                return false;
            }

            if (path.IsContaining(".editor/binaries")
                || path.IsContaining(".editor/workspace")
                || path.IsContaining(".editor/build/temp"))
            {
                return false;
            }

            if (path.IsContaining(".component/binaries")
                || path.IsContaining(".component/workspace")
                || path.IsContaining(".component/build/temp"))
            {
                return false;
            }
        }

        if (!target->AreCoffeeFilesRequired() && path.IsPrefixed(storage::System::Get().GetRootPath()+"/internals"))
            return false;

        if (target->IsDeployingAssetsOnly() && path.IsContaining("/import"))
            return false;
        if (!target->IsDeployingAssetsOnly() && path.IsContaining("/assets"))
            return false;
        if (path.IsContaining("/editor/thumbnails"))
            return false;
        if (path.IsSuffixed(".stamp"))
            return false;
        return true;
    }

}
}
