#include "system/graphics/frame/buffer/graphics_frame_buffer.h"
#include "system/graphics/viewport/graphics_viewport.h"
#include "system/graphics/device/graphics_device.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::FrameBuffer);
    COFFEE_EndType();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    FrameBuffer::FrameBuffer(uint32 width, uint32 height, bool it_supports_mipmaps) :
        _Width(width),
        _Height(height),
        _ItSupportsMipmaps(it_supports_mipmaps),
        _Viewport(width, height)
    {
        COFFEE_Assert(!_ItSupportsMipmaps || (IsPowerOfTwo((int32)width) && IsPowerOfTwo((int32)height)),
            core::ERROR_CODE_IncorrectUsage, "Mipmap supports require power of two sizes");
        _Create();
    }

    //--------------------------------------------------------------------------------------------//

    FrameBuffer::~FrameBuffer()
    {
        _Destroy();
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void FrameBuffer::SetViewport(basic::Vector2i viewport)
    {
        _Viewport.Set(Minimum((uint32)viewport.X, _Width), Minimum((uint32)viewport.Y, _Height));
    }

    //--------------------------------------------------------------------------------------------//

    const FrameLayer& FrameBuffer::GetLayer(uint32 index) const
    {
        COFFEE_Assert(index<_Layers.GetSize(), core::ERROR_CODE_IncorrectUsage, "Incorrect layer index");
        return *_Layers[index];
    }
    
    //--------------------------------------------------------------------------------------------//

    FrameLayer& FrameBuffer::GetLayer(uint32 index)
    {
        COFFEE_Assert(index<_Layers.GetSize(), core::ERROR_CODE_IncorrectUsage, "Incorrect layer index");
        return *_Layers[index];
    }

    //--------------------------------------------------------------------------------------------//

    uint32 FrameBuffer::GetLayerIdentifier(const FrameLayer& layer) const
    {
        uint32 index = _Layers.FindItem((FrameLayer*)&layer);
        COFFEE_Assert(index!=NONE, core::ERROR_CODE_IncorrectUsage, "Layer isnt attached");
        return _LayerIdentifiers[index];
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void FrameBuffer::AttachLayer(FrameLayer& layer)
    {
        COFFEE_Assert(_ItSupportsMipmaps==layer.IsSupportingMipmaps(), core::ERROR_CODE_IncorrectUsage,
            "Mimap modes are different");
        _Layers.AddItem(&layer);
        _Update();
    }
    
    //--------------------------------------------------------------------------------------------//

    void FrameBuffer::DetachLayer(FrameLayer& layer)
    {
        _Layers.RemoveItem(&layer);
        _Update();
    }
    
    //--------------------------------------------------------------------------------------------//

    void FrameBuffer::Bind(Viewport& viewport)
    {
        glViewport(0, 0, _Viewport.X, _Viewport.Y);
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _Identifier);
        viewport.BindFrameBuffer(*this);
    }

    //--------------------------------------------------------------------------------------------//

    void FrameBuffer::UnBind(Viewport& viewport)
    {
        //_CheckValidity();
        viewport.UnBindFrameBuffer(*this);
        glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void FrameBuffer::_Create()
    {
        if (_Width!=0 && _Height!=0)
            glGenFramebuffersEXT(1, &_Identifier);
    }

    //--------------------------------------------------------------------------------------------//

    void FrameBuffer::_Destroy()
    {
        if (_Width!=0 && _Height!=0)
            glDeleteFramebuffersEXT(1, &_Identifier);
    }

    //--------------------------------------------------------------------------------------------//

    void FrameBuffer::_Update()
    {
        if (_Width!=0 && _Height!=0)
        {
            glEnable(_GetTextureMode());
            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, _Identifier);
            
            // Clear attachments
            glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, _GetTextureMode(), 0, 0);
            glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_STENCIL_ATTACHMENT_EXT, _GetTextureMode(), 0, 0);
            for (uint32 i=0 ; i<Device::Get().GetMaximumFrameColorLayers() ; ++i)
                glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT+i, _GetTextureMode(), 0, 0);
            
            // Build the new list
            uint32 color_layer_index(0);
            uint32* color_layers = (uint32*)COFFEE_Allocate(_Layers.GetSize()*sizeof(uint32));
            _LayerIdentifiers.Resize(_Layers.GetSize());
            for (uint32 i=0 ; i<_Layers.GetSize() ; ++i)
            {
                if (_Layers[i]->IsA<FrameLayerBGRA>())
                {
                    _LayerIdentifiers[i] = GL_COLOR_ATTACHMENT0_EXT+color_layer_index;
                    color_layers[color_layer_index] = _LayerIdentifiers[i];
                    ++color_layer_index;

                    COFFEE_Assert(color_layer_index<=Device::Get().GetMaximumFrameColorLayers(),
                        core::ERROR_CODE_GraphicsSystem, "Framebuffer unexpected error.");
                }
                else
                {
                    _LayerIdentifiers[i] = GL_DEPTH_ATTACHMENT_EXT;
                }

                glBindTexture(_GetTextureMode(), _Layers[i]->GetIdentifier());
                glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, _LayerIdentifiers[i],
                    _GetTextureMode(), _Layers[i]->GetIdentifier(), 0);
                
                if (_Layers[i]->IsA<FrameLayerDepth>())
                {
                    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_STENCIL_ATTACHMENT_EXT,
                        _GetTextureMode(), _Layers[i]->GetIdentifier(), 0);
                }
            }

            if (color_layer_index>0)
            {
                glDrawBuffers(color_layer_index, color_layers);
                _CheckValidity();
            }

            glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
            COFFEE_Free(color_layers);
            glBindTexture(_GetTextureMode(), 0);
            glDisable(_GetTextureMode());
        }
    }

    //--------------------------------------------------------------------------------------------//

    void FrameBuffer::_CheckValidity()
    {
        GLenum status;

        status = (GLenum) glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT);

        switch(status)
        {
            case GL_FRAMEBUFFER_COMPLETE_EXT:
                break;

            case GL_FRAMEBUFFER_UNSUPPORTED_EXT:
                COFFEE_Error(core::ERROR_CODE_GraphicsSystem, "Unsupported framebuffer format");
                break;

            case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT_EXT:
                COFFEE_Error(core::ERROR_CODE_GraphicsSystem, "Framebuffer incomplete, missing attachment");
                break;

            case GL_FRAMEBUFFER_INCOMPLETE_DUPLICATE_ATTACHMENT_EXT:
                COFFEE_Error(core::ERROR_CODE_GraphicsSystem, "Framebuffer incomplete, duplicate attachment");
                break;

            case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
                COFFEE_Error(core::ERROR_CODE_GraphicsSystem, "Framebuffer incomplete, attached images must have same dimensions");
                break;

            case GL_FRAMEBUFFER_INCOMPLETE_FORMATS_EXT:
                COFFEE_Error(core::ERROR_CODE_GraphicsSystem, "Framebuffer incomplete, attached images must have same format");
                break;

            case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER_EXT:
                COFFEE_Error(core::ERROR_CODE_GraphicsSystem, "Framebuffer incomplete, missing draw buffer");
                break;

            case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER_EXT:
                //COFFEE_Error(core::ERROR_CODE_GraphicsSystem, "Framebuffer incomplete, missing read buffer");
                break;

            case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT_EXT:
                COFFEE_Error(core::ERROR_CODE_GraphicsSystem, "Framebuffer incomplete attachment");
                break;

            default:
                COFFEE_Error(core::ERROR_CODE_GraphicsSystem, "Framebuffer error");
        }
    }

}
}
