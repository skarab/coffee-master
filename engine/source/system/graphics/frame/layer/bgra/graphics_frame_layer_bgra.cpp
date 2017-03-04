#include "system/graphics/frame/layer/bgra/graphics_frame_layer_bgra.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::FrameLayerBGRA);
        COFFEE_Ancestor(graphics::FrameLayer);
    COFFEE_EndType();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    FrameLayerBGRA::FrameLayerBGRA(uint32 width, uint32 height, bool it_is_hdr, bool it_supports_mipmaps) :
        FrameLayer(width, height, it_supports_mipmaps),
        _ItIsHDR(it_is_hdr)
    {
        _Create();
    }

    //--------------------------------------------------------------------------------------------//

    FrameLayerBGRA::~FrameLayerBGRA()
    {
        _Destroy();
    }

}
}
