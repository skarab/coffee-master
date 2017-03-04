#ifndef _COFFEE_UI_WINDOW_HIT_TYPE_H_
#define _COFFEE_UI_WINDOW_HIT_TYPE_H_

#include "coffee_includes.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Window hit types
    //--------------------------------------------------------------------------------------------//
    enum WINDOW_HIT_TYPE
    {
        WINDOW_HIT_TYPE_None = 1 << 0,
        WINDOW_HIT_TYPE_BorderTop = 1 << 1,
        WINDOW_HIT_TYPE_BorderBottom = 1 << 2,
        WINDOW_HIT_TYPE_BorderLeft = 1 << 3,
        WINDOW_HIT_TYPE_BorderRight = 1 << 4
    };
}
}
#endif
