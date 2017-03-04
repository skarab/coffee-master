//------------------------------------------------------------------------------------------------//
/// @file wide/ui/skin/widget/ui_skin_scroll_bar.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "wide/ui/skin/widget/ui_skin_scroll_bar.h"
#include "system/graphics/renderer/graphics_renderer.h"
#include "system/graphics/device/graphics_device.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::SkinScrollBar);
        COFFEE_Ancestor(ui::SkinWidget);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SkinScrollBar::SkinScrollBar() :
        SkinWidget("ScrollBar", widget::ScrollBar::GetClassMetaType())
    {
    }

    //--------------------------------------------------------------------------------------------//

    SkinScrollBar::~SkinScrollBar()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//
    
    void SkinScrollBar::ApplyTheme(SkinTheme& theme)
    {
        SetBorderSize(basic::Vector2i(1, 1));
    }

    //--------------------------------------------------------------------------------------------//

    void SkinScrollBar::Render(Window& window, const SkinContext& paint_context)
    {
    }

}
}
//------------------------------------------------------------------------------------------------//
