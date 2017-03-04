//------------------------------------------------------------------------------------------------//
/// @file wide/ui/skin/widget/ui_skin_menu_item.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "wide/ui/skin/widget/ui_skin_menu_item.h"
#include "system/graphics/renderer/graphics_renderer.h"
#include "system/graphics/device/graphics_device.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::SkinMenuItem);
        COFFEE_Ancestor(ui::SkinWidget);
        COFFEE_Attribute(ui::SkinWidgetState, _StateDisabled, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(ui::SkinWidgetState, _StateEnabled, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(ui::SkinWidgetState, _StateCursorOver, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SkinMenuItem::SkinMenuItem() :
        SkinWidget("MenuItem", widget::MenuItem::GetClassMetaType())
    {
    }

    //--------------------------------------------------------------------------------------------//

    SkinMenuItem::~SkinMenuItem()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void SkinMenuItem::ApplyTheme(SkinTheme& theme)
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
    
        _StateEnabled.SetColor(theme.GetWindow());
        _StateEnabled.GetColor().A = theme.GetAlpha();
        _StateEnabled.SetHighlightColor(theme.GetWindowLight());
        _StateEnabled.GetHighlightColor().A = theme.GetAlpha();
        _StateEnabled.SetShadowColor(theme.GetWindowDark());
        _StateEnabled.GetShadowColor().A = theme.GetAlpha();
        _StateEnabled.SetFontColor(theme.GetFontColor());

        _StateCursorOver.SetColor(theme.GetActiveItems());
        _StateCursorOver.GetColor().A = theme.GetAlpha();
        _StateCursorOver.SetHighlightColor(theme.GetWindowLight());
        _StateCursorOver.GetHighlightColor().A = theme.GetAlpha();
        _StateCursorOver.SetShadowColor(theme.GetWindowDark());
        _StateCursorOver.GetShadowColor().A = theme.GetAlpha();
        _StateCursorOver.SetFontColor(theme.GetFontColor()
            + basic::Color(0.1f, 0.1f, 0.1f, 1.0f));

        SetShadowsColor(theme.GetShadows());
        EnableShadows(theme.GetShadows().A > 0.0f);
        SetBumpColor(theme.GetBump());
        EnableBump(theme.GetBump().A > 0.0f);
    }

    //--------------------------------------------------------------------------------------------//

    void SkinMenuItem::Render(Window& window, const SkinContext& paint_context)
    {
        widget::MenuItem* menu_item = (widget::MenuItem*) &window;

        if(menu_item->GetType()!=widget::MENU_ITEM_TYPE_Panel)
            return;

        if(!menu_item->IsEnabled())
        {
            _SetState(_StateDisabled);
        }
        else if(menu_item->HasCursorOver() || menu_item->GetMenu()->HasState(WINDOW_STATE_Visible))
        {
            _SetState(_StateCursorOver);
        }
        else
        {
            _SetState(_StateEnabled);
        }

        graphics::Renderer::Get().SetColor(_GetState().GetColor());

        paint_context.Render().Rectangle(
            paint_context.GetDesktopWindowRect().GetMinimum(),
            paint_context.GetDesktopWindowRect().GetMaximum());

        // Borders

        graphics::Renderer::Get().SetColor(_GetState().GetShadowColor());

        paint_context.Render().Line(
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X + menu_item->GetRect().Size.X,
            paint_context.GetDesktopWindowRect().GetMinimum().Y),
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X + menu_item->GetRect().Size.X,
            paint_context.GetDesktopWindowRect().GetMinimum().Y + menu_item->GetRect().Size.Y));

        paint_context.Render().Line(
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X,
            paint_context.GetDesktopWindowRect().GetMinimum().Y + menu_item->GetRect().Size.Y),
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X + menu_item->GetRect().Size.X,
            paint_context.GetDesktopWindowRect().GetMinimum().Y + menu_item->GetRect().Size.Y));

        graphics::Renderer::Get().SetColor(_GetState().GetHighlightColor());

        paint_context.Render().Line(
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X,
            paint_context.GetDesktopWindowRect().GetMinimum().Y),
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X,
            paint_context.GetDesktopWindowRect().GetMinimum().Y + menu_item->GetRect().Size.Y));

        paint_context.Render().Line(
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X,
            paint_context.GetDesktopWindowRect().GetMinimum().Y),
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X + menu_item->GetRect().Size.X,
            paint_context.GetDesktopWindowRect().GetMinimum().Y));

        if(menu_item->GetText().GetLength() > 0)
        {
            basic::Vector2i text_position;

            text_position.X=paint_context.GetDesktopWindowRect().GetMinimum().X + menu_item->GetBorders().X;
            text_position.Y=paint_context.GetDesktopWindowRect().GetMinimum().Y + paint_context.GetDesktopWindowRect().Size.Y / 2 + GetFont().GetHeight() / 2;

            GetFont().Print(menu_item->GetText(), text_position);
        }
    }

}
}
//------------------------------------------------------------------------------------------------//
