#ifndef _COFFEE_GRAPHICS_FRAME_LAYER_DEPTH_H_
#define _COFFEE_GRAPHICS_FRAME_LAYER_DEPTH_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/frame/layer/graphics_frame_layer.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Layer based on a depth texture
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API FrameLayerDepth : public FrameLayer
    {
        COFFEE_Type(FrameLayerDepth);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        FrameLayerDepth(uint32 width=0, uint32 height=0);
        ~FrameLayerDepth();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Bind(uint32 slot);
        void BindStencil(uint32 slot);
        void UnBind(uint32 slot);

    protected:

        //-QUERIES--------------------------------------------------------------------------------//

        uint32 _GetInternalFormat() const { return GL_DEPTH24_STENCIL8_EXT; }
        uint32 _GetFormat() const { return GL_DEPTH_STENCIL_EXT; }
        uint32 _GetType() const { return GL_UNSIGNED_INT_24_8_EXT; }
        uint32 _GetMask() const { return GL_DEPTH_BUFFER_BIT; }
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, FrameLayerDepth);
}
}
#endif
