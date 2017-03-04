#ifndef _COFFEE_GRAPHICS_FRAME_PICKER_H_
#define _COFFEE_GRAPHICS_FRAME_PICKER_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/frame/buffer/graphics_frame_buffer.h"
#include "system/graphics/material/graphics_material.h"

namespace coffee
{
namespace graphics
{
    //-FORWARDS-----------------------------------------------------------------------------------//
    class FramePickerContext;

    //--------------------------------------------------------------------------------------------//
    /// Frame picker
    ///
    /// For now its only used to keep the picker material loaded, used by the picking context.
    /// Maybe it'll be moved somewhere else in the future...
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API FramePicker
    {
        friend class FramePickerContext;

        COFFEE_DeclareSingleton(FramePicker);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        FramePicker();
        ~FramePicker();

        //-ACCESSORS------------------------------------------------------------------------------//

        Material& GetMaterial() { return _Material; }

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Material _Material;
    };
}
}
#endif
