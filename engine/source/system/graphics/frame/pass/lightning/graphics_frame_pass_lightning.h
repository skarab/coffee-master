#ifndef _COFFEE_GRAPHICS_FRAME_PASS_LIGHTNING_H_
#define _COFFEE_GRAPHICS_FRAME_PASS_LIGHTNING_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/frame/pass/graphics_frame_pass.h"
#include "system/graphics/frame/pass/post_process/graphics_frame_pass_post_process.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Lightning pass
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API FramePassLightning : public FramePass
    {
        COFFEE_Type(FramePassLightning);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        FramePassLightning();
        ~FramePassLightning();

        //-ACCESSORS------------------------------------------------------------------------------//

        int32 GetShadowDepthPass() const { return _ShadowDepthPass; }

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Initialize(FramePass* previous_pass);
        void Finalize(FramePass* previous_pass);
        void Render(Viewport& viewport, FramePass* previous_pass);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _RenderLight(Light& light, Viewport& viewport);
        void _PreRenderShadows(Light& light, Viewport& viewport);
        void _PostRenderShadows(Light& light, Viewport& viewport);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        FrameLayerBGRA* _Layer;
        graphics::Material _ShadowsMaterial;
        int32 _ShadowDepthPass;
        FramePassPostProcess _SoftFilterH;
        FramePassPostProcess _SoftFilterV;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, FramePassLightning);
}
}
#endif
