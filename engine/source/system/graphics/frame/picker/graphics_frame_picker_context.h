#ifndef _COFFEE_GRAPHICS_FRAME_PICKER_CONTEXT_H_
#define _COFFEE_GRAPHICS_FRAME_PICKER_CONTEXT_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/frame/picker/graphics_frame_picker.h"
#include "system/graphics/viewport/graphics_viewport.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Frame picker context
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API FramePickerContext
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        FramePickerContext(const basic::Rectangle& screen_rectangle);
        FramePickerContext(const basic::Vector2i& screen_point);
        ~FramePickerContext();

        //-QUERIES--------------------------------------------------------------------------------//

        uint32 GetHitCount() const;
        uint32 GetHitIndex(uint32 index) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Begin(Viewport& viewport);
        void End(Viewport& viewport);
        void Register(uint32 index);

    private:

        //-QUERIES--------------------------------------------------------------------------------//

        basic::Color _GetColorFromIndex(uint32 index) const;
        uint32 _GetIndexFromColor(uint8* buffer) const;
        bool _HasHitIndex(uint32 index) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _RetrieveHits(Viewport& viewport);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Rope<uint32> _HitIndexArray;
        basic::Rectangle _Rectangle;
        Viewport* _OldViewport;
    };
}
}
#endif
