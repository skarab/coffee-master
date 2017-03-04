#include "wide/application/application.h"
#include "coffee.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_ImplementModuleSingleton(Application);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Application::Application() :
        _ItHasFocus(true)
    {
        COFFEE_CreateModuleSingleton(Application);
    }

    //--------------------------------------------------------------------------------------------//

    Application::~Application()
    {
        COFFEE_DestroyModuleSingleton(Application);
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const ApplicationControlManager& Application::GetControlManager() const
    {
        return *_ControlManager;
    }

    //--------------------------------------------------------------------------------------------//

    ApplicationControlManager& Application::GetControlManager()
    {
        return *_ControlManager;
    }

    //--------------------------------------------------------------------------------------------//

    bool Application::HasFocus() const
    {
        return _ItHasFocus;
    }

    //--------------------------------------------------------------------------------------------//

    const Project& Application::GetProject() const
    {
        return _Project;
    }
    
    //--------------------------------------------------------------------------------------------//
    
    Project& Application::GetProject()
    {
        return _Project;
    }

    //--------------------------------------------------------------------------------------------//
    
    ui::Window* Application::GetWindow()
    {
        if (ui::WindowManager::IsAvailable() && ui::WindowManager::Get().HasDesktopWindow())
            return &ui::WindowManager::Get().GetDesktopWindow();
        return NULL;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Application::OnInitialize()
    {
        COFFEE_GRAPHICS_Debug();
        
        _ControlManager = COFFEE_New(ApplicationControlManager);
        _ControlManager->Initialize();
    
        COFFEE_Assert(GetProject().MountBaseFolders(), core::ERROR_CODE_Unexpected, "Invalid file system");

        COFFEE_GRAPHICS_Debug();
        
        if (ui::WindowManager::IsInstantiated())
            ui::WindowManager::Get()._CreateDesktopWindow();

        COFFEE_GRAPHICS_Debug();
        
        if (resource::Manager::IsInstantiated())
            GetProject().Initialize();
    
        COFFEE_GRAPHICS_Debug();        
    }

    //--------------------------------------------------------------------------------------------//

    void Application::OnFinalize()
    {
        _ControlManager->Destroy();
    }

    //--------------------------------------------------------------------------------------------//

    void Application::OnUpdate(const basic::Time& time_step)
    {
        if (graphics::Device::IsInstantiated())
        {
            if (graphics::Device::Get().IsWindowFocused())
            {
                if (!HasFocus())
                    OnGetFocus();
            }
            else
            {
                if (HasFocus())
                    OnLoseFocus();
            }
        }

        _ControlManager->Update(time_step);
        
        if (resource::Manager::IsInstantiated())
            _Project.Update(time_step);
    }

    //--------------------------------------------------------------------------------------------//

    void Application::OnRender(graphics::Viewport& viewport, bool it_is_transparent, bool it_is_hdr)
    {
        _ControlManager->Render(viewport, it_is_transparent, it_is_hdr);
    }

    //--------------------------------------------------------------------------------------------//

	void Application::OnGetFocus()
	{
        COFFEE_Assert(!_ItHasFocus, core::ERROR_CODE_IncorrectUsage,
            "OnGetFocus called while application is already focused");
        _ItHasFocus = true;
	}

    //--------------------------------------------------------------------------------------------//

	void Application::OnLoseFocus()
	{
         COFFEE_Assert(_ItHasFocus, core::ERROR_CODE_IncorrectUsage,
            "OnLoseFocus called while application is not focused");
        _ItHasFocus = false;
	}

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(Application, shell::Module)
        COFFEE_RegisterEventHandler(shell::MODULE_EVENT_Start, shell::Module, OnStart)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool Application::OnStart(shell::Event& event)
    {
        if (input::Module::IsInstantiated())
            static_cast<input::Config&>(input::Module::Get().GetConfig()).Apply();
        return false;
    }

}
