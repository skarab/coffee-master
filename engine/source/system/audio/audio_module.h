#ifndef _COFFEE_AUDIO_MODULE_H_
#define _COFFEE_AUDIO_MODULE_H_

#include "coffee_includes.h"
#include "kernel/shell/module/shell_module_manager.h"
#include "system/audio/device/audio_device.h"
#include "system/audio/sound/audio_sound.h"
#include "system/audio/component/audio_components.h"

namespace coffee
{
namespace audio
{
    //--------------------------------------------------------------------------------------------//
    /// Audio module
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Module : public shell::Module
    {
        COFFEE_Type(Module);
        COFFEE_DeclareModuleSingleton(Module);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Module();
        ~Module();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void OnInitialize();
        void OnFinalize();
        void OnStart();
        void OnStop();
        void OnUpdate(const basic::Time& time_step);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Device* _Device;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Module);
}
}
#endif
