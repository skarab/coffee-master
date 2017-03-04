#ifndef _COFFEE_INPUT_MODULE_H_
#define _COFFEE_INPUT_MODULE_H_

#include "coffee_includes.h"
#include "kernel/shell/module/shell_module_manager.h"
#include "system/input/input_device.h"
#include "system/input/keyboard/input_keyboard.h"
#include "system/input/mouse/input_mouse.h"
#include "system/input/input_system.h"
#include "system/input/config/input_config.h"

namespace coffee
{
namespace input
{
    //--------------------------------------------------------------------------------------------//
    /// Input Module
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Module : public shell::Module
    {
        COFFEE_Type(Module);
        COFFEE_DeclareModuleSingleton(Module);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Module();
        ~Module();

        //-ACCESSORS------------------------------------------------------------------------------//

        const System& GetSystem() const;
        System& GetSystem();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void OnInitialize();
        void OnFinalize();
        void OnUpdate(const basic::Time& time_step);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Config _Config;
        System* _System;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Module);
}
}
#endif
