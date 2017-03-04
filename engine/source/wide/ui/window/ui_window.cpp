#include "coffee.h"
#include "wide/ui/window/ui_window.h"
#include "wide/ui/window/ui_window_manager.h"
#include "wide/ui/window/ui_window_context.h"
#include "wide/ui/skin/ui_skin.h"
#include "wide/ui/widget/scroll_bar/widget_scroll_bar.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::Window);
        COFFEE_Ancestor(shell::EventHandler);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Window::Window() :
        _Focus(NULL),
        _Style(WINDOW_STYLE_None),
        _ExtendedStyle(0),
        _State(WINDOW_STATE_None),
        _Skin(NULL)
    {
        _Layout.SetWindow(*this);
    }

    //--------------------------------------------------------------------------------------------//

    Window::~Window()
    {
        if (WindowManager::IsAvailable() && WindowManager::Get()._CursorOverWindow==this)
            WindowManager::Get()._CursorOverWindow = NULL;

        if (WindowManager::IsAvailable() && WindowManager::Get()._FocusWindow==this)
            WindowManager::Get()._FocusWindow = NULL;

        if (WindowManager::IsAvailable() && WindowManager::Get()._ActiveWindow==this)
            WindowManager::Get()._ActiveWindow = NULL;

        if (WindowManager::IsAvailable() && WindowManager::Get().GetCursor()._HitItem==this)
            WindowManager::Get().GetCursor()._HitItem = NULL;

        if (WindowManager::IsAvailable() && WindowManager::Get().GetCursor()._HitWindow==this)
            WindowManager::Get().GetCursor()._HitWindow = NULL;

        if (WindowManager::IsAvailable() && WindowManager::Get()._ModalWindow==this)
            WindowManager::Get()._ModalWindow = NULL;

        if (WindowManager::IsAvailable() && WindowManager::Get().GetCursor()._DragItem==this)
            WindowManager::Get().GetCursor()._DragItem = NULL;

        if (WindowManager::IsAvailable() && WindowManager::Get().GetCursor()._DropItem==this)
            WindowManager::Get().GetCursor()._DropItem = NULL;
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const Window& Window::GetParentWindow() const
    {
        return *((const Window*) &GetParent());
    }

    //--------------------------------------------------------------------------------------------//

    Window& Window::GetParentWindow()
    {
        return *((Window*) &GetParent());
    }

    //--------------------------------------------------------------------------------------------//

    const Window& Window::GetChildWindow(uint32 child_index) const
    {
        return *((const Window*) &GetChild(child_index));
    }

    //--------------------------------------------------------------------------------------------//

    Window& Window::GetChildWindow(uint32 child_index)
    {
        return *((Window*) &GetChild(child_index));
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Rectangle& Window::GetRect() const
    {
        return _Rect;
    }

    //--------------------------------------------------------------------------------------------//

    void Window::SetPosition(const basic::Vector2i& position)
    {
        Move(position);
        _Rect.Position = position;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Vector2i& Window::GetPosition() const
    {
        return _Rect.Position;
    }

    //--------------------------------------------------------------------------------------------//

    void Window::SetSize(const basic::Vector2i& size)
    {
        basic::Vector2i new_size = GetLayout().GetValidSize(size);
        Resize(new_size);
        _Rect.Size = new_size;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Vector2i& Window::GetSize() const
    {
        return _Rect.Size;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Rectangle& Window::GetClientRect() const
    {
        return _ClientRect;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Vector2i& Window::GetBorders() const
    {
        return _Borders;
    }

    //--------------------------------------------------------------------------------------------//

    void Window::SetStyle(uint32 style)
    {
        _Style = style;
    }

    //--------------------------------------------------------------------------------------------//

    uint32 Window::GetStyle() const
    {
        return _Style;
    }

    //--------------------------------------------------------------------------------------------//

    void Window::SetExtendedStyle(uint32 extended_style)
    {
        _ExtendedStyle = extended_style;
    }

    //--------------------------------------------------------------------------------------------//

    uint32 Window::GetExtendedStyle() const
    {
        return _ExtendedStyle;
    }

    //--------------------------------------------------------------------------------------------//

    void Window::SetSkin(Skin* skin)
    {
        _Skin = skin;
    }

    //--------------------------------------------------------------------------------------------//

    const Skin& Window::GetSkin() const
    {
        if (!HasSkin())
        {
            COFFEE_Assert(HasParent(), core::ERROR_CODE_Unexpected, "Incorrect files mount/data suspected...");
            return GetParentWindow().GetSkin();
        }
        return *_Skin;
    }

    //--------------------------------------------------------------------------------------------//

    Skin& Window::GetSkin()
    {
        if (!HasSkin())
            return GetParentWindow().GetSkin();

        return *_Skin;
    }

    //--------------------------------------------------------------------------------------------//

    const SkinWidget& Window::GetSkinWidget() const
    {
        return *GetSkin().GetWidget(*this);
    }

    //--------------------------------------------------------------------------------------------//

    const Layout& Window::GetLayout() const
    {
        return _Layout;
    }

    //--------------------------------------------------------------------------------------------//

    Layout& Window::GetLayout()
    {
        return _Layout;
    }

    //--------------------------------------------------------------------------------------------//

    const Window* Window::GetFocus() const
    {
        return _Focus;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool Window::HasStyle(const WINDOW_STYLE& style) const
    {
        return COFFEE_IsFlagEnabled(_Style, style);
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::HasStyle(uint32 style) const
    {
        return COFFEE_IsFlagEnabled(_Style, style);
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::HasExtendedStyle(uint32 extended_style) const
    {
        return COFFEE_IsFlagEnabled(_ExtendedStyle, extended_style);
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::HasState(const WINDOW_STATE& state) const
    {
        return COFFEE_IsFlagEnabled(_State, state);
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::IsVisible() const
    {
        return HasState(WINDOW_STATE_Visible);
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::HasSkin() const
    {
        return (_Skin != NULL);
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::IsActiveWindow() const
    {
        return (
            WindowManager::Get().HasActiveWindow()
            && this==&WindowManager::Get().GetActiveWindow());
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::HasFocus() const
    {
        return (
            WindowManager::Get().HasFocusWindow()
            && this==&WindowManager::Get().GetFocusWindow());
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::HasCursorOver() const
    {
        return (
            WindowManager::Get().HasCursorOverWindow()
            && this==&WindowManager::Get().GetCursorOverWindow());
    }

    //--------------------------------------------------------------------------------------------//

    Window* Window::FindActivableParent()
    {
        Window* window = this;

        while(!window->HasStyle(WINDOW_STYLE_Activable))
        {
            if (!window->HasParent())
                return NULL;

            window = &window->GetParentWindow();
        }

        return window;
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::IsParentedBy(const Window* window) const
    {
        if (this==window)
            return true;

        if (HasParent())
            return GetParentWindow().IsParentedBy(window);

        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::Sort(const Window& child1, const Window& child2) const
    {
        if (HasParent())
            return GetParentWindow().Sort(child1, child2);
        return false;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Window::SendEvent(const WINDOW_EVENT& event, void* parameters)
    {
        shell::EventCode event_code((uint32) event, Window::GetClassMetaType());
        shell::EventParameters event_parameters(parameters);
        shell::Event shell_event;
        shell_event.Set(event_code, event_parameters,
            shell::EVENT_FLAG_StopWhenHandled|shell::EVENT_FLAG_ForwardToParent);
        shell::EventHandler::SendEvent(shell_event);
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::SendImmediateEvent(const WINDOW_EVENT& event, void* parameters)
    {
        shell::EventCode event_code((uint32) event, Window::GetClassMetaType());
        shell::EventParameters event_parameters(parameters);
        shell::Event shell_event;
        shell_event.Set(event_code, event_parameters,
            shell::EVENT_FLAG_StopWhenHandled|shell::EVENT_FLAG_ForwardToParent);
        return shell::EventHandler::SendImmediateEvent(shell_event);
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::SendImmediateEvent(const WINDOW_EVENT& event, meta::Object& parameter)
    {
        shell::EventCode event_code((uint32) event, Window::GetClassMetaType());
        shell::EventParameters event_parameters;
        event_parameters.SetParameter(&parameter);
        shell::Event shell_event;
        shell_event.Set(event_code, event_parameters,
            shell::EVENT_FLAG_StopWhenHandled|shell::EVENT_FLAG_ForwardToParent);
        return shell::EventHandler::SendImmediateEvent(shell_event);
    }

    //--------------------------------------------------------------------------------------------//

    void Window::Create(Window* parent, const basic::Vector2i& position,
        const basic::Vector2i& size, uint32 style)
    {
        if (parent==NULL)
        {
            if (WindowManager::Get().HasDesktopWindow())
                WindowManager::Get().GetDesktopWindow().Attach(*this,
                    HasStyle(WINDOW_STYLE_BottomMost) ? 0 : NONE);
        }
        else if (parent==GAME_WINDOW)
        {
            Application::Get().GetWindow()->Attach(*this,
                HasStyle(WINDOW_STYLE_BottomMost) ? 0 : NONE);
        }
        else
        {
            parent->Attach(*this, HasStyle(WINDOW_STYLE_BottomMost) ? 0 : NONE);
        }

        _Style = style;

        if (HasParent() && GetSkin().IsAvailable())
            _Borders = GetSkinWidget().GetBorderSize();

        SendEvent(WINDOW_EVENT_Show, (void*)1);    
        SetPosition(position);
        SetSize(size);
    }

    //--------------------------------------------------------------------------------------------//

    void Window::Show(bool it_has_to_show)
    {
        SendEvent(WINDOW_EVENT_Show, (void*)(it_has_to_show?1:0));
    }

    //--------------------------------------------------------------------------------------------//

    void Window::Move(const basic::Vector2i& position)
    {
        if (GetPosition() != position)
            SendEvent(WINDOW_EVENT_Move, (void *) COFFEE_New(basic::Vector2i, position));
    }

    //--------------------------------------------------------------------------------------------//

    void Window::Resize(const basic::Vector2i& size)
    {
        basic::Vector2i new_size = GetLayout().GetValidSize(size);
        if (new_size!=GetSize())
            SendEvent(WINDOW_EVENT_Resize, (void *) COFFEE_New(basic::Vector2i, new_size));
    }

    //--------------------------------------------------------------------------------------------//

    void Window::Activate()
    {
        SendImmediateEvent(WINDOW_EVENT_Activate);
    }

    //--------------------------------------------------------------------------------------------//

    void Window::SetFocus()
    {
        Window* activable_parent = FindActivableParent();

        if (activable_parent!=NULL && !activable_parent->IsActiveWindow())
        {
            activable_parent->_Focus = this;
            activable_parent->Activate();
        }
        else
        {
            SendEvent(WINDOW_EVENT_SetFocus);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Window::KillFocus()
    {
        Window* activable_parent = FindActivableParent();
        if (activable_parent!=NULL && activable_parent->_Focus==this)
        {
            if (WindowManager::Get().HasFocusWindow()
                && this==&WindowManager::Get().GetFocusWindow())
            {
                SendEvent(WINDOW_EVENT_KillFocus);
                WindowManager::Get()._FocusWindow = NULL;
            }

            activable_parent->_Focus = NULL;
        }
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::DoModal()
    {
        Window* modal = WindowManager::Get()._ModalWindow;
        WindowManager::Get().SetModalWindow(this);
        SetFocus();
        while(WindowManager::Get()._ModalWindow!=NULL)
        {
            if (!Engine::Get().Update())
                WindowManager::Get()._ModalWindow->Destroy();
        }
        bool result = WindowManager::Get()._ModalWindowResult;
        WindowManager::Get().SetModalWindow(modal);
        return result;
    }

    //--------------------------------------------------------------------------------------------//

    void Window::Destroy()
    {
        if (HasParent() && !GetParentWindow().IsDestroyed())
            OnShow(shell::Event::Null);
        
        Window* window(this);
        while (window->HasParent())
        {
            window = &window->GetParentWindow();
            if (window->_Focus!=NULL && (window->_Focus==this || IsChild(*window->_Focus)))
                window->_Focus = NULL;
        }

        shell::EventHandler::Destroy();
    }

    //--------------------------------------------------------------------------------------------//

    void Window::PositionToCenter()
    {
        basic::Vector2i screen_center;
        screen_center = WindowManager::Get().GetDesktopWindow().GetSize()/2;
        SetPosition(screen_center-GetSize()/2);
    }

    //--------------------------------------------------------------------------------------------//

    void Window::PositionToCursor()
    {
        basic::Vector2i cursor_position(
            (int32)input::Mouse::Get().GetPosition().X,
            (int32)input::Mouse::Get().GetPosition().Y);
        SetPosition(cursor_position-GetSize()/2);
    }
    
    //--------------------------------------------------------------------------------------------//

    void Window::PositionToDesktop()
    {
        WindowContext context;
        basic::Vector2i position;
        Window& desktop = WindowManager::Get().GetDesktopWindow();

        context.Create(this);
        position = context.GetDesktopWindowRect().GetMinimum();

        if (position.X < desktop.GetClientRect().GetMinimum().X)
            position.X=(desktop.GetClientRect().GetMinimum().X);

        if (position.X + GetSize().X > desktop.GetClientRect().GetMaximum().X)
            position.X=(desktop.GetClientRect().GetMaximum().X - GetSize().X);

        if (position.Y < desktop.GetClientRect().GetMinimum().Y)
            position.Y=desktop.GetClientRect().GetMinimum().Y;

        if (position.Y + GetSize().Y > desktop.GetClientRect().GetMaximum().Y)
            position.Y=desktop.GetClientRect().GetMaximum().Y - GetSize().Y;

        SetPosition(position + (GetPosition() - context.GetDesktopWindowRect().GetMinimum()));
    }

    //--------------------------------------------------------------------------------------------//

    void Window::UpdateWindow(const basic::Time& time_step)
    {
        if (graphics::Module::IsAvailable())
            _Draw(time_step);
        Update();
    }

    //--------------------------------------------------------------------------------------------//

    void Window::Update()
    {
        _UpdateClientArea();
        GetLayout().Update();
    
        if (HasStyle(WINDOW_STYLE_TopMost) && HasParent())
        {
            uint32 index(GetIndex());

            if (index != GetParent().GetChildCount() - 1
                && !GetParentWindow().GetChildWindow(index + 1).HasStyle(WINDOW_STYLE_TopMost))
            {
                GetParent().Attach(*this);
            }
        }

        if (HasStyle(WINDOW_STYLE_BottomMost) && HasParent())
        {
            uint32 child_index(GetIndex());
            if (child_index!=0)
                GetParent().Attach(*this, 0);
        }

        shell::EventHandler::Update();
    }

    //--------------------------------------------------------------------------------------------//

    Window* Window::HitTest(const basic::Vector2i& position, uint32 style_mask)
    {
        return _InternalHitTest(position, style_mask);
    }

    //--------------------------------------------------------------------------------------------//

    uint32 Window::HitTestWindow(const basic::Vector2i& position) const
    {
        WindowContext context;

        context.Create(this);

        uint32 hit_test_result(WINDOW_HIT_TYPE_None);

        if (position.X <= context.GetDesktopWindowRect().GetMinimum().X + GetBorders().X + 2)
            hit_test_result |= WINDOW_HIT_TYPE_BorderLeft;

        if (position.X >= context.GetDesktopWindowRect().GetMaximum().X - GetBorders().X - 2)
            hit_test_result |= WINDOW_HIT_TYPE_BorderRight;

        if (position.Y <= context.GetDesktopWindowRect().GetMinimum().Y + GetBorders().Y + 2)
            hit_test_result |= WINDOW_HIT_TYPE_BorderTop;

        if (position.Y >= context.GetDesktopWindowRect().GetMaximum().Y - GetBorders().Y - 2)
            hit_test_result |= WINDOW_HIT_TYPE_BorderBottom;

        return hit_test_result;
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(Window, shell::EventHandler)
        COFFEE_RegisterEventHandler(WINDOW_EVENT_Show, Window, OnShow)
        COFFEE_RegisterEventHandler(WINDOW_EVENT_Move, Window, OnMove)
        COFFEE_RegisterEventHandler(WINDOW_EVENT_Resize, Window, OnResize)
        COFFEE_RegisterEventHandler(WINDOW_EVENT_Activate, Window, OnActivate)
        COFFEE_RegisterEventHandler(WINDOW_EVENT_Deactivate, Window, OnDeactivate)
        COFFEE_RegisterEventHandler(WINDOW_EVENT_SetFocus, Window, OnSetFocus)
        COFFEE_RegisterEventHandler(WINDOW_EVENT_KillFocus, Window, OnKillFocus)
        COFFEE_RegisterEventHandler(WINDOW_EVENT_BeginCursorOver, Window, OnBeginCursorOver)
        COFFEE_RegisterEventHandler(WINDOW_EVENT_EndCursorOver, Window, OnEndCursorOver)
        COFFEE_RegisterEventHandler(WINDOW_EVENT_ScrollUp, Window, OnScrollUp)
        COFFEE_RegisterEventHandler(WINDOW_EVENT_ScrollDown, Window, OnScrollDown)
        COFFEE_RegisterEventHandler(WINDOW_EVENT_QueryDrag, Window, OnQueryDrag)
        COFFEE_RegisterEventHandler(WINDOW_EVENT_QueryDrop, Window, OnQueryDrop)
        COFFEE_RegisterEventHandler(WINDOW_EVENT_Drop, Window, OnDrop)
        COFFEE_RegisterEventHandler(input::EVENT_MouseLeftButtonPressed, input::Handler, OnMouseLeftButtonPressed)
        COFFEE_RegisterEventHandler(input::EVENT_MouseLeftButtonReleased, input::Handler, OnMouseLeftButtonReleased)
        COFFEE_RegisterEventHandler(input::EVENT_MouseDoubleClick, input::Handler, OnMouseDoubleClick)
        COFFEE_RegisterEventHandler(input::EVENT_MouseRightButtonPressed, input::Handler, OnMouseRightButtonPressed)
        COFFEE_RegisterEventHandler(input::EVENT_MouseRightButtonReleased, input::Handler, OnMouseRightButtonReleased)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool Window::OnShow(shell::Event& event)
    {
        if (HasState(WINDOW_STATE_Visible)==!event.GetBoolean())
        {
            _State ^= (uint32) WINDOW_STATE_Visible;
            GetLayout().OnShow(HasState(WINDOW_STATE_Visible));
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::OnMove(shell::Event& event)
    {
        basic::Vector2i* position = (basic::Vector2i*) event.GetParameters().GetCustomParameter();
        _Rect.Position = *position;
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::OnResize(shell::Event& event)
    {
        basic::Vector2i* size = (basic::Vector2i*) event.GetParameters().GetCustomParameter();
        _Rect.Size = *size;
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::OnActivate(shell::Event& event)
    {
        if (event.GetTarget() == this)
        {
            if (WindowManager::Get().HasActiveWindow())
                WindowManager::Get().GetActiveWindow().SendEvent(WINDOW_EVENT_Deactivate);

            WindowManager::Get()._ActiveWindow = this;

            if (_Focus!=NULL)
            {
                if (!_Focus->HasFocus())
                    _Focus->SendEvent(WINDOW_EVENT_SetFocus);
            }
            else
            {
                if (WindowManager::Get().HasFocusWindow()
                    && this!=&WindowManager::Get().GetFocusWindow())
                {
                    WindowManager::Get().GetFocusWindow().SendEvent(WINDOW_EVENT_KillFocus);
                }

                WindowManager::Get()._FocusWindow = NULL;
            }
        }

        if (HasParent() && !HasStyle(WINDOW_STYLE_BottomMost))
            GetParent().Attach(*this);
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::OnDeactivate(shell::Event& event)
    {
        if (WindowManager::Get()._ActiveWindow==this)
            WindowManager::Get()._ActiveWindow = NULL;
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::OnSetFocus(shell::Event& event)
    {
        if (event.GetTarget() == this)
        {
            if (WindowManager::Get().HasFocusWindow() && WindowManager::Get()._FocusWindow != this)
                WindowManager::Get().GetFocusWindow().SendEvent(WINDOW_EVENT_KillFocus);

            WindowManager::Get()._FocusWindow = this;

            if (HasParent())
                GetParentWindow()._Focus = this;
        }

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::OnKillFocus(shell::Event& event)
    {
        if (HasState(WINDOW_STATE_MouseLeftButtonPressed))
        {
            shell::Event input_event;
            input_event.Set(shell::EventCode(input::EVENT_MouseLeftButtonReleased, input::Handler::GetClassMetaType()),
                shell::EventParameters((void*)COFFEE_New(input::EventMouse, GetPosition())),
                shell::EVENT_FLAG_StopWhenHandled|shell::EVENT_FLAG_ForwardToParent);
            shell::EventHandler::SendImmediateEvent(input_event);      
        }

        if (HasState(WINDOW_STATE_MouseRightButtonPressed))
        {
            shell::Event input_event;
            input_event.Set(shell::EventCode(input::EVENT_MouseRightButtonReleased, input::Handler::GetClassMetaType()),
                shell::EventParameters((void*)COFFEE_New(input::EventMouse, GetPosition())),
                shell::EVENT_FLAG_StopWhenHandled|shell::EVENT_FLAG_ForwardToParent);
            shell::EventHandler::SendImmediateEvent(input_event);      
        }

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::OnBeginCursorOver(shell::Event& event)
    {
        if (event.GetTarget() == this)
        {
            if (WindowManager::Get().HasCursorOverWindow())
                WindowManager::Get().GetCursorOverWindow().SendEvent(WINDOW_EVENT_EndCursorOver);

            WindowManager::Get()._CursorOverWindow = this;
        }

        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::OnEndCursorOver(shell::Event& event)
    {
         return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::OnScrollUp(shell::Event& event)
    {
        return _HandleScroll((WINDOW_EVENT) event.GetCode().GetIdentifier());
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::OnScrollDown(shell::Event& event)
    {
        return _HandleScroll((WINDOW_EVENT) event.GetCode().GetIdentifier());
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::OnQueryDrag(shell::Event& event)
    {
        return false;
    }
    
    //--------------------------------------------------------------------------------------------//

    bool Window::OnQueryDrop(shell::Event& event)
    {
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::OnDrop(shell::Event& event)
    {
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::OnMouseLeftButtonPressed(shell::Event& event)
    {
        if (!HasState(WINDOW_STATE_MouseLeftButtonPressed))
            _State ^= (uint32) WINDOW_STATE_MouseLeftButtonPressed;
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::OnMouseLeftButtonReleased(shell::Event& event)
    {
        if (HasState(WINDOW_STATE_MouseLeftButtonPressed))
            _State ^= (uint32) WINDOW_STATE_MouseLeftButtonPressed;
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::OnMouseDoubleClick(shell::Event& event)
    {
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::OnMouseRightButtonPressed(shell::Event& event)
    {
        if (!HasState(WINDOW_STATE_MouseRightButtonPressed))
            _State ^= (uint32) WINDOW_STATE_MouseRightButtonPressed;
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::OnMouseRightButtonReleased(shell::Event& event)
    {
        if (HasState(WINDOW_STATE_MouseRightButtonPressed))
            _State ^= (uint32) WINDOW_STATE_MouseRightButtonPressed;
        return true;
    }
        
    //--------------------------------------------------------------------------------------------//

    bool Window::OnPackEvents(shell::Event& new_event, const shell::Event& old_event)
    {
        if (&new_event.GetCode().GetType()==&GetClassMetaType()
            && &old_event.GetCode().GetType()==&GetClassMetaType()
            && new_event.GetCode().GetIdentifier()==old_event.GetCode().GetIdentifier())
        {
            switch((WINDOW_EVENT)new_event.GetCode().GetIdentifier())
            {
                case WINDOW_EVENT_Resize:
                case WINDOW_EVENT_Move:
                case WINDOW_EVENT_Show:                  
                    return true;

                default:
                    break;
            }
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    void Window::OnDestroyEvent(shell::Event& event)
    {
        if (&event.GetCode().GetType()==&GetClassMetaType())
        {
            basic::Vector2i* vector;
            switch((WINDOW_EVENT)event.GetCode().GetIdentifier())
            {
                case WINDOW_EVENT_Resize:
                case WINDOW_EVENT_Move:
                    vector = (basic::Vector2i*) event.GetParameters().GetCustomParameter();
                    COFFEE_Delete(vector);
                    break;

                default:
                    break;
            }
        }
        else
        {
            input::Handler::ForwardDestroyEvent(event);
        }
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Window::_SetClientRect(const basic::Rectangle& client_rect)
    {
        _ClientRect = client_rect;
        _ClientRect.Size = basic::Vector2i(
            Maximum(0, _ClientRect.Size.X),
            Maximum(0, _ClientRect.Size.Y));
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Window::_UpdateClientArea()
    {
        if (HasParent() && GetSkin().IsAvailable())
            _Borders = GetSkinWidget().GetBorderSize();
        _ClientRect.Position = basic::Vector2i(_Borders.X, _Borders.Y);
        _ClientRect.Size = basic::Vector2i(
            Maximum(0, _Rect.Size.X - _Borders.X * 2),
            Maximum(0, _Rect.Size.Y - _Borders.Y * 2));
    }

    //--------------------------------------------------------------------------------------------//

    void Window::_Paint(const basic::Time& time_step, const SkinContext& paint_context)
    {
        basic::Rectangle rect(paint_context.GetDesktopWindowRect());
        rect -= paint_context.GetDesktopClipRect();
        if (rect.IsEmpty())
            return;

        ((SkinContext*) &paint_context)->GetSkin().DrawWindow(*this, paint_context);

        for (uint32 child_index=0 ; child_index<GetChildCount() ; ++child_index)
            GetChildWindow(child_index)._Draw(time_step, &paint_context);
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::_HitTest(const basic::Vector2i& position, const WindowContext& hit_test_context)
    {
        return hit_test_context.GetDesktopWindowRect().IsPointInside(position)
            && hit_test_context.GetDesktopClipRect().IsPointInside(position);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//
    
    void Window::_Draw(const basic::Time& time_step, const WindowContext* parent_context)
    {
        if (!HasState(WINDOW_STATE_Visible) || GetRect().IsEmpty())
            return;

        SkinContext* context;

        if (HasSkin())
        {
            context = GetSkin().CreateContext();
        }
        else if (parent_context!=NULL && parent_context->HasSkin())
        {
            context = parent_context->GetSkin().CreateContext();
        }
        else
        {
            COFFEE_Error(core::ERROR_CODE_WindowManager, "At least one skin as to be set on the root window.");
        }

        context->Create(this, parent_context);

        if (!context->GetDesktopClipRect().IsEmpty()) //|| HasStyle(WINDOW_STYLE_NoParentClientClip))
            _Paint(time_step, *context);

        COFFEE_Delete(context);
    }

    //--------------------------------------------------------------------------------------------//
    
    Window* Window::_InternalHitTest(const basic::Vector2i& position, uint32 style_mask,
        const WindowContext* parent_context)
    {
        if (!HasState(WINDOW_STATE_Visible))
            return false;

        WindowContext context;
        int32 child_index;
        Window * hit_window;

        context.Create(this, parent_context);

        for (child_index=(int32)GetChildCount()-1 ; child_index>=0 ; --child_index)
        {
            hit_window = GetChildWindow(child_index)._InternalHitTest(position, style_mask, &context);

            if (hit_window != NULL)
                return hit_window;
        }

        if ((style_mask==WINDOW_STYLE_All || HasStyle(style_mask)) && _HitTest(position, context))
            return this;
        
        return NULL;
    }

    //--------------------------------------------------------------------------------------------//

    bool Window::_HandleScroll(const WINDOW_EVENT& scroll_message)
    {
        uint32 child_index;
        widget::ScrollBar* scroll_bar(NULL);

        for (child_index=0 ; child_index<GetChildCount() ; ++child_index)
        {
            if (GetChildWindow(child_index).IsA<ui::widget::ScrollBar>())
            {
                scroll_bar = (widget::ScrollBar*) &GetChildWindow(child_index);

                if (!scroll_bar->HasExtendedStyle((uint32) widget::SCROLL_BAR_STYLE_Horizontal))
                {
                    scroll_bar->Window::SendEvent(scroll_message);
                    return true;
                }

                break;
            }
        }

        if (scroll_bar!=NULL)
        {
            scroll_bar->Window::SendEvent(scroll_message);
            return true;
        }

        return false;
    }

}
}
