#include "system/graphics/frame/picker/graphics_frame_picker_context.h"
#include "system/graphics/renderer/graphics_renderer.h"
#include "system/graphics/viewport/graphics_viewport.h"

namespace coffee
{
namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    FramePickerContext::FramePickerContext(const basic::Vector2i& screen_point)
    {
        _Rectangle.AddPoint(screen_point, true);
    }
        
    //----------------------------------------------------------------------------------------//

    FramePickerContext::FramePickerContext(const basic::Rectangle& screen_rectangle) :
        _Rectangle(screen_rectangle)
    {
    }

    //----------------------------------------------------------------------------------------//

    FramePickerContext::~FramePickerContext()
    {
    }

    //-QUERIES--------------------------------------------------------------------------------//

    uint32 FramePickerContext::GetHitCount() const
    {
        return _HitIndexArray.GetSize();
    }

    //----------------------------------------------------------------------------------------//

    uint32 FramePickerContext::GetHitIndex(uint32 index) const
    {
        return _HitIndexArray[index];
    }

    //-OPERATIONS-----------------------------------------------------------------------------//

    void FramePickerContext::Begin(Viewport& viewport)
    {
        _OldViewport = NULL;
        if (Viewport::HasCurrent())
            _OldViewport = &Viewport::GetCurrent();
        Viewport::SetCurrent(&viewport);

        Renderer::Get().SetDefaultRenderState();
        FramePassSystem::Get().GetGBufferPass().GetFrameBuffer().Bind(viewport);
        Renderer::Get().ClearAll();
        FramePicker::Get()._Material.Bind();
        Renderer::Get().LockMaterial();
        
        // Set viewport camera matrix
        Renderer::Get().SetCameraToViewportMatrix(
            viewport.GetCamera().GetComponent().GetInfiniteProjectionMatrix());

        // Transform rectangle from viewport to frame
        basic::Vector2i screen_minimum = _Rectangle.GetMinimum();
        basic::Vector2i screen_maximum = _Rectangle.GetMaximum();
        basic::Vector2 frame_minimum = Viewport::GetCurrent().ComputeViewportToFramePoint(basic::Vector2(
            (real)screen_minimum.X, (real)screen_minimum.Y));
        basic::Vector2 frame_maximum = Viewport::GetCurrent().ComputeViewportToFramePoint(basic::Vector2(
            (real)screen_maximum.X, (real)screen_maximum.Y));
        _Rectangle.SetFromExtent(basic::Vector2i((int32)frame_minimum.X, (int32)frame_maximum.Y),
            basic::Vector2i((int32)frame_maximum.X, (int32)frame_minimum.Y));
    }

    //----------------------------------------------------------------------------------------//

    void FramePickerContext::End(Viewport& viewport)
    {
        Renderer::Get().UnLockMaterial();
        FramePicker::Get()._Material.UnBind();
        _RetrieveHits(viewport);
        FramePassSystem::Get().GetGBufferPass().GetFrameBuffer().UnBind(viewport);
        Viewport::SetCurrent(_OldViewport);

        if (_OldViewport!=NULL && _OldViewport->HasCamera())
        {
            Renderer::Get().SetCameraToViewportMatrix(
                _OldViewport->GetCamera().GetComponent().GetInfiniteProjectionMatrix());
        }
    }

    //----------------------------------------------------------------------------------------//

    void FramePickerContext::Register(uint32 index)
    {
        ShaderProperty* evaluator = FramePicker::Get()._Material.GrabShader().FindProperty("picker");
        if (evaluator!=NULL)
        {
            *static_cast<basic::Color*>(evaluator->GetValue().GetObject()) =
                _GetColorFromIndex(index+1);
        }
        
        Renderer::Get().UnLockMaterial();
        FramePicker::Get()._Material.Bind();
        Renderer::Get().LockMaterial();
    }

    //-QUERIES--------------------------------------------------------------------------------//

    basic::Color FramePickerContext::_GetColorFromIndex(uint32 index) const
    {
        return basic::Color(
            real((index>>16)&0xff ) * (1.0f/255.0f),
            real((index>>8)&0xff ) * (1.0f/255.0f),
            real(index&0xff) * (1.0f/255.0f),
            1.0f);
    }

    //----------------------------------------------------------------------------------------//

    uint32 FramePickerContext::_GetIndexFromColor(uint8* buffer) const
    {
        return ((uint32)buffer[2]<<16)
            | ((uint32)buffer[1]<<8)
            | ((uint32)buffer[0]);
    }

    //----------------------------------------------------------------------------------------//

    bool FramePickerContext::_HasHitIndex(uint32 index) const
    {
        for (int32 hit_index=_HitIndexArray.GetSize()-1 ; hit_index>=0 ; --hit_index)
        {
            if (_HitIndexArray[hit_index]==index)
                return true;
        }
        return false;
    }

    //-OPERATIONS-----------------------------------------------------------------------------//

    void FramePickerContext::_RetrieveHits(Viewport& viewport)
    {
        basic::Vector2i size = _Rectangle.Size;
        basic::Vector2i min = _Rectangle.GetMinimum();
        basic::Vector2i max = _Rectangle.GetMaximum();
        bool it_is_single_selection = size.X<4 && size.Y<4;
        uint8* buffer;
        uint32 index;
        
        if (it_is_single_selection)
            max += 1;

        Clamp(min.X, 0, viewport.GetFrameBufferSize().X);
        Clamp(min.Y, 0, viewport.GetFrameBufferSize().Y);
        Clamp(max.X, 0, viewport.GetFrameBufferSize().X);
        Clamp(max.Y, 0, viewport.GetFrameBufferSize().Y);
       
        buffer = (uint8*)COFFEE_Allocate(viewport.GetFrameBufferSize().X
            * viewport.GetFrameBufferSize().Y * 4);

        FramePassSystem::Get().GetGBufferPass().GetColor().GetData(
            buffer, FramePassSystem::Get().GetGBufferPass().GetFrameBuffer(),
            min.X, min.Y, max.X, max.Y);

        for (int32 y=0 ; y<max.Y-min.Y ; ++y)
        for (int32 x=0 ; x<max.X-min.X ; ++x)
        {
            index = _GetIndexFromColor(&buffer[(y*(max.X-min.X)+x)*4]);

            if (index!=0 && !_HasHitIndex(index-1))
            {
                _HitIndexArray.AddItem(index-1);
            
                if (it_is_single_selection)
                {
                    COFFEE_Free(buffer);
                    return;
                }
            }
        }        
        COFFEE_Free(buffer);
    }

}
}
