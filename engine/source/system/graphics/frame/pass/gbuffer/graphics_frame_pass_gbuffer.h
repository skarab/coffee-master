#ifndef _COFFEE_GRAPHICS_FRAME_PASS_GBUFFER_H_
#define _COFFEE_GRAPHICS_FRAME_PASS_GBUFFER_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/frame/pass/graphics_frame_pass.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// GeometricBuffer pass
    ///
    ///  Architecture :
    ///  -----------------------------------------------------------------------
    ///  |   Layer   |     R     |     G     |     B     |     A     | Binding |
    ///  -----------------------------------------------------------------------
    ///  | depth     |  Depth using infinite projection  | Stencil   |  depth  |
    ///  -----------------------------------------------------------------------
    ///  | l. depth  |      Linear Depth     |           |    ---    |    0
    ///  -----------------------------------------------------------------------
    ///  | normal    |     Nx    |     Ny    |     Nz    |    ---    |    1
    ///  -----------------------------------------------------------------------
    ///  | color     |     R     |     G     |     B     |           |    2    |
    ///  -----------------------------------------------------------------------
    ///  | material  | Metallic  | Roughness |           |           |    3    |
    ///  -----------------------------------------------------------------------
    ///
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API FramePassGBuffer : public FramePass
    {
        COFFEE_Type(FramePassGBuffer);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        FramePassGBuffer();
        ~FramePassGBuffer();

        //-ACCESSORS------------------------------------------------------------------------------//

        FrameLayerDepth& GetDepth() { return *_Depth; }
        FrameLayerBGRA& GetLinearDepth() { return *_LinearDepth; }
        FrameLayerBGRA& GetNormal() { return *_Normal; }
        FrameLayerBGRA& GetColor() { return *_Color; }
        FrameLayerBGRA& GetMaterial() { return *_Material; }
        
        //-OPERATIONS-----------------------------------------------------------------------------//

        void Initialize(FramePass* previous_pass);
        void Finalize(FramePass* previous_pass);
        void Render(Viewport& viewport, FramePass* previous_pass);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        FrameLayerDepth* _Depth;
        FrameLayerBGRA* _LinearDepth;
        FrameLayerBGRA* _Normal;
        FrameLayerBGRA* _Color;
        FrameLayerBGRA* _Material;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, FramePassGBuffer);
}
}
#endif
