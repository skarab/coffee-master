#ifndef _COFFEE_BASIC_GEOMETRIC_FRUSTUM3_PLANE_H_
#define _COFFEE_BASIC_GEOMETRIC_FRUSTUM3_PLANE_H_

#include "coffee_includes.h"

namespace coffee
{
namespace basic
{
    //--------------------------------------------------------------------------------------------//
    /// Frustum3 planes enumeration
    //--------------------------------------------------------------------------------------------//
    enum FRUSTUM3_PLANE
    {
        FRUSTUM3_PLANE_Right,
        FRUSTUM3_PLANE_Left,
        FRUSTUM3_PLANE_Top,
        FRUSTUM3_PLANE_Bottom,
        FRUSTUM3_PLANE_Near,
        FRUSTUM3_PLANE_Far,
        FRUSTUM3_PLANE_Count
    };

    //--------------------------------------------------------------------------------------------//
    /// Frustum3 corners enumeration
    //--------------------------------------------------------------------------------------------//
    enum FRUSTUM3_CORNER
    {
        FRUSTUM3_CORNER_FarTopRight,
        FRUSTUM3_CORNER_FarTopLeft,
        FRUSTUM3_CORNER_FarBottomRight,
        FRUSTUM3_CORNER_FarBottomLeft,
        FRUSTUM3_CORNER_NearTopRight,
        FRUSTUM3_CORNER_NearTopLeft,
        FRUSTUM3_CORNER_NearBottomRight,
        FRUSTUM3_CORNER_NearBottomLeft,
        FRUSTUM3_CORNER_Count
    };

}
}
#endif
