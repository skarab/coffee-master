#include "coffee.h"
#include "system/graphics/renderer/graphics_renderer.h"
#include "system/graphics/geometric/graphics_geometric_renderer.h"

namespace coffee
{
namespace graphics
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_ImplementSingleton(Renderer);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Renderer::Renderer() :
        _ItIsLockingMaterial(false),
        _CurrentLight(NULL)
    {
        COFFEE_CreateSingleton(Renderer);
        _InitializeRenderState();
        _FramePicker = COFFEE_New(FramePicker);
    }

    //--------------------------------------------------------------------------------------------//

    Renderer::~Renderer()
    {
        COFFEE_DestroySingleton(Renderer);
        COFFEE_Delete(_FramePicker);
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const FramePassSystem& Renderer::GetPassSystem() const
    {
        return _PassSystem;
    }

    //--------------------------------------------------------------------------------------------//

    FramePassSystem& Renderer::GetPassSystem()
    {
        return _PassSystem;
    }

    //--------------------------------------------------------------------------------------------//

    void Renderer::SetCurrentLight(ComponentLight& light)
    {
        _CurrentLight = &light;
        _Evaluators.Update();
    }

    //--------------------------------------------------------------------------------------------//

    const ComponentLight& Renderer::GetCurrentLight() const
    {
        return *_CurrentLight;
    }

    //--------------------------------------------------------------------------------------------//

    ComponentLight& Renderer::GetCurrentLight()
    {
        return *_CurrentLight;
    }

    //--------------------------------------------------------------------------------------------//

    bool Renderer::HasCurrentLight() const
    {
        return _CurrentLight != NULL;
    }

    //--------------------------------------------------------------------------------------------//

    void Renderer::SetNoCurrentLight()
    {
        _CurrentLight = NULL;
    }

    //--------------------------------------------------------------------------------------------//

    void Renderer::LockMaterial()
    {
        _ItIsLockingMaterial = true;
    }

    //--------------------------------------------------------------------------------------------//

    void Renderer::UnLockMaterial()
    {
        _ItIsLockingMaterial = false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Renderer::IsLockingMaterial() const
    {
        return _ItIsLockingMaterial;
    }

    //--------------------------------------------------------------------------------------------//

    void Renderer::SetLocalToWorldMatrix(const basic::Matrix& local_to_world_matrix)
    {
        if (graphics::Viewport::GetCurrent().HasCamera())
        {
            glMatrixMode(GL_MODELVIEW);
            glLoadMatrixf((local_to_world_matrix*graphics::Viewport::GetCurrent().GetCamera().GetComponent().GetNode().GetTransform().GetMatrix(scene::TRS_World, scene::TRS_Local)).GetData());
            _LocalToWorldMatrix = local_to_world_matrix;
            _WorldToLocalMatrix.SetInversed(local_to_world_matrix);
            _Evaluators.Update();
        }
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Matrix& Renderer::GetLocalToWorldMatrix() const
    {
        return _LocalToWorldMatrix;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Matrix& Renderer::GetWorldToLocalMatrix() const
    {
        return _WorldToLocalMatrix;
    }

    //--------------------------------------------------------------------------------------------//

    void Renderer::SetIdentityMatrix()
    {
        glLoadIdentity();
        _LocalToWorldMatrix.SetIdentity();
        _WorldToLocalMatrix.SetInversed(_LocalToWorldMatrix);
        _Evaluators.Update();
    }

    //--------------------------------------------------------------------------------------------//

    void Renderer::GetLocalToCameraMatrix(basic::Matrix& local_to_camera_matrix)
    {
        glGetFloatv(GL_MODELVIEW_MATRIX, local_to_camera_matrix.GetData());
    }

    //--------------------------------------------------------------------------------------------//

    void Renderer::SetCameraToViewportMatrix(const basic::Matrix& camera_to_viewport_matrix)
    {
        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(camera_to_viewport_matrix.GetData());
        glMatrixMode(GL_MODELVIEW);
        _Evaluators.Update();
    }

    //--------------------------------------------------------------------------------------------//

    void Renderer::GetCameraToViewportMatrix(basic::Matrix& camera_to_viewport_matrix)
    {
        glGetFloatv(GL_PROJECTION_MATRIX, camera_to_viewport_matrix.GetData());
    }

    //--------------------------------------------------------------------------------------------//

    void Renderer::SetRenderState(const RenderState& render_state)
    {
        SetFaceCullingMode(render_state.GetFaceCullingMode());
        SetPolygonModes(render_state.GetFrontPolygonMode(), render_state.GetBackPolygonMode());

        EnableDepthTest(render_state.IsDepthTestEnabled());
        if (render_state.IsDepthTestEnabled())
            SetDepthTestFunction(render_state.GetDepthTestFunction());

        EnableDepthWriting(render_state.IsDepthWritingEnabled());

        SetShadeModel(render_state.GetShadeModel());

        EnableBlending(render_state.IsBlendingEnabled());
        if (render_state.IsBlendingEnabled())
            SetBlendingFactors(render_state.GetBlendingSourceFactor(), render_state.GetBlendingDestinationFactor());

        EnableAlphaTest(render_state.IsAlphaTestEnabled());
        if (render_state.IsAlphaTestEnabled())
            SetAlphaTestFunction(render_state.GetAlphaTestFunction(), render_state.GetAlphaTestThreshold());
    
        EnableColorWriting(render_state.IsColorWritingEnabled());
    }

    //--------------------------------------------------------------------------------------------//

    void Renderer::SetColor(const basic::Color& color, bool additive)
    {
        if (additive)
        {
            SetBlendingFactors(RENDER_STATE_BLENDING_FACTOR_One, RENDER_STATE_BLENDING_FACTOR_One);
            EnableBlending(true);
        }
        else if(color.A!=1.0f)
        {
            SetBlendingFactors(RENDER_STATE_BLENDING_FACTOR_SourceAlpha, RENDER_STATE_BLENDING_FACTOR_SourceAlphaInversed);
            EnableBlending(true);
        }
        else
        {
            EnableBlending(false);
        }

        _SetColor(color, _RenderState);
    }

    //--------------------------------------------------------------------------------------------//

    void Renderer::SetFaceCullingMode(RENDER_STATE_FACE_CULLING mode)
    {
        if (mode!=_RenderState.GetFaceCullingMode())
            _SetFaceCullingMode(mode, _RenderState);
    }

    //--------------------------------------------------------------------------------------------//

    void Renderer::SetPolygonModes(RENDER_STATE_POLYGON_MODE front_mode,
        RENDER_STATE_POLYGON_MODE back_mode)
    {
        if (front_mode!=_RenderState.GetFrontPolygonMode()
            || back_mode!=_RenderState.GetBackPolygonMode())
        {
            _SetPolygonModes(front_mode, back_mode, _RenderState);
        }
    }
    
    //--------------------------------------------------------------------------------------------//

    void Renderer::EnableDepthTest(bool enabled)
    {
        if (enabled!=_RenderState.IsDepthTestEnabled())
            _EnableDepthTest(enabled, _RenderState);
    }

    //--------------------------------------------------------------------------------------------//

    void Renderer::SetDepthTestFunction(RENDER_STATE_TEST_FUNCTION function)
    {
        if (function!=_RenderState.GetDepthTestFunction())
            _SetDepthTestFunction(function, _RenderState);
    }

    //--------------------------------------------------------------------------------------------//

    void Renderer::EnableDepthWriting(bool enabled)
    {
        if (enabled!=_RenderState.IsDepthWritingEnabled())
            _EnableDepthWriting(enabled, _RenderState);
    }

    //--------------------------------------------------------------------------------------------//

    void Renderer::SetShadeModel(RENDER_STATE_SHADE_MODEL shade_model)
    {
        if (shade_model!=_RenderState.GetShadeModel())
            _SetShadeModel(shade_model, _RenderState);
    }

    //--------------------------------------------------------------------------------------------//

    void Renderer::EnableBlending(bool enabled)
    {
        if (enabled!=_RenderState.IsBlendingEnabled())
            _EnableBlending(enabled, _RenderState);
    }
    
    //--------------------------------------------------------------------------------------------//

    void Renderer::SetBlendingFactors(RENDER_STATE_BLENDING_FACTOR source,
        RENDER_STATE_BLENDING_FACTOR destination)
    {
        if (source!=_RenderState.GetBlendingSourceFactor()
            || destination!=_RenderState.GetBlendingDestinationFactor())
        {
            _SetBlendingFactors(source, destination, _RenderState);
        }
    }
    
    //--------------------------------------------------------------------------------------------//

    void Renderer::EnableAlphaTest(bool enabled)
    {
        if (enabled!=_RenderState.IsAlphaTestEnabled())
            _EnableAlphaTest(enabled, _RenderState);
    }

    //--------------------------------------------------------------------------------------------//

    void Renderer::SetAlphaTestFunction(RENDER_STATE_TEST_FUNCTION function, real threshold)
    {
        if (function!=_RenderState.GetAlphaTestFunction()
            || threshold!=_RenderState.GetAlphaTestThreshold())
        {
            _SetAlphaTestFunction(function, threshold, _RenderState);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Renderer::EnableColorWriting(bool enabled)
    {
        if (enabled!=_RenderState.IsColorWritingEnabled())
            _EnableColorWriting(enabled, _RenderState);
    }
    
    //-OPERATIONS---------------------------------------------------------------------------------//

    void Renderer::SetDefaultRenderState()
    {
        SetColor(basic::Color(1.0f, 1.0f, 1.0f, 1.0f));
        SetRenderState(_DefaultRenderState);
    }

    //--------------------------------------------------------------------------------------------//

    void Renderer::UpdateEvaluators()
    {
        _Evaluators.Update();
    }
        
    //--------------------------------------------------------------------------------------------//

    void Renderer::ClearDepth()
    {
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    //--------------------------------------------------------------------------------------------//

    void Renderer::ClearColor()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    //--------------------------------------------------------------------------------------------//

    void Renderer::ClearStencil(uint32 value)
    {
        glClearStencil(value);
        glClear(GL_STENCIL_BUFFER_BIT);
    }

    //--------------------------------------------------------------------------------------------//

    void Renderer::ClearAll()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Renderer::_InitializeRenderState()
    {
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        glEnable(GL_DITHER);
        glDisable(GL_LIGHTING);
        glDisable(GL_NORMALIZE);

        _SetFaceCullingMode(RENDER_STATE_FACE_CULLING_Back, _DefaultRenderState);
        _SetPolygonModes(RENDER_STATE_POLYGON_MODE_Fill, RENDER_STATE_POLYGON_MODE_Fill, _DefaultRenderState);
        _EnableDepthTest(true, _DefaultRenderState);
        _SetDepthTestFunction(RENDER_STATE_TEST_FUNCTION_LessOrEqual, _DefaultRenderState);
        _EnableDepthWriting(true, _DefaultRenderState);
        _SetShadeModel(RENDER_STATE_SHADE_MODEL_Smooth, _DefaultRenderState);
        _EnableBlending(false, _DefaultRenderState);
        _SetBlendingFactors(RENDER_STATE_BLENDING_FACTOR_One, RENDER_STATE_BLENDING_FACTOR_One, _DefaultRenderState);
        _EnableAlphaTest(false, _DefaultRenderState);
        _SetAlphaTestFunction(RENDER_STATE_TEST_FUNCTION_GreaterOrEqual, 0.5f, _DefaultRenderState);
        _EnableColorWriting(true, _DefaultRenderState);

        SetDefaultRenderState();
    }
    
    //-FUNCTIONS----------------------------------------------------------------------------------//

    inline void Renderer::_SetColor(const basic::Color& color, RenderState& render_state)
    {
        glColor4fv(color.GetBuffer());
    }

    //--------------------------------------------------------------------------------------------//

    inline void Renderer::_SetFaceCullingMode(RENDER_STATE_FACE_CULLING mode, RenderState& render_state)
    {
        render_state.SetFaceCullingMode(mode);
        
        if (mode==RENDER_STATE_FACE_CULLING_None)
        {
            glDisable(GL_CULL_FACE);
        }
        else
        {
            glEnable(GL_CULL_FACE);
            if (mode==RENDER_STATE_FACE_CULLING_Front) glCullFace(GL_BACK);
            else glCullFace(GL_FRONT);
        }
    }

    //--------------------------------------------------------------------------------------------//

    static inline GLenum _GetPolygonMode(RENDER_STATE_POLYGON_MODE mode)
    {
        switch (mode)
        {
            case RENDER_STATE_POLYGON_MODE_Point:
                return GL_POINT;
            case RENDER_STATE_POLYGON_MODE_Line:
                return GL_LINE;
        }
        return GL_FILL;
    }

    //--------------------------------------------------------------------------------------------//

    inline void Renderer::_SetPolygonModes(RENDER_STATE_POLYGON_MODE front_mode,
        RENDER_STATE_POLYGON_MODE back_mode, RenderState& render_state)
    {
        render_state.SetPolygonModes(front_mode, back_mode);
            
        if (front_mode==back_mode)
        {
            glPolygonMode(GL_FRONT_AND_BACK, _GetPolygonMode(front_mode));
        }
        else
        {
            glPolygonMode(GL_BACK, _GetPolygonMode(front_mode));
            glPolygonMode(GL_FRONT, _GetPolygonMode(back_mode));
        }
    }
    
    //--------------------------------------------------------------------------------------------//

    inline void Renderer::_EnableDepthTest(bool enabled, RenderState& render_state)
    {
        render_state.EnableDepthTest(enabled);
        if (enabled) glEnable(GL_DEPTH_TEST);
        else glDisable(GL_DEPTH_TEST);
    }
    
    //--------------------------------------------------------------------------------------------//

    inline void Renderer::_SetDepthTestFunction(RENDER_STATE_TEST_FUNCTION function,
        RenderState& render_state)
    {
        render_state.SetDepthTestFunction(function);
        glDepthFunc(GL_NEVER+(uint32)function);
    }

    //--------------------------------------------------------------------------------------------//

    inline void Renderer::_EnableDepthWriting(bool enabled, RenderState& render_state)
    {
        render_state.EnableDepthWriting(enabled);
        glDepthMask(enabled?GL_TRUE:GL_FALSE);
    }

    //--------------------------------------------------------------------------------------------//

    inline void Renderer::_SetShadeModel(RENDER_STATE_SHADE_MODEL shade_model, RenderState& render_state)
    {
        render_state.SetShadeModel(shade_model);
        glShadeModel(shade_model==RENDER_STATE_SHADE_MODEL_Smooth?GL_SMOOTH:GL_FLAT);
    }

    //--------------------------------------------------------------------------------------------//

    inline void Renderer::_EnableBlending(bool enabled, RenderState& render_state)
    {
        render_state.EnableBlending(enabled);
        if (enabled) glEnable(GL_BLEND);
        else glDisable(GL_BLEND);
    }
        
    //--------------------------------------------------------------------------------------------//

    static inline GLenum _GetBlendingFactor(RENDER_STATE_BLENDING_FACTOR factor)
    {
        switch(factor)
        {
            case RENDER_STATE_BLENDING_FACTOR_Zero:                      return GL_ZERO;
            case RENDER_STATE_BLENDING_FACTOR_One:                       return GL_ONE;
            case RENDER_STATE_BLENDING_FACTOR_SourceColor:               return GL_SRC_COLOR;
            case RENDER_STATE_BLENDING_FACTOR_SourceColorInversed:       return GL_ONE_MINUS_SRC_COLOR;
            case RENDER_STATE_BLENDING_FACTOR_SourceAlpha:               return GL_SRC_ALPHA;
            case RENDER_STATE_BLENDING_FACTOR_SourceAlphaInversed:       return GL_ONE_MINUS_SRC_ALPHA;
            case RENDER_STATE_BLENDING_FACTOR_SourceAlphaSatured:        return GL_SRC_ALPHA_SATURATE;
            case RENDER_STATE_BLENDING_FACTOR_DestinationColor:          return GL_DST_COLOR;
            case RENDER_STATE_BLENDING_FACTOR_DestinationColorInversed:  return GL_ONE_MINUS_DST_COLOR;
            case RENDER_STATE_BLENDING_FACTOR_DestinationAlpha:          return GL_DST_ALPHA;
            case RENDER_STATE_BLENDING_FACTOR_DestinationAlphaInversed:  return GL_ONE_MINUS_DST_ALPHA;
            case RENDER_STATE_BLENDING_FACTOR_ConstantColor:             return GL_CONSTANT_COLOR;
            case RENDER_STATE_BLENDING_FACTOR_ConstantColorInversed:     return GL_ONE_MINUS_CONSTANT_COLOR;
            case RENDER_STATE_BLENDING_FACTOR_ConstantAlpha:             return GL_CONSTANT_ALPHA;
            case RENDER_STATE_BLENDING_FACTOR_ConstantAlphaInversed:     return GL_ONE_MINUS_CONSTANT_ALPHA;
        }
        return GL_ZERO;
    }

    //--------------------------------------------------------------------------------------------//

    inline void Renderer::_SetBlendingFactors(RENDER_STATE_BLENDING_FACTOR source_factor,
        RENDER_STATE_BLENDING_FACTOR destination_factor, RenderState& render_state)
    {
        render_state.SetBlendingFactors(source_factor, destination_factor);
        glBlendFunc(_GetBlendingFactor(source_factor), _GetBlendingFactor(destination_factor));
    }
    
    //--------------------------------------------------------------------------------------------//

    inline void Renderer::_EnableAlphaTest(bool enabled, RenderState& render_state)
    {
        render_state.EnableAlphaTest(enabled);
        if (enabled) glEnable(GL_ALPHA_TEST);
        else glDisable(GL_ALPHA_TEST);
    }

    //--------------------------------------------------------------------------------------------//

    inline void Renderer::_SetAlphaTestFunction(RENDER_STATE_TEST_FUNCTION function, real threshold,
        RenderState& render_state)
    {
        render_state.SetAlphaTestFunction(function);
        render_state.SetAlphaTestThreshold(threshold);
        glAlphaFunc(GL_NEVER+function, threshold);
    }

    //--------------------------------------------------------------------------------------------//

    inline void Renderer::_EnableColorWriting(bool enabled, RenderState& render_state)
    {
        render_state.EnableColorWriting(enabled);
        if (enabled) glColorMask(1, 1, 1, 1);
        else glColorMask(0, 0, 0, 0);
    }

}
}
