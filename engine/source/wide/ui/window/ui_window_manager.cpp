#include "wide/ui/window/ui_window_manager.h"
#include "wide/application/application.h"
#include "system/graphics/device/graphics_device.h"
#include "system/graphics/frame/scissor/graphics_frame_scissor.h"
#include "system/graphics/graphics_module.h"

#define COFFEE_UI_WINDOW_MANAGER_ToolTipTime  0.7f

namespace coffee
{
namespace ui
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_ImplementModuleSingleton(WindowManager);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    WindowManager::WindowManager() :
        _DesktopWindow(NULL),
        _ActiveWindow(NULL),
        _FocusWindow(NULL),
        _Cursor(NULL),
        _CursorOverWindow(NULL),
        _ModalWindow(NULL),
        _ModalWindowResult(false),
        _ToolTipWindow(NULL),
        _Skin(NULL)
    {
        COFFEE_CreateModuleSingleton(WindowManager);
    }

    //--------------------------------------------------------------------------------------------//

    WindowManager::~WindowManager()
    {
        COFFEE_DestroyModuleSingleton(WindowManager);
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const DesktopWindow& WindowManager::GetDesktopWindow() const
    {
        return *_DesktopWindow;
    }

    //--------------------------------------------------------------------------------------------//

    DesktopWindow& WindowManager::GetDesktopWindow()
    {
        return *_DesktopWindow;
    }

    //--------------------------------------------------------------------------------------------//

    const Window& WindowManager::GetActiveWindow() const
    {
        return *_ActiveWindow;
    }

    //--------------------------------------------------------------------------------------------//

    Window& WindowManager::GetActiveWindow()
    {
        return *_ActiveWindow;
    }

    //--------------------------------------------------------------------------------------------//

    const Window& WindowManager::GetFocusWindow() const
    {
        return *_FocusWindow;
    }

    //--------------------------------------------------------------------------------------------//

    Window& WindowManager::GetFocusWindow()
    {
        return *_FocusWindow;
    }

    //--------------------------------------------------------------------------------------------//

    const Window& WindowManager::GetCursorOverWindow() const
    {
        return *_CursorOverWindow;
    }

    //--------------------------------------------------------------------------------------------//

    Window& WindowManager::GetCursorOverWindow()
    {
        return *_CursorOverWindow;
    }

    //--------------------------------------------------------------------------------------------//

    const Cursor& WindowManager::GetCursor() const
    {
        return *_Cursor;
    }

    //--------------------------------------------------------------------------------------------//

    Cursor& WindowManager::GetCursor()
    {
        return *_Cursor;
    }

    //--------------------------------------------------------------------------------------------//

    const ClipBoard& WindowManager::GetClipBoard() const
    {
        return _ClipBoard;
    }

    //--------------------------------------------------------------------------------------------//

    ClipBoard& WindowManager::GetClipBoard()
    {
        return _ClipBoard;
    }

    //--------------------------------------------------------------------------------------------//

    void WindowManager::SetSkin(const Skin& skin)
    {
        *_Skin = skin;
        _DesktopWindow->SetSkin(_Skin);
    }

    //--------------------------------------------------------------------------------------------//

    void WindowManager::SetModalWindow(Window* window)
    {
        _ModalWindow = window;
        if (window!=NULL)
            _ModalWindowResult = false;
    }

    //--------------------------------------------------------------------------------------------//

    const Window* WindowManager::GetModalWindow() const
    {
        return _ModalWindow;
    }

    //--------------------------------------------------------------------------------------------//

    void WindowManager::AcceptModalWindow()
    {
        _ModalWindowResult = true;
        SetModalWindow(NULL);
    }

    //--------------------------------------------------------------------------------------------//

    void WindowManager::SetToolTipWindow(Window* window)
    {
        if (_ToolTipWindow!=NULL)
            _ToolTipWindow->Destroy();

        _ToolTipTime.SetSecondCount(0.0f);
        _ToolTipWindow = window;
    }

    //--------------------------------------------------------------------------------------------//

    void WindowManager::SetNoToolTipWindow(Window* window)
    {
        if (_ToolTipWindow==window)
            _ToolTipWindow = NULL;
    }

    //--------------------------------------------------------------------------------------------//

    Window* WindowManager::GetToolTipWindow() const
    {
        return _ToolTipWindow;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool WindowManager::HasDesktopWindow() const
    {
        return _DesktopWindow != NULL;
    }

    //--------------------------------------------------------------------------------------------//

    bool WindowManager::HasActiveWindow() const
    {
        return _ActiveWindow != NULL;
    }

    //--------------------------------------------------------------------------------------------//

    bool WindowManager::HasFocusWindow() const
    {
        return _FocusWindow != NULL;
    }

    //--------------------------------------------------------------------------------------------//

    bool WindowManager::HasCursorOverWindow() const
    {
        return _CursorOverWindow != NULL;
    }

    //--------------------------------------------------------------------------------------------//

    bool WindowManager::HasModalWindow() const
    {
        return _ModalWindow != NULL;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void WindowManager::OnInitialize()
    {
        COFFEE_RegisterResourceLibrary("skin");        
    }

    //--------------------------------------------------------------------------------------------//

    void WindowManager::OnFinalize()
    {
    }

    //--------------------------------------------------------------------------------------------//

    void WindowManager::OnStart()
    {
        _Skin = COFFEE_New(Skin);
        _PropertyManager = COFFEE_New(PropertyManager);
    }

    //--------------------------------------------------------------------------------------------//

    void WindowManager::OnStop()
    {
        if (_DesktopWindow!=NULL)
        {
            while(!_DesktopWindow->AreQueuesEmpty())
                _DesktopWindow->Update();

            _DesktopWindow->Destroy();
            _DesktopWindow = NULL;
        }

        if (_Cursor!=NULL)
        {
            _Cursor->Destroy();
            _Cursor = NULL;
        }

        COFFEE_Delete(_PropertyManager);
        _PropertyManager = NULL;

        COFFEE_Delete(_Skin);
        _Skin = NULL;
    }

    //--------------------------------------------------------------------------------------------//

    void WindowManager::OnUpdate(const basic::Time& time_step)
    {
        if (HasDesktopWindow())
        {
            if (graphics::Module::IsAvailable())
            {
                GetDesktopWindow().Resize(basic::Vector2i(
                    graphics::Device::Get().GetWidth(),
                    graphics::Device::Get().GetHeight()));
            }

            GetDesktopWindow().UpdateWindow(time_step);
            _Cursor->Update();
            _UpdateToolTip(time_step);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void WindowManager::_CreateDesktopWindow()
    {
        COFFEE_GRAPHICS_Debug();
        
        storage::Path skin_path(COFFEE_GUI_DefaultSkin);
        if (!storage::System::Get().HasPath(skin_path))
        {
            Skin* skin = COFFEE_New(Skin);
            skin->Create();
            skin->PreCreateLOD(0);
            resource::Chunk* resource_chunk;
            resource_chunk = resource::Manager::Get().Create(skin_path);
            resource_chunk->AddLOD(*skin);
            resource::Manager::Get().Save(*resource_chunk);
        }
        
        COFFEE_GRAPHICS_Debug();
        
        *_Skin = resource::Manager::Get().Load(skin_path);
        
        basic::Vector2i desktop_size(
            graphics::Device::Get().GetWidth(),
            graphics::Device::Get().GetHeight());

        COFFEE_GRAPHICS_Debug();

        DesktopWindow* desktop_window = COFFEE_New(DesktopWindow);
        
        COFFEE_GRAPHICS_Debug();
        
        desktop_window->Create(
            NULL,
            basic::Vector2i(),
            desktop_size,
            WINDOW_STYLE_Activable);
        desktop_window->SetSkin(_Skin);
        _DesktopWindow = desktop_window;
        _DesktopWindow->SetFocus();

        _Cursor = COFFEE_New(Cursor);
        input::Module::Get().GetSystem().Register(*_Cursor);
        input::Module::Get().GetSystem().Register(Application::Get().GetControlManager());
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void WindowManager::_UpdateToolTip(const basic::Time& time_step)
    {
        if (_ToolTipWindow != NULL)
        {
            if (!HasCursorOverWindow()
                || &GetCursorOverWindow()!=((widget::ToolTip*)_ToolTipWindow)->GetOverWindow())
            {
                _ToolTipWindow->Destroy();
                _ToolTipWindow = NULL;
            }
            else if (_ToolTipTime.GetSecondCount() < COFFEE_UI_WINDOW_MANAGER_ToolTipTime)
            {
                _ToolTipTime += time_step;

                if (_ToolTipTime.GetSecondCount() >= COFFEE_UI_WINDOW_MANAGER_ToolTipTime)
                {
                    _ToolTipWindow->PositionToDesktop();
                }
            }
        }
    }

}
}

#undef COFFEE_UI_WINDOW_MANAGER_ToolTipTime

