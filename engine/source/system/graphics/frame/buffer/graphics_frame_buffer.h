#ifndef _COFFEE_GRAPHICS_FRAME_BUFFER_H_
#define _COFFEE_GRAPHICS_FRAME_BUFFER_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/frame/layer/graphics_frame_layer.h"
#include "system/graphics/frame/layer/depth/graphics_frame_layer_depth.h"
#include "system/graphics/frame/layer/bgra/graphics_frame_layer_bgra.h"

namespace coffee
{
namespace graphics
{
    class Viewport;

    //--------------------------------------------------------------------------------------------//
    /// Frame buffer
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API FrameBuffer : public meta::Object
    {
        COFFEE_Type(FrameBuffer);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        FrameBuffer(uint32 width=0, uint32 height=0, bool it_supports_mipmaps=false);
        ~FrameBuffer();

        //-ACCESSORS------------------------------------------------------------------------------//

        uint32 GetWidth() const { return _Width; }
        uint32 GetHeight() const { return _Height; }
        bool IsSupportingMipmaps() const { return _ItSupportsMipmaps; }
        void SetViewport(basic::Vector2i viewport);
        const basic::Vector2i& GetViewport() const { return _Viewport; }
        const uint32 GetLayerCount() const { return _Layers.GetSize(); }
        const FrameLayer& GetLayer(uint32 index) const;
        FrameLayer& GetLayer(uint32 index);
        uint32 GetIdentifier() const { return _Identifier; }
        uint32 GetLayerIdentifier(const FrameLayer& layer) const;
        
        //-OPERATIONS-----------------------------------------------------------------------------//

        void AttachLayer(FrameLayer& layer);
        void DetachLayer(FrameLayer& layer);
        void Bind(Viewport& viewport);
        void UnBind(Viewport& viewport);

    private:

        //-QUERIES--------------------------------------------------------------------------------//

        uint32 _GetTextureMode() { return _ItSupportsMipmaps?GL_TEXTURE_2D:GL_TEXTURE_RECTANGLE_ARB; }

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _Create();
        void _Destroy();
        void _Update();
        void _CheckValidity();
        
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        uint32 _Width;
        uint32 _Height;
        bool _ItSupportsMipmaps;
        basic::Vector2i _Viewport;
        basic::Prow< FrameLayer* > _Layers;
        uint32 _Identifier;
        basic::Array<uint32> _LayerIdentifiers;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, FrameBuffer);
}
}
#endif
