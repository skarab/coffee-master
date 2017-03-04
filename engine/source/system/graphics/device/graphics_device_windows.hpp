#ifdef COFFEE_OS_WINDOWS

#include "system/input/mouse/input_mouse.h"
#include "coffee.h"

//-CONSTANTS--------------------------------------------------------------------------------------//

#define COFFEE_ClassName "coffee_class"

bool operator ==(const DISPLAY_DEVICE &,const DISPLAY_DEVICE &) { return false; }
bool operator ==(const DEVMODE &,const DEVMODE &) { return false; }

namespace coffee
{
namespace graphics
{
    //-QUERIES------------------------------------------------------------------------------------//

    bool Device::IsWindowFocused() const
    {
        HWND focus = GetFocus();
        return _Window!=NULL && focus==_Window;
    }

    //--------------------------------------------------------------------------------------------//

    void Device::ListDevices(basic::Array<DISPLAY_DEVICE>& device_array) const
    {
        uint32 device_index(0);
        DISPLAY_DEVICE device;
        device.cb = sizeof(DISPLAY_DEVICE);
        while(EnumDisplayDevices(0, device_index++, &device, 0))
        {
            if(device.StateFlags&DISPLAY_DEVICE_ATTACHED_TO_DESKTOP)
                device_array.AddItem(device);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Device::ListModes(basic::Array<DEVMODE>& mode_array, uint32 device_index) const
    {
        basic::Array<DISPLAY_DEVICE> device_array;
        uint32 mode_index(0);
        ListDevices(device_array);
        if (device_index>=device_array.GetSize())
            return;

        mode_array.Clear();
        DEVMODE mode;
        mode.dmSize = sizeof(DEVMODE);
        while(EnumDisplaySettings(device_array[device_index].DeviceName, mode_index++, &mode))
            mode_array.AddItem(mode);
    }

    //--------------------------------------------------------------------------------------------//

    bool Device::GetDisplayMode(DEVMODE& display_mode, uint32 device_index, uint32 device_mode_index) const
    {
        basic::Array<DISPLAY_DEVICE> device_array;
        ListDevices(device_array);
        if (device_index>=device_array.GetSize())
            return false;

        basic::Array<DEVMODE> mode_array;
        ListModes(mode_array, device_index);
        if (device_mode_index>=mode_array.GetSize())
            return false;

        memcpy(&display_mode, &mode_array[device_mode_index], sizeof(DEVMODE));
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    void Device::GetDesktopResolution(uint32& width, uint32& height, uint32& bpp, CONFIG_ASPECT_RATIO& aspect_ratio)
    {
        HDC dc = GetDC(NULL);
        width = GetDeviceCaps(dc, HORZRES);
        height = GetDeviceCaps(dc, VERTRES);
        bpp = GetDeviceCaps(dc, BITSPIXEL);

        uint32 physical_width = GetDeviceCaps(dc, HORZSIZE);
        uint32 physical_height = GetDeviceCaps(dc, VERTSIZE);

        real ar = width/(real)height;
        real physical_ar = physical_width/(real)physical_height;
        aspect_ratio = CONFIG_ASPECT_RATIO_GetRatio(ar*ar/physical_ar);

        ReleaseDC(NULL, dc);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Device::PositionWindowToCenter(uint32 width, uint32 height)
    {
        uint32 screen_width = GetSystemMetrics(SM_CXSCREEN);
        uint32 screen_height = GetSystemMetrics(SM_CYSCREEN);
        WINDOWPLACEMENT placement;
        GetWindowPlacement(GetPlatformWindow(), &placement);
        placement.showCmd = SW_SHOWNORMAL;
        placement.rcNormalPosition.left = (screen_width-width)/2;
        placement.rcNormalPosition.right = (screen_width-width)/2+width;
        placement.rcNormalPosition.top = (screen_height-height)/2;
        placement.rcNormalPosition.bottom = (screen_height-height)/2+height;
        SetWindowPlacement(GetPlatformWindow(), &placement);
    }

    //--------------------------------------------------------------------------------------------//

    void Device::Maximize()
    {
        WINDOWPLACEMENT placement;
        GetWindowPlacement(GetPlatformWindow(), &placement);
        placement.showCmd = SW_SHOWMAXIMIZED;
        SetWindowPlacement(GetPlatformWindow(), &placement);
    }

    //--------------------------------------------------------------------------------------------//

    void Device::EnableContext(bool it_is_enabled)
    {
        if (_OpenglContext==NULL)
            return;

        if (it_is_enabled)
        {
            if (!_ItHasActiveContext)
            {
                _OldDC = wglGetCurrentDC();
                _OldContext = wglGetCurrentContext();
                wglMakeCurrent(NULL, NULL);
                if (_OpenglContext==NULL || !wglMakeCurrent(_DesktopContext, _OpenglContext))
                    COFFEE_Error(core::ERROR_CODE_GraphicsDriver, "Failed to set current opengl context");
                _ItHasActiveContext = true;
            }
        }
        else
        {
            if (_ItHasActiveContext)
            {
                wglMakeCurrent(NULL, NULL);
                wglMakeCurrent(_OldDC, _OldContext);
                _ItHasActiveContext = false;
            }
        }
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Device::_CreateWindow()
    {
        _ItIsUpToDate = false;
        
        _CreateWindowClass();
        _CreateWindowDialog(_CreateWindowStyle());
        _CreateWindowPixelFormat();
        _EnableVerticalSync();
        
        ShowWindow(_Window, GetConfig().IsModeEnabled(CONFIG_MODE_Fullscreen)?
            SW_SHOWNORMAL:SW_SHOWMAXIMIZED);

        SetFocus(_Window);        
    }

    //--------------------------------------------------------------------------------------------//

    void Device::_DestroyWindow()
    {
        EnableContext(false);

        if (_OpenglContext!=NULL)
        {
            wglDeleteContext(_OpenglContext);
            _OpenglContext = NULL;
        }
    
        if (_Window!=NULL)
        {
            ReleaseDC(_Window, _DesktopContext);
            _DesktopContext = NULL;

            DestroyWindow(_Window);
            _Window = NULL;
            UnregisterClass(COFFEE_ClassName, core::Platform::Get().GetDllInstance());
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Device::_UpdateWindow(bool it_is_visible)
    {
        MSG msg;
        while (PeekMessage(&msg, _Window, 0U, 0U, PM_REMOVE)!=0)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }   

        if (it_is_visible)
        {
            SwapBuffers(_DesktopContext);
            
            // Clear primary framebuffer
            glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClearDepth(1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            if (!_ItIsUpToDate)
                _UpdateSize(_Width, _Height);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Device::_CreateWindowClass()
    {
        WNDCLASS win_class;

        memset(&win_class, 0, sizeof(WNDCLASS));
        win_class.style           = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
        win_class.lpfnWndProc     = _WindowFunction;
        win_class.hInstance       = core::Platform::Get().GetDllInstance();
        win_class.hCursor         = LoadCursor(NULL, IDC_ARROW);
        win_class.hbrBackground   = (HBRUSH) (COLOR_WINDOW + 1);
        win_class.lpszClassName   = COFFEE_ClassName;

        if (!RegisterClass(&win_class))
            COFFEE_Error(core::ERROR_CODE_GraphicsDriver, "Failed to register class");
    }

    //--------------------------------------------------------------------------------------------//

    ulong Device::_CreateWindowStyle()
    {
        ulong style = 0;
        DEVMODE mode;

        // Try to find a mode looking mostly the same as defined by config
        bool it_has_valid_mode = false;
        COFFEE_Log(core::Log::None, "Finding graphics mode...");
        basic::Array<DISPLAY_DEVICE> devices;
        ListDevices(devices);
        for (uint32 d=0 ; d<devices.GetSize() && !it_has_valid_mode ; ++d)
        {
            if (GetConfig().GetState(CONFIG_STATE_Device)==NONE
                || d==GetConfig().GetState(CONFIG_STATE_Device))
            {
                basic::Array<DEVMODE> modes;
                ListModes(modes, d);
                for (uint32 m=0 ; m<modes.GetSize() ; ++m)
                {
                    if (modes[m].dmPelsWidth==GetConfig().GetState(CONFIG_STATE_Width)
                        && modes[m].dmPelsHeight==GetConfig().GetState(CONFIG_STATE_Height))
                    {
                        mode = modes[m];
                        it_has_valid_mode = true;
                        if (modes[m].dmBitsPerPel==GetConfig().GetState(CONFIG_STATE_Bpp))
                            break;
                    }
                }
            }
        }

        // Set default style to windowed...
        style = WS_OVERLAPPED
             | WS_CAPTION
             | WS_SYSMENU
             | WS_THICKFRAME
             | WS_MINIMIZEBOX
             | WS_MAXIMIZEBOX;

        // Set config according to choosen mode
        if (it_has_valid_mode)
        {
            if (mode.dmBitsPerPel<16 && GetConfig().IsModeEnabled(CONFIG_MODE_Fullscreen))
            {
                COFFEE_Log(core::Log::Warning, "Failed to go fullscreen with less than 16bpp!");
                GetConfig().EnableMode(CONFIG_MODE_Fullscreen, false);
            }

            if (GetConfig().IsModeEnabled(CONFIG_MODE_Fullscreen))
            {
                style = WS_POPUP | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;
                if (ChangeDisplaySettings(&mode, CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
                    COFFEE_Error(core::ERROR_CODE_GraphicsDriver, "Failed to set fullscreen graphics mode!");
                _BitsPerPixel = mode.dmBitsPerPel;
            }
            else
            {
                _BitsPerPixel = 32;  // fake current windows desktop
            }
            
            _FrameWidth = mode.dmPelsWidth;
            _FrameHeight = mode.dmPelsHeight;
            _Width = _FrameWidth;
            _Height = _FrameHeight;
        }
        else
        {            
            COFFEE_Log(core::Log::None, "Falling back to desktop graphics mode...");

            CONFIG_ASPECT_RATIO aspect_ratio;
            Device::Get().GetDesktopResolution(_Width, _Height, _BitsPerPixel, aspect_ratio);
            GetConfig().EnableMode(CONFIG_MODE_Fullscreen, false);
            GetConfig().SetState(CONFIG_STATE_Device, NONE);
            GetConfig().SetFormat(aspect_ratio);
            GetConfig().SetState(CONFIG_STATE_Bpp, _BitsPerPixel);
            _FrameWidth = _Width;
            _FrameHeight = _Height;
        }

        _AspectRatio = CONFIG_ASPECT_RATIO_GetValue(GetConfig().GetFormat());
        
        COFFEE_Log(core::Log::None, "Graphics mode set to %ix%i %ibpp", _Width, _Height, _BitsPerPixel);
        return style;
    }

    //--------------------------------------------------------------------------------------------//

    void Device::_CreateWindowDialog(ulong style)
    {
        RECT window_rec;

        window_rec.left = 0;
        window_rec.right = _Width;
        window_rec.top = 0;
        window_rec.bottom = _Height;

        if (!GetConfig().IsModeEnabled(CONFIG_MODE_Fullscreen))
            window_rec.bottom += ::GetSystemMetrics(SM_CYCAPTION);

        AdjustWindowRect(&window_rec, style, false);

        _Window = CreateWindow(COFFEE_ClassName,
            Engine::Get().GetApplicationName(),
            style, 0, 0, window_rec.right - window_rec.left,
            window_rec.bottom - window_rec.top, (HWND)NULL,
            NULL, core::Platform::Get().GetDllInstance(), NULL);

        COFFEE_Assert(_Window!=NULL, core::ERROR_CODE_GraphicsDriver, "Failed to create graphics window");

        GetClientRect(_Window, &_WindowRec);
        _DesktopContext = GetDC(_Window);
    }

    //--------------------------------------------------------------------------------------------//

    void Device::_CreateWindowPixelFormat()
    {
        static PIXELFORMATDESCRIPTOR pfd =
        {
            sizeof(PIXELFORMATDESCRIPTOR), 1,
            PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
            PFD_TYPE_RGBA, _BitsPerPixel, 0, 0, 0, 0, 0, 0, 0, 0,
            _BitsPerPixel, 0, 0, 0, 0, _BitsPerPixel,
            1, 0, PFD_MAIN_PLANE, 0, 0, 0, 0
        };

        _PixelFormat = ChoosePixelFormat(_DesktopContext, &pfd);
        COFFEE_Assert(_PixelFormat!=0, core::ERROR_CODE_GraphicsDriver, "Failed to choose pixel format");
        if (SetPixelFormat(_DesktopContext, _PixelFormat, &pfd)==0)
            COFFEE_Error(core::ERROR_CODE_GraphicsDriver, "Failed to set pixel format");

        _OpenglContext = wglCreateContext(_DesktopContext);
        EnableContext(true);
        COFFEE_Log(core::Log::None, "Using %i Bits per pixel", _BitsPerPixel);
    }

    //--------------------------------------------------------------------------------------------//

    void Device::_UpdateSize(uint32 width, uint32 height)
    {
        if ((width!=_Width || height!=_Height) && width>5 && height>5)
        {
            if (width/2.0f!=(float)(width/2))
                width = (width/2)*2;
            if (height/2.0f!=(float)(height/2))
                height = (height/2)*2;

            _Width = width;
            _Height = height;
            _ItIsUpToDate = false;
        }

        if (!_ItIsUpToDate && ui::WindowManager::IsAvailable() && ui::WindowManager::Get().HasDesktopWindow())
        {
            real monitor_format = CONFIG_ASPECT_RATIO_GetValue(GetConfig().GetFormat());
            real framebuffer_format = _FrameWidth/(real)_FrameHeight;
            _AspectRatio = framebuffer_format/monitor_format;
            _ItIsUpToDate = true;
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Device::_OnDropFiles(HDROP hdrop)
    {
        POINT point;
        if (DragQueryPoint(hdrop, &point))
        {
            basic::Vector2i position(point.x, point.y);                
            char filepath[MAX_PATH];
            uint32 filecount = DragQueryFile(hdrop, 0xFFFFFFFF, filepath, MAX_PATH);
            basic::Vector<storage::PhysicalPath> files;
            files.Reserve(filecount);
            for (uint32 i=0 ; i<filecount ; ++i)
            {
                if (DragQueryFile(hdrop, i, filepath, MAX_PATH)>0)
                    files.AddItem(filepath);
            }
            if (files.GetSize()>0)
            {
                if (ui::WindowManager::IsAvailable())
                    ui::WindowManager::Get().GetCursor().OnDropFiles(files, position);
            }
        }
    }
    
    //-FUNCTIONS----------------------------------------------------------------------------------//

    LRESULT CALLBACK Device::_WindowFunction(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        int32 scroll;
        char character;

        switch (uMsg)
        {
            case WM_CREATE:
            {
                DragAcceptFiles(hWnd, TRUE);
            } break;

            case WM_DROPFILES:
            {
                Get()._OnDropFiles((HDROP)wParam);
            } break;

            case WM_SYSCOMMAND:
            {
                // Disable screensaver and powersaving
                switch (wParam)
			    {
				    case SC_SCREENSAVE:
				    case SC_MONITORPOWER:
				        return 0;
			    }
            } break;

            case WM_SIZE:
            {
                Get()._UpdateSize(LOWORD(lParam), HIWORD(lParam));
                switch (wParam)
                {
                    case SIZE_MINIMIZED:
                        Get()._ItIsVisible = false;
                        break;

                    case SIZE_MAXIMIZED:
                    case SIZE_RESTORED:
                        Get()._ItIsVisible = true;
                        break;
                }
            } break;

            case WM_SIZING:
            {
                Get()._UpdateSize(((RECT*)(lParam))->right-((RECT*)(lParam))->left,
                    ((RECT*)(lParam))->bottom-((RECT*)(lParam))->top);
            } break;

            case WM_CLOSE:
            {
                Engine::Get().Quit();
                PostQuitMessage(0);
                return 0;
            } break;

            case WM_MOUSEWHEEL:
            {
                if (input::Mouse::IsAvailable())
                {
                    scroll = HIWORD(wParam);
                    if(scroll > 64000) input::Mouse::Get().OnScroll(-1);
                    else input::Mouse::Get().OnScroll(1);
                    return 0;
                }
            } break;

            case WM_CHAR:
            {
                if (input::Keyboard::IsAvailable())
                {
                    character = (char)wParam;
                    bool check = (unsigned)(character+1)<256;
                    if ((check && isgraph(character)) || character == ' ')
                        input::Keyboard::Get().SetCharacterPressed(character);
                    return 0;
                }
            } break;

            case WM_LBUTTONDOWN:
            {
                // Web player focus workaround
                //SetFocus(hWnd);
            } break;
        }
        return (LONG) DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

}
}
#endif
