#ifndef _COFFEE_META_MODE_H_
#define _COFFEE_META_MODE_H_

#include "coffee_includes.h"

namespace coffee
{
namespace meta
{
    //--------------------------------------------------------------------------------------------//
    /// Object meta behavior
    ///
    /// The modes define basics behavior of the serialization system and GUI properties.
    /// More specifics behavior are defined using the meta::Param
    //--------------------------------------------------------------------------------------------//
    enum MODE
    {
        MODE_None = 0,                  ///< object is not serialized, nor editable
        MODE_Serializeable = 1 << 0,    ///< object is serialized
        MODE_Editable = 1 << 2,         ///< object appears in the GUI
        MODE_ReadOnly = 1 << 3,         ///< object is read only in the GUI
        MODE_NoGroup = 1 << 4,          ///< special case to not create GUI Group
        MODE_Undoable = 1 << 5,         ///< GUI changes will create undo object
        MODE_Default = MODE_Serializeable | MODE_Editable
    };
}
}
#endif
