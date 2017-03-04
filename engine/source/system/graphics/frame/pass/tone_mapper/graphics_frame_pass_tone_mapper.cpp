#include "system/graphics/frame/pass/tone_mapper/graphics_frame_pass_tone_mapper.h"
#include "system/graphics/graphics.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::FramePassToneMapper);
        COFFEE_Ancestor(graphics::FramePass);
    COFFEE_EndType();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    FramePassToneMapper::FramePassToneMapper() :
        FramePass("ToneMapper"),
        _ItIsReady(0)
    {
    }

    //--------------------------------------------------------------------------------------------//

    FramePassToneMapper::~FramePassToneMapper()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void FramePassToneMapper::Initialize(FramePass* previous_pass)
    {
        _Layer = COFFEE_New(FrameLayerBGRA, GetFrameBuffer().GetWidth(), GetFrameBuffer().GetHeight(), false);
        GetFrameBuffer().AttachLayer(*_Layer);
        _LuminanceMaterial = resource::Manager::Get().Load("/coffee/import/shaders/tonemap/compute_luminance.material");
        _EyeAdaptationMaterial = resource::Manager::Get().Load("/coffee/import/shaders/tonemap/eye_adaptation.material");
        _AdaptationTime = 0.0f;

        for (int32 i=0 ; i<7 ; ++i)
        {
            uint32 size = (uint32)pow(2.0, 6-i);
            _MipmapBuffers[i] = COFFEE_New(FrameBuffer, size, size);
            _MipmapLayers[i] = COFFEE_New(FrameLayerBGRA, size, size, true);
            _MipmapBuffers[i]->AttachLayer(*_MipmapLayers[i]);
        }
        _MipmapMaterial = resource::Manager::Get().Load("/coffee/import/shaders/tonemap/generate_mipmap.material");
    }

    //--------------------------------------------------------------------------------------------//

    void FramePassToneMapper::Finalize(FramePass* previous_pass)
    {
        for (uint32 i=0 ; i<7 ; ++i)
        {
            _MipmapBuffers[i]->DetachLayer(*_MipmapLayers[i]);
            COFFEE_Delete(_MipmapLayers[i]);
            COFFEE_Delete(_MipmapBuffers[i]);
        }

        GetFrameBuffer().DetachLayer(*_Layer);
        COFFEE_Delete(_Layer);
    }

    //--------------------------------------------------------------------------------------------//
    
    void FramePassToneMapper::Render(Viewport& viewport, FramePass* previous_pass)
    {
        if (viewport.HasCamera() && viewport.GetCamera().GetComponent().GetToneMapper().IsAvailable())
        {
            GetFrameBuffer().UnBind(viewport);

            uint32 old_layer = 0;
            uint32 new_layer = 1;
            uint32 eye_layer = 2;            

            // Compute scene average luminance
            _AdaptationTime += viewport.GetTimeStep().GetSecondCount();

            real adaptation_speed = Minimum(viewport.GetCamera().GetComponent().GetBrightAdaptationTime(),
                    viewport.GetCamera().GetComponent().GetDarkAdaptationTime());

            if (_ItIsReady<2)
                _AdaptationTime = adaptation_speed+1.0f;

            if (_EyeAdaptationMaterial.IsAvailable()
                && _LuminanceMaterial.IsAvailable()
                && _MipmapMaterial.IsAvailable()
                && _AdaptationTime>=adaptation_speed)
            {
                _AdaptationTime = Minimum(_AdaptationTime, adaptation_speed);

                FrameBuffer* old_buffer = viewport._LuminanceBuffers[old_layer];
                FrameLayerBGRA* old = viewport._LuminanceLayers[old_layer];
                viewport._LuminanceBuffers[old_layer] = viewport._LuminanceBuffers[eye_layer];
                viewport._LuminanceLayers[old_layer] = viewport._LuminanceLayers[eye_layer];
                viewport._LuminanceBuffers[eye_layer] = old_buffer;
                viewport._LuminanceLayers[eye_layer] = old;

                // Manually generate mipmaps since glGenerateMipmaps stalls GPU depending of drivers

                _MipmapBuffers[0]->Bind(viewport);
                previous_pass->GetFrameBuffer().GetLayer(0).Bind(0);
                _LuminanceMaterial.Bind();
                RenderQuad(viewport, &previous_pass->GetFrameBuffer());
                _LuminanceMaterial.UnBind();
                previous_pass->GetFrameBuffer().GetLayer(0).UnBind(0);
                _MipmapBuffers[0]->UnBind(viewport);

                for (uint32 i=1 ; i<8 ; ++i)
                {
                    if (i<7) _MipmapBuffers[i]->Bind(viewport);
                    else viewport._LuminanceBuffers[new_layer]->Bind(viewport);

                    _MipmapLayers[i-1]->Bind(0);
                    _MipmapMaterial.Bind();
                    RenderQuad(viewport, _MipmapBuffers[i-1]);
                    _MipmapMaterial.UnBind();
                    _MipmapLayers[i-1]->UnBind(0);
                    
                    if (i<7) _MipmapBuffers[i]->UnBind(viewport);
                    else viewport._LuminanceBuffers[new_layer]->UnBind(viewport);
                }
                
                if (_ItIsReady>=2)
                {
                    _AdaptationTime = 0.0f;
                }
                else
                {
                    ++_ItIsReady;
                }
            }

            // Compute eye adaptation
            viewport._LuminanceBuffers[eye_layer]->Bind(viewport);
            viewport._LuminanceLayers[old_layer]->Bind(0);
            viewport._LuminanceLayers[new_layer]->Bind(1, viewport._LuminanceLayers[new_layer]->GetMipmapCount()-1);
            _EyeAdaptationMaterial.Bind();
            RenderQuad(viewport);
            _EyeAdaptationMaterial.UnBind();
            viewport._LuminanceLayers[new_layer]->UnBind(1);
            viewport._LuminanceLayers[old_layer]->UnBind(0);
            viewport._LuminanceBuffers[eye_layer]->UnBind(viewport);

            // Apply tone mapper
            GetFrameBuffer().Bind(viewport);
            previous_pass->GetFrameBuffer().GetLayer(0).Bind(0);
            viewport._LuminanceLayers[eye_layer]->Bind(1);            
            viewport.GetCamera().GetComponent().GetToneMapper().Bind();
            RenderQuad(viewport);
            viewport.GetCamera().GetComponent().GetToneMapper().UnBind();
            viewport._LuminanceLayers[eye_layer]->UnBind(1);
            previous_pass->GetFrameBuffer().GetLayer(0).UnBind(0);
        }
        else
        {
            Renderer::Get().ClearColor();
        }
     }

}
}
