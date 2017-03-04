#include "system/graphics/device/config/graphics_config_quality.h"

namespace coffee
{
namespace graphics
{
    //-FUNCTIONS----------------------------------------------------------------------------------//

    basic::String CONFIG_QUALITY_GetString(CONFIG_QUALITY quality)
    {
        static char quality_string_array[CONFIG_QUALITY_Count][16] =
        {
            "Ultra-Low",
            "Low",
            "Medium",
            "High",
            "Ultra-High"
        };

        return quality_string_array[(uint32)quality];
    }

}
}
