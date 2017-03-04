#include "system/graphics/frame/pass/ambient/graphics_frame_pass_ambient.h"
#include "system/graphics/graphics.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::FramePassAmbient);
        COFFEE_Ancestor(graphics::FramePass);
    COFFEE_EndType();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    FramePassAmbient::FramePassAmbient() :
        FramePass("Ambient")
    {
    }

    //--------------------------------------------------------------------------------------------//

    FramePassAmbient::~FramePassAmbient()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void FramePassAmbient::Initialize(FramePass* previous_pass)
    {
        GetFrameBuffer().AttachLayer(previous_pass->GetFrameBuffer().GetLayer(0));
        GetFrameBuffer().AttachLayer(FramePassSystem::Get().GetGBufferPass().GetDepth());
        _AmbientMaterial = resource::Manager::Get().Load("/coffee/import/shaders/ambient.material");
    }

    //--------------------------------------------------------------------------------------------//

    void FramePassAmbient::Finalize(FramePass* previous_pass)
    {
        GetFrameBuffer().DetachLayer(previous_pass->GetFrameBuffer().GetLayer(0));
        GetFrameBuffer().DetachLayer(FramePassSystem::Get().GetGBufferPass().GetDepth());
    }

    //--------------------------------------------------------------------------------------------//
    
    void FramePassAmbient::Render(Viewport& viewport, FramePass* previous_pass)
    {
        ComponentSky* sky = viewport.GetCamera().GetScene().Get().GetRoot().FindComponent<ComponentSky>();
        if (sky!=NULL && sky->GetSky().IsReady() && _AmbientMaterial.IsAvailable())
        {
            COFFEE_GRAPHICS_Debug();
        
            FramePassSystem::Get().GetGBufferPass().GetNormal().Bind(0);
            FramePassSystem::Get().GetGBufferPass().GetColor().Bind(1);
            FramePassSystem::Get().GetGBufferPass().GetMaterial().Bind(2);

            Device::Get().CheckStatus();
        
            sky->GetSky().Bind(true);
            COFFEE_GRAPHICS_Debug();
                
            _AmbientMaterial.Bind();
            RenderQuad(viewport);
            _AmbientMaterial.UnBind();
            sky->GetSky().UnBind(true);
            FramePassSystem::Get().GetGBufferPass().GetMaterial().UnBind(2);
            FramePassSystem::Get().GetGBufferPass().GetColor().UnBind(1);
            FramePassSystem::Get().GetGBufferPass().GetNormal().UnBind(0);
        }
     }

}
}
