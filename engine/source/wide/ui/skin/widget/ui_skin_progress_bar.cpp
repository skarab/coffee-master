//------------------------------------------------------------------------------------------------//
/// @file wide/ui/skin/widget/ui_skin_progress_bar.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "wide/ui/skin/widget/ui_skin_progress_bar.h"
#include "system/graphics/renderer/graphics_renderer.h"
#include "system/graphics/device/graphics_device.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::SkinProgressBar);
        COFFEE_Ancestor(ui::SkinWidget);
        COFFEE_Attribute(ui::SkinWidgetState, _StateDisabled, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(ui::SkinWidgetState, _StateEnabled, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SkinProgressBar::SkinProgressBar() :
        SkinWidget("ProgressBar", widget::ProgressBar::GetClassMetaType())
    {
    }

    //--------------------------------------------------------------------------------------------//

    SkinProgressBar::~SkinProgressBar()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void SkinProgressBar::ApplyTheme(SkinTheme& theme)
    {
        SetBorderSize(basic::Vector2i(2, 2));
        _StateDisabled.SetColor((theme.GetActiveItems()+theme.GetWindowDark())/2.0f);
        _StateEnabled.SetColor(theme.GetActiveItems());
    }

    //--------------------------------------------------------------------------------------------//

    void SkinProgressBar::Render(Window& window, const SkinContext& paint_context)
    {
        widget::ProgressBar* progress_bar = (widget::ProgressBar*) &window;
        SkinWidgetState state;

        if(!progress_bar->IsEnabled()) _SetState(_StateDisabled);
        else _SetState(_StateEnabled);

        basic::Vector2i minimum_position, maximum_position;

        minimum_position = paint_context.GetDesktopWindowRect().GetMinimum() + progress_bar->GetBorders();
        maximum_position = paint_context.GetDesktopWindowRect().GetMaximum() - progress_bar->GetBorders();

        if(progress_bar->HasExtendedStyle(ui::widget::PROGRESS_BAR_STYLE_Horizontal))
        {
            maximum_position.X=(int32)(minimum_position.X + (maximum_position.X - minimum_position.X)
                * progress_bar->GetPercentage());
        }
        else
        {
            maximum_position.Y=(int32)(minimum_position.Y + (maximum_position.Y - minimum_position.Y)
                * progress_bar->GetPercentage());
        }

        graphics::Renderer::Get().SetColor(_GetState().GetColor());

        paint_context.Render().Rectangle(
            minimum_position,
            maximum_position);
    }

}
}
//------------------------------------------------------------------------------------------------//
