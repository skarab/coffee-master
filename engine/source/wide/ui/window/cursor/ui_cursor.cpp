#include "wide/ui/window/cursor/ui_cursor.h"
#include "wide/ui/window/ui_window_manager.h"
#include "wide/ui/widget/widgets.h"
#include "system/input/input.h"
#include "system/graphics/graphics.h"
#include "wide/application/application.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::Cursor);
        COFFEE_Ancestor(input::Handler);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Cursor::Cursor() :
        _DragContext(NULL),
        _ItIsResizing(false),
        _ItIsCapturing(false),
        _HitWindow(NULL),
        _HitItem(NULL),
        _DragItem(NULL),
        _DropItem(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Cursor::~Cursor()
    {
        if (_DragContext!=NULL)
        {
            COFFEE_Delete(_DragContext);
            _DragContext = NULL;
        }
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Cursor::SetIcon(const SKIN_ICON& icon)
    {
        if (resource::Manager::IsAvailable()
            && WindowManager::Get().GetDesktopWindow().GetSkin().IsAvailable())
        {
            SetIcon(WindowManager::Get().GetDesktopWindow().GetSkin().GetIcon(icon));
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Cursor::SetIcon(graphics::Texture icon)
    {
        _Icon = icon;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Cursor::BeginCapture()
    {
        _ItIsCapturing = true;

        if (input::Mouse::IsAvailable())
            input::Mouse::Get().BeginCapture();
    }

    //--------------------------------------------------------------------------------------------//

    void Cursor::EndCapture()
    {
        _ItIsCapturing = false;

       if (input::Mouse::IsAvailable())
            input::Mouse::Get().EndCapture();
    }

    //--------------------------------------------------------------------------------------------//

    void Cursor::Update()
    {
        if (input::Mouse::IsAvailable()
            && WindowManager::IsAvailable()
            && WindowManager::Get().HasCursorOverWindow())
        {
            if (input::Mouse::Get().IsButtonPressed(input::BUTTON_ScrollUp))
            {
                WindowManager::Get().GetCursorOverWindow().SendEvent(WINDOW_EVENT_ScrollUp);
            }
            else if (input::Mouse::Get().IsButtonPressed(input::BUTTON_ScrollDown))
            {
                WindowManager::Get().GetCursorOverWindow().SendEvent(WINDOW_EVENT_ScrollDown);
            }
        }

        input::Mouse::Get().ShowMouseCursor(
            !graphics::Module::IsAvailable()
            || !Application::IsInstantiated()
            || !Application::Get().HasFocus());
    }

    //--------------------------------------------------------------------------------------------//

    void Cursor::Draw()
    {
        if (_ItIsCapturing)
            return;
        
        if (graphics::Module::IsAvailable() && _Icon.IsAvailable()
            && Application::IsInstantiated() && Application::Get().HasFocus())
        {
            basic::Vector2i minimum_position, maximum_position;

            graphics::Renderer::Get().EnableDepthTest(false);
            graphics::Renderer::Get().SetColor(basic::Color(1.0f, 1.0f, 1.0f, 1.0f));
            graphics::Renderer::Get().EnableBlending(true);
            graphics::Renderer::Get().SetBlendingFactors(
                graphics::RENDER_STATE_BLENDING_FACTOR_SourceAlpha,
                graphics::RENDER_STATE_BLENDING_FACTOR_SourceAlphaInversed);

            minimum_position.Set(
                (int32) input::Mouse::Get().GetPosition().X
                - ((graphics::Texture2D *) &_Icon.GetResource())->GetImage().GetWidth() / 2,
                (int32) input::Mouse::Get().GetPosition().Y
                - ((graphics::Texture2D *) &_Icon.GetResource())->GetImage().GetHeight() / 2);

            maximum_position.Set(
                minimum_position.X + ((graphics::Texture2D *) &_Icon.GetResource())->GetImage().GetWidth(),
                minimum_position.Y + ((graphics::Texture2D *) &_Icon.GetResource())->GetImage().GetHeight());

            _Icon.Bind(0);
            graphics::GeometricRenderer::RenderViewportTexturedRectangle(minimum_position, maximum_position);
            _Icon.UnBind(0);
        }

        if (_DragItem!=NULL && _DropItem!=NULL && _DropItem!=_DragItem)
        {
            SkinContext paint_context;
            paint_context.Create(_DragItem, NULL);
            paint_context.Set(input::Mouse::Get().GetPosition()+basic::Vector2i(24, 0),
                _DragItem->GetSize());
            paint_context.SetSkin(&_DragItem->GetSkin());
            _DragItem->GetSkin().DrawWindow(*_DragItem, paint_context);
        }
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(Cursor, input::Handler)
        COFFEE_RegisterEventHandler(input::EVENT_KeyPressed, input::Handler, OnKeyPressed)
        COFFEE_RegisterEventHandler(input::EVENT_KeyReleased, input::Handler, OnKeyReleased)
        COFFEE_RegisterEventHandler(input::EVENT_CharacterKeyPressed, input::Handler, OnCharacterKeyPressed)
        COFFEE_RegisterEventHandler(input::EVENT_MouseMove, input::Handler, OnMouseMove)
        COFFEE_RegisterEventHandler(input::EVENT_MouseLeftButtonPressed, input::Handler, OnMouseLeftButtonPressed)
        COFFEE_RegisterEventHandler(input::EVENT_MouseLeftButtonReleased, input::Handler, OnMouseLeftButtonReleased)
        COFFEE_RegisterEventHandler(input::EVENT_MouseDoubleClick, input::Handler, OnMouseDoubleClick)
        COFFEE_RegisterEventHandler(input::EVENT_MouseRightButtonPressed, input::Handler, OnMouseRightButtonPressed)
        COFFEE_RegisterEventHandler(input::EVENT_MouseRightButtonReleased, input::Handler, OnMouseRightButtonReleased)
        COFFEE_RegisterEventHandler(input::EVENT_Command, input::Handler, OnCommand)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool Cursor::OnKeyPressed(shell::Event& event)
    {
        input::EventKey* parameter = (input::EventKey*)
            event.GetParameters().GetCustomParameter();
    
        if (WindowManager::IsAvailable() && WindowManager::Get().HasFocusWindow())
        {
            shell::Event forward_event;
            input::EventKey* custom_parameter = COFFEE_New(input::EventKey, 
                parameter->Key, parameter->ItIsRepeating);
            forward_event.Set(event.GetCode(), shell::EventParameters((void*)custom_parameter),
                shell::EVENT_FLAG_StopWhenHandled|shell::EVENT_FLAG_ForwardToParent);
            return WindowManager::Get().GetFocusWindow().shell::EventHandler::SendImmediateEvent(forward_event);
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Cursor::OnKeyReleased(shell::Event& event)
    {
        input::EventKey* parameter = (input::EventKey*)
            event.GetParameters().GetCustomParameter();
    
        if (WindowManager::IsAvailable() && WindowManager::Get().HasFocusWindow())
        {
            shell::Event forward_event;
            input::EventKey* custom_parameter = COFFEE_New(input::EventKey, 
                parameter->Key, parameter->ItIsRepeating);
            forward_event.Set(event.GetCode(), shell::EventParameters((void*)custom_parameter),
                shell::EVENT_FLAG_StopWhenHandled|shell::EVENT_FLAG_ForwardToParent);
            return WindowManager::Get().GetFocusWindow().shell::EventHandler::SendImmediateEvent(forward_event);
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//
   
    bool Cursor::OnCharacterKeyPressed(shell::Event& event)
    {
        if (WindowManager::IsAvailable() && WindowManager::Get().HasFocusWindow())
        {
            event.SetFlags(shell::EVENT_FLAG_StopWhenHandled|shell::EVENT_FLAG_ForwardToParent);
            return WindowManager::Get().GetFocusWindow().shell::EventHandler::SendImmediateEvent(shell::Event(event));
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//
   
    bool Cursor::OnMouseMove(shell::Event& event)
    {
        _DropItem = NULL;
        input::EventMouse* parameter = (input::EventMouse*)
            event.GetParameters().GetCustomParameter();

        if (!WindowManager::IsAvailable())
            return false;

        if (_DragContext!=NULL)
        {
            basic::Vector2i window_position;
            basic::Vector2i window_size;

            if (_ItIsResizing)
            {
                window_position = _DragContext->GetWindowPosition();
                window_size = _DragContext->GetWindowSize();

                if (_HitTestResult & WINDOW_HIT_TYPE_BorderLeft)
                {
                    int32 move_x = parameter->Position.X - _DragContext->GetPosition().X;

                    move_x = - (Maximum(_DragContext->GetWindow().GetLayout().GetMinimumSize().X,
                        window_size.X - move_x) - window_size.X);

                    window_position.X=(window_position.X + move_x);
                    window_size.X=(window_size.X - move_x);
                }

                if (_HitTestResult & WINDOW_HIT_TYPE_BorderRight)
                {
                    window_size.X=(window_size.X + parameter->Position.X - _DragContext->GetPosition().X);
                }

                if (_HitTestResult & WINDOW_HIT_TYPE_BorderTop)
                {
                    int32 move_y = parameter->Position.Y - _DragContext->GetPosition().Y;

                    move_y = - (Maximum(_DragContext->GetWindow().GetLayout().GetMinimumSize().Y,
                        window_size.Y - move_y) - window_size.Y);

                    window_position.Y=window_position.Y + move_y;
                    window_size.Y=window_size.Y - move_y;
                }

                if (_HitTestResult & WINDOW_HIT_TYPE_BorderBottom)
                {
                    window_size.Y=window_size.Y + parameter->Position.Y - _DragContext->GetPosition().Y;
                }

                _DragContext->GetWindow().Move(window_position);
                _DragContext->GetWindow().Resize(window_size);
            }
            else
            {
                //SetIcon(SKIN_ICON_CursorMove);
                window_position = _DragContext->GetWindowPosition() + parameter->Position - _DragContext->GetPosition();
                _DragContext->GetWindow().Move(window_position);
            }
            return true;
        }
        else
        {
            _ItIsResizing = false;

            Window* hit_window;
            Window* hit_item;

            SetIcon(SKIN_ICON_CursorDefault);

            hit_window = WindowManager::Get().GetDesktopWindow().HitTest(parameter->Position, WINDOW_STYLE_Activable);

            if (hit_window!=NULL && WindowManager::Get().HasModalWindow()
                && !hit_window->IsParentedBy(WindowManager::Get()._ModalWindow))
            {
                return true;
            }

            if (hit_window!=NULL && hit_window->HasStyle(WINDOW_STYLE_Resizeable))
            {
                _HitTestResult = hit_window->HitTestWindow(parameter->Position);

                if (_IsResizingAvailable(*hit_window, _HitTestResult))
                {
                    _ItIsResizing = true;

                    if (_HitTestResult&WINDOW_HIT_TYPE_BorderTop && _HitTestResult&WINDOW_HIT_TYPE_BorderLeft)
                        SetIcon(SKIN_ICON_CursorResizeUpLeft);
                    else if (_HitTestResult&WINDOW_HIT_TYPE_BorderTop && _HitTestResult&WINDOW_HIT_TYPE_BorderRight)
                        SetIcon(SKIN_ICON_CursorResizeUpRight);
                    else if (_HitTestResult&WINDOW_HIT_TYPE_BorderBottom && _HitTestResult&WINDOW_HIT_TYPE_BorderRight)
                        SetIcon(SKIN_ICON_CursorResizeDownRight);
                    else if (_HitTestResult&WINDOW_HIT_TYPE_BorderBottom && _HitTestResult&WINDOW_HIT_TYPE_BorderLeft)
                        SetIcon(SKIN_ICON_CursorResizeDownLeft);
                    else if (_HitTestResult&WINDOW_HIT_TYPE_BorderTop)
                        SetIcon(SKIN_ICON_CursorResizeUp);
                    else if (_HitTestResult&WINDOW_HIT_TYPE_BorderBottom)
                        SetIcon(SKIN_ICON_CursorResizeDown);
                    else if (_HitTestResult&WINDOW_HIT_TYPE_BorderLeft)
                        SetIcon(SKIN_ICON_CursorResizeLeft);
                    else if (_HitTestResult&WINDOW_HIT_TYPE_BorderRight)
                        SetIcon(SKIN_ICON_CursorResizeRight);
                }
            }

            if (hit_window != NULL
                && ((hit_item = hit_window->HitTest(parameter->Position, WINDOW_STYLE_Focusable)) == NULL
                    || hit_item->IsEnabled()))
            {
                if (hit_item==NULL)
                    hit_item = hit_window;

                if (hit_item->IsKindOf<widget::EditBox>()
                    && !static_cast<widget::EditBox *>(hit_item)->IsReadOnly())
                {
                    SetIcon(SKIN_ICON_CursorEditText);
                }

                _DropItem = hit_item;

                if (_DragItem!=NULL && _DropItem!=_DragItem)
                {
                    if (hit_item->SendImmediateEvent(WINDOW_EVENT_QueryDrop, *_DragItem))
                    {
                        SetIcon(SKIN_ICON_CursorDrop);
                    }
                    else
                    {
                        SetIcon(SKIN_ICON_CursorNoDrop);
                    }
                }

                if (hit_item!=WindowManager::Get()._CursorOverWindow)
                    hit_item->SendImmediateEvent(WINDOW_EVENT_BeginCursorOver);
            }
            else
            {
                if (WindowManager::Get().HasCursorOverWindow())
                {
                    WindowManager::Get().GetCursorOverWindow().SendImmediateEvent(WINDOW_EVENT_EndCursorOver);
                    WindowManager::Get()._CursorOverWindow = NULL;
                }
            }

            if (WindowManager::IsAvailable() && WindowManager::Get().HasFocusWindow())
            {
                shell::Event forward_event;
                input::EventMouse* custom_parameter = COFFEE_New(input::EventMouse, 
                    parameter->Position);
                forward_event.Set(event.GetCode(), shell::EventParameters((void*)custom_parameter),
                    shell::EVENT_FLAG_StopWhenHandled|shell::EVENT_FLAG_ForwardToParent);
                WindowManager::Get().GetFocusWindow().shell::EventHandler::SendImmediateEvent(forward_event);
            }
            
            if (!(hit_window == NULL || hit_window == &WindowManager::Get().GetDesktopWindow()
                || hit_window->HasStyle(WINDOW_STYLE_ForwardsInput)))
            {
                return true;
            }
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Cursor::OnMouseLeftButtonPressed(shell::Event& event)
    {
        input::EventMouse* parameter = (input::EventMouse*)
            event.GetParameters().GetCustomParameter();

        _HitItem = NULL;
        _DragItem = NULL;

        if (_ItIsCapturing)
            return true;
        
        if (!WindowManager::IsAvailable())
            return false;

        Window* hit_window;

        hit_window = WindowManager::Get().GetDesktopWindow().HitTest(parameter->Position, WINDOW_STYLE_Activable);

        if (hit_window != NULL && WindowManager::Get().HasModalWindow()
            && !hit_window->IsParentedBy(WindowManager::Get()._ModalWindow))
        {
            return true;
        }

        _HitWindow = hit_window;

        if (_HitWindow != NULL)
        {
            _HitItem = _HitWindow->HitTest(parameter->Position, WINDOW_STYLE_Focusable);

            if (!_ItIsResizing && (_HitItem!=NULL
                && ((_HitItem!=_HitWindow)
                    ||(_HitItem->HasStyle(WINDOW_STYLE_Focusable)&&_HitItem->HasStyle(WINDOW_STYLE_Activable)))))
            {
                if (_HitItem->HasStyle(WINDOW_STYLE_Focusable))
                {
                    _HitItem->SetFocus();
                    if (_HitItem==NULL)
                        return true;

                    if (_HitItem->SendImmediateEvent(WINDOW_EVENT_QueryDrag))
                        _DragItem = _HitItem;

                    shell::Event forward_event;
                    input::EventMouse* custom_parameter = COFFEE_New(input::EventMouse, 
                        parameter->Position);
                    forward_event.Set(event.GetCode(), shell::EventParameters((void*)custom_parameter),
                        shell::EVENT_FLAG_StopWhenHandled|shell::EVENT_FLAG_ForwardToParent);
                    _HitItem->shell::EventHandler::SendImmediateEvent(forward_event);
                }
            }
            else if (_HitWindow->HasStyle(WINDOW_STYLE_Draggable) || _HitWindow->HasStyle(WINDOW_STYLE_Resizeable))
            {
                _HitTestResult = _HitWindow->HitTestWindow(parameter->Position);
                _DragContext = COFFEE_New(DragContext, _HitWindow, parameter->Position, _HitWindow->GetPosition(), _HitWindow->GetSize());
                _HitWindow->SetFocus();

                if (_IsResizingAvailable(*_HitWindow, _HitTestResult))
                {
                    _ItIsResizing = true;
                }
                else
                {
                    _ItIsResizing = false;

                    if (!_HitWindow->HasStyle(WINDOW_STYLE_Draggable))
                    {
                        COFFEE_Delete(_DragContext);
                        _DragContext = NULL;
                    }
                }
            }

            if (!_HitWindow->IsActiveWindow())
                _HitWindow->Activate();
        }

        if (!(((_HitItem == NULL || _HitItem == &WindowManager::Get().GetDesktopWindow())
            && _HitWindow==&WindowManager::Get().GetDesktopWindow())
            || (_HitItem != NULL && _HitItem->HasStyle(WINDOW_STYLE_ForwardsInput))
            || (_HitWindow != NULL && _HitWindow->HasStyle(WINDOW_STYLE_ForwardsInput))))
        {
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Cursor::OnMouseLeftButtonReleased(shell::Event& event)
    {
        input::EventMouse* parameter = (input::EventMouse*)
            event.GetParameters().GetCustomParameter();

        if (_DragContext!=NULL)
        {
            COFFEE_Delete(_DragContext);
            _DragContext = NULL;
        }

        if (!WindowManager::IsAvailable())
        {
            _DragItem = NULL;
            return false;
        }

        if (WindowManager::Get().HasFocusWindow()
            && WindowManager::Get().GetFocusWindow().HasState(WINDOW_STATE_MouseLeftButtonPressed))
        {
            shell::Event forward_event;
            input::EventMouse* custom_parameter = COFFEE_New(input::EventMouse, 
                parameter->Position);
            forward_event.Set(event.GetCode(), shell::EventParameters((void*)custom_parameter),
                shell::EVENT_FLAG_StopWhenHandled|shell::EVENT_FLAG_ForwardToParent);
            WindowManager::Get().GetFocusWindow().shell::EventHandler::SendImmediateEvent(forward_event);
        }

        if (_DragItem!=NULL && _DropItem!=NULL && _DropItem!=_DragItem)
        {
            if (_DropItem->SendImmediateEvent(WINDOW_EVENT_QueryDrop, *_DragItem))
                _DropItem->SendImmediateEvent(WINDOW_EVENT_Drop, *_DragItem);
        }
        _DragItem = NULL;
        
        SetIcon(SKIN_ICON_CursorDefault);

        if (!(((_HitItem == NULL || _HitItem == &WindowManager::Get().GetDesktopWindow())
            && _HitWindow==&WindowManager::Get().GetDesktopWindow())
            || (_HitItem != NULL && _HitItem->HasStyle(WINDOW_STYLE_ForwardsInput))
            || (_HitWindow != NULL && _HitWindow->HasStyle(WINDOW_STYLE_ForwardsInput))))
        {
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Cursor::OnMouseDoubleClick(shell::Event& event)
    {
        input::EventMouse* parameter = (input::EventMouse*)
            event.GetParameters().GetCustomParameter();

        if (_ItIsCapturing)
            return true;
        
        if (!WindowManager::IsAvailable())
            return false;

        if (WindowManager::Get().HasFocusWindow())
        {
            shell::Event forward_event;
            input::EventMouse* custom_parameter = COFFEE_New(input::EventMouse, 
                parameter->Position);
            forward_event.Set(event.GetCode(), shell::EventParameters((void*)custom_parameter),
                shell::EVENT_FLAG_StopWhenHandled|shell::EVENT_FLAG_ForwardToParent);
            WindowManager::Get().GetFocusWindow().shell::EventHandler::SendImmediateEvent(forward_event);
        }

        if (!(((_HitItem == NULL || _HitItem == &WindowManager::Get().GetDesktopWindow())
            && _HitWindow==&WindowManager::Get().GetDesktopWindow())
            || (_HitItem != NULL && _HitItem->HasStyle(WINDOW_STYLE_ForwardsInput))
            || (_HitWindow != NULL && _HitWindow->HasStyle(WINDOW_STYLE_ForwardsInput))))
        {
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Cursor::OnMouseRightButtonPressed(shell::Event& event)
    {
        input::EventMouse* parameter = (input::EventMouse*)
            event.GetParameters().GetCustomParameter();

        _HitItem = NULL;

        if (_ItIsCapturing)
            return true;
        
        if (!WindowManager::IsAvailable())
            return false;

        Window* hit_window;

        hit_window = WindowManager::Get().GetDesktopWindow().HitTest(parameter->Position, WINDOW_STYLE_Activable);

        if (hit_window != NULL && WindowManager::Get().HasModalWindow()
            && !hit_window->IsParentedBy(WindowManager::Get()._ModalWindow))
        {
            return true;
        }

        _HitWindow = hit_window;

        if (_HitWindow != NULL)
        {
            if (!_HitWindow->IsActiveWindow())
                _HitWindow->Activate();

            _HitItem = _HitWindow->HitTest(parameter->Position, WINDOW_STYLE_Focusable);

            if (_HitItem != NULL
                && ((_HitItem!=_HitWindow)
                    ||(_HitItem->HasStyle(WINDOW_STYLE_Focusable)&&_HitItem->HasStyle(WINDOW_STYLE_Activable))))
            {
                if (_HitItem->HasStyle(WINDOW_STYLE_Focusable))
                {
                    _HitItem->SetFocus();
                    if (_HitItem==NULL)
                        return true;

                    shell::Event forward_event;
                    input::EventMouse* custom_parameter = COFFEE_New(input::EventMouse, 
                        parameter->Position);
                    forward_event.Set(event.GetCode(), shell::EventParameters((void*)custom_parameter),
                        shell::EVENT_FLAG_StopWhenHandled|shell::EVENT_FLAG_ForwardToParent);
                    _HitItem->shell::EventHandler::SendImmediateEvent(forward_event);
                }
            }
        }

        if (!(((_HitItem == NULL || _HitItem == &WindowManager::Get().GetDesktopWindow())
            && _HitWindow==&WindowManager::Get().GetDesktopWindow())
            || (_HitItem != NULL && _HitItem->HasStyle(WINDOW_STYLE_ForwardsInput))
            || (_HitWindow != NULL && _HitWindow->HasStyle(WINDOW_STYLE_ForwardsInput))))
        {
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Cursor::OnMouseRightButtonReleased(shell::Event& event)
    {
        input::EventMouse* parameter = (input::EventMouse*)
            event.GetParameters().GetCustomParameter();

        if (_ItIsCapturing)
            return true;
        
        if (!WindowManager::IsAvailable())
            return false;

        if (WindowManager::Get().HasFocusWindow()
            && WindowManager::Get().GetFocusWindow().HasState(WINDOW_STATE_MouseRightButtonPressed))
        {
            shell::Event forward_event;
            input::EventMouse* custom_parameter = COFFEE_New(input::EventMouse, 
                parameter->Position);
            forward_event.Set(event.GetCode(), shell::EventParameters((void*)custom_parameter),
                shell::EVENT_FLAG_StopWhenHandled|shell::EVENT_FLAG_ForwardToParent);
            WindowManager::Get().GetFocusWindow().shell::EventHandler::SendImmediateEvent(forward_event);
            
            if (_HitItem!=NULL)
            {
                _HitItem->SetFocus();
                if (_HitItem==NULL)
                        return true;
            }
        }

        SetIcon(SKIN_ICON_CursorDefault);

        if (!(((_HitItem == NULL || _HitItem == &WindowManager::Get().GetDesktopWindow())
            && _HitWindow==&WindowManager::Get().GetDesktopWindow())
            || (_HitItem != NULL && _HitItem->HasStyle(WINDOW_STYLE_ForwardsInput))
            || (_HitWindow != NULL && _HitWindow->HasStyle(WINDOW_STYLE_ForwardsInput))))
        {
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Cursor::OnCommand(shell::Event& event)
    {
        // TODO: Uncomment this when default Camera won't be using Control key!
        //if (_ItIsCapturing)
        //    return true;

        if (WindowManager::IsAvailable() && WindowManager::Get().HasFocusWindow())
        {
            shell::Event forward_event;
            forward_event.Set(event.GetCode(), event.GetParameters(),
                shell::EVENT_FLAG_StopWhenHandled|shell::EVENT_FLAG_ForwardToParent);
            return WindowManager::Get().GetFocusWindow().shell::EventHandler::SendImmediateEvent(forward_event);
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Cursor::OnDropFiles(const basic::Vector<storage::PhysicalPath>& files,
        const basic::Vector2i& position)
    {
        bool result = false;
        if (_DropItem!=NULL)
        {
            for (uint32 i=0 ; i<files.GetSize() ; ++i)
            {
                if (_DropItem->SendImmediateEvent(WINDOW_EVENT_QueryDrop, *(meta::Object*)&files[i]))
                {
                    result = true;
                    _DropItem->SendImmediateEvent(WINDOW_EVENT_Drop, *(meta::Object*)&files[i]);
                }
            }
        }
        return result;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool Cursor::_IsResizingAvailable(const Window& window, uint32 hit) const
    {
        if (!window.HasStyle(WINDOW_STYLE_Resizeable)
            || hit==WINDOW_HIT_TYPE_None)
        {
            return false;
        }
        uint32 style = hit<<2;
        return (window.GetStyle()&style)==style;
    }

}
}
