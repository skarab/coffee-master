#include "system/graphics/frame/pass/graphics_frame_pass_system.h"
#include "system/graphics/component/graphics_component.h"
#include "system/graphics/device/graphics_device.h"
#include "system/graphics/viewport/graphics_viewport.h"
#include "system/graphics/renderer/graphics_renderer.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::FramePassSystem);
        COFFEE_Attribute(< graphics::FramePass* >, _Passes, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace graphics
{
    COFFEE_ImplementSingleton(FramePassSystem);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    FramePassSystem::FramePassSystem() :
        _CurrentPass(NULL)
    {
        COFFEE_CreateSingleton(FramePassSystem);
    
        if (Device::IsInstantiated())
        {
            COFFEE_GRAPHICS_Debug();

            _GBufferPass = COFFEE_New(FramePassGBuffer);
            _Passes.AddItem(_GBufferPass);
            _LightningPass = COFFEE_New(FramePassLightning);
            _Passes.AddItem(_LightningPass);
            _AmbientPass = COFFEE_New(FramePassAmbient);
            _Passes.AddItem(_AmbientPass);
            _SkyPass = COFFEE_New(FramePassSky);
            _Passes.AddItem(_SkyPass);
            _Passes.AddItem(COFFEE_New(FramePassTransparent, true));
            _ToneMappingPass = COFFEE_New(FramePassToneMapper);
            _Passes.AddItem(_ToneMappingPass);
            _Passes.AddItem(COFFEE_New(FramePassTransparent, false));

            for (uint32 i=0 ; i<_Passes.GetSize() ; ++i)
                _Passes[i]->Initialize(i==0?NULL:_Passes[i-1]);
        
            COFFEE_GRAPHICS_Debug();
        }
    }

    //--------------------------------------------------------------------------------------------//

    FramePassSystem::~FramePassSystem()
    {
        for (int32 i=_Passes.GetSize()-1 ; i>=0 ; --i)
            _Passes[i]->Finalize(i==0?NULL:_Passes[i-1]);

        COFFEE_DestroySingleton(FramePassSystem);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void FramePassSystem::Render(Viewport& viewport)
    {
        COFFEE_GRAPHICS_Debug();

        FrameScissor::Disable();

        FramePass* previous_pass = NULL;

        for (uint32 pass_index=0 ; pass_index<_Passes.GetSize() ; ++pass_index)
        {
            FramePass* pass = _Passes[pass_index];

            if (pass->IsEnabled())
            {
                _CurrentPass = pass;
                COFFEE_GRAPHICS_Debug();
        
                pass->GetFrameBuffer().Bind(viewport);
                COFFEE_GRAPHICS_Debug();
                pass->Render(viewport, previous_pass);
                COFFEE_GRAPHICS_Debug();
                pass->GetFrameBuffer().UnBind(viewport);                
                COFFEE_GRAPHICS_Debug();
                previous_pass = pass;
            }
        }

        COFFEE_GRAPHICS_Debug();
        
        FrameScissor::Enable();
        _Blit();   

        COFFEE_GRAPHICS_Debug();
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void FramePassSystem::_Blit()
    {
        Renderer::Get().SetDefaultRenderState();
        Renderer::Get().EnableDepthTest(false);
        Renderer::Get().EnableDepthWriting(false);
        Renderer::Get().SetFaceCullingMode(RENDER_STATE_FACE_CULLING_None);

        _CurrentPass->GetFrameBuffer().GetLayer(0).Bind(0);        
        
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();

        glBegin(GL_QUADS);
            glMultiTexCoord2i(GL_TEXTURE0, 0, 0); glVertex3i(-1, -1, -1);
            glMultiTexCoord2i(GL_TEXTURE0, _CurrentPass->GetFrameBuffer().GetWidth(), 0); glVertex3i(1, -1, -1);
            glMultiTexCoord2i(GL_TEXTURE0, _CurrentPass->GetFrameBuffer().GetWidth(), _CurrentPass->GetFrameBuffer().GetHeight()); glVertex3i(1,  1, -1);
            glMultiTexCoord2i(GL_TEXTURE0, 0, _CurrentPass->GetFrameBuffer().GetHeight()); glVertex3i(-1,  1, -1);
        glEnd();

        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();

        _CurrentPass->GetFrameBuffer().GetLayer(0).UnBind(0);        
    }

}
}
