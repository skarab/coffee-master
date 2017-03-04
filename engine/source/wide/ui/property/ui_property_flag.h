#ifndef _COFFEE_UI_PROPERTY_FLAG_H_
#define _COFFEE_UI_PROPERTY_FLAG_H_

#include "coffee_includes.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// property creation flags
    ///
    /// Flags passed to coffee::ui::PropertyList::CreateHierarchy(...) and
    /// coffee::ui::PropertyManager::CreatePropertyInterface().
    //--------------------------------------------------------------------------------------------//
    enum PROPERTY_FLAG
    {
        PROPERTY_FLAG_None = 1 << 0,
        PROPERTY_FLAG_Root = 1 << 1,
        PROPERTY_FLAG_Array = 1 << 2,
        PROPERTY_FLAG_ResourceInstance = 1 << 3,
        PROPERTY_FLAG_ResourceProperty = 1 << 4,
        PROPERTY_FLAG_NodeProperty = 1 << 5
    };
}
}
#endif
