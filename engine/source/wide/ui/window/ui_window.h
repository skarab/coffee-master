#ifndef _COFFEE_UI_WINDOW_H_
#define _COFFEE_UI_WINDOW_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "kernel/shell/event/shell_event_handler.h"
#include "system/input/input.h"
#include "wide/ui/window/ui_window_state.h"
#include "wide/ui/window/ui_window_style.h"
#include "wide/ui/window/ui_window_hit_type.h"
#include "wide/ui/window/ui_window_event.h"
#include "wide/ui/window/layout/ui_layout.h"

namespace coffee
{
namespace ui
{
    //-FORWARDS-----------------------------------------------------------------------------------//
    class Skin;
    class SkinWidget;
    class SkinContext;
    class WindowContext;
    class WindowManager;
    
    //--------------------------------------------------------------------------------------------//
    /// Window base class
    ///
    /// This is the base class for all windows, it contains layout, skin, and manages basics
    /// behaviors (moving, resizing, hit testing, etc...).
    /// It inherits from shell::EventHandler since GUI and inputs are events based.
    ///
    /// For layout management, all inherited widgets and controls use the ui::Layout
    /// system to control all positioning and resizing policies.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Window : public shell::EventHandler
    {
        friend class WindowContext;
        friend class WindowManager;
        friend class Layout;
        
        COFFEE_Type(Window);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Window();
        virtual ~Window();

        //-ACCESSORS------------------------------------------------------------------------------//

        const Window& GetParentWindow() const;
        Window& GetParentWindow();
        const Window& GetChildWindow(uint32 child_index) const;
        Window& GetChildWindow(uint32 child_index);
        const basic::Rectangle& GetRect() const;
        void SetPosition(const basic::Vector2i& position);
        const basic::Vector2i& GetPosition() const;
        void SetSize(const basic::Vector2i& size);
        const basic::Vector2i& GetSize() const;
        const basic::Rectangle& GetClientRect() const;
        const basic::Vector2i& GetBorders() const;
        void SetStyle(uint32 style);
        uint32 GetStyle() const;
        void SetExtendedStyle(uint32 extended_style);
        uint32 GetExtendedStyle() const;
        void SetSkin(Skin* skin);
        const Skin& GetSkin() const;
        Skin& GetSkin();
        const SkinWidget& GetSkinWidget() const;
        const Layout& GetLayout() const;
        Layout& GetLayout();
        const Window* GetFocus() const;

        //-QUERIES--------------------------------------------------------------------------------//

        bool HasStyle(const WINDOW_STYLE& style) const;
        bool HasStyle(uint32 style) const;
        bool HasExtendedStyle(uint32 extended_style) const;
        bool HasState(const WINDOW_STATE& state) const;
        bool IsVisible() const;
        bool HasSkin() const;

        bool IsActiveWindow() const;
        bool HasFocus() const;
        bool HasCursorOver() const;

        Window* FindActivableParent();
        bool IsParentedBy(const Window* window) const;

        virtual bool Sort(const Window& child1, const Window& child2) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void SendEvent(const WINDOW_EVENT& event, void* parameters=NULL);
        bool SendImmediateEvent(const WINDOW_EVENT& event, void* parameters=NULL);
        bool SendImmediateEvent(const WINDOW_EVENT& event, meta::Object& parameter);

        // if parent==NULL then it attaches to the desktop window
        // if parent==GAME_WINDOW then it attaches to the Application::GetWindow() (useful for components)
        virtual void Create(Window* parent, const basic::Vector2i& position,
            const basic::Vector2i& size, uint32 style);
        
        void Show(bool it_has_to_show);
        void Move(const basic::Vector2i& position);
        void Resize(const basic::Vector2i& size);
        void Activate();
        void SetFocus();
        void KillFocus();
        bool DoModal();
        void Destroy();

        void PositionToCenter();
        void PositionToCursor();
        void PositionToDesktop();

        void UpdateWindow(const basic::Time& time_step);
        virtual void Update();
        Window* HitTest(const basic::Vector2i& position, uint32 style_mask = WINDOW_STYLE_All);
        virtual uint32 HitTestWindow(const basic::Vector2i& position) const;

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(Window);
        COFFEE_Event bool OnShow(shell::Event& event);
        COFFEE_Event bool OnMove(shell::Event& event);
        COFFEE_Event bool OnResize(shell::Event& event);
        COFFEE_Event bool OnActivate(shell::Event& event);
        COFFEE_Event bool OnDeactivate(shell::Event& event);
        COFFEE_Event bool OnSetFocus(shell::Event& event);
        COFFEE_Event bool OnKillFocus(shell::Event& event);
        COFFEE_Event bool OnBeginCursorOver(shell::Event& event);
        COFFEE_Event bool OnEndCursorOver(shell::Event& event);
        COFFEE_Event bool OnScrollUp(shell::Event& event);
        COFFEE_Event bool OnScrollDown(shell::Event& event);
        COFFEE_Event bool OnQueryDrag(shell::Event& event);
        COFFEE_Event bool OnQueryDrop(shell::Event& event);
        COFFEE_Event bool OnDrop(shell::Event& event);
        COFFEE_Event bool OnMouseLeftButtonPressed(shell::Event& event);
        COFFEE_Event bool OnMouseLeftButtonReleased(shell::Event& event);
        COFFEE_Event bool OnMouseDoubleClick(shell::Event& event);
        COFFEE_Event bool OnMouseRightButtonPressed(shell::Event& event);
        COFFEE_Event bool OnMouseRightButtonReleased(shell::Event& event);
        
        bool OnPackEvents(shell::Event& new_event, const shell::Event& old_event);
        void OnDestroyEvent(shell::Event& event);

    protected:

        //-ACCESSORS------------------------------------------------------------------------------//

        void _SetClientRect(const basic::Rectangle& client_rect);

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void _UpdateClientArea();
        virtual void _Paint(const basic::Time& time_step, const SkinContext& paint_context);
        virtual bool _HitTest(const basic::Vector2i& position, const WindowContext& hit_test_context);
        
    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _Draw(const basic::Time& time_step, const WindowContext* parent_context=NULL);
        Window* _InternalHitTest(const basic::Vector2i& position, uint32 style_mask,
            const WindowContext* parent_context=NULL);
        bool _HandleScroll(const WINDOW_EVENT& scroll_message);
        
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Rectangle _Rect;
        basic::Rectangle _ClientRect;
        basic::Vector2i _Borders;
        Window* _Focus;
        uint32 _Style;
        uint32 _ExtendedStyle;
        uint32 _State;
        Skin* _Skin;
        Layout _Layout;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Window);
}
}
#endif
