#ifndef _COFFEE_GRAPHICS_FRAME_PASS_TRANSPARENT_H_
#define _COFFEE_GRAPHICS_FRAME_PASS_TRANSPARENT_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/frame/pass/graphics_frame_pass.h"
#include "system/graphics/component/graphics_components.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Transparent pass
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API FramePassTransparent : public FramePass
    {
        COFFEE_Type(FramePassTransparent);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        FramePassTransparent(bool it_is_hdr=false);
        ~FramePassTransparent();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Initialize(FramePass* previous_pass);
        void Finalize(FramePass* previous_pass);
        void Render(Viewport& viewport, FramePass* previous_pass);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        bool _ItIsHDR;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, FramePassTransparent);
}
}
#endif
