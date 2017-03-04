#ifndef _COFFEE_GRAPHICS_CONFIG_ASPECT_RATIO_H_
#define _COFFEE_GRAPHICS_CONFIG_ASPECT_RATIO_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Aspect ratio
    //--------------------------------------------------------------------------------------------//
    enum CONFIG_ASPECT_RATIO
    {
        CONFIG_ASPECT_RATIO_4_3,
        CONFIG_ASPECT_RATIO_5_4,
        CONFIG_ASPECT_RATIO_16_9,
        CONFIG_ASPECT_RATIO_16_10,
        CONFIG_ASPECT_RATIO_2_1,
        CONFIG_ASPECT_RATIO_3_2,
        CONFIG_ASPECT_RATIO_3_4,
        CONFIG_ASPECT_RATIO_4_5,
        CONFIG_ASPECT_RATIO_9_16,
        CONFIG_ASPECT_RATIO_10_16,
        CONFIG_ASPECT_RATIO_1_2,
        CONFIG_ASPECT_RATIO_2_3,
        CONFIG_ASPECT_RATIO_Count
    };

    //-FUNCTIONS----------------------------------------------------------------------------------//

    COFFEE_API basic::String CONFIG_ASPECT_RATIO_GetString(CONFIG_ASPECT_RATIO format);
    COFFEE_API real CONFIG_ASPECT_RATIO_GetValue(CONFIG_ASPECT_RATIO format);
    COFFEE_API CONFIG_ASPECT_RATIO CONFIG_ASPECT_RATIO_GetRatio(real aspect_ratio);

}
}
#endif
