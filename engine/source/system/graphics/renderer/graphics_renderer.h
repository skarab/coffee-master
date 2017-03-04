#ifndef _COFFEE_GRAPHICS_RENDERER_H_
#define _COFFEE_GRAPHICS_RENDERER_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/renderer/state/graphics_render_state.h"
#include "system/graphics/frame/graphics_frame.h"
#include "system/graphics/material/graphics_material.h"
#include "system/graphics/shader/graphics_shader_evaluators.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Graphics Renderer handling rendering states
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Renderer
    {
        COFFEE_DeclareSingleton(Renderer);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Renderer();
        ~Renderer();

        //-ACCESSORS------------------------------------------------------------------------------//

        const FramePassSystem& GetPassSystem() const;
        FramePassSystem& GetPassSystem();

        void SetCurrentLight(ComponentLight& light);
        const ComponentLight& GetCurrentLight() const;
        ComponentLight& GetCurrentLight();
        bool HasCurrentLight() const;
        void SetNoCurrentLight();

        void LockMaterial();
        void UnLockMaterial();
        bool IsLockingMaterial() const;

        void SetLocalToWorldMatrix(const basic::Matrix& local_to_world_matrix);
        const basic::Matrix& GetLocalToWorldMatrix() const;
        const basic::Matrix& GetWorldToLocalMatrix() const;

        void SetIdentityMatrix();
        void GetLocalToCameraMatrix(basic::Matrix& local_to_camera_matrix);
        void SetCameraToViewportMatrix(const basic::Matrix& camera_to_viewport_matrix);
        void GetCameraToViewportMatrix(basic::Matrix& camera_to_viewport_matrix);

        void SetRenderState(const RenderState& render_state);
        void SetColor(const basic::Color& color, bool additive = false);
        void SetFaceCullingMode(RENDER_STATE_FACE_CULLING mode);
        void SetPolygonModes(RENDER_STATE_POLYGON_MODE front_mode, RENDER_STATE_POLYGON_MODE back_mode);
        void EnableDepthTest(bool enabled);
        void SetDepthTestFunction(RENDER_STATE_TEST_FUNCTION function);
        void EnableDepthWriting(bool enabled);
        void SetShadeModel(RENDER_STATE_SHADE_MODEL shade_model);
        void EnableBlending(bool enabled);
        void SetBlendingFactors(RENDER_STATE_BLENDING_FACTOR source_factor, RENDER_STATE_BLENDING_FACTOR destination_factor);
        void EnableAlphaTest(bool enabled);
        void SetAlphaTestFunction(RENDER_STATE_TEST_FUNCTION function, real threshold);
        void EnableColorWriting(bool enabled);
        
        //-OPERATIONS-----------------------------------------------------------------------------//

        void SetDefaultRenderState();
        void UpdateEvaluators();

        void ClearDepth();
        void ClearColor();
        void ClearStencil(uint32 value);
        void ClearAll();

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _InitializeRenderState();
        
        //-FUNCTIONS------------------------------------------------------------------------------//

        static inline void _SetColor(const basic::Color& color, RenderState& render_state);
        static inline void _SetFaceCullingMode(RENDER_STATE_FACE_CULLING mode, RenderState& render_state);
        static inline void _SetPolygonModes(RENDER_STATE_POLYGON_MODE front_mode, RENDER_STATE_POLYGON_MODE back_mode, RenderState& render_state);
        static inline void _EnableDepthTest(bool enabled, RenderState& render_state);
        static inline void _SetDepthTestFunction(RENDER_STATE_TEST_FUNCTION function, RenderState& render_state);
        static inline void _EnableDepthWriting(bool enabled, RenderState& render_state);
        static inline void _SetShadeModel(RENDER_STATE_SHADE_MODEL shade_model, RenderState& render_state);
        static inline void _EnableBlending(bool enabled, RenderState& render_state);
        static inline void _SetBlendingFactors(RENDER_STATE_BLENDING_FACTOR source_factor, RENDER_STATE_BLENDING_FACTOR destination_factor, RenderState& render_state);
        static inline void _EnableAlphaTest(bool enabled, RenderState& render_state);
        static inline void _SetAlphaTestFunction(RENDER_STATE_TEST_FUNCTION function, real threshold, RenderState& render_state);
        static inline void _EnableColorWriting(bool enabled, RenderState& render_state);
        
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Matrix _LocalToWorldMatrix;
        basic::Matrix _WorldToLocalMatrix;
        RenderState _RenderState;
        RenderState _DefaultRenderState;
        FramePassSystem _PassSystem;
        ShaderEvaluators _Evaluators;
        FramePicker* _FramePicker;

        ComponentLight* _CurrentLight;
        bool _ItIsLockingMaterial;
    };
}
}
#endif
