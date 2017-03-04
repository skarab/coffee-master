#ifndef _COFFEE_GRAPHICS_FRAME_LAYER_H_
#define _COFFEE_GRAPHICS_FRAME_LAYER_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"

namespace coffee
{
namespace graphics
{
    class FrameBuffer;

    //--------------------------------------------------------------------------------------------//
    /// Frame layer which may be attached to multiple frame buffers
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API FrameLayer : public meta::Object
    {
        COFFEE_Type(FrameLayer);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        FrameLayer(uint32 width=0, uint32 height=0, bool it_supports_mipmaps=false);
        virtual ~FrameLayer();

        //-ACCESSORS------------------------------------------------------------------------------//

        uint32 GetWidth() const { return _Width; }
        uint32 GetHeight() const { return _Height; }
        bool IsSupportingMipmaps() const { return _ItSupportsMipmaps; }
        uint32 GetIdentifier() const { return _Identifier; }
        
        //-QUERIES--------------------------------------------------------------------------------//

        uint32 GetMipmapCount() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void Bind(uint32 slot, uint32 mipmap=0);
        virtual void UnBind(uint32 slot);
        void SetData(const FrameBuffer& framebuffer, const void* buffer);
        void GetData(void* buffer, const FrameBuffer& framebuffer, uint32 x_start, uint32 y_start, uint32 x_end, uint32 y_end) const;
        void CopyTo(const FrameBuffer& input, FrameBuffer& output, FrameLayer& output_layer) const; 
        void GenerateMipmaps();

    protected:

        //-QUERIES--------------------------------------------------------------------------------//

        uint32 _GetTextureMode() { return _ItSupportsMipmaps?GL_TEXTURE_2D:GL_TEXTURE_RECTANGLE_ARB; }
        virtual uint32 _GetInternalFormat() const { return 0; }
        virtual uint32 _GetFormat() const { return 0; }
        virtual uint32 _GetType() const { return 0; }
        virtual uint32 _GetMask() const { return 0; }
       
        //-OPERATIONS-----------------------------------------------------------------------------//

        void _Create();
        void _Destroy();

        //-ATTRIBUTES-----------------------------------------------------------------------------//
        
        uint32 _Width;
        uint32 _Height;
        bool _ItSupportsMipmaps;
        uint32 _Identifier;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, FrameLayer);
}
}
#endif
