#include "system/graphics/frame/shader/graphics_frame_shader.h"
#include "system/graphics/graphics.h"

namespace coffee
{
namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    FrameShader::FrameShader()
    {
        /*
        _Width = FrameGBuffer::Get().GetWidth();
        _Height = FrameGBuffer::Get().GetHeight();
        _FrameBuffer = (uint8*)COFFEE_Allocate(_Width*_Height*4);
        _DepthBuffer = (real*)COFFEE_Allocate(_Width*_Height*sizeof(real));*/
    }

    //--------------------------------------------------------------------------------------------//

    FrameShader::~FrameShader()
    {
        COFFEE_Free(_FrameBuffer);
        COFFEE_Free(_DepthBuffer);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    static uint32 FrameShader_Offset = 0;

    void FrameShader::Render(FrameLayer& frame_buffer)
    {
        //frame_buffer.GetData(_FrameBuffer, 0, 0, _Width, _Height);
        //FrameGBuffer::Get().GetLayer((uint32) FRAME_GBUFFER_LAYER_TYPE_Depth).GetTextureData(
        //    _DepthBuffer, 0, 0, _Width, _Height);
        
        uint8* frame_ptr = _FrameBuffer;
        real* depth_ptr = _DepthBuffer;

        FrameShader_Offset = basic::GetRandom(10);

        for (uint32 y=0 ; y<_Height ; ++y)
        for (uint32 x=0 ; x<_Width ; ++x)
        {
            RenderPixel(frame_ptr, depth_ptr, x, y);
            frame_ptr += 4;
            ++depth_ptr;
        }
    
       // frame_buffer.SetData(_FrameBuffer);
    }

    //--------------------------------------------------------------------------------------------//

    void FrameShader::RenderPixel(uint8* pixel, const real* depth, uint32 x, uint32 y)
    {
        if (x<_Width-FrameShader_Offset*3)
        {
            //float v = (1.0f-*depth)*60000.0f/25.0f;
            //Clamp(v, 0.0f, 1.0f);
            pixel[0] = pixel[4*FrameShader_Offset];
            pixel[1] = pixel[1+4*FrameShader_Offset*2];
            pixel[2] = pixel[2+4*FrameShader_Offset*3];
        }
    }

}
}
