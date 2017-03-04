#include "wide/ui/skin/widget/ui_skin_button.h"
#include "system/graphics/renderer/graphics_renderer.h"
#include "system/graphics/device/graphics_device.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::SkinButton);
        COFFEE_Ancestor(ui::SkinWidget);
        COFFEE_Attribute(ui::SkinWidgetState, _StateDisabled, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(ui::SkinWidgetState, _StatePressed, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(ui::SkinWidgetState, _StateReleased, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(ui::SkinWidgetState, _StateCursorOver, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(ui::SkinWidgetState, _StatePressedImage, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(ui::SkinWidgetState, _StateCursorOverImage, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();
    
namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SkinButton::SkinButton() :
        SkinWidget("Button", widget::Button::GetClassMetaType())
    {
    }

    //--------------------------------------------------------------------------------------------//

    SkinButton::~SkinButton()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void SkinButton::ApplyTheme(SkinTheme& theme)
    {
        SkinWidget::ApplyTheme(theme);

        SetBorderSize(basic::Vector2i(1, 1));

        _StateDisabled.SetColor(theme.GetWindow());
        _StateDisabled.GetColor().A = theme.GetAlpha();
        _StateDisabled.SetHighlightColor(theme.GetWindowLight()
            + (theme.GetWindow() - theme.GetWindowLight()) / 2.0f);
        _StateDisabled.GetHighlightColor().A = theme.GetAlpha();
        _StateDisabled.SetShadowColor(theme.GetWindowDark()
            + (theme.GetWindow() - theme.GetWindowDark()) / 2.0f);
        _StateDisabled.GetShadowColor().A = theme.GetAlpha();
        _StateDisabled.SetFontColor(basic::Color(
            (theme.GetWindow().R*2.0f+theme.GetFontColor().R)/3.0f,
            (theme.GetWindow().G*2.0f+theme.GetFontColor().G)/3.0f,
            (theme.GetWindow().B*2.0f+theme.GetFontColor().B)/3.0f,
            theme.GetFontColor().A*0.8f));

        _StateReleased.SetColor(theme.GetWindow());
        _StateReleased.GetColor().A = theme.GetAlpha();
        _StateReleased.SetHighlightColor(theme.GetWindowLight());
        _StateReleased.GetHighlightColor().A = theme.GetAlpha();
        _StateReleased.SetShadowColor(theme.GetWindowDark());
        _StateReleased.GetShadowColor().A = theme.GetAlpha();
        _StateReleased.SetFontColor(theme.GetFontColor());
        
        _StatePressed.SetColor(theme.GetActiveItems());
        _StatePressed.GetColor().A = theme.GetAlpha();
        _StatePressed.SetHighlightColor(theme.GetWindowLight());
        _StatePressed.GetHighlightColor().A = theme.GetAlpha();
        _StatePressed.SetShadowColor(theme.GetWindowDark());
        _StatePressed.GetShadowColor().A = theme.GetAlpha();
        _StatePressed.SetFontColor(theme.GetFontColor());
        
        _StateCursorOver.SetColor((theme.GetWindow() + theme.GetActiveItems())/2.0f);
        _StateCursorOver.GetColor().A = theme.GetAlpha();
        _StateCursorOver.SetHighlightColor(theme.GetWindowLight());
        _StateCursorOver.GetHighlightColor().A = theme.GetAlpha();
        _StateCursorOver.SetShadowColor(theme.GetWindowDark());
        _StateCursorOver.GetShadowColor().A = theme.GetAlpha();
        _StateCursorOver.SetFontColor(theme.GetFontColor()
            + basic::Color(0.1f, 0.1f, 0.1f, 1.0f));
    
        _StatePressedImage.SetColor(theme.GetActiveItems());
        _StatePressedImage.GetColor().A = 0.20f;
        _StatePressedImage.SetHighlightColor(theme.GetWindowLight());
        _StatePressedImage.GetHighlightColor().A = 0.20f;
        _StatePressedImage.SetShadowColor(theme.GetWindowDark());
        _StatePressedImage.GetShadowColor().A = 0.20f;
        _StatePressedImage.SetFontColor(theme.GetFontColor());
        
        _StateCursorOverImage.SetColor((theme.GetWindow() + theme.GetActiveItems())/2.0f);
        _StateCursorOverImage.GetColor().A = 0.20f;
        _StateCursorOverImage.SetHighlightColor(theme.GetWindowLight());
        _StatePressedImage.GetHighlightColor().A = 0.20f;
        _StateCursorOverImage.SetShadowColor(theme.GetWindowDark());
        _StatePressedImage.GetShadowColor().A = 0.20f;
        _StateCursorOverImage.SetFontColor(theme.GetFontColor()
            + basic::Color(0.1f, 0.1f, 0.1f, 1.0f));
    
        SetShadowsColor(theme.GetShadows());
        EnableShadows(theme.GetShadows().A > 0.0f);
        SetBumpColor(theme.GetBump());
        EnableBump(theme.GetBump().A > 0.0f);
    }

    //--------------------------------------------------------------------------------------------//

    void SkinButton::Render(Window& window, const SkinContext& paint_context)
    {
        widget::Button* button = (widget::Button*) &window;
        SkinWidgetState state;

        if(button->HasToOverwriteColor())
        {
            basic::Color color;
            basic::Color highlight_color;
            basic::Color shadow_color;
            basic::Color font_color;
            real alpha;

            real sum = button->GetColor().R + button->GetColor().G + button->GetColor().B;

            if(sum / 3.0f > 0.5f)
            {
                font_color.Set(0.0f, 0.0f, 0.0f, 1.0f);
            }
            else
            {
                font_color.Set(1.0f, 1.0f, 1.0f, 1.0f);
            }

            alpha = button->GetColor().A / 2.0f + 0.5f;
            color.Set(button->GetColor().R, button->GetColor().G, button->GetColor().B, alpha);
            highlight_color.Set(button->GetColor().R * 1.5f, button->GetColor().G * 1.5f, button->GetColor().B * 1.5f, alpha);
            shadow_color.Set(button->GetColor().R / 1.5f, button->GetColor().G / 1.5f, button->GetColor().B / 1.5f, alpha);

            state.SetColor(color);
            state.SetFontColor(font_color);
            state.SetHighlightColor(highlight_color);
            state.SetShadowColor(shadow_color);
            _SetState(state);
        }
        else
        {
            if(button->HasExtendedStyle(widget::BUTTON_STYLE_HideFrame))
            {
                if(button->HasImage() && !button->IsEnabled())
                    return;

                if(button->GetState()==widget::BUTTON_STATE_On)
                {
                    _SetState(_StatePressedImage);
                }
                else if(button->HasCursorOver())
                {
                    _SetState(_StateCursorOverImage);
                }
                else if (button->HasImage())
                {                    
                    return;
                }
                else if(!button->IsEnabled())
                {
                    _SetState(_StateDisabled);
                }
                else
                {
                    _SetState(_StateReleased);
                }
            }
            else
            {
                if(!button->IsEnabled())
                {
                    _SetState(_StateDisabled);
                }
                else if(button->HasCursorOver())
                {
                    _SetState(_StateCursorOver);
                }
                else if(button->GetState() == ui::widget::BUTTON_STATE_On)
                {
                    _SetState(_StatePressed);
                }
                else
                {
                    _SetState(_StateReleased);
                }
            }
        }

        if(!button->HasExtendedStyle(widget::BUTTON_STYLE_HideFrame) || (button->HasImage()
            || button->HasCursorOver() || button->GetState()==widget::BUTTON_STATE_On))
        {
            graphics::Renderer::Get().SetColor(_GetState().GetColor());

            paint_context.Render().Rectangle(
                paint_context.GetDesktopWindowRect().GetMinimum(),
                paint_context.GetDesktopWindowRect().GetMaximum());

            // Borders

            if(button->GetState() == ui::widget::BUTTON_STATE_On)
            {
                graphics::Renderer::Get().SetColor(_GetState().GetHighlightColor());
            }
            else
            {
                graphics::Renderer::Get().SetColor(_GetState().GetShadowColor());
            }

            paint_context.Render().Line(
                basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X
                + button->GetRect().Size.X, paint_context.GetDesktopWindowRect().GetMinimum().Y),
                basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X
                + button->GetRect().Size.X, paint_context.GetDesktopWindowRect().GetMinimum().Y
                + button->GetRect().Size.Y));

            paint_context.Render().Line(
                basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X,
                paint_context.GetDesktopWindowRect().GetMinimum().Y + button->GetRect().Size.Y),
                basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X
                + button->GetRect().Size.X, paint_context.GetDesktopWindowRect().GetMinimum().Y
                + button->GetRect().Size.Y));

            if(button->GetState()==widget::BUTTON_STATE_On)
            {
                graphics::Renderer::Get().SetColor(_GetState().GetShadowColor());
            }
            else
            {
                graphics::Renderer::Get().SetColor(_GetState().GetHighlightColor());
            }

            paint_context.Render().Line(
                basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X,
                paint_context.GetDesktopWindowRect().GetMinimum().Y),
                basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X, 
                paint_context.GetDesktopWindowRect().GetMinimum().Y + button->GetRect().Size.Y));

            paint_context.Render().Line(
                basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X,
                paint_context.GetDesktopWindowRect().GetMinimum().Y),
                basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X
                + button->GetRect().Size.X, paint_context.GetDesktopWindowRect().GetMinimum().Y));
        }

        if (!button->HasImage() && button->GetText().GetLength() > 0)
        {
            graphics::FrameScissor scissor;
            basic::Rectangle rect;

            rect.Position = paint_context.GetDesktopWindowRect().GetMinimum()+1;
            rect.Size = paint_context.GetDesktopWindowRect().Size-1;
            rect -= paint_context.GetDesktopClipRect();

            scissor.SetRectangle(rect);
            scissor.Bind();

            basic::Vector2i text_position;

            text_position.X=paint_context.GetDesktopWindowRect().GetMinimum().X
                + button->GetBorders().X;
            text_position.Y=paint_context.GetDesktopWindowRect().GetMinimum().Y
                + paint_context.GetDesktopWindowRect().Size.Y / 2 + GetFont().GetHeight() / 2;

            if(button->GetState()==widget::BUTTON_STATE_On)
                text_position += 1;

            GetFont().Print(basic::String("  ") + button->GetText(), text_position);
        }
    }

}
}
