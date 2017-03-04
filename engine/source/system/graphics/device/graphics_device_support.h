#ifndef _COFFEE_GRAPHICS_DEVICE_SUPPORT_H_
#define _COFFEE_GRAPHICS_DEVICE_SUPPORT_H_

#include "coffee_includes.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Special feature support
    //--------------------------------------------------------------------------------------------//
    enum DEVICE_SUPPORT
    {
        DEVICE_SUPPORT_GeometryShader = 1<<0,
        DEVICE_SUPPORT_SubstractiveBlend = 1<<1,
        DEVICE_SUPPORT_StencilWrap = 1<<2,
        DEVICE_SUPPORT_TwoSidedStencil = 1<<3,
        DEVICE_SUPPORT_TwoSidedStencilATI = 1<<4,
        DEVICE_SUPPORT_ShadowVolumes = 1<<5,
        DEVICE_SUPPORT_SoftShadows = 1<<6
    };
}
}
#endif
