#include "system/graphics/frame/pass/transparent/graphics_frame_pass_transparent.h"
#include "wide/application/application.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::FramePassTransparent);
        COFFEE_Ancestor(graphics::FramePass);
    COFFEE_EndType();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    FramePassTransparent::FramePassTransparent(bool it_is_hdr) :
        FramePass("Transparent"),
        _ItIsHDR(it_is_hdr)
    {
    }

    //--------------------------------------------------------------------------------------------//

    FramePassTransparent::~FramePassTransparent()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void FramePassTransparent::Initialize(FramePass* previous_pass)
    {
        COFFEE_Assert(previous_pass->GetFrameBuffer().GetLayer(0).IsA<FrameLayerBGRA>(),
            core::ERROR_CODE_GraphicsSystem, "Failed to initialize");
        COFFEE_Assert(_ItIsHDR==static_cast<FrameLayerBGRA&>(previous_pass->GetFrameBuffer().GetLayer(0)).IsHDR(),
            core::ERROR_CODE_GraphicsSystem, "Failed to initialize");

        GetFrameBuffer().AttachLayer(previous_pass->GetFrameBuffer().GetLayer(0));
        GetFrameBuffer().AttachLayer(FramePassSystem::Get().GetGBufferPass().GetDepth());
    }

    //--------------------------------------------------------------------------------------------//

    void FramePassTransparent::Finalize(FramePass* previous_pass)
    {
        GetFrameBuffer().DetachLayer(previous_pass->GetFrameBuffer().GetLayer(0));
        GetFrameBuffer().DetachLayer(FramePassSystem::Get().GetGBufferPass().GetDepth());
    }

    //--------------------------------------------------------------------------------------------//

    void FramePassTransparent::Render(Viewport& viewport, FramePass* previous_pass)
    {
        Renderer::Get().SetDefaultRenderState();
        Renderer::Get().SetCameraToViewportMatrix(
            viewport.GetCamera().GetComponent().GetInfiniteProjectionMatrix());

        if (_ItIsHDR)
        {
            // Forward to the application render callbacks
            if (Application::IsAvailable())
                Application::Get().OnRender(viewport, false, _ItIsHDR);

            for (uint32 i=0 ; i<viewport.GetGatherer().GetTransparentChunks().GetSize() ; ++i)
                viewport.GetGatherer().GetTransparentChunks()[i]->Render(viewport);
        }

        // Forward to the application render callbacks
        if (Application::IsAvailable())
            Application::Get().OnRender(viewport, true, _ItIsHDR);
    }

}
}
