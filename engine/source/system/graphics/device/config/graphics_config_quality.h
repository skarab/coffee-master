#ifndef _COFFEE_GRAPHICS_CONFIG_QUALITY_H_
#define _COFFEE_GRAPHICS_CONFIG_QUALITY_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Config quality setting (future use)
    //--------------------------------------------------------------------------------------------//
    enum CONFIG_QUALITY
    {
        CONFIG_QUALITY_UltraLow,
        CONFIG_QUALITY_Low,
        CONFIG_QUALITY_Medium,
        CONFIG_QUALITY_High,
        CONFIG_QUALITY_UltraHigh,
        CONFIG_QUALITY_Count
    };

    //-FUNCTIONS----------------------------------------------------------------------------------//

    COFFEE_API basic::String CONFIG_QUALITY_GetString(CONFIG_QUALITY quality);
}
}
#endif
