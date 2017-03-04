//------------------------------------------------------------------------------------------------//
/// @file wide/ui/property/basic/ui_property_image.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "wide/ui/property/basic/ui_property_image.h"
#include "wide/ui/window/ui_window_manager.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

	COFFEE_BeginType(ui::PropertyImage);
        COFFEE_Ancestor(ui::Property);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PropertyImage::PropertyImage() :
        _Image(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    PropertyImage::~PropertyImage()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void PropertyImage::CreateContent()
    {
        basic::Image* image = (basic::Image*)GetData();

        GetLayout().SetStyle(LAYOUT_STYLE_VerticalCanvas | LAYOUT_STYLE_StickChildren
            | LAYOUT_STYLE_HorizontalExpand | LAYOUT_STYLE_VerticalShrink);
    
        _Image = COFFEE_New(widget::Image);
        _Image->Create(this, basic::Vector2i(),
            basic::Vector2i(),
            widget::IMAGE_STYLE_AutoSize | widget::IMAGE_STYLE_DrawFrame);
        _Image->GetLayout().SetStyle(LAYOUT_STYLE_HorizontalCanvas
            | LAYOUT_STYLE_HorizontalExpand);
        _Image->SetImage(*image);
    }

}
}
//------------------------------------------------------------------------------------------------//
