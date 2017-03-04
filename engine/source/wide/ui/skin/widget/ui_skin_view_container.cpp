//------------------------------------------------------------------------------------------------//
/// @file wide/ui/skin/widget/ui_skin_view_container.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "wide/ui/skin/widget/ui_skin_view_container.h"
#include "system/graphics/renderer/graphics_renderer.h"
#include "system/graphics/device/graphics_device.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::SkinViewContainer);
        COFFEE_Ancestor(ui::SkinWidget);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SkinViewContainer::SkinViewContainer() :
        SkinWidget("ViewContainer", widget::ViewContainer::GetClassMetaType())
    {
    }

    //--------------------------------------------------------------------------------------------//

    SkinViewContainer::~SkinViewContainer()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void SkinViewContainer::ApplyTheme(SkinTheme& theme)
    {
        SetBorderSize(basic::Vector2i(0, 0));
    }

    //--------------------------------------------------------------------------------------------//

    void SkinViewContainer::Render(Window& window, const SkinContext& paint_context)
    {
    }

}
}
//------------------------------------------------------------------------------------------------//
