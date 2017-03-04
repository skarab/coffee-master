//------------------------------------------------------------------------------------------------//
/// @file wide/ui/skin/widget/ui_skin_tool_tip.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "wide/ui/skin/widget/ui_skin_tool_tip.h"
#include "system/graphics/renderer/graphics_renderer.h"
#include "system/graphics/device/graphics_device.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::SkinToolTip);
        COFFEE_Ancestor(ui::SkinWidget);
        COFFEE_Attribute(ui::SkinWidgetState, _StateEnabled, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SkinToolTip::SkinToolTip() :
        SkinWidget("ToolTip", widget::ToolTip::GetClassMetaType())
    {
    }

    //--------------------------------------------------------------------------------------------//

    SkinToolTip::~SkinToolTip()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void SkinToolTip::ApplyTheme(SkinTheme& theme)
    {
        SkinWidget::ApplyTheme(theme);

        SetBorderSize(basic::Vector2i(5, 5));

        _StateEnabled.SetFontColor(theme.GetFontColor());

        _StateEnabled.SetColor(theme.GetWindow());
        _StateEnabled.GetColor().A = theme.GetAlpha();
        _StateEnabled.SetHighlightColor(theme.GetWindowLight());
        _StateEnabled.GetHighlightColor().A = theme.GetAlpha();
        _StateEnabled.SetShadowColor(theme.GetWindowDark());
        _StateEnabled.GetShadowColor().A = theme.GetAlpha();

        SetShadowsColor(theme.GetShadows());
        EnableShadows(theme.GetShadows().A > 0.0f);
        SetBumpColor(theme.GetBump());
        EnableBump(theme.GetBump().A > 0.0f);
    }

    //--------------------------------------------------------------------------------------------//

    void SkinToolTip::Render(Window& window, const SkinContext& paint_context)
    {
        widget::ToolTip* bullet = (widget::ToolTip *) &window;
        graphics::FrameScissor scissor;

        _SetState(_StateEnabled);

        scissor.SetRectangle(paint_context.GetDesktopClipRect());
        scissor.Bind();

        graphics::Renderer::Get().SetDefaultRenderState();
        graphics::Renderer::Get().EnableDepthTest(false);
        graphics::Renderer::Get().SetFaceCullingMode(graphics::RENDER_STATE_FACE_CULLING_None);

        graphics::Renderer::Get().SetColor(_StateEnabled.GetColor());

        paint_context.Render().Rectangle(
            paint_context.GetDesktopWindowRect().GetMinimum(),
            paint_context.GetDesktopWindowRect().GetMaximum());

        graphics::Renderer::Get().SetColor(_StateEnabled.GetShadowColor());

        paint_context.Render().Line(
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMaximum().X,
            paint_context.GetDesktopWindowRect().GetMinimum().Y),
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMaximum().X,
            paint_context.GetDesktopWindowRect().GetMaximum().Y));

        paint_context.Render().Line(
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X,
            paint_context.GetDesktopWindowRect().GetMaximum().Y),
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMaximum().X,
            paint_context.GetDesktopWindowRect().GetMaximum().Y));

        graphics::Renderer::Get().SetColor(_StateEnabled.GetHighlightColor());

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

        basic::Vector2i text_position;

        text_position.X=paint_context.GetDesktopWindowRect().GetMinimum().X + bullet->GetBorders().X;
        text_position.Y=paint_context.GetDesktopWindowRect().GetMinimum().Y
            + paint_context.GetDesktopWindowRect().Size.Y / 2 + GetFont().GetHeight() / 2;

        GetFont().Print(bullet->GetHelpText(), text_position);
    }

}
}
//------------------------------------------------------------------------------------------------//
