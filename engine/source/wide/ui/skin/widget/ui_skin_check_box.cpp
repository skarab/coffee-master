//------------------------------------------------------------------------------------------------//
/// @file wide/ui/skin/widget/ui_skin_check_box.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "wide/ui/skin/widget/ui_skin_check_box.h"
#include "system/graphics/renderer/graphics_renderer.h"
#include "system/graphics/device/graphics_device.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::SkinCheckBox);
        COFFEE_Ancestor(ui::SkinWidget)
        COFFEE_Attribute(ui::SkinWidgetState, _StateDisabled, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(ui::SkinWidgetState, _StateEnabled, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(ui::SkinWidgetState, _StateChecked, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(ui::SkinWidgetState, _StateCursorOver, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();
    
namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SkinCheckBox::SkinCheckBox() :
        SkinWidget("CheckBox", widget::CheckBox::GetClassMetaType())
    {
    }

    //--------------------------------------------------------------------------------------------//

    SkinCheckBox::~SkinCheckBox()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void SkinCheckBox::ApplyTheme(SkinTheme& theme)
    {
        SkinWidget::ApplyTheme(theme);

        SetBorderSize(basic::Vector2i(0, 0));
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
        _StateEnabled.SetFontColor(theme.GetEditZoneFontColor());
        
        _StateCursorOver.SetColor(theme.GetEditZone() + basic::Color(0.1f, 0.1f, 0.1f, 1.0f));
        _StateCursorOver.GetColor().A = theme.GetAlpha();
        _StateCursorOver.SetHighlightColor(theme.GetWindowLight());
        _StateCursorOver.GetHighlightColor().A = theme.GetAlpha();
        _StateCursorOver.SetShadowColor(theme.GetWindowDark());
        _StateCursorOver.GetShadowColor().A = theme.GetAlpha();
        _StateCursorOver.SetFontColor(theme.GetActiveItems());
    
        _StateChecked.SetColor(theme.GetActiveItems());
        _StateChecked.SetHighlightColor(theme.GetWindowLight());
        _StateChecked.GetHighlightColor().A = theme.GetAlpha();
        _StateChecked.SetShadowColor(theme.GetWindowDark());
        _StateChecked.GetShadowColor().A = theme.GetAlpha();
        _StateChecked.SetFontColor(theme.GetEditZoneFontColor());
    }

    //--------------------------------------------------------------------------------------------//

    void SkinCheckBox::Render(Window& window, const SkinContext& paint_context)
    {
        widget::CheckBox* check_box = (widget::CheckBox*) &window;
        basic::Rectangle rect;

        if(!check_box->IsEnabled())
        {
            _SetState(_StateDisabled);
        }
        else if(check_box->HasCursorOver())
        {
            _SetState(_StateCursorOver);
        }
        else if(check_box->GetState()!=widget::CHECK_BOX_STATE_UnChecked)
        {
            _SetState(_StateChecked);
        }
        else
        {
            _SetState(_StateEnabled);
        }

        rect.Position = basic::Vector2i(
            paint_context.GetDesktopWindowRect().GetMinimum().X + 4,
            (paint_context.GetDesktopWindowRect().GetMinimum().Y
            + paint_context.GetDesktopWindowRect().GetMaximum().Y - 10) / 2);
        rect.Size = basic::Vector2i(10);

        if (!check_box->IsEnabled())
        {
            graphics::Renderer::Get().SetColor(_StateDisabled.GetColor());
        }
        else if(check_box->HasCursorOver())
        {
            graphics::Renderer::Get().SetColor(_StateCursorOver.GetColor());
        }
        else
        {
            graphics::Renderer::Get().SetColor(_StateEnabled.GetColor());
        }

        paint_context.Render().Rectangle(
            rect.GetMinimum(),
            rect.GetMaximum());

        // Borders

        if(!check_box->IsEnabled())
        {
            graphics::Renderer::Get().SetColor(_StateDisabled.GetHighlightColor());
        }
        else
        {
            graphics::Renderer::Get().SetColor(_StateEnabled.GetHighlightColor());
        }

        paint_context.Render().Line(
            basic::Vector2i(rect.GetMinimum().X + 10, rect.GetMinimum().Y),
            basic::Vector2i(rect.GetMinimum().X + 10, rect.GetMinimum().Y + 10));

        paint_context.Render().Line(
            basic::Vector2i(rect.GetMinimum().X, rect.GetMinimum().Y + 10),
            basic::Vector2i(rect.GetMinimum().X + 10, rect.GetMinimum().Y + 10));

        if(!check_box->IsEnabled())
        {
            graphics::Renderer::Get().SetColor(_StateDisabled.GetShadowColor());
        }
        else
        {
            graphics::Renderer::Get().SetColor(_StateEnabled.GetShadowColor());
        }

        paint_context.Render().Line(
            basic::Vector2i(rect.GetMinimum().X, rect.GetMinimum().Y),
            basic::Vector2i(rect.GetMinimum().X, rect.GetMinimum().Y + 10));

        paint_context.Render().Line(
            basic::Vector2i(rect.GetMinimum().X, rect.GetMinimum().Y),
            basic::Vector2i(rect.GetMinimum().X + 10, rect.GetMinimum().Y));

        // text

        if(check_box->GetText().GetLength() > 0)
        {
            basic::Vector2i text_position;

            text_position.X=paint_context.GetDesktopWindowRect().GetMinimum().X
                + check_box->GetBorders().X + 18;
            text_position.Y=paint_context.GetDesktopWindowRect().GetMinimum().Y
                + paint_context.GetDesktopWindowRect().Size.Y / 2 + GetFont().GetHeight() / 2 + 2;

            GetFont().Print(check_box->GetText(), text_position);
        }

        // state

        if(check_box->GetState()==widget::CHECK_BOX_STATE_UnChecked)
        {
            return;
        }
        else if(check_box->GetState()==widget::CHECK_BOX_STATE_Checked)
        {
            graphics::Renderer::Get().SetColor(_StateChecked.GetColor());
        }
        else if(check_box->GetState() == ui::widget::CHECK_BOX_STATE_AlternateChecked)
        {
            graphics::Renderer::Get().SetColor(_StateChecked.GetHighlightColor());
        }

        paint_context.Render().Line(
            basic::Vector2i(rect.GetMinimum().X + 2, rect.GetMaximum().Y - 5),
            basic::Vector2i(rect.GetMinimum().X + 5, rect.GetMaximum().Y - 2));

        paint_context.Render().Line(
            basic::Vector2i(rect.GetMaximum().X - 2, rect.GetMinimum().Y + 2),
            basic::Vector2i(rect.GetMinimum().X + 5, rect.GetMaximum().Y - 2));
    }

}
}
//------------------------------------------------------------------------------------------------//
