#include "system/graphics/frame/layer/depth/graphics_frame_layer_depth.h"
#include "system/graphics/frame/buffer/graphics_frame_buffer.h"
#include "system/graphics/renderer/graphics_renderer.h"
#include "system/graphics/device/graphics_device.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::FrameLayerDepth);
        COFFEE_Ancestor(graphics::FrameLayer);
    COFFEE_EndType();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    FrameLayerDepth::FrameLayerDepth(uint32 width, uint32 height) :
        FrameLayer(width, height)
    {
        _Create();
    }

    //--------------------------------------------------------------------------------------------//

    FrameLayerDepth::~FrameLayerDepth()
    {
        _Destroy();
    }

    //-OPERATIONS---------------------------------------------------------------------------------//
    
    void FrameLayerDepth::Bind(uint32 slot)
    {
        glActiveTexture(GL_TEXTURE0+slot);
        glEnable(_GetTextureMode());
        glBindTexture(_GetTextureMode(), _Identifier);

        if (Device::Get().IsSupporting(DEVICE_SUPPORT_SoftShadows))
            glTexParameteri(_GetTextureMode(), GL_DEPTH_STENCIL_TEXTURE_MODE, GL_DEPTH_COMPONENT);
    }

    //--------------------------------------------------------------------------------------------//

    void FrameLayerDepth::BindStencil(uint32 slot)
    {
        COFFEE_Assert(Device::Get().IsSupporting(DEVICE_SUPPORT_SoftShadows), core::ERROR_CODE_GraphicsSystem,
            "Trying to bind unsupported stencil texture.");
        
        glActiveTexture(GL_TEXTURE0+slot);
        glEnable(_GetTextureMode());
        glBindTexture(_GetTextureMode(), _Identifier);
        glTexParameteri(_GetTextureMode(), GL_DEPTH_STENCIL_TEXTURE_MODE, GL_STENCIL_INDEX);
    }

    //--------------------------------------------------------------------------------------------//

    void FrameLayerDepth::UnBind(uint32 slot)
    {
        glActiveTexture(GL_TEXTURE0+slot);
        
        if (Device::Get().IsSupporting(DEVICE_SUPPORT_SoftShadows))
            glTexParameteri(_GetTextureMode(), GL_DEPTH_STENCIL_TEXTURE_MODE, GL_DEPTH_COMPONENT);
        
        glDisable(_GetTextureMode());
        glActiveTexture(GL_TEXTURE0);
    }

}
}
