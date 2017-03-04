//------------------------------------------------------------------------------------------------//
/// @file system/graphics/device/config/graphics_config_aspect_ratio.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "system/graphics/device/config/graphics_config_aspect_ratio.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
namespace graphics
{
    //-FUNCTIONS----------------------------------------------------------------------------------//

    basic::String CONFIG_ASPECT_RATIO_GetString(CONFIG_ASPECT_RATIO format)
    {
        static char format_string_array[CONFIG_ASPECT_RATIO_Count][16] =
        {
            "4:3",
            "5:4",
            "16:9",
            "16:10",
            "2:1",
            "3:2",
            "3:4",
            "4:5",
            "9:16",
            "10:16",
            "1:2",
            "2:3"
        };

        return format_string_array[(uint32)format];
    }

    //--------------------------------------------------------------------------------------------//

    real CONFIG_ASPECT_RATIO_GetValue(CONFIG_ASPECT_RATIO format)
    {
        static real format_value_array[CONFIG_ASPECT_RATIO_Count] =
        {
            4.0f/3.0f,
            5.0f/4.0f,
            16.0f/9.0f,
            16.0f/10.0f,
            2.0f/1.0f,
            3.0f/2.0f,
            3.0f/4.0f,
            4.0f/5.0f,
            9.0f/16.0f,
            10.0f/16.0f,
            1.0f/2.0f,
            2.0f/3.0f
        };

        return format_value_array[(uint32)format];
    }

    //--------------------------------------------------------------------------------------------//

    CONFIG_ASPECT_RATIO CONFIG_ASPECT_RATIO_GetRatio(real aspect_ratio)
    {
        real min_diff = 99999.9f;
        CONFIG_ASPECT_RATIO ratio = CONFIG_ASPECT_RATIO_4_3;
        for (uint32 i=0 ; i<(uint32)CONFIG_ASPECT_RATIO_Count ; ++i)
        {
            real val = CONFIG_ASPECT_RATIO_GetValue((CONFIG_ASPECT_RATIO)i);
            real diff = Absolute(aspect_ratio-val);
            if (diff<min_diff)
            {
                min_diff = diff;
                ratio = (CONFIG_ASPECT_RATIO)i;
            }
        }
        return ratio;
    }

}
}
//------------------------------------------------------------------------------------------------//
