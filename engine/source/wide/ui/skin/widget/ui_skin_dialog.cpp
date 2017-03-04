//------------------------------------------------------------------------------------------------//
/// @file wide/ui/skin/widget/ui_skin_dialog.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "wide/ui/skin/widget/ui_skin_dialog.h"
#include "system/graphics/renderer/graphics_renderer.h"
#include "system/graphics/device/graphics_device.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::SkinDialog);
        COFFEE_Ancestor(ui::SkinWidget);
        COFFEE_Attribute(ui::SkinWidgetState, _StateDisabled, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(ui::SkinWidgetState, _StateEnabled, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(ui::SkinWidgetState, _StateActive, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SkinDialog::SkinDialog() :
        SkinWidget("Dialog", widget::Dialog::GetClassMetaType())
    {
    }

    //--------------------------------------------------------------------------------------------//

    SkinDialog::~SkinDialog()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void SkinDialog::ApplyTheme(SkinTheme& theme)
    {
        SetBorderSize(basic::Vector2i(4, 4));

        GetFont() = theme.GetDialogFont();
        
        _StateDisabled.SetColor(theme.GetDialog() - (theme.GetDialogActive() - theme.GetDialog()));
        _StateDisabled.SetFontColor(theme.GetDialogFontColor());
        
        _StateEnabled.SetColor(theme.GetDialog());
        _StateEnabled.SetFontColor(theme.GetDialogFontColor());
        
        _StateActive.SetColor(theme.GetDialogActive());
        _StateActive.SetFontColor(theme.GetDialogFontColor());
        
        SetShadowsColor(theme.GetShadows());
        EnableShadows(theme.GetShadows().A > 0.0f);
        SetBumpColor(theme.GetBump());
        EnableBump(theme.GetBump().A > 0.0f);
    }

    //--------------------------------------------------------------------------------------------//

    void SkinDialog::Render(Window& window, const SkinContext& paint_context)
    {
        widget::Dialog* dialog = (widget::Dialog*) &window;
        
        if(!dialog->IsEnabled())
        {
            _SetState(_StateDisabled);
        }
        else if(dialog->IsActiveWindow())
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
            + dialog->GetBorders().X - 1, paint_context.GetDesktopWindowRect().GetMinimum().Y
            + dialog->GetBorders().Y),
            basic::Vector2i(paint_context.GetDesktopWindowRect().GetMinimum().X
            + dialog->GetBorders().X + 1 + dialog->GetClientRect().Size.X,
            paint_context.GetDesktopWindowRect().GetMinimum().Y + dialog->GetBorders().Y
            + dialog->GetTitleBarHeight() + 1));

        graphics::FrameScissor scissor;

        basic::Rectangle rect;

        rect.SetFromExtent(
            paint_context.GetDesktopWindowRect().GetMinimum() + dialog->GetBorders(),
                basic::Vector2i(paint_context.GetDesktopWindowRect().GetMaximum().X
                - dialog->GetBorders().X,
                paint_context.GetDesktopWindowRect().GetMinimum().Y + dialog->GetBorders().Y
                + dialog->GetTitleBarHeight()));

        scissor.SetRectangle(rect - paint_context.GetDesktopClipRect());
        scissor.Bind();

        GetFont().Print(
            dialog->GetTitleBarText(),
            basic::Vector2i(
                paint_context.GetDesktopWindowRect().GetMinimum().X
                    + dialog->GetClientRect().Position.X,
                paint_context.GetDesktopWindowRect().GetMinimum().Y
                    + dialog->GetClientRect().Position.Y - dialog->GetBorders().Y - 1));
    }

}
}
//------------------------------------------------------------------------------------------------//
