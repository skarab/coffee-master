#include "wide/ui/skin/widget/ui_skin_window.h"
#include "wide/ui/window/ui_window_manager.h"
#include "system/graphics/geometric/graphics_geometric_renderer.h"
#include "system/graphics/device/graphics_device.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//
    
    COFFEE_BeginType(ui::SkinWindow);
        COFFEE_Ancestor(ui::SkinWidget);
        COFFEE_Attribute(ui::SkinWidgetState, _WindowArea, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(ui::SkinWidgetState, _WindowClientRaised, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(ui::SkinWidgetState, _WindowClientSunken, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SkinWindow::SkinWindow() :
        SkinWidget("Window", Window::GetClassMetaType())
    {
    }

    //--------------------------------------------------------------------------------------------//

    SkinWindow::~SkinWindow()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void SkinWindow::ApplyTheme(SkinTheme& theme)
    {
        SkinWidget::ApplyTheme(theme);

        SetBorderSize(basic::Vector2i(0, 0));

        _WindowArea.SetColor(theme.GetWindow());
        _WindowArea.GetColor().A = theme.GetAlpha();
        _WindowArea.SetHighlightColor(theme.GetWindowLight());
        _WindowArea.GetHighlightColor().A = theme.GetAlpha();
        _WindowArea.SetShadowColor(theme.GetWindowDark());
        _WindowArea.GetShadowColor().A = theme.GetAlpha();

        _WindowClientRaised.SetColor(theme.GetWindowRaised());
        _WindowClientRaised.GetColor().A = theme.GetAlpha();
        _WindowClientRaised.SetHighlightColor(theme.GetWindowRaised()
            + (theme.GetWindowLight() - theme.GetWindow()));
        _WindowClientRaised.GetHighlightColor().A = theme.GetAlpha();
        _WindowClientRaised.SetShadowColor(theme.GetWindowRaised()
            - (theme.GetWindow() - theme.GetWindowDark()));
        _WindowClientRaised.GetShadowColor().A = theme.GetAlpha();

        _WindowClientSunken.SetColor(theme.GetWindowSunken());
        _WindowClientSunken.GetColor().A = theme.GetAlpha();
        _WindowClientSunken.SetHighlightColor(theme.GetWindowSunken()
            + (theme.GetWindowLight() - theme.GetWindow()));
        _WindowClientSunken.GetHighlightColor().A = theme.GetAlpha();
        _WindowClientSunken.SetShadowColor(theme.GetWindowSunken()
            - (theme.GetWindow() - theme.GetWindowDark()));
        _WindowClientSunken.GetShadowColor().A = theme.GetAlpha();
    }

    //--------------------------------------------------------------------------------------------//

    void SkinWindow::Render(Window& window, const SkinContext& paint_context)
    {
        graphics::FrameScissor scissor;

        if (!window.HasParent() || !paint_context.GetSkin().IsAvailable())
            return;

        if (WindowManager::Get().GetModalWindow()==&window)
        {
            scissor.UnBind();
            graphics::Renderer::Get().SetColor(basic::Color(0.0f, 0.0f, 0.0f, 0.5f));
            graphics::GeometricRenderer::RenderFullScreenQuad();
        }

        if (window.HasStyle(WINDOW_STYLE_DrawFrame))
        {
            _RenderShadows(window, paint_context);
        }

        scissor.SetRectangle(paint_context.GetDesktopClipRect());
        scissor.Bind();

        if (window.HasStyle(WINDOW_STYLE_DrawFrame))
        {
            graphics::Renderer::Get().SetColor(_WindowArea.GetColor());

            // WindowArea

            paint_context.Render().Rectangle(
                paint_context.GetDesktopWindowRect().GetMinimum(),
                paint_context.GetDesktopWindowRect().GetMaximum());

            // WindowBorders

            graphics::Renderer::Get().SetColor(_WindowArea.GetShadowColor());

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

            graphics::Renderer::Get().SetColor(_WindowArea.GetHighlightColor());

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

            // ClientArea

            if (!window.GetClientRect().IsEmpty())
            {
                if (window.HasStyle(WINDOW_STYLE_DrawClientRaised)
                    || window.HasStyle(WINDOW_STYLE_DrawClientSunken))
                {
                    if (window.HasStyle(WINDOW_STYLE_DrawClientRaised))
                    {
                        graphics::Renderer::Get().SetColor(_WindowClientRaised.GetColor());
                    }
                    else if (window.HasStyle(WINDOW_STYLE_DrawClientSunken))
                    {
                        graphics::Renderer::Get().SetColor(_WindowClientSunken.GetColor());
                    }

                    paint_context.Render().Rectangle(
                        paint_context.GetDesktopWindowRect().GetMinimum()
                        + window.GetClientRect().Position,
                        paint_context.GetDesktopWindowRect().GetMinimum()
                        + window.GetClientRect().Position + window.GetClientRect().Size);

                    // ClientBorders

                    if (window.HasStyle(WINDOW_STYLE_DrawClientRaised))
                    {
                        graphics::Renderer::Get().SetColor(_WindowClientRaised.GetShadowColor());
                    }
                    else if (window.HasStyle(WINDOW_STYLE_DrawClientSunken))
                    {
                        graphics::Renderer::Get().SetColor(_WindowClientSunken.GetHighlightColor());
                    }

                    paint_context.Render().Line(
                        basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X
                        + window.GetClientRect().Position.X + window.GetClientRect().Size.X + 1,
                        paint_context.GetDesktopWindowRect().GetMinimum().Y + window.GetClientRect().Position.Y - 1),
                        basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X
                        + window.GetClientRect().Position.X + window.GetClientRect().Size.X + 1,
                        paint_context.GetDesktopWindowRect().GetMinimum().Y + window.GetClientRect().Position.Y
                        + window.GetClientRect().Size.Y + 1));

                    paint_context.Render().Line(
                        basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X
                        + window.GetClientRect().Position.X - 1,
                        paint_context.GetDesktopWindowRect().GetMinimum().Y
                        + window.GetClientRect().Position.Y + window.GetClientRect().Size.Y + 1),
                        basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X
                        + window.GetClientRect().Position.X + window.GetClientRect().Size.X + 1,
                        paint_context.GetDesktopWindowRect().GetMinimum().Y
                        + window.GetClientRect().Position.Y + window.GetClientRect().Size.Y + 1));

                    if (window.HasStyle(WINDOW_STYLE_DrawClientRaised))
                    {
                        graphics::Renderer::Get().SetColor(_WindowClientRaised.GetHighlightColor());
                    }
                    else if (window.HasStyle(WINDOW_STYLE_DrawClientSunken))
                    {
                        graphics::Renderer::Get().SetColor(_WindowClientSunken.GetShadowColor());
                    }

                    paint_context.Render().Line(
                        basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X
                        + window.GetClientRect().Position.X - 1,
                        paint_context.GetDesktopWindowRect().GetMinimum().Y
                        + window.GetClientRect().Position.Y - 1),
                        basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X
                        + window.GetClientRect().Position.X - 1,
                        paint_context.GetDesktopWindowRect().GetMinimum().Y
                        + window.GetClientRect().Position.Y + window.GetClientRect().Size.Y + 1));

                    paint_context.Render().Line(
                        basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X
                        + window.GetClientRect().Position.X - 1,
                        paint_context.GetDesktopWindowRect().GetMinimum().Y
                        + window.GetClientRect().Position.Y - 1),
                        basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X
                        + window.GetClientRect().Position.X + window.GetClientRect().Size.X + 1,
                        paint_context.GetDesktopWindowRect().GetMinimum().Y
                        + window.GetClientRect().Position.Y - 1));
                }
            }
        }

        if (window.HasStyle(WINDOW_STYLE_DrawFrame))
        {
            _RenderBump(window, paint_context);
        }
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void SkinWindow::_RenderShadows(Window& window, const SkinContext& paint_context)
    {
        if (!((SkinWidget&) window.GetSkinWidget()).HasShadowsEnabled())
            return;

        graphics::FrameScissor::Disable();

        graphics::Renderer::Get().SetDefaultRenderState();
        graphics::Renderer::Get().EnableDepthTest(false);
        graphics::Renderer::Get().SetFaceCullingMode(graphics::RENDER_STATE_FACE_CULLING_None);
        int32 size = 5;
        basic::Color shadow_on(((SkinWidget&) window.GetSkinWidget()).GetShadowsColor());
        basic::Color shadow_off(shadow_on);
        
        shadow_off.A = 0.0f;

        graphics::Renderer::Get().SetColor(shadow_on);

        paint_context.Render().Rectangle(
            paint_context.GetDesktopWindowRect().GetMinimum() + size * 2,
            paint_context.GetDesktopWindowRect().GetMaximum() + size);

        graphics::GeometricRenderer::RenderViewportColoredRectangle(
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X + size,
            paint_context.GetDesktopWindowRect().GetMinimum().Y + size * 2),
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X + size * 2,
            paint_context.GetDesktopWindowRect().GetMaximum().Y + size),
            shadow_off, shadow_on, shadow_on, shadow_off);

        graphics::GeometricRenderer::RenderViewportColoredRectangle(
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMaximum().X + size,
            paint_context.GetDesktopWindowRect().GetMinimum().Y + size * 2),
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMaximum().X + size * 2,
            paint_context.GetDesktopWindowRect().GetMaximum().Y + size),
            shadow_on, shadow_off, shadow_off, shadow_on);

        graphics::GeometricRenderer::RenderViewportColoredRectangle(
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X + size * 2,
            paint_context.GetDesktopWindowRect().GetMinimum().Y + size),
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMaximum().X + size,
            paint_context.GetDesktopWindowRect().GetMinimum().Y + size * 2),
            shadow_off, shadow_off, shadow_on, shadow_on);

        graphics::GeometricRenderer::RenderViewportColoredRectangle(
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X + size * 2,
            paint_context.GetDesktopWindowRect().GetMaximum().Y + size),
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMaximum().X + size,
            paint_context.GetDesktopWindowRect().GetMaximum().Y + size * 2),
            shadow_on, shadow_on, shadow_off, shadow_off);

        graphics::GeometricRenderer::RenderViewportColoredRectangle(
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X + size,
            paint_context.GetDesktopWindowRect().GetMinimum().Y + size),
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X + size * 2,
            paint_context.GetDesktopWindowRect().GetMinimum().Y + size * 2),
            shadow_off, shadow_off, shadow_on, shadow_off);

        graphics::GeometricRenderer::RenderViewportColoredRectangle(
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMaximum().X + size,
            paint_context.GetDesktopWindowRect().GetMinimum().Y + size),
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMaximum().X + size * 2,
            paint_context.GetDesktopWindowRect().GetMinimum().Y + size * 2),
            shadow_off, shadow_off, shadow_off, shadow_on);

        graphics::GeometricRenderer::RenderViewportColoredRectangle(
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMaximum().X + size,
            paint_context.GetDesktopWindowRect().GetMaximum().Y + size),
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMaximum().X + size * 2,
            paint_context.GetDesktopWindowRect().GetMaximum().Y + size * 2),
            shadow_on, shadow_off, shadow_off, shadow_off);

        graphics::GeometricRenderer::RenderViewportColoredRectangle(
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X + size,
            paint_context.GetDesktopWindowRect().GetMaximum().Y + size),
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X + size * 2,
            paint_context.GetDesktopWindowRect().GetMaximum().Y + size * 2),
            shadow_off, shadow_on, shadow_off, shadow_off);
    }

    //--------------------------------------------------------------------------------------------//

    void SkinWindow::_RenderBump(Window& window, const SkinContext& paint_context)
    {
        if (!((SkinWidget&) window.GetSkinWidget()).HasBumpEnabled())
            return;

        graphics::Renderer::Get().SetDefaultRenderState();
        graphics::Renderer::Get().EnableDepthTest(false);
        graphics::Renderer::Get().SetFaceCullingMode(graphics::RENDER_STATE_FACE_CULLING_None);
        int32 size = 5;

        basic::Color bump_on(((SkinWidget&) window.GetSkinWidget()).GetBumpColor());
        basic::Color bump_off(bump_on);

        bump_off.A = 0.0f;

        graphics::Renderer::Get().SetColor(bump_on);

        paint_context.Render().Rectangle(
            paint_context.GetDesktopWindowRect().GetMinimum() + size,
            paint_context.GetDesktopWindowRect().GetMaximum() - size
           );

        graphics::GeometricRenderer::RenderViewportColoredRectangle(
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X,
            paint_context.GetDesktopWindowRect().GetMinimum().Y + size),
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X + size,
            paint_context.GetDesktopWindowRect().GetMaximum().Y - size),
            bump_off, bump_on, bump_on, bump_off);

        graphics::GeometricRenderer::RenderViewportColoredRectangle(
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMaximum().X - size,
            paint_context.GetDesktopWindowRect().GetMinimum().Y + size),
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMaximum().X,
            paint_context.GetDesktopWindowRect().GetMaximum().Y - size),
            bump_on, bump_off, bump_off, bump_on);

        graphics::GeometricRenderer::RenderViewportColoredRectangle(
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X + size,
            paint_context.GetDesktopWindowRect().GetMinimum().Y),
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMaximum().X - size,
            paint_context.GetDesktopWindowRect().GetMinimum().Y + size),
            bump_off, bump_off, bump_on, bump_on);

        graphics::GeometricRenderer::RenderViewportColoredRectangle(
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X + size,
            paint_context.GetDesktopWindowRect().GetMaximum().Y - size),
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMaximum().X - size,
            paint_context.GetDesktopWindowRect().GetMaximum().Y),
            bump_on, bump_on, bump_off, bump_off);

        graphics::GeometricRenderer::RenderViewportColoredRectangle(
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X,
            paint_context.GetDesktopWindowRect().GetMinimum().Y),
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X + size,
            paint_context.GetDesktopWindowRect().GetMinimum().Y + size),
            bump_off, bump_off, bump_on, bump_off);

        graphics::GeometricRenderer::RenderViewportColoredRectangle(
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMaximum().X - size,
            paint_context.GetDesktopWindowRect().GetMinimum().Y),
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMaximum().X,
            paint_context.GetDesktopWindowRect().GetMinimum().Y + size),
            bump_off, bump_off, bump_off, bump_on);

        graphics::GeometricRenderer::RenderViewportColoredRectangle(
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMaximum().X - size,
            paint_context.GetDesktopWindowRect().GetMaximum().Y - size),
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMaximum().X,
            paint_context.GetDesktopWindowRect().GetMaximum().Y),
            bump_on, bump_off, bump_off, bump_off);

        graphics::GeometricRenderer::RenderViewportColoredRectangle(
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X,
            paint_context.GetDesktopWindowRect().GetMaximum().Y - size),
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X + size,
            paint_context.GetDesktopWindowRect().GetMaximum().Y),
            bump_off, bump_on, bump_off, bump_off);
    }

}
}
