#include "system/graphics/frame/pass/lightning/graphics_frame_pass_lightning.h"
#include "system/graphics/frame/pass/graphics_frame_pass_system.h"
#include "system/graphics/renderer/graphics_renderer.h"
#include "system/graphics/component/graphics_components.h"
#include "system/graphics/device/graphics_device.h"

#define COFFEE_LIGHT_SoftnessThreshold  0.01f

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::FramePassLightning);
        COFFEE_Ancestor(graphics::FramePass);
    COFFEE_EndType();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    FramePassLightning::FramePassLightning() :
        FramePass("Lightning"),
        _ShadowDepthPass(0)
    {
    }

    //--------------------------------------------------------------------------------------------//

    FramePassLightning::~FramePassLightning()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void FramePassLightning::Initialize(FramePass* previous_pass)
    {
        _ShadowsMaterial = resource::Manager::Get().Load("/coffee/import/shaders/lights/shadows.material");
        _Layer = COFFEE_New(FrameLayerBGRA, GetFrameBuffer().GetWidth(), GetFrameBuffer().GetHeight(), true);
        GetFrameBuffer().AttachLayer(*_Layer);
        GetFrameBuffer().AttachLayer(FramePassSystem::Get().GetGBufferPass().GetDepth());
    
        if (Device::Get().IsSupporting(DEVICE_SUPPORT_SoftShadows))
        {
            _SoftFilterH.SetMaterial(resource::Manager::Get().Load(
                "/coffee/import/shaders/filters/soft_shadows_h.material"));
            _SoftFilterH.Initialize(this);

            _SoftFilterV.SetMaterial(resource::Manager::Get().Load(
                "/coffee/import/shaders/filters/soft_shadows_v.material"));
            _SoftFilterV.Initialize(this);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void FramePassLightning::Finalize(FramePass* previous_pass)
    {
        if (Device::Get().IsSupporting(DEVICE_SUPPORT_SoftShadows))
        {
            _SoftFilterV.Finalize(this);
            _SoftFilterH.Finalize(this);
        }
        
        GetFrameBuffer().DetachLayer(*_Layer);
        COFFEE_Delete(_Layer);
        GetFrameBuffer().DetachLayer(FramePassSystem::Get().GetGBufferPass().GetDepth());
    }

    //--------------------------------------------------------------------------------------------//

    void FramePassLightning::Render(Viewport& viewport, FramePass* previous_pass)
    {
        Renderer::Get().ClearColor();
        
        if (viewport.GetGatherer().GetLights().GetSize()>0)
        {
            for (uint32 light_index=0 ; light_index<viewport.GetGatherer().GetLights().GetSize() ; ++light_index)
                _RenderLight(*viewport.GetGatherer().GetLights()[light_index], viewport);

            Renderer::Get().SetNoCurrentLight();
        }
    }

    //-OPERATIONS---------------------------------------------------------------------------------//
        
    void FramePassLightning::_RenderLight(Light& light, Viewport& viewport)
    {
        Renderer::Get().SetCurrentLight(light.GetComponent());

        FrameScissor scissor;
        bool it_uses_scissor = !light.GetComponent().IsA<ComponentLightDirectional>();
        bool it_is_visible = !it_uses_scissor;

        if (it_uses_scissor)
        {
            basic::Rectangle rectangle = viewport.GetCamera().ComputeFrameProjectedBox(
                light.GetComponent().GetNode().GetBounding().GetBox(),
                light.GetComponent().GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World));
            scissor.SetRectangle(rectangle);
            it_is_visible = !scissor.GetRectangle().IsEmpty();
            if (it_is_visible)
                scissor.BindOnFrameBuffer();
        }

        if (it_is_visible)
        {
            if (light.GetChunks().GetSize()>0)
                _PreRenderShadows(light, viewport);
                
            FramePassSystem::Get().GetGBufferPass().GetLinearDepth().Bind(0);
            FramePassSystem::Get().GetGBufferPass().GetNormal().Bind(1);
            FramePassSystem::Get().GetGBufferPass().GetColor().Bind(2);
            FramePassSystem::Get().GetGBufferPass().GetMaterial().Bind(3);
            
            light.GetComponent().GetMaterial().Bind();
            RenderQuad(viewport);
            light.GetComponent().GetMaterial().UnBind(); 

            FramePassSystem::Get().GetGBufferPass().GetMaterial().UnBind(3);
            FramePassSystem::Get().GetGBufferPass().GetColor().UnBind(2);
            FramePassSystem::Get().GetGBufferPass().GetNormal().UnBind(1);
            FramePassSystem::Get().GetGBufferPass().GetLinearDepth().UnBind(0);
            
            if (light.GetChunks().GetSize())
                _PostRenderShadows(light, viewport);

            if (it_uses_scissor)
                scissor.UnBind();
        }
    }

    //--------------------------------------------------------------------------------------------//

    inline int32 _IncrOp()
    {
        if (Device::Get().IsSupporting(DEVICE_SUPPORT_StencilWrap))
            return GL_INCR_WRAP_EXT;
        return GL_INCR;        
    }

    inline int32 _DecrOp()
    {
        if (Device::Get().IsSupporting(DEVICE_SUPPORT_StencilWrap))
            return GL_DECR_WRAP_EXT;
        return GL_DECR;        
    }

    void FramePassLightning::_PreRenderShadows(Light& light, Viewport& viewport)
    {
        if (!Device::Get().IsSupporting(DEVICE_SUPPORT_ShadowVolumes))
            return;

        Renderer::Get().ClearStencil(128);
        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_ALWAYS, 1, ~0);
        
        Renderer::Get().SetCameraToViewportMatrix(
            viewport.GetCamera().GetComponent().GetInfiniteProjectionMatrix());
        
        if (Device::Get().IsSupporting(DEVICE_SUPPORT_TwoSidedStencil))
        {
            _ShadowsMaterial.GrabRenderState().SetFaceCullingMode(RENDER_STATE_FACE_CULLING_None);
            glEnable(GL_STENCIL_TEST_TWO_SIDE_EXT);    
            for (uint32 i=0 ; i<light.GetChunks().GetSize() ; ++i)
            {
                bool it_is_capped = light.GetCappedShadows()[i];
                _ShadowDepthPass = it_is_capped?0:1;
                glActiveStencilFaceEXT(GL_BACK);
                glStencilOp(GL_KEEP, it_is_capped?_IncrOp():GL_KEEP, it_is_capped?GL_KEEP:_DecrOp());
                glActiveStencilFaceEXT( GL_FRONT );
                glStencilOp(GL_KEEP, it_is_capped?_DecrOp():GL_KEEP, it_is_capped?GL_KEEP:_IncrOp());
                light.GetChunks()[i]->RenderShadows(viewport, _ShadowsMaterial);
            }
            glDisable(GL_STENCIL_TEST_TWO_SIDE_EXT);
        }
        else if (Device::Get().IsSupporting(DEVICE_SUPPORT_TwoSidedStencilATI))
        {
            _ShadowsMaterial.GrabRenderState().SetFaceCullingMode(RENDER_STATE_FACE_CULLING_None);

            for (uint32 i=0 ; i<light.GetChunks().GetSize() ; ++i)
            {
                bool it_is_capped = light.GetCappedShadows()[i];
                _ShadowDepthPass = it_is_capped?0:1;
                glStencilOpSeparateATI(GL_BACK, GL_KEEP, it_is_capped?_IncrOp():GL_KEEP, it_is_capped?GL_KEEP:_DecrOp());
                glStencilOpSeparateATI(GL_FRONT, GL_KEEP, it_is_capped?_DecrOp():GL_KEEP, it_is_capped?GL_KEEP:_IncrOp());
                light.GetChunks()[i]->RenderShadows(viewport, _ShadowsMaterial);
            }
        }
        else
        {
            _ShadowsMaterial.GrabRenderState().SetFaceCullingMode(RENDER_STATE_FACE_CULLING_Back);
            glEnable(GL_CULL_FACE);
            for (uint32 i=0 ; i<light.GetChunks().GetSize() ; ++i)
            {
                bool it_is_capped = light.GetCappedShadows()[i];
                _ShadowDepthPass = it_is_capped?0:1;
                glCullFace(it_is_capped?GL_FRONT:GL_BACK);
                glStencilOp(GL_KEEP, it_is_capped?_IncrOp():GL_KEEP, it_is_capped?GL_KEEP:_DecrOp());
                light.GetChunks()[i]->RenderShadows(viewport, _ShadowsMaterial);
                glCullFace(it_is_capped?GL_BACK:GL_FRONT);
                glStencilOp(GL_KEEP, it_is_capped?_DecrOp():GL_KEEP, it_is_capped?GL_KEEP:_IncrOp());
                light.GetChunks()[i]->RenderShadows(viewport, _ShadowsMaterial);
            }
            glDisable(GL_CULL_FACE);
        }

        glStencilFunc(GL_EQUAL, 128, ~0);
	    glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
        
        if (light.GetComponent().GetSoftness()>COFFEE_LIGHT_SoftnessThreshold
            && Device::Get().IsSupporting(DEVICE_SUPPORT_SoftShadows))
        {
            glDisable(GL_STENCIL_TEST);
            GetFrameBuffer().UnBind(viewport);
            
            _SoftFilterH.GetFrameBuffer().Bind(viewport);
            FramePassSystem::Get().GetGBufferPass().GetLinearDepth().Bind(0);
            FramePassSystem::Get().GetGBufferPass().GetNormal().Bind(1);
            FramePassSystem::Get().GetGBufferPass().GetDepth().BindStencil(2);
            _SoftFilterH.GetMaterial().Bind();
            RenderQuad(viewport);
            _SoftFilterH.GetMaterial().UnBind(); 
            FramePassSystem::Get().GetGBufferPass().GetDepth().UnBind(2);
            FramePassSystem::Get().GetGBufferPass().GetNormal().UnBind(1);
            FramePassSystem::Get().GetGBufferPass().GetLinearDepth().UnBind(0);
            _SoftFilterH.GetFrameBuffer().UnBind(viewport);
            
            _SoftFilterV.GetFrameBuffer().Bind(viewport);
            FramePassSystem::Get().GetGBufferPass().GetLinearDepth().Bind(0);
            FramePassSystem::Get().GetGBufferPass().GetNormal().Bind(1);
            _SoftFilterH.GetLayer().Bind(2);
            _SoftFilterV.GetMaterial().Bind();
            RenderQuad(viewport);
            _SoftFilterV.GetMaterial().UnBind(); 
            _SoftFilterH.GetLayer().UnBind(2);
            FramePassSystem::Get().GetGBufferPass().GetNormal().UnBind(1);
            FramePassSystem::Get().GetGBufferPass().GetLinearDepth().UnBind(0);
            _SoftFilterV.GetFrameBuffer().UnBind(viewport);

            GetFrameBuffer().Bind(viewport);
            _SoftFilterV.GetLayer().Bind(5);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void FramePassLightning::_PostRenderShadows(Light& light, Viewport& viewport)
    {
        if (Device::Get().IsSupporting(DEVICE_SUPPORT_ShadowVolumes))
        {
            if (light.GetComponent().GetSoftness()>COFFEE_LIGHT_SoftnessThreshold
                && Device::Get().IsSupporting(DEVICE_SUPPORT_SoftShadows))
            {
                _SoftFilterV.GetLayer().UnBind(5);
            }
            else
            {
                glDisable(GL_STENCIL_TEST);
            }
        }
    }

}
}
