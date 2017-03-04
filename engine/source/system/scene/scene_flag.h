#ifndef _COFFEE_SCENE_FLAG_H_
#define _COFFEE_SCENE_FLAG_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_enum.h"

namespace coffee
{
namespace scene
{
    //--------------------------------------------------------------------------------------------//
    /// Flags defining nodes and components behaviors
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(coffee::scene, FLAG, "Flags", Multi)
        COFFEE_EnumValue(FLAG, Running, 1<<0)          ///< currently running
        COFFEE_EnumValue(FLAG, Automatic, 1<<1)        ///< automatically started
        COFFEE_EnumValue(FLAG, Instantiable, 1<<2)     ///< will exist in instances
        COFFEE_EnumValue(FLAG, Updating, 1<<3)         ///< it is updating
        COFFEE_EnumValue(FLAG, Destroyed, 1<<4)        ///< it is destroyed
        COFFEE_EnumValue(FLAG, StopInEditor, 1<<5)      ///< it wont run in the editor
    COFFEE_EndEnum(COFFEE_API, COFFEE_EXPORT_STATICS, FLAG)
}
}
#endif
