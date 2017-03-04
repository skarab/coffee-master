#ifndef _COFFEE_GRAPHICS_FRAME_PASS_SKY_H_
#define _COFFEE_GRAPHICS_FRAME_PASS_SKY_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/frame/pass/graphics_frame_pass.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Sky pass
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API FramePassSky : public FramePass
    {
        COFFEE_Type(FramePassSky);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        FramePassSky();
        ~FramePassSky();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Initialize(FramePass* previous_pass);
        void Finalize(FramePass* previous_pass);
        void Render(Viewport& viewport, FramePass* previous_pass);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Material _SkyMaterial;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, FramePassSky);
}
}
#endif
