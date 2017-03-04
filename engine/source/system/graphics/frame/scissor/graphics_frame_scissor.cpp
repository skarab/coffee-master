#include "system/graphics/frame/scissor/graphics_frame_scissor.h"
#include "system/graphics/device/graphics_device.h"
#include "system/graphics/viewport/graphics_viewport.h"

namespace coffee
{
namespace graphics
{
    //-VARIABLES----------------------------------------------------------------------------------//

    basic::Rectangle FrameScissor::_LatestRectangle;

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    FrameScissor::FrameScissor()
    {
    }

    //--------------------------------------------------------------------------------------------//

    FrameScissor::FrameScissor(const FrameScissor& scissor) :
        _Rectangle(scissor._Rectangle)
    {
    }

    //--------------------------------------------------------------------------------------------//

    FrameScissor::~FrameScissor()
    {
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    FrameScissor& FrameScissor::operator = (const FrameScissor& scissor)
    {
        _Rectangle = scissor._Rectangle;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    FrameScissor FrameScissor::operator - (const FrameScissor& scissor) const
    {
        FrameScissor result;
        result.SetRectangle(_Rectangle - scissor._Rectangle);
        return result;
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void FrameScissor::SetRectangle(const basic::Rectangle& rectangle)
    {
        _Rectangle = rectangle;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Rectangle& FrameScissor::GetRectangle() const
    {
        return _Rectangle;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void FrameScissor::Bind()
    {
        _LatestRectangle = _Rectangle;
        Enable();
    }

    //--------------------------------------------------------------------------------------------//

    void FrameScissor::BindOnFrameBuffer()
    {
        glEnable(GL_SCISSOR_TEST);

        int32 size_x = _Rectangle.GetMaximum().X-_Rectangle.GetMinimum().X;
        if (size_x<0) size_x=0;
        int32 size_y = _Rectangle.GetMaximum().Y-_Rectangle.GetMinimum().Y;
        if (size_y<0) size_y=0;
        
        glScissor(
            _Rectangle.GetMinimum().X-1,
            _Rectangle.GetMinimum().Y-1,
            size_x+1, size_y+1 );
    }

    //--------------------------------------------------------------------------------------------//

    void FrameScissor::UnBind()
    {
        Disable();
    }

    //-FUNCTIONS----------------------------------------------------------------------------------//

    void FrameScissor::Enable()
    {
        glEnable(GL_SCISSOR_TEST);

        int32 size_x = _LatestRectangle.GetMaximum().X-_LatestRectangle.GetMinimum().X;
        if (size_x<0) size_x=0;
        int32 size_y = _LatestRectangle.GetMaximum().Y-_LatestRectangle.GetMinimum().Y;
        if (size_y<0) size_y=0;
                
        glScissor(
            _LatestRectangle.GetMinimum().X-1,
            Device::Get().GetHeight()-_LatestRectangle.GetMaximum().Y-1,
            size_x+1, size_y+1 );
    }

    //--------------------------------------------------------------------------------------------//

    void FrameScissor::Disable()
    {
        glDisable(GL_SCISSOR_TEST);
    }

}
}
