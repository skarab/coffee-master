#ifndef _COFFEE_GRAPHICS_FRAME_PASS_TONE_MAPPER_H_
#define _COFFEE_GRAPHICS_FRAME_PASS_TONE_MAPPER_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/frame/pass/graphics_frame_pass.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Tone mapper pass
    ///
    /// It maps final HDR output to [0,1] range, applying gamma correction.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API FramePassToneMapper : public FramePass
    {
        COFFEE_Type(FramePassToneMapper);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        FramePassToneMapper();
        ~FramePassToneMapper();

        //-ACCESSORS------------------------------------------------------------------------------//

        real GetAdaptationTime() const { return _AdaptationTime; }

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Initialize(FramePass* previous_pass);
        void Finalize(FramePass* previous_pass);
        void Render(Viewport& viewport, FramePass* previous_pass);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        FrameLayerBGRA* _Layer;
        Material _LuminanceMaterial;
        Material _EyeAdaptationMaterial;
        real _AdaptationTime;
        uint32 _ItIsReady;

        // 64, 32, 16, 8, 4, 2, 1
        FrameBuffer* _MipmapBuffers[7];
        FrameLayerBGRA* _MipmapLayers[7];
        Material _MipmapMaterial;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, FramePassToneMapper);
}
}
#endif
