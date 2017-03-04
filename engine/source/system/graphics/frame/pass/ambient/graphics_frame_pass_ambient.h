#ifndef _COFFEE_GRAPHICS_FRAME_PASS_AMBIENT_H_
#define _COFFEE_GRAPHICS_FRAME_PASS_AMBIENT_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/frame/pass/graphics_frame_pass.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Ambient pass
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API FramePassAmbient : public FramePass
    {
        COFFEE_Type(FramePassAmbient);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        FramePassAmbient();
        ~FramePassAmbient();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Initialize(FramePass* previous_pass);
        void Finalize(FramePass* previous_pass);
        void Render(Viewport& viewport, FramePass* previous_pass);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Material _AmbientMaterial;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, FramePassAmbient);
}
}
#endif
