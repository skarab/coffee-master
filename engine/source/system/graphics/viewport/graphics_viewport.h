#ifndef _COFFEE_GRAPHICS_VIEWPORT_H_
#define _COFFEE_GRAPHICS_VIEWPORT_H_

#include "coffee_includes.h"
#include "wide/ui/window/ui_window.h"
#include "wide/ui/skin/ui_skin_context.h"
#include "system/graphics/camera/graphics_camera.h"
#include "system/graphics/frame/buffer/graphics_frame_buffer.h"
#include "system/graphics/gatherer/graphics_gatherer.h"

namespace coffee
{
namespace graphics
{
    class FramePassToneMapper;

    //--------------------------------------------------------------------------------------------//
    /// Viewport is a window used for rendering
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Viewport : public ui::Window
    {
        friend class FramePassToneMapper;

        COFFEE_Type(Viewport);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Viewport();
        ~Viewport();

        //-ACCESSORS------------------------------------------------------------------------------//

        static bool HasCurrent();
        static void SetCurrent(Viewport* viewport);
        static Viewport& GetCurrent();
        
        const basic::Matrix& GetViewportToFrameMatrix() const;
        const basic::Matrix& GetFrameToViewportMatrix() const;
        const Camera& GetCamera() const;
        Camera& GetCamera();
        Gatherer& GetGatherer() { return _Gatherer; }
        const basic::Time& GetTimeStep() const { return _TimeStep; }

        //-QUERIES--------------------------------------------------------------------------------//

        bool HasCamera() const;
        bool IsMainViewport() const;
        basic::Vector2i GetFrameBufferSize() const;

        basic::Vector2 ComputeScreenToViewportPoint(const basic::Vector2& screen_point) const;
        basic::Vector2 ComputeViewportToFramePoint(const basic::Vector2& viewport_point) const;
        basic::Vector2 ComputeViewportToGLViewportPoint(const basic::Vector2& viewport_point) const;
        basic::Vector2 ComputeScreenToFramePoint(const basic::Vector2& screen_point) const;
        
        basic::Vector2 ComputeFrameToViewportPoint(const basic::Vector2& frame_point) const;
        basic::Vector2 ComputeViewportToScreenPoint(const basic::Vector2& viewport_point) const;
        basic::Vector2 ComputeFrameToScreenPoint(const basic::Vector2& frame_point) const;
        
        //-OPERATIONS-----------------------------------------------------------------------------//

        void AttachCamera(const resource::Handler<scene::Resource>& scene, ComponentCamera* component);
        void DetachCamera();
        void BindFrameBuffer(FrameBuffer& frame_buffer);
        void UnBindFrameBuffer(FrameBuffer& frame_buffer);

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(Viewport);
        COFFEE_Event bool OnKeyReleased(shell::Event& event);
        COFFEE_Event bool OnSetFocus(shell::Event& event);
        COFFEE_Event bool OnKillFocus(shell::Event& event);
        COFFEE_Event bool OnInputEvent(shell::Event& event);
        
    protected:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _Paint(const basic::Time& time_step, const ui::SkinContext& paint_context);
        
    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _Activate(bool it_has_to_set_scissor=true);
        void _UpdateMatrices();
        void _ApplyView();
        void _ListInputComponents(scene::Node& node);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Camera* _Camera;
        FrameBuffer* _FrameBuffer;
        basic::Matrix _ViewportToFrameMatrix;
        basic::Matrix _FrameToViewportMatrix;
        basic::Prow<scene::Component*> _InputComponents;        
        Gatherer _Gatherer;
        basic::Time _TimeStep;

        // TODO: handle this in a generic way
        // (Hard coded required buffers for tone mapper)
        FrameBuffer* _LuminanceBuffers[3];
        FrameLayerBGRA* _LuminanceLayers[3];
        
        //-VARIABLES------------------------------------------------------------------------------//

        static Viewport* _Current;
        static Viewport* _Main;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Viewport);
}
}
#endif
