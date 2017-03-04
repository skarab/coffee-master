#ifndef _COFFEE_GRAPHICS_CONFIG_STATE_H_
#define _COFFEE_GRAPHICS_CONFIG_STATE_H_

#include "coffee_includes.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Device configuration states
    //--------------------------------------------------------------------------------------------//
    enum CONFIG_STATE
    {
        CONFIG_STATE_Device,        ///< Graphics device index
        CONFIG_STATE_Bpp,           ///< Bits per pixel
        CONFIG_STATE_Width,         ///< Width of framebuffer
        CONFIG_STATE_Height,        ///< Height of framebuffer
        CONFIG_STATE_Anisotropic,   ///< Anisotropic multiplier
        CONFIG_STATE_Count
    };
}
}
#endif
