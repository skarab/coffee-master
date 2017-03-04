#include "system/graphics/frame/pass/sky/graphics_frame_pass_sky.h"
#include "system/graphics/graphics.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::FramePassSky);
        COFFEE_Ancestor(graphics::FramePass);
    COFFEE_EndType();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    FramePassSky::FramePassSky() :
        FramePass("Sky")
    {
    }

    //--------------------------------------------------------------------------------------------//

    FramePassSky::~FramePassSky()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void FramePassSky::Initialize(FramePass* previous_pass)
    {
        GetFrameBuffer().AttachLayer(previous_pass->GetFrameBuffer().GetLayer(0));
        GetFrameBuffer().AttachLayer(FramePassSystem::Get().GetGBufferPass().GetDepth());
        _SkyMaterial = resource::Manager::Get().Load("/coffee/import/shaders/sky/skyprobe.material");
    }

    //--------------------------------------------------------------------------------------------//

    void FramePassSky::Finalize(FramePass* previous_pass)
    {
        GetFrameBuffer().DetachLayer(previous_pass->GetFrameBuffer().GetLayer(0));
        GetFrameBuffer().DetachLayer(FramePassSystem::Get().GetGBufferPass().GetDepth());
    }

    //--------------------------------------------------------------------------------------------//
    
    void FramePassSky::Render(Viewport& viewport, FramePass* previous_pass)
    {
        ComponentSky* sky = viewport.GetCamera().GetScene().Get().GetRoot().FindComponent<ComponentSky>();
        if (sky!=NULL && sky->GetSky().IsReady() && _SkyMaterial.IsAvailable())
        {
            sky->GetSky().Bind();
            _SkyMaterial.Bind();
            RenderQuad(viewport);
            _SkyMaterial.UnBind();
            sky->GetSky().UnBind();
        }
     }

}
}
