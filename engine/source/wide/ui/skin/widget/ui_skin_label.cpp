//------------------------------------------------------------------------------------------------//
/// @file wide/ui/skin/widget/ui_skin_label.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "wide/ui/skin/widget/ui_skin_label.h"
#include "system/graphics/renderer/graphics_renderer.h"
#include "system/graphics/device/graphics_device.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::SkinLabel);
        COFFEE_Ancestor(ui::SkinWidget);
        COFFEE_Attribute(ui::SkinWidgetState, _StateEnabled, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SkinLabel::SkinLabel() :
        SkinWidget("Label", widget::Label::GetClassMetaType())
    {
    }

    //--------------------------------------------------------------------------------------------//

    SkinLabel::~SkinLabel()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void SkinLabel::ApplyTheme(SkinTheme& theme)
    {
        SkinWidget::ApplyTheme(theme);
        SetBorderSize(basic::Vector2i(2, 2));
        _StateEnabled.SetFontColor(theme.GetFontColor());
    }

    //--------------------------------------------------------------------------------------------//

    void SkinLabel::Render(Window& window, const SkinContext& paint_context)
    {
        widget::Label* text = (widget::Label*) &window;
        
        _SetState(_StateEnabled);

        if(text->GetText().GetLength() > 0)
        {
            graphics::FrameScissor scissor;
            basic::Rectangle rect;

            rect.Position = paint_context.GetDesktopWindowRect().GetMinimum() + text->GetBorders();
            rect.Size = paint_context.GetDesktopWindowRect().Size - text->GetBorders() * 2;
            rect -= paint_context.GetDesktopClipRect();

            scissor.SetRectangle(rect);
            scissor.Bind();

            basic::Vector2i text_position;

            text_position.X=paint_context.GetDesktopWindowRect().GetMinimum().X + text->GetBorders().X;
            text_position.Y=paint_context.GetDesktopWindowRect().GetMinimum().Y + paint_context.GetDesktopWindowRect().Size.Y / 2 + GetFont().GetHeight() / 2;
            GetFont().Print(text->GetText(), text_position);
        }
    }

}
}
//------------------------------------------------------------------------------------------------//
