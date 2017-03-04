#ifndef _COFFEE_GRAPHICS_FRAME_SHADER_H_
#define _COFFEE_GRAPHICS_FRAME_SHADER_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/frame/layer/graphics_frame_layer.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// CPU shader test - Unusable
    /// 
    /// It retrieves GPU depth & color buffers, generate RGB offsets and upload to the GPU.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API FrameShader
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        FrameShader();
        ~FrameShader();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Render(FrameLayer& frame_buffer);
        void RenderPixel(uint8* pixel, const real* depth, uint32 x, uint32 y);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        uint32 _Width;
        uint32 _Height;
        uint8* _FrameBuffer;
        real* _DepthBuffer;
    };
}
}
#endif
