#ifndef _COFFEE_GRAPHICS_FRAME_PASS_SYSTEM_H_
#define _COFFEE_GRAPHICS_FRAME_PASS_SYSTEM_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/frame/pass/graphics_frame_pass.h"
#include "system/graphics/frame/pass/gbuffer/graphics_frame_pass_gbuffer.h"
#include "system/graphics/frame/pass/lightning/graphics_frame_pass_lightning.h"
#include "system/graphics/frame/pass/transparent/graphics_frame_pass_transparent.h"
#include "system/graphics/frame/pass/ambient/graphics_frame_pass_ambient.h"
#include "system/graphics/frame/pass/sky/graphics_frame_pass_sky.h"
#include "system/graphics/frame/pass/tone_mapper/graphics_frame_pass_tone_mapper.h"
#include "system/graphics/frame/pass/post_process/graphics_frame_pass_post_process.h"
#include "system/graphics/viewport/graphics_viewport.h"
#include "system/graphics/material/graphics_material.h"

namespace coffee
{
namespace graphics
{
    class Component;

    //--------------------------------------------------------------------------------------------//
    /// Frame pass system
    ///
    /// It uses stack based frame passes to generate a final framebuffer, using deffered shading,
    /// at the end it blits depth from GBuffer and the latest generated color buffer.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API FramePassSystem : public meta::Object
    {
        COFFEE_DeclareSingleton(FramePassSystem);
        COFFEE_Type(FramePassSystem);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        FramePassSystem();
        ~FramePassSystem();

        //-ACCESSORS------------------------------------------------------------------------------//

        const FramePassGBuffer& GetGBufferPass() const { return *_GBufferPass; }
        FramePassGBuffer& GetGBufferPass() { return *_GBufferPass; }
        const FramePassLightning& GetLightningPass() const { return *_LightningPass; }
        FramePassLightning& GetLightningPass() { return *_LightningPass; }
        const FramePassSky& GetSkyPass() const { return *_SkyPass; }
        FramePassSky& GetSkyPass() { return *_SkyPass; }
        const FramePassToneMapper& GetToneMappingPass() const { return *_ToneMappingPass; }
        FramePassToneMapper& GetToneMappingPass() { return *_ToneMappingPass; }
        const basic::Prow< FramePass*, true >& GetPasses() const { return _Passes; }
        basic::Prow< FramePass*, true >& GetPasses() { return _Passes; }

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Render(Viewport& viewport);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _Blit();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        FramePass* _CurrentPass;
        basic::Prow< FramePass*, true > _Passes;
        FramePassGBuffer* _GBufferPass;
        FramePassLightning* _LightningPass;
        FramePassAmbient* _AmbientPass;
        FramePassSky* _SkyPass;
        FramePassToneMapper* _ToneMappingPass;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, FramePassSystem);
}
}
#endif
