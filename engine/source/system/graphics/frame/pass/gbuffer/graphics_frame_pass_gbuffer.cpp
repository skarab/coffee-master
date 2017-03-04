#include "system/graphics/frame/pass/gbuffer/graphics_frame_pass_gbuffer.h"
#include "system/graphics/renderer/graphics_renderer.h"
#include "system/graphics/device/graphics_device.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::FramePassGBuffer);
        COFFEE_Ancestor(graphics::FramePass);
    COFFEE_EndType();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    FramePassGBuffer::FramePassGBuffer() :
        FramePass("Geometric Buffer")
    {
    }

    //--------------------------------------------------------------------------------------------//

    FramePassGBuffer::~FramePassGBuffer()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void FramePassGBuffer::Initialize(FramePass* previous_pass)
    {
        _Depth = COFFEE_New(FrameLayerDepth, GetFrameBuffer().GetWidth(), GetFrameBuffer().GetHeight());
        GetFrameBuffer().AttachLayer(*_Depth);
        _LinearDepth = COFFEE_New(FrameLayerBGRA, GetFrameBuffer().GetWidth(), GetFrameBuffer().GetHeight(), true);
        GetFrameBuffer().AttachLayer(*_LinearDepth);
        _Normal = COFFEE_New(FrameLayerBGRA, GetFrameBuffer().GetWidth(), GetFrameBuffer().GetHeight(), true);
        GetFrameBuffer().AttachLayer(*_Normal);
        _Color = COFFEE_New(FrameLayerBGRA, GetFrameBuffer().GetWidth(), GetFrameBuffer().GetHeight());
        GetFrameBuffer().AttachLayer(*_Color);
        _Material = COFFEE_New(FrameLayerBGRA, GetFrameBuffer().GetWidth(), GetFrameBuffer().GetHeight());
        GetFrameBuffer().AttachLayer(*_Material);
    }

    //--------------------------------------------------------------------------------------------//

    void FramePassGBuffer::Finalize(FramePass* previous_pass)
    {
        GetFrameBuffer().DetachLayer(*_Material);
        COFFEE_Delete(_Material);
        GetFrameBuffer().DetachLayer(*_Color);
        COFFEE_Delete(_Color);
        GetFrameBuffer().DetachLayer(*_Normal);
        COFFEE_Delete(_Normal);
        GetFrameBuffer().DetachLayer(*_LinearDepth);
        COFFEE_Delete(_LinearDepth);
        GetFrameBuffer().DetachLayer(*_Depth);
        COFFEE_Delete(_Depth);
    }

    //--------------------------------------------------------------------------------------------//
        
    void FramePassGBuffer::Render(Viewport& viewport, FramePass* previous_pass)
    {
        COFFEE_GRAPHICS_Debug();
        
        Renderer::Get().ClearAll();
        COFFEE_GRAPHICS_Debug();
        Renderer::Get().SetCameraToViewportMatrix(
            viewport.GetCamera().GetComponent().GetInfiniteProjectionMatrix());
        COFFEE_GRAPHICS_Debug();
        
        for (uint32 i=0 ; i<viewport.GetGatherer().GetOpaqueChunks().GetSize() ; ++i)
            viewport.GetGatherer().GetOpaqueChunks()[i]->Render(viewport);

        COFFEE_GRAPHICS_Debug();        
    }

}
}
