#include "system/graphics/frame/layer/graphics_frame_layer.h"
#include "system/graphics/frame/buffer/graphics_frame_buffer.h"
#include "system/graphics/renderer/graphics_renderer.h"
#include "system/graphics/device/graphics_device.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::FrameLayer);
        COFFEE_Attribute(uint32, _Width, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(uint32, _Height, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(bool, _ItSupportsMipmaps, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    FrameLayer::FrameLayer(uint32 width, uint32 height, bool it_supports_mipmaps) :
        _Width(width),
        _Height(height),
        _ItSupportsMipmaps(it_supports_mipmaps)
    {
        COFFEE_Assert(!_ItSupportsMipmaps || (IsPowerOfTwo((int32)width) && IsPowerOfTwo((int32)height)),
            core::ERROR_CODE_IncorrectUsage, "Mipmap supports require power of two sizes");
    }

    //--------------------------------------------------------------------------------------------//

    FrameLayer::~FrameLayer()
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

    uint32 FrameLayer::GetMipmapCount() const
    {
        if (_ItSupportsMipmaps)
            return 1+(uint32)(floor(log10((float)Maximum(_Width, _Height))/log10(2.0f)));
        return 0;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//
    
    void FrameLayer::Bind(uint32 slot, uint32 mipmap)
    {
        glActiveTexture(GL_TEXTURE0+slot);
        glEnable(_GetTextureMode());
        glBindTexture(_GetTextureMode(), _Identifier);
    
        COFFEE_Assert(mipmap==0 || _ItSupportsMipmaps, core::ERROR_CODE_GraphicsSystem, "Mipmaps aren't enabled");
        if (_ItSupportsMipmaps)
            glTexParameteri(_GetTextureMode(), GL_TEXTURE_BASE_LEVEL, mipmap);
    }

    //--------------------------------------------------------------------------------------------//

    void FrameLayer::UnBind(uint32 slot)
    {
        glActiveTexture(GL_TEXTURE0+slot);
        if (_ItSupportsMipmaps)
            glTexParameteri(_GetTextureMode(), GL_TEXTURE_BASE_LEVEL, 0);
        glDisable(_GetTextureMode());
        glActiveTexture(GL_TEXTURE0);
    }

    //--------------------------------------------------------------------------------------------//

    void FrameLayer::SetData(const FrameBuffer& framebuffer, const void* buffer)
    {
        Renderer::Get().EnableDepthTest(false);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, framebuffer.GetWidth(), 0, framebuffer.GetHeight(), 0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRasterPos2i(0, 0); 
        glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, framebuffer.GetIdentifier());
        glDrawBuffer(framebuffer.GetLayerIdentifier(*this));
        glDrawPixels(framebuffer.GetWidth(), framebuffer.GetHeight(), _GetFormat(), _GetType(), buffer);
        glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, 0);
    }
    
    //--------------------------------------------------------------------------------------------//

    void FrameLayer::GetData(void* buffer, const FrameBuffer& framebuffer, uint32 x_start, uint32 y_start, uint32 x_end, uint32 y_end) const
    {
        glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, framebuffer.GetIdentifier());
        glReadBuffer(framebuffer.GetLayerIdentifier(*this));
        glReadPixels(x_start, y_start, x_end-x_start, y_end-y_start, _GetFormat(), _GetType(), buffer);
        glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, 0);
    }
    
    //--------------------------------------------------------------------------------------------//

    void FrameLayer::CopyTo(const FrameBuffer& input, FrameBuffer& output, FrameLayer& output_layer) const
    {
        // This will need testing on Intel graphics, blitting behaves strangely if sizes are different...
        COFFEE_Assert(_Width==output_layer._Width && _Height==output_layer._Height,
            core::ERROR_CODE_GraphicsSystem, "Copying layer of different size is unsupported");

        glBindFramebufferEXT(GL_READ_FRAMEBUFFER_EXT, input.GetIdentifier());
        glReadBuffer(input.GetLayerIdentifier(*this));
        glBindFramebufferEXT(GL_DRAW_FRAMEBUFFER_EXT, output.GetIdentifier());
        glDrawBuffer(output.GetLayerIdentifier(output_layer));
        glBlitFramebufferEXT(0, 0, input.GetWidth(), input.GetHeight(), 0, 0,
            output.GetWidth(), output.GetHeight(), _GetMask(), GL_NEAREST);
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    }

    //--------------------------------------------------------------------------------------------//

    void FrameLayer::GenerateMipmaps()
    {
        COFFEE_Assert(_ItSupportsMipmaps, core::ERROR_CODE_GraphicsSystem, "Mipmaps aren't enabled");
        //glHint(GL_GENERATE_MIPMAP_HINT, GL_FASTEST);
        glGenerateMipmapEXT(_GetTextureMode());
        //glHint(GL_GENERATE_MIPMAP_HINT, GL_NICEST);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//
    
    void FrameLayer::_Create()
    {
        if (_Width!=0 && _Height!=0)
        {
            COFFEE_GRAPHICS_Debug();        
            glEnable(_GetTextureMode());
            glGenTextures(1, &_Identifier);        
            COFFEE_GRAPHICS_Debug();

            glBindTexture(_GetTextureMode(), _Identifier);
            COFFEE_GRAPHICS_Debug();
            glTexImage2D(_GetTextureMode(), 0, _GetInternalFormat(),
                _Width, _Height, 0, _GetFormat(), _GetType(), NULL);
            COFFEE_GRAPHICS_Debug();
        
            if (_ItSupportsMipmaps)
            {
                glTexParameteri(_GetTextureMode(), GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
                glTexParameteri(_GetTextureMode(), GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            }
            else
            {
                glTexParameteri(_GetTextureMode(), GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(_GetTextureMode(), GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            }
            COFFEE_GRAPHICS_Debug();
            glDisable(_GetTextureMode());
            COFFEE_GRAPHICS_Debug();
        }
    }

    //--------------------------------------------------------------------------------------------//

    void FrameLayer::_Destroy()
    {
        
        if (_Width!=0 && _Height!=0)
        {
            COFFEE_GRAPHICS_Debug();
            glDeleteTextures(1, &_Identifier);
            COFFEE_GRAPHICS_Debug();
            _Width = 0;
            _Height = 0;
        }
        
    }

}
}
