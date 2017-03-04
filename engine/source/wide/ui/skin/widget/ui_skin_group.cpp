//------------------------------------------------------------------------------------------------//
/// @file wide/ui/skin/widget/ui_skin_group.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "wide/ui/skin/widget/ui_skin_group.h"
#include "system/graphics/renderer/graphics_renderer.h"
#include "system/graphics/device/graphics_device.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::SkinGroup);
        COFFEE_Ancestor(ui::SkinWidget);
        COFFEE_Attribute(ui::SkinWidgetState, _StateDisabled, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(ui::SkinWidgetState, _StateEnabled, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(ui::SkinWidgetState, _StateActive, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SkinGroup::SkinGroup() :
        SkinWidget("Group", widget::Group::GetClassMetaType())
    {
    }

    //--------------------------------------------------------------------------------------------//

    SkinGroup::~SkinGroup()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void SkinGroup::ApplyTheme(SkinTheme& theme)
    {
        SetBorderSize(basic::Vector2i(3, 3));

        GetFont() = theme.GetDialogFont();

        _StateDisabled.SetColor(theme.GetDialog() - (theme.GetDialogActive() - theme.GetDialog()));
        _StateDisabled.SetFontColor(theme.GetFontColor());

        _StateEnabled.SetColor(theme.GetDialog());
        _StateEnabled.SetFontColor(theme.GetFontColor());

        _StateActive.SetColor(theme.GetDialogActive());
        _StateActive.SetFontColor(theme.GetFontColor());

        SetShadowsColor(theme.GetShadows());
        EnableShadows(theme.GetShadows().A > 0.0f);
        SetBumpColor(theme.GetBump());
        EnableBump(theme.GetBump().A > 0.0f);
    }

    //--------------------------------------------------------------------------------------------//

    void SkinGroup::Render(Window& window, const SkinContext& paint_context)
    {
        widget::Group* group = (widget::Group*) &window;
        
        if(!group->IsEnabled())
        {
            _SetState(_StateDisabled);
        }
        else if(group->IsActiveWindow())
        {
            _SetState(_StateActive);
        }
        else
        {
            _SetState(_StateEnabled);
        }

        // TitleBar

        graphics::Renderer::Get().SetColor(_GetState().GetColor());

        paint_context.Render().Rectangle(
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X
            + group->GetBorders().X - 1,
            paint_context.GetDesktopWindowRect().GetMinimum().Y + group->GetBorders().Y),
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMaximum().X - 2,
            paint_context.GetDesktopWindowRect().GetMinimum().Y + group->GetBorders().Y
            + group->GetTitleBarHeight() + 1));

        graphics::FrameScissor scissor;

        basic::Rectangle rect;

        rect.SetFromExtent(
            paint_context.GetDesktopWindowRect().GetMinimum() + group->GetBorders(),
                basic::Vector2i(paint_context.GetDesktopWindowRect().GetMaximum().X - group->GetBorders().X,
                paint_context.GetDesktopWindowRect().GetMinimum().Y + group->GetBorders().Y
                + group->GetTitleBarHeight()));

        scissor.SetRectangle(rect - paint_context.GetDesktopClipRect());
        scissor.Bind();

        GetFont().Print(group->GetTitleBarText(), basic::Vector2i(
            paint_context.GetDesktopWindowRect().GetMinimum().X + group->GetClientRect().Position.X
            + group->GetBorders().X * 2,
            paint_context.GetDesktopWindowRect().GetMinimum().Y + group->GetClientRect().Position.Y
            - group->GetBorders().Y - 1));
    }

}
}
//------------------------------------------------------------------------------------------------//
