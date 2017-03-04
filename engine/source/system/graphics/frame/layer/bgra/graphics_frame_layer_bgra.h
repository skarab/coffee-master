#ifndef _COFFEE_GRAPHICS_FRAME_LAYER_BGRA_H_
#define _COFFEE_GRAPHICS_FRAME_LAYER_BGRA_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/frame/layer/graphics_frame_layer.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Layer based on an BGRA texture
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API FrameLayerBGRA : public FrameLayer
    {
        COFFEE_Type(FrameLayerBGRA);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        FrameLayerBGRA(uint32 width=0, uint32 height=0, bool it_is_hdr=false, bool it_supports_mipmaps=false);
        ~FrameLayerBGRA();

        //-QUERIES--------------------------------------------------------------------------------//

        bool IsHDR() const { return _ItIsHDR; }

    protected:

        //-QUERIES--------------------------------------------------------------------------------//

        uint32 _GetInternalFormat() const { return _ItIsHDR?GL_R11F_G11F_B10F_EXT:GL_RGBA8; }
        uint32 _GetFormat() const { return _ItIsHDR?GL_RGB:GL_BGRA; }
        uint32 _GetType() const { return _ItIsHDR?GL_UNSIGNED_INT_10F_11F_11F_REV_EXT:GL_UNSIGNED_INT_8_8_8_8_REV; }
        uint32 _GetMask() const { return GL_COLOR_BUFFER_BIT; }

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        bool _ItIsHDR;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, FrameLayerBGRA);
}
}
#endif
