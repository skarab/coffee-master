//------------------------------------------------------------------------------------------------//
/// @file wide/ui/property/array/ui_property_array.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "wide/ui/property/array/ui_property_array.h"
#include "wide/ui/property/ui_property_list.h"
#include "wide/ui/window/ui_window_manager.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::PropertyArray);
        COFFEE_Ancestor(ui::Property);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PropertyArray::PropertyArray() :
        _Group(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    PropertyArray::~PropertyArray()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void PropertyArray::CreateContent()
    {
        _Group = COFFEE_New(widget::Group);
        _Group->Create(this, basic::Vector2i(),
            basic::Vector2i(GetClientRect().Size.X, 20));
        _Group->SetTitleBarText(GetName());
        
        for(uint32 child_index=0 ; child_index<GetObjectInfo().GetChildCount() ; ++child_index)
        {
            PropertyList::CreateHierarchy(GetObjectInfo().GetChild(child_index), *_Group);
        }
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(PropertyArray, Property)
    COFFEE_EndEventHandler()
}
}
//------------------------------------------------------------------------------------------------//
