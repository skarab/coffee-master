//------------------------------------------------------------------------------------------------//
/// @file wide/ui/skin/widget/ui_skin_tree_control_item.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "wide/ui/skin/widget/ui_skin_tree_control_item.h"
#include "system/graphics/renderer/graphics_renderer.h"
#include "system/graphics/device/graphics_device.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::SkinTreeControlItem);
        COFFEE_Ancestor(ui::SkinWidget);
        COFFEE_Attribute(ui::SkinWidgetState, _StateDisabled, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(ui::SkinWidgetState, _StateEnabled, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(ui::SkinWidgetState, _StateActive, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(ui::SkinWidgetState, _StateCursorOver, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SkinTreeControlItem::SkinTreeControlItem() :
        SkinWidget("TreeItem", widget::TreeControlItem::GetClassMetaType())
    {
    }

    //--------------------------------------------------------------------------------------------//

    SkinTreeControlItem::~SkinTreeControlItem()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void SkinTreeControlItem::ApplyTheme(SkinTheme& theme)
    {
        SkinWidget::ApplyTheme(theme);
        SetBorderSize(basic::Vector2i(0, 0));

        _StateEnabled.SetFontColor((theme.GetFontColor()+theme.GetWindow())/2.0f);
        _StateEnabled.SetColor(theme.GetWindowSunken());
        _StateEnabled.SetHighlightColor(theme.GetWindowLight());
        _StateEnabled.SetShadowColor(theme.GetWindowDark());

        _StateActive.SetFontColor(theme.GetFontColor());
        _StateActive.SetColor(theme.GetActiveItems());
        _StateActive.SetHighlightColor(theme.GetWindowLight());
        _StateActive.SetShadowColor(theme.GetWindowDark());

        _StateCursorOver.SetFontColor(theme.GetFontColor());
        _StateCursorOver.SetColor((theme.GetWindow()+theme.GetActiveItems())/2.0f);
        _StateCursorOver.SetHighlightColor(theme.GetWindowLight());
        _StateCursorOver.SetShadowColor(theme.GetWindowDark());
    }

    //--------------------------------------------------------------------------------------------//

    void SkinTreeControlItem::Render(Window& window, const SkinContext& paint_context)
    {
        widget::TreeControlItem* item = static_cast<widget::TreeControlItem*>(&window);
        widget::TreeControl* tree = (widget::TreeControl*)item->FindParent<widget::TreeControl>();

        if(!item->IsEnabled())
        {
            _SetState(_StateDisabled);
        }
        else if(item==tree->GetSelectedItem())
        {
            _SetState(_StateActive);
        }
        else if(item->HasCursorOver())
        {
            _SetState(_StateCursorOver);
        }
        else
        {
            _SetState(_StateEnabled);
        }

        // TitleBar

        graphics::Renderer::Get().SetColor(_GetState().GetColor());

        paint_context.Render().Rectangle(
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X + item->GetBorders().X - 1,
            paint_context.GetDesktopWindowRect().GetMinimum().Y + item->GetBorders().Y),
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMaximum().X - 2,
            paint_context.GetDesktopWindowRect().GetMinimum().Y + item->GetBorders().Y + item->GetItemHeight() + 1));

        paint_context.Render().Rectangle(
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X + item->GetBorders().X - 1,
            paint_context.GetDesktopWindowRect().GetMinimum().Y + item->GetBorders().Y),
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X + item->GetBorders().X - 2
            + item->GetItemHeight(), paint_context.GetDesktopWindowRect().GetMaximum().Y + item->GetBorders().Y));

        graphics::FrameScissor scissor;

        basic::Rectangle rect;

        rect.SetFromExtent(
            paint_context.GetDesktopWindowRect().GetMinimum() + item->GetBorders(),
                basic::Vector2i(paint_context.GetDesktopWindowRect().GetMaximum().X - item->GetBorders().X,
                paint_context.GetDesktopWindowRect().GetMinimum().Y + item->GetBorders().Y + item->GetItemHeight()));

        scissor.SetRectangle(rect - paint_context.GetDesktopClipRect());
        scissor.Bind();

        GetFont().Print(item->GetText(), basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X
            + item->GetClientRect().Position.X + item->GetBorders().X * 2 + item->GetItemHeight(),
            paint_context.GetDesktopWindowRect().GetMinimum().Y + item->GetClientRect().Position.Y
            - item->GetBorders().Y - 1));
    }

}
}
//------------------------------------------------------------------------------------------------//
