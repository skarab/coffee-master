#ifndef _COFFEE_UI_WINDOW_MANAGER_H_
#define _COFFEE_UI_WINDOW_MANAGER_H_

#include "coffee_includes.h"
#include "kernel/shell/module/shell_module.h"
#include "wide/ui/window/ui_window.h"
#include "wide/ui/window/ui_desktop_window.h"    
#include "wide/ui/window/cursor/ui_cursor.h"
#include "wide/ui/skin/ui_skin.h"
#include "wide/ui/property/ui_property_manager.h"
#include "wide/ui/window/clip_board/ui_clip_board.h"

#define COFFEE_GUI_DefaultSkin  "/coffee/skins/default.skin"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Window Manager
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API WindowManager : public shell::Module
    {
        friend class Window;
        friend class Cursor;

        COFFEE_DeclareModuleSingleton(WindowManager);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        WindowManager();
        ~WindowManager();

        //-ACCESSORS------------------------------------------------------------------------------//

        const DesktopWindow& GetDesktopWindow() const;
        DesktopWindow& GetDesktopWindow();
        const Window& GetActiveWindow() const;
        Window& GetActiveWindow();
        const Window& GetFocusWindow() const;
        Window& GetFocusWindow();
        const Window& GetCursorOverWindow() const;
        Window& GetCursorOverWindow();
        const Cursor& GetCursor() const;
        Cursor& GetCursor();
        const ClipBoard& GetClipBoard() const;
        ClipBoard& GetClipBoard();

        void SetSkin(const Skin& skin);
        void SetModalWindow(Window* window);
        const Window* GetModalWindow() const;
        void AcceptModalWindow();
        void SetToolTipWindow(Window* window);
        void SetNoToolTipWindow(Window* window);
        Window* GetToolTipWindow() const;

        //-QUERIES--------------------------------------------------------------------------------//

        bool HasDesktopWindow() const;
        bool HasActiveWindow() const;
        bool HasFocusWindow() const;
        bool HasCursorOverWindow() const;
        bool HasModalWindow() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void OnInitialize();
        void OnFinalize();
        void OnStart();
        void OnStop();
        void OnUpdate(const basic::Time& time_step);

        void _CreateDesktopWindow();
        
    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _UpdateToolTip(const basic::Time& time_step);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        DesktopWindow* _DesktopWindow;
        Window* _ActiveWindow;
        Window* _FocusWindow;
        Window* _CursorOverWindow;
        Window* _ModalWindow;
        Cursor* _Cursor;
        Skin* _Skin;
        PropertyManager* _PropertyManager;
        ClipBoard _ClipBoard;
        bool _ModalWindowResult;
        bool _ItHasEndedModalWindow;
        Window* _ToolTipWindow;
        basic::Time _ToolTipTime;
    };
}
}
#endif
