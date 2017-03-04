#include "coffee.h"
#include "system/graphics/viewport/graphics_viewport.h"
#include "system/graphics/component/camera/graphics_component_camera_perspective.h"
#include "wide/plugins/component/plugins_component.h"

namespace coffee
{
namespace graphics
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::Viewport);
        COFFEE_Ancestor(ui::Window);
    COFFEE_EndType();
    
    //-VARIABLES----------------------------------------------------------------------------------//

    Viewport* Viewport::_Current = NULL;
    Viewport* Viewport::_Main = NULL;
    bool Viewport::HasCurrent() { return _Current!=NULL; }
    void Viewport::SetCurrent(Viewport* viewport) { _Current = viewport; }
    Viewport& Viewport::GetCurrent() { return *_Current; }
    
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Viewport::Viewport() :
        _Camera(NULL),
        _FrameBuffer(NULL)
    {
        if (_Main==NULL)
            _Main = this;
        
        if (Device::IsInstantiated())
        {
            COFFEE_GRAPHICS_Debug();

            for (uint32 i=0 ; i<3 ; ++i)
            {
                _LuminanceBuffers[i] = COFFEE_New(FrameBuffer, 1, 1, true);
                COFFEE_GRAPHICS_Debug();
                _LuminanceLayers[i] = COFFEE_New(FrameLayerBGRA, 1, 1, true, true);
                COFFEE_GRAPHICS_Debug();
                _LuminanceBuffers[i]->AttachLayer(*_LuminanceLayers[i]);
                COFFEE_GRAPHICS_Debug();
            }
        
            _UpdateMatrices();
            COFFEE_GRAPHICS_Debug();
        }
    }

    //--------------------------------------------------------------------------------------------//

    Viewport::~Viewport()
    {
        if (Device::IsInstantiated())
        {
            for (uint32 i=0 ; i<3 ; ++i)
            {
                COFFEE_GRAPHICS_Debug();        
                _LuminanceBuffers[i]->DetachLayer(*_LuminanceLayers[i]);
                COFFEE_Delete(_LuminanceLayers[i]);
                COFFEE_Delete(_LuminanceBuffers[i]);
                COFFEE_GRAPHICS_Debug();
            }
        }

        if (this==_Main)
            _Main = NULL;
        if (this==_Current)
            _Current = NULL;
        DetachCamera();
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const Camera& Viewport::GetCamera() const
    {
        return *_Camera;
    }

    //--------------------------------------------------------------------------------------------//

    Camera& Viewport::GetCamera()
    {
        return *_Camera;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Matrix& Viewport::GetViewportToFrameMatrix() const
    {
        return _ViewportToFrameMatrix;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Matrix& Viewport::GetFrameToViewportMatrix() const
    {
        return _FrameToViewportMatrix;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool Viewport::HasCamera() const
    {
        return _Camera!=NULL;
    }

    //--------------------------------------------------------------------------------------------//
    
    bool Viewport::IsMainViewport() const
    {
        return this==_Main;
    }

    //--------------------------------------------------------------------------------------------//

    basic::Vector2i Viewport::GetFrameBufferSize() const
    {
        if (_FrameBuffer!=NULL)
            return basic::Vector2i(_FrameBuffer->GetWidth(), _FrameBuffer->GetHeight());
        return GetSize();            
    }

    //--------------------------------------------------------------------------------------------//

    basic::Vector2 Viewport::ComputeScreenToViewportPoint(const basic::Vector2& screen_point) const
    {
        ui::WindowContext context;
        context.Create(this);
        return screen_point-context.GetDesktopWindowRect().GetMinimum(); 
    }
    
    //--------------------------------------------------------------------------------------------//

    basic::Vector2 Viewport::ComputeViewportToFramePoint(const basic::Vector2& viewport_point) const
    {
        basic::Vector2 frame_point(viewport_point.X, GetSize().Y-viewport_point.Y);
        return frame_point*GetFrameBufferSize()/GetSize();
    }

    //--------------------------------------------------------------------------------------------//

    basic::Vector2 Viewport::ComputeViewportToGLViewportPoint(const basic::Vector2& viewport_point) const
    {
        basic::Vector2 frame_point(viewport_point.X, GetSize().Y-viewport_point.Y);
        frame_point = frame_point*GetFrameBufferSize()/GetSize();
        basic::Vector4 point;
        point.Set(frame_point.X, frame_point.Y, 1.0f, 1.0f);
        point *= GetFrameToViewportMatrix();
        point *= point.W;
        return basic::Vector2(point.X, point.Y);
    }
        
    //--------------------------------------------------------------------------------------------//

    basic::Vector2 Viewport::ComputeScreenToFramePoint(const basic::Vector2& screen_point) const
    {
        return ComputeViewportToFramePoint(ComputeScreenToViewportPoint(screen_point));
    }
        
    //--------------------------------------------------------------------------------------------//

    basic::Vector2 Viewport::ComputeFrameToViewportPoint(const basic::Vector2& frame_point) const
    {
        basic::Vector2 viewport_point(frame_point*GetSize()/GetFrameBufferSize());
        viewport_point.Y = GetSize().Y-viewport_point.Y;
        return viewport_point;
    }

    //--------------------------------------------------------------------------------------------//

    basic::Vector2 Viewport::ComputeViewportToScreenPoint(const basic::Vector2& viewport_point) const
    {
        ui::WindowContext context;
        context.Create(this);
        return viewport_point+context.GetDesktopWindowRect().GetMinimum();
    }
        
    //--------------------------------------------------------------------------------------------//
    
    basic::Vector2 Viewport::ComputeFrameToScreenPoint(const basic::Vector2& frame_point) const
    {
        return ComputeViewportToScreenPoint(ComputeFrameToViewportPoint(frame_point));
    }
        
    //-OPERATIONS---------------------------------------------------------------------------------//

    void Viewport::AttachCamera(const resource::Handler<scene::Resource>& scene, ComponentCamera* component)
    {
        DetachCamera();
        _Camera = COFFEE_New(Camera, this, scene, component);
        COFFEE_Assert(component->_Viewport==NULL, core::ERROR_CODE_Unexpected, "Camera is already attached");
        component->_Viewport = this;
        if (HasFocus())
        {
            component::Controller* controller = _Camera->GetComponent().GetNode().FindComponent<component::Controller>();
            if (controller!=NULL && (!Engine::Get().HasMode(RUN_MODE_Editor) || controller->GetNode().GetName()!="_EditorCamera"))
                controller->Start();
        }
    }
    
    //--------------------------------------------------------------------------------------------//

    void Viewport::DetachCamera()
    {
        if (_Camera!=NULL)
        {
            COFFEE_Assert(_Camera->GetComponent()._Viewport==this, core::ERROR_CODE_Unexpected, "Unexpected error");
            _Camera->GetComponent()._Viewport = NULL;
            component::Controller* controller = _Camera->GetComponent().GetNode().FindComponent<component::Controller>();
            if (controller!=NULL && (!Engine::Get().HasMode(RUN_MODE_Editor) || controller->GetNode().GetName()!="_EditorCamera"))
                controller->Stop();
        
            COFFEE_Delete(_Camera);
            _Camera = NULL;
            _InputComponents.Clear();
            _Gatherer.Clear();
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Viewport::BindFrameBuffer(FrameBuffer& frame_buffer)
    {
        _FrameBuffer = &frame_buffer;
        _FrameBuffer->SetViewport(GetSize());
        _Activate(false);
    }
    
    //--------------------------------------------------------------------------------------------//

    void Viewport::UnBindFrameBuffer(FrameBuffer& frame_buffer)
    {
        _FrameBuffer = NULL;
        _Activate(false);
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(Viewport, ui::Window)
        COFFEE_RegisterEventHandler(input::EVENT_KeyReleased, input::Handler, OnKeyReleased)
        COFFEE_RegisterEventHandler(ui::WINDOW_EVENT_SetFocus, ui::Window, OnSetFocus)
        COFFEE_RegisterEventHandler(ui::WINDOW_EVENT_KillFocus, ui::Window, OnKillFocus)
        COFFEE_RegisterEventHandler(ui::WINDOW_EVENT_Activate, ui::Window, OnSetFocus)
        COFFEE_RegisterEventHandler(ui::WINDOW_EVENT_Deactivate, ui::Window, OnKillFocus)
        COFFEE_RegisterEventHandler(NONE, input::Handler, OnInputEvent)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool Viewport::OnKeyReleased(shell::Event& event)
    {
        input::EventKey* parameter = (input::EventKey*)
            event.GetParameters().GetCustomParameter();
        if (parameter->Key==input::KEY_Escape)
        {
            SendEvent(ui::WINDOW_EVENT_KillFocus);
            SendEvent(ui::WINDOW_EVENT_Deactivate);
            return true;
        }
        return false;
    }
        
    //--------------------------------------------------------------------------------------------//

    bool Viewport::OnSetFocus(shell::Event& event)
    {
        if (HasCamera())
        {
            component::Controller* controller = _Camera->GetComponent().GetNode().FindComponent<component::Controller>();
            if (controller!=NULL && (!Engine::Get().HasMode(RUN_MODE_Editor) || controller->GetNode().GetName()!="_EditorCamera"))
                controller->Start();
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Viewport::OnKillFocus(shell::Event& event)
    {
        if (HasCamera())
        {
            component::Controller* controller = _Camera->GetComponent().GetNode().FindComponent<component::Controller>();
            if (controller!=NULL)
                controller->Stop();
        }
        return false;
    }
    
    //--------------------------------------------------------------------------------------------//

    bool Viewport::OnInputEvent(shell::Event& event)
    {
        if (HasCamera() && _Camera->GetScene().GetState()==resource::HANDLER_STATE_Ready)
        {
            input::EVENT code = (input::EVENT)event.GetCode().GetIdentifier();
            const void* parameters = event.GetParameters().GetCustomParameter();
            for (uint32 i=0 ; i<_InputComponents.GetSize() ; ++i)
            {
                if (_InputComponents[i]->OnInputEvent(code, parameters))
                    return true;
            }
        }
        return false;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Viewport::_Paint(const basic::Time& time_step, const ui::SkinContext& paint_context)
    {
        COFFEE_GRAPHICS_Debug();

        _TimeStep = time_step;

        static bool it_is_first_camera = false;
        if (!HasParent())
            it_is_first_camera = false;

        if (HasCamera() && _Camera->GetScene().Update()==resource::HANDLER_STATE_BeginLoading)
            DetachCamera();
        
        Viewport* old_viewport = _Current;
        _Current = this;
        bool it_is_visible = Device::Get().IsVisible();
        if (it_is_visible)
        {
            // Activate viewport
            _Activate();      

            _InputComponents.Clear();
            _Gatherer.Clear();
                 
            if (HasCamera() && _Camera->GetScene().GetState()==resource::HANDLER_STATE_Ready)
            {
                if (!it_is_first_camera && _Camera->GetComponent().GetNode().HasTransform())
                {
                    it_is_first_camera = true;

                    basic::Vector3 position = _Camera->GetComponent().GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World).GetTranslation();
                    audio::Device::Get().SetListenerPosition(position);
                    audio::Device::Get().SetListenerRotation(
                        _Camera->GetComponent().GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World).GetRotation());
                
                    static basic::Vector3 old_position;
                    basic::Vector3 velocity = (position-old_position)/time_step.GetSecondCount();
                    old_position = position;
                    audio::Device::Get().SetListenerVelocity(velocity);
                }

                if (HasCamera() && _Camera->GetScene().GetState()==resource::HANDLER_STATE_Ready)
                {
                    _ListInputComponents(_Camera->GetScene().Get().GetRoot());
                    _Camera->GetComponent().Update(*this);
                    _Gatherer.Update(_Camera->GetScene().Get().GetRoot(), _Camera->GetComponent(), *this);
                }
           
                COFFEE_GRAPHICS_Debug();

                Renderer::Get().GetPassSystem().Render(*this);
            }

            // Reset the renderer to GUI mode
            Renderer::Get().SetDefaultRenderState();
            Renderer::Get().SetFaceCullingMode(RENDER_STATE_FACE_CULLING_None);
        
            // Activate main viewport and render the GUI
            if (old_viewport!=NULL)
                _Main->_Activate();

            _Current = _Main;
            ui::Window::_Paint(time_step, paint_context);
            graphics::FrameScissor::Disable();
            _Current = this;
            _Activate(false);
            
            // Reset the renderer to override GUI changes
            Renderer::Get().SetDefaultRenderState();
            Renderer::Get().SetFaceCullingMode(RENDER_STATE_FACE_CULLING_None);
        
            // Hack: draw the GUI cursor if it's the main viewport
            if (IsMainViewport())
                ui::WindowManager::Get().GetCursor().Draw();
        }

        // Flush if its the main viewport
        if (IsMainViewport())
            Device::Get().Update(it_is_visible);

        // Activate old viewport
        _Current = old_viewport;
        if (_Current!=NULL)
            _Current->_Activate(false);
    }
        
    //-OPERATIONS---------------------------------------------------------------------------------//

    void Viewport::_Activate(bool it_has_to_set_scissor)
    {
        _ApplyView();
        _UpdateMatrices();
        Renderer::Get().UpdateEvaluators();

        if (it_has_to_set_scissor)
        {
            graphics::FrameScissor scissor;
            basic::Rectangle rect;
            ui::WindowContext context;
            context.Create(this);
            rect.Position = context.GetDesktopWindowRect().GetMinimum()+1;
            rect.Size = context.GetDesktopWindowRect().Size-1;
            rect -= context.GetDesktopClipRect();
            rect.Position.Y -= 1;
            scissor.SetRectangle(rect);
            scissor.Bind();
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Viewport::_UpdateMatrices()
    {
        _ViewportToFrameMatrix.SetIdentity();
        _FrameToViewportMatrix.SetIdentity();
        if (GetFrameBufferSize().X>0 && GetFrameBufferSize().Y>0)
        {
            real* matrix_data = _ViewportToFrameMatrix.GetData();
            matrix_data[0] = GetFrameBufferSize().X/2.0f;
            matrix_data[5] = GetFrameBufferSize().Y/2.0f;
            matrix_data[12] = GetFrameBufferSize().X/2.0f;
            matrix_data[13] = GetFrameBufferSize().Y/2.0f;
            _FrameToViewportMatrix.SetInversed(_ViewportToFrameMatrix);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Viewport::_ListInputComponents(scene::Node& node)
    {
        for (uint32 i=0 ; i<node.GetComponentCount() ; ++i)
        {
            if (node.GetComponent(i).IsRunning()
                && node.GetComponent(i).HandleInputs())
            {
                _InputComponents.AddItem(&node.GetComponent(i));
            }
        }

        for (uint32 i=0 ; i<node.GetChildCount() ; ++i)
            _ListInputComponents(node.GetChild(i));
    }

    //--------------------------------------------------------------------------------------------//

    void Viewport::_ApplyView()
    {
        basic::Vector2i offset;
        if (_FrameBuffer==NULL)
        {
            ui::WindowContext context;
            context.Create(this);
            offset = context.GetDesktopWindowRect().Position;
        }

        int32 pos_y = offset.Y;
        int32 width = GetFrameBufferSize().X;
        int32 height = GetFrameBufferSize().Y;
        int32 ipos_y;
        if (_FrameBuffer==NULL)
        {
            ipos_y = (int32)graphics::Device::Get().GetHeight()-(pos_y+height);
        }
        else
        {
            ipos_y = (int32)_FrameBuffer->GetHeight()-(pos_y+height);
        }
        
        glViewport(offset.X, ipos_y, width, height);
    }

}
}
