#include "system/graphics/frame/pass/post_process/graphics_frame_pass_post_process.h"
#include "system/graphics/graphics.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::FramePassPostProcess);
        COFFEE_Ancestor(graphics::FramePass);
        COFFEE_Attribute(graphics::Material, _Material, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    FramePassPostProcess::FramePassPostProcess(bool it_is_hdr) :
        FramePass("PostProcess"),
        _ItIsHDR(it_is_hdr)
    {
    }

    //--------------------------------------------------------------------------------------------//

    FramePassPostProcess::~FramePassPostProcess()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void FramePassPostProcess::Initialize(FramePass* previous_pass)
    {
        _Layer = COFFEE_New(FrameLayerBGRA, GetFrameBuffer().GetWidth(), GetFrameBuffer().GetHeight(), _ItIsHDR);
        GetFrameBuffer().AttachLayer(*_Layer);
    }

    //--------------------------------------------------------------------------------------------//

    void FramePassPostProcess::Finalize(FramePass* previous_pass)
    {
        GetFrameBuffer().DetachLayer(*_Layer);
        COFFEE_Delete(_Layer);
    }

    //--------------------------------------------------------------------------------------------//
    
    void FramePassPostProcess::Render(Viewport& viewport, FramePass* previous_pass)
    {
        if (_Material.IsAvailable())
        {
            FramePassSystem::Get().GetGBufferPass().GetLinearDepth().Bind(0);
            FramePassSystem::Get().GetGBufferPass().GetNormal().Bind(1);
            FramePassSystem::Get().GetGBufferPass().GetColor().Bind(2);
            FramePassSystem::Get().GetGBufferPass().GetMaterial().Bind(3);
            previous_pass->GetFrameBuffer().GetLayer(0).Bind(4);

            _Material.Bind();
            RenderQuad(viewport);
            _Material.UnBind();

            previous_pass->GetFrameBuffer().GetLayer(0).UnBind(4);
            FramePassSystem::Get().GetGBufferPass().GetMaterial().UnBind(3);
            FramePassSystem::Get().GetGBufferPass().GetColor().UnBind(2);
            FramePassSystem::Get().GetGBufferPass().GetNormal().UnBind(1);
            FramePassSystem::Get().GetGBufferPass().GetLinearDepth().UnBind(0);
        }
     }

}
}
