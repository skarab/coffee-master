#ifndef _AUDIO_CONFIG_H_
#define _AUDIO_CONFIG_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"

namespace coffee
{
namespace audio
{

    //--------------------------------------------------------------------------------------------//
    /// Audio config
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Config : public shell::ModuleConfig
    {
        COFFEE_Type(Config);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Config();
        ~Config();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void SetDefaults();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Config);
}
}
#endif
