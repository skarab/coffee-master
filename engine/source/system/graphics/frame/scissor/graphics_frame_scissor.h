#ifndef _COFFEE_GRAPHICS_FRAME_SCISSOR_H_
#define _COFFEE_GRAPHICS_FRAME_SCISSOR_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"

namespace coffee
{
namespace graphics
{
    class Viewport;

    //--------------------------------------------------------------------------------------------//
    /// Frame scissor
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API FrameScissor
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        FrameScissor();
        FrameScissor(const FrameScissor& scissor);
        virtual ~FrameScissor();

        //-OPERATORS------------------------------------------------------------------------------//

        FrameScissor& operator = (const FrameScissor& scissor);
        FrameScissor operator - (const FrameScissor& scissor) const;

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetRectangle(const basic::Rectangle& rectangle);
        const basic::Rectangle& GetRectangle() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Bind();
        void BindOnFrameBuffer();
        void UnBind();
        
        //-FUNCTIONS------------------------------------------------------------------------------//

        static void Enable();
        static void Disable();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Rectangle _Rectangle;

        //-VARIABLES------------------------------------------------------------------------------//

        static basic::Rectangle _LatestRectangle;
    };
}
}
#endif
