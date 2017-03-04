#ifndef _COFFEE_EDITION_GIZMO_AXIS_H_
#define _COFFEE_EDITION_GIZMO_AXIS_H_

#include "coffee_includes.h"

namespace coffee
{
namespace edition
{
    //--------------------------------------------------------------------------------------------//
    /// Gizmo axis
    //--------------------------------------------------------------------------------------------//
    enum GIZMO_AXIS
    {
        GIZMO_AXIS_None,
        GIZMO_AXIS_Camera,
        GIZMO_AXIS_Free,
        GIZMO_AXIS_X,
        GIZMO_AXIS_Y,
        GIZMO_AXIS_Z,
        GIZMO_AXIS_XY,
        GIZMO_AXIS_XZ,
        GIZMO_AXIS_YZ,
        GIZMO_AXIS_XYZ,
        GIZMO_AXIS_Count
    };
}
}
#endif
