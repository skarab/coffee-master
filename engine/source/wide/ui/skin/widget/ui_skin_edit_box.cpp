#include "wide/ui/skin/widget/ui_skin_edit_box.h"
#include "system/graphics/renderer/graphics_renderer.h"
#include "system/graphics/device/graphics_device.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::SkinEditBox);
        COFFEE_Ancestor(ui::SkinWidget);
        COFFEE_Attribute(ui::SkinWidgetState, _StateDisabled, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(ui::SkinWidgetState, _StateEnabled, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(ui::SkinWidgetState, _StateCursorOver, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(ui::SkinWidgetState, _StateSelection, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();
    
namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SkinEditBox::SkinEditBox() :
        SkinWidget("EditBox", widget::EditBox::GetClassMetaType())
    {
    }

    //--------------------------------------------------------------------------------------------//

    SkinEditBox::~SkinEditBox()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void SkinEditBox::ApplyTheme(SkinTheme& theme)
    {
        SetBorderSize(basic::Vector2i(2, 0));

        GetFont() = theme.GetEditZoneFont();

        _StateDisabled.SetColor((theme.GetEditZone() + theme.GetWindow()) / 2.0f);
        _StateDisabled.GetColor().A = theme.GetAlpha();
        _StateDisabled.SetHighlightColor(theme.GetWindowLight()
            + (theme.GetWindow() - theme.GetWindowLight()) / 2.0f);
        _StateDisabled.GetHighlightColor().A = theme.GetAlpha();
        _StateDisabled.SetShadowColor(theme.GetWindowDark()
            + (theme.GetWindow() - theme.GetWindowDark()) / 2.0f);
        _StateDisabled.GetShadowColor().A = theme.GetAlpha();
        _StateDisabled.SetFontColor(basic::Color(
            (theme.GetWindow().R*2.0f+theme.GetEditZoneFontColor().R)/3.0f,
            (theme.GetWindow().G*2.0f+theme.GetEditZoneFontColor().G)/3.0f,
            (theme.GetWindow().B*2.0f+theme.GetEditZoneFontColor().B)/3.0f,
            theme.GetEditZoneFont().GetColor().A*0.8f));
    
        _StateEnabled.SetColor(theme.GetEditZone());
        _StateEnabled.GetColor().A = theme.GetAlpha();
        _StateEnabled.SetHighlightColor(theme.GetWindowLight());
        _StateEnabled.GetHighlightColor().A = theme.GetAlpha();
        _StateEnabled.SetShadowColor(theme.GetWindowDark());
        _StateEnabled.GetShadowColor().A = theme.GetAlpha();
        _StateEnabled.SetFontColor(theme.GetActiveItems());

        _StateCursorOver.SetColor(theme.GetEditZone() + basic::Color(0.1f, 0.1f, 0.1f, 1.0f));
        _StateCursorOver.GetColor().A = theme.GetAlpha();
        _StateCursorOver.SetHighlightColor(theme.GetWindowLight());
        _StateCursorOver.GetHighlightColor().A = theme.GetAlpha();
        _StateCursorOver.SetShadowColor(theme.GetWindowDark());
        _StateCursorOver.GetShadowColor().A = theme.GetAlpha();
        _StateCursorOver.SetFontColor(theme.GetEditZoneFontColor()
            + basic::Color(0.1f, 0.1f, 0.1f, 1.0f));

        _StateSelection.SetColor(theme.GetEditZone());
        _StateSelection.GetColor().A = theme.GetAlpha();
        _StateSelection.SetHighlightColor(theme.GetWindowLight());
        _StateSelection.GetHighlightColor().A = theme.GetAlpha();
        _StateSelection.SetShadowColor(theme.GetWindowDark());
        _StateSelection.GetShadowColor().A = theme.GetAlpha();
        _StateSelection.SetFontColor(theme.GetEditZoneFontColor());
    }

    //--------------------------------------------------------------------------------------------//

    void SkinEditBox::Render(Window& window, const SkinContext& paint_context)
    {
        widget::EditBox* edit_box = (widget::EditBox*) &window;
        
        if(!edit_box->IsEnabled())
        {
            _SetState(_StateDisabled);
        }
        else if(edit_box->HasCursorOver())
        {
            _SetState(_StateCursorOver);
        }
        else
        {
            _SetState(_StateEnabled);
        }

        graphics::Renderer::Get().SetColor(_GetState().GetColor());
        basic::Vector2i minimum_position(paint_context.GetDesktopWindowRect().GetMinimum());
        basic::Vector2i maximum_position(paint_context.GetDesktopWindowRect().GetMaximum());

        if(edit_box->HasExtendedStyle((uint32)widget::EDIT_BOX_STYLE_NoBorders))
        {
            maximum_position += 1;
        }

        if (!edit_box->HasExtendedStyle((uint32)widget::EDIT_BOX_STYLE_NoFrame)
            || edit_box->HasCursorOver() || edit_box->HasFocus())
        {
            paint_context.Render().Rectangle(
                minimum_position,
                maximum_position);
        }

        // Borders

        if(!edit_box->HasExtendedStyle((uint32)widget::EDIT_BOX_STYLE_NoBorders))
        {
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
                basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X,
                paint_context.GetDesktopWindowRect().GetMaximum().Y));

            paint_context.Render().Line(
                basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X,
                paint_context.GetDesktopWindowRect().GetMinimum().Y),
                basic::Vector2i(paint_context.GetDesktopWindowRect().GetMaximum().X,
                paint_context.GetDesktopWindowRect().GetMinimum().Y));
        }

        graphics::FrameScissor scissor;
        basic::Rectangle rect;

        rect.Position = paint_context.GetDesktopWindowRect().GetMinimum() + edit_box->GetBorders();
        rect.Size = paint_context.GetDesktopWindowRect().Size - edit_box->GetBorders() * 2;
        rect -= paint_context.GetDesktopClipRect();

        scissor.SetRectangle(rect);
        scissor.Bind();

        // text

        basic::String visible_text(edit_box->GetVisibleText());

        if(edit_box->GetText().GetLength() > 0)
        {
            basic::Vector2i text_position;

            text_position.X = paint_context.GetDesktopWindowRect().GetMinimum().X
                + edit_box->GetBorders().X;
            text_position.Y = paint_context.GetDesktopWindowRect().GetMinimum().Y
                + paint_context.GetDesktopWindowRect().Size.Y / 2 + GetFont().GetHeight() / 2 + 2;

            GetFont().Print(visible_text, text_position);
        }

        // selection

        if(edit_box->HasFocus())
        {
            uint32 position_x(0);
            uint32 size_x(0);
            uint32 char_index;
            uint32 cursor_start;
            uint32 cursor_stop;

            cursor_start = Minimum(edit_box->GetCursorPosition(),
                edit_box->GetCursorPosition() + edit_box->GetCursorSize());
            cursor_stop = Maximum(edit_box->GetCursorPosition(),
                edit_box->GetCursorPosition() + edit_box->GetCursorSize());

            if(edit_box->GetCursorSize() == 0 && input::Keyboard::Get().IsReplacing())
                ++ cursor_stop;

            if(GetFont().IsAvailable())
            {
                graphics::Font* font2d = (graphics::Font*) &GetFont().GetResource();

                for(char_index=edit_box->GetVisibilityStart() ; char_index<cursor_start ; ++char_index)
                {
                    unsigned char c = edit_box->GetText().GetBuffer()[ char_index ] - font2d->GetFirstCharacterCode();

                    if(c <= font2d->GetLastCharacterCode() - font2d->GetFirstCharacterCode())
                        position_x += font2d->GetGlyphArray()[c]->GetSize().X;
                }

                for(char_index=cursor_start ; char_index<cursor_stop ; ++char_index)
                {
                    unsigned char c = edit_box->GetText().GetBuffer()[char_index] - font2d->GetFirstCharacterCode();

                    if(c <= font2d->GetLastCharacterCode() - font2d->GetFirstCharacterCode())
                        size_x += font2d->GetGlyphArray()[c]->GetSize().X;
                }

                graphics::Renderer::Get().SetColor(_StateSelection.GetColor());

                if(size_x > 0)
                {
                    paint_context.Render().Rectangle(
                        basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X
                        + edit_box->GetBorders().X + position_x + 1,
                        paint_context.GetDesktopWindowRect().GetMinimum().Y + edit_box->GetBorders().Y),
                        basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X
                        + edit_box->GetBorders().X + position_x + size_x,
                        paint_context.GetDesktopWindowRect().GetMaximum().Y - edit_box->GetBorders().Y));
                }

                if(edit_box->HasToRenderCursor())
                {
                    if(edit_box->GetCursorSize() > 0)
                    {
                        paint_context.Render().Rectangle(
                            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X
                            + edit_box->GetBorders().X + position_x + size_x,
                            paint_context.GetDesktopWindowRect().GetMinimum().Y + edit_box->GetBorders().Y),
                            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X
                            + edit_box->GetBorders().X + position_x + size_x + 1,
                            paint_context.GetDesktopWindowRect().GetMaximum().Y - edit_box->GetBorders().Y));
                    }
                    else
                    {
                        paint_context.Render().Rectangle(
                            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X
                            + edit_box->GetBorders().X + position_x,
                            paint_context.GetDesktopWindowRect().GetMinimum().Y + edit_box->GetBorders().Y),
                            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X
                            + edit_box->GetBorders().X + position_x + 1,
                            paint_context.GetDesktopWindowRect().GetMaximum().Y - edit_box->GetBorders().Y));
                    }
                }
            }
        }
    }

}
}
