#ifndef _COFFEE_GRAPHICS_FRAME_PASS_H_
#define _COFFEE_GRAPHICS_FRAME_PASS_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/frame/buffer/graphics_frame_buffer.h"
#include "system/graphics/viewport/graphics_viewport.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Frame pass interface
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API FramePass : public meta::Object
    {
        COFFEE_Type(FramePass);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        FramePass();
        FramePass(basic::String name);
        virtual ~FramePass();

        //-ACCESSORS------------------------------------------------------------------------------//

        const basic::String& GetName() const { return _Name; }
        void Enable(bool it_is_enabled) { _ItIsEnabled = it_is_enabled; }
        bool IsEnabled() const { return _ItIsEnabled; }
        const FrameBuffer& GetFrameBuffer() const { return *_FrameBuffer; }
        FrameBuffer& GetFrameBuffer() { return *_FrameBuffer; }
        
        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void Initialize(FramePass* previous_pass) {};
        virtual void Finalize(FramePass* previous_pass) {};
        virtual void Render(Viewport& viewport, FramePass* previous_pass) {};
        
    protected:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void RenderQuad(Viewport& viewport, FrameBuffer* input_frame_buffer=NULL);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::String _Name;
        bool _ItIsEnabled;
        FrameBuffer* _FrameBuffer;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, FramePass);
}
}
#endif
