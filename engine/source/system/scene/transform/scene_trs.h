#ifndef _COFFEE_SCENE_TRS_H_
#define _COFFEE_SCENE_TRS_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_enum.h"

namespace coffee
{
namespace scene
{
    //--------------------------------------------------------------------------------------------//
    /// Defines which viewpoint is used in Transform operations
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(coffee::scene, TRS, "TRS", Single)
        COFFEE_EnumValue(TRS, Local, 0)     ///< local transform
        COFFEE_EnumValue(TRS, Parent, 1)    ///< parent transform
        COFFEE_EnumValue(TRS, World, 2)     ///< world transform
    COFFEE_EndEnum(COFFEE_API, COFFEE_EXPORT_STATICS, TRS)

    //--------------------------------------------------------------------------------------------//
    /// Defines from where comes transform modification
    //--------------------------------------------------------------------------------------------//
    COFFEE_BeginEnum(coffee::scene, TRS_FLAG, "TRS_FLAG", Single)
        COFFEE_EnumValue(TRS_FLAG, Physics, 0)  ///< physics transform
        COFFEE_EnumValue(TRS_FLAG, User, 1)   ///< component or other transform
    COFFEE_EndEnum(COFFEE_API, COFFEE_EXPORT_STATICS, TRS_FLAG)
}
}
#endif
