//------------------------------------------------------------------------------------------------//
/// @file wide/ui/skin/widget/ui_skin_view_control.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "wide/ui/skin/widget/ui_skin_view_control.h"
#include "system/graphics/renderer/graphics_renderer.h"
#include "system/graphics/device/graphics_device.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::SkinViewControl);
        COFFEE_Ancestor(ui::SkinWidget);
        COFFEE_Attribute(ui::SkinWidgetState, _StateDisabled, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(ui::SkinWidgetState, _StateEnabled, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SkinViewControl::SkinViewControl() :
        SkinWidget("ViewControl", widget::ViewControl::GetClassMetaType())
    {
    }

    //--------------------------------------------------------------------------------------------//

    SkinViewControl::~SkinViewControl()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void SkinViewControl::ApplyTheme(SkinTheme& theme)
    {
        SkinWidget::ApplyTheme(theme);

        SetBorderSize(basic::Vector2i(0, 0));

        _StateDisabled.SetColor(theme.GetWindowSunken());
        _StateDisabled.GetColor().A = theme.GetAlpha() * 2.0f;
        _StateDisabled.SetHighlightColor(theme.GetWindowLight()
            + (theme.GetWindowSunken() - theme.GetWindowLight()) / 2.0f);
        _StateDisabled.GetHighlightColor().A = theme.GetAlpha() * 2.0f;
        _StateDisabled.SetShadowColor(theme.GetWindowDark()
            + (theme.GetWindowSunken() - theme.GetWindowDark()) / 2.0f);
        _StateDisabled.GetShadowColor().A = theme.GetAlpha() * 2.0f;
        _StateDisabled.SetFontColor(theme.GetFontColor()
            + (theme.GetWindowSunken() - theme.GetFontColor()) / 2.0f);

        _StateEnabled.SetColor(theme.GetWindowSunken());
        _StateEnabled.GetColor().A = theme.GetAlpha() * 2.0f;
        _StateEnabled.SetHighlightColor(theme.GetWindowLight()
            + (theme.GetWindowSunken() - theme.GetWindowLight()) / 2.0f);
        _StateEnabled.GetHighlightColor().A = theme.GetAlpha() * 2.0f;
        _StateEnabled.SetShadowColor(theme.GetWindowDark()
            + (theme.GetWindowSunken() - theme.GetWindowDark()) / 2.0f);
        _StateEnabled.GetShadowColor().A = theme.GetAlpha() * 2.0f;
        _StateEnabled.SetFontColor(theme.GetFontColor()
            + (theme.GetWindowSunken() - theme.GetFontColor()) / 2.0f);
    }

    //--------------------------------------------------------------------------------------------//

    void SkinViewControl::Render(Window& window, const SkinContext& paint_context)
    {
        graphics::FrameScissor scissor;

        if(!window.IsEnabled())
        {
            _SetState(_StateDisabled);
        }
        else
        {
            _SetState(_StateEnabled);
        }

        scissor.SetRectangle(paint_context.GetDesktopClipRect());
        scissor.Bind();

        graphics::Renderer::Get().SetDefaultRenderState();
        graphics::Renderer::Get().EnableDepthTest(false);
        graphics::Renderer::Get().SetFaceCullingMode(graphics::RENDER_STATE_FACE_CULLING_None);

        graphics::Renderer::Get().SetColor(_GetState().GetColor());

        paint_context.Render().Rectangle(
            paint_context.GetDesktopWindowRect().GetMinimum(),
            paint_context.GetDesktopWindowRect().GetMaximum());

        graphics::Renderer::Get().SetColor(_GetState().GetHighlightColor());

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

        graphics::Renderer::Get().SetColor(_GetState().GetShadowColor());

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

}
}
//------------------------------------------------------------------------------------------------//
