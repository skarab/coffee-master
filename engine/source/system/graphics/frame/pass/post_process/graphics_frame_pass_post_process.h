#ifndef _COFFEE_GRAPHICS_FRAME_PASS_POST_PROCESS_H_
#define _COFFEE_GRAPHICS_FRAME_PASS_POST_PROCESS_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/frame/pass/graphics_frame_pass.h"
#include "system/graphics/material/graphics_material.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Post-Process pass
    ///
    /// Render a full screen quad with the post process shader, having GBuffer and latest pass 
    /// framebuffer binded in input.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API FramePassPostProcess : public FramePass
    {
        COFFEE_Type(FramePassPostProcess);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        FramePassPostProcess(bool it_is_hdr=false);
        ~FramePassPostProcess();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetMaterial(Material material) { _Material = material; }
        const Material& GetMaterial() const { return _Material; }
        Material& GetMaterial() { return _Material; }
        const FrameLayerBGRA& GetLayer() const { return *_Layer; }
        FrameLayerBGRA& GetLayer() { return *_Layer; }

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Initialize(FramePass* previous_pass);
        void Finalize(FramePass* previous_pass);
        void Render(Viewport& viewport, FramePass* previous_pass);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        bool _ItIsHDR;
        Material _Material;
        FrameLayerBGRA* _Layer;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, FramePassPostProcess);
}
}
#endif
