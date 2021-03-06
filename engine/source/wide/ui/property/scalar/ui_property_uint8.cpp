//------------------------------------------------------------------------------------------------//
/// @file wide/ui/property/scalar/ui_property_uint8.hpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "wide/ui/property/scalar/ui_property_uint8.h"
#include "wide/ui/window/ui_window_manager.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::PropertyUInt8);
        COFFEE_Ancestor(ui::Property);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PropertyUInt8::PropertyUInt8()
    {
    }

    //--------------------------------------------------------------------------------------------//

    PropertyUInt8::~PropertyUInt8()
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

    basic::String PropertyUInt8::_GetTextFromValue(uint8 value) const
    {
        return basic::String("%u", value);
    }

    //--------------------------------------------------------------------------------------------//

    uint8 PropertyUInt8::_GetValueFromText(const basic::String& text) const
    {
        return text.GetInteger();
    }

}
}
//------------------------------------------------------------------------------------------------//
