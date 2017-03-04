//------------------------------------------------------------------------------------------------//
/// @file wide/ui/skin/widget/ui_skin_image.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "wide/ui/skin/widget/ui_skin_image.h"
#include "system/graphics/renderer/graphics_renderer.h"
#include "system/graphics/device/graphics_device.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::SkinImage);
        COFFEE_Ancestor(ui::SkinWidget);
        COFFEE_Attribute(ui::SkinWidgetState, _Frame, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();
    
namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SkinImage::SkinImage() :
        SkinWidget("Image", widget::Image::GetClassMetaType())
    {
    }

    //--------------------------------------------------------------------------------------------//

    SkinImage::~SkinImage()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void SkinImage::ApplyTheme(SkinTheme& theme)
    {
        SetBorderSize(basic::Vector2i(5, 5));

        _Frame.SetFontColor(basic::Color(0.0f, 0.0f, 0.0f, 1.0f));
        _Frame.SetColor(basic::Color(0.22f, 0.22f, 0.22f, 1.0f));
        _Frame.SetHighlightColor(basic::Color(0.30f, 0.30f, 0.30f, 1.0f));
        _Frame.SetShadowColor(basic::Color(0.04f, 0.04f, 0.04f, 1.0f));
    }

    //--------------------------------------------------------------------------------------------//

    void SkinImage::Render(Window& window, const SkinContext& paint_context)
    {
        graphics::FrameScissor scissor;

        scissor.SetRectangle(paint_context.GetDesktopClipRect());
        scissor.Bind();

        if(window.HasExtendedStyle(widget::IMAGE_STYLE_DrawFrame))
        {
            graphics::Renderer::Get().SetDefaultRenderState();
            graphics::Renderer::Get().EnableDepthTest(false);
            graphics::Renderer::Get().SetFaceCullingMode(graphics::RENDER_STATE_FACE_CULLING_None);

            graphics::Renderer::Get().SetColor(_Frame.GetColor());

            // FrameArea

            paint_context.Render().Rectangle(
                paint_context.GetDesktopWindowRect().GetMinimum(),
                paint_context.GetDesktopWindowRect().GetMaximum());

            // FrameBorders

            graphics::Renderer::Get().SetColor(_Frame.GetShadowColor());

            paint_context.Render().Line(
                basic::Vector2i(paint_context.GetDesktopWindowRect().GetMaximum().X,
                paint_context.GetDesktopWindowRect().GetMaximum().Y),
                basic::Vector2i(paint_context.GetDesktopWindowRect().GetMaximum().X,
                paint_context.GetDesktopWindowRect().GetMinimum().Y));

            paint_context.Render().Line(
                basic::Vector2i(paint_context.GetDesktopWindowRect().GetMaximum().X,
                paint_context.GetDesktopWindowRect().GetMaximum().Y),
                basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X,
                paint_context.GetDesktopWindowRect().GetMaximum().Y));

            graphics::Renderer::Get().SetColor(_Frame.GetHighlightColor());

            paint_context.Render().Line(
                basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X,
                paint_context.GetDesktopWindowRect().GetMinimum().Y),
                basic::Vector2i(paint_context.GetDesktopWindowRect().GetMaximum().X,
                paint_context.GetDesktopWindowRect().GetMinimum().Y));

            paint_context.Render().Line(
                basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X,
                paint_context.GetDesktopWindowRect().GetMinimum().Y),
                basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X,
                paint_context.GetDesktopWindowRect().GetMaximum().Y));
        }

        widget::Image* widget = (widget::Image*) &window;
        widget->RenderImage(paint_context);
    }

}
}
//------------------------------------------------------------------------------------------------//
