#include "coffee_player.h"

namespace coffee_player
{
    //-META---------------------------------------------------------------------------------------//
    
    COFFEE_ImplementSingleton(Application);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Application::Application()
    {
    }

    //--------------------------------------------------------------------------------------------//

    Application::~Application()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Application::OnInitialize()
    {
        coffee::Application::OnInitialize();
        
        COFFEE_Assert(storage::System::Get().HasPath("/root/" COFFEE_ProjectConfigFile), core::ERROR_CODE_Unexpected,
            "Project's config file " COFFEE_ProjectConfigFile " not found");
        GetProject().Serialize("/root/" COFFEE_ProjectConfigFile, storage::MODE_Input);
        
        if (GetProject().MountFolders())
        {
            _Scene = scene::World::Get().Attach(GetProject().GetStartScene());
        }
        else
        {
            ui::DoMessageBox("Error", "Failed to mount project's folders");
            GetProject().SetPath("");
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Application::OnFinalize()
    {
        ui::WindowManager::Get().GetDesktopWindow().DetachCamera();
        scene::World::Get().Detach(_Scene);
        coffee::Application::OnFinalize();
    }

    //--------------------------------------------------------------------------------------------//

    void Application::OnUpdate(const basic::Time& time_step)
    {
        coffee::Application::OnUpdate(time_step);

        switch(_Scene.Update())
        {
            case resource::HANDLER_STATE_EndLoading:
            {
                // Initialize scene
                scene::Node& root = _Scene.Get().GetRoot();
                scene::Node* camera_node = NULL;
                if (GetProject().GetCamera().GetLength()>0)
                    camera_node = root.FindChild(GetProject().GetCamera());
                if (camera_node==NULL)
                {
                    // Use editor camera
                    camera_node = root.FindChild("_EditorCamera");
                }
                if (camera_node!=NULL)
                {
                    graphics::ComponentCameraPerspective* camera = camera_node->FindComponent<graphics::ComponentCameraPerspective>();
                    ui::WindowManager::Get().GetDesktopWindow().AttachCamera(_Scene, camera);
                }
            } break;

            case resource::HANDLER_STATE_Invalid:
            {
                COFFEE_Error(core::ERROR_CODE_Unexpected, "Scene load failed");                
            } break;

            default:
                break;
        }
    }

}
