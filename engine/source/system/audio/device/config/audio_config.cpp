#include "system/audio/device/config/audio_config.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(audio::Config);
        COFFEE_Ancestor(shell::ModuleConfig);
    COFFEE_EndType();

namespace audio
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Config::Config()
    {
    }

    //--------------------------------------------------------------------------------------------//

    Config::~Config()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Config::SetDefaults()
    {
    }

}
}
