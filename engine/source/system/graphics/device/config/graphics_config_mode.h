#ifndef _COFFEE_GRAPHICS_CONFIG_MODE_H_
#define _COFFEE_GRAPHICS_CONFIG_MODE_H_

#include "coffee_includes.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Basics On/Off modes
    //--------------------------------------------------------------------------------------------//
    enum CONFIG_MODE
    {
        CONFIG_MODE_Fullscreen = 1 << 0,
        CONFIG_MODE_VerticalSync = 1 << 1
    };
}
}
#endif
