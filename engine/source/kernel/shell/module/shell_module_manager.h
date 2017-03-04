#ifndef _COFFEE_SHELL_MODULE_MANAGER_H_
#define _COFFEE_SHELL_MODULE_MANAGER_H_

#include "coffee_includes.h"
#include "kernel/basic/time/basic_clock.h"
#include "kernel/shell/module/shell_module.h"
#include "kernel/shell/module/shell_module_manager_config.h"

namespace coffee
{
namespace shell
{
    //--------------------------------------------------------------------------------------------//
    /// Module manager
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ModuleManager
    {
        COFFEE_DeclareSingleton(ModuleManager);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ModuleManager();
        ~ModuleManager();

        //-ACCESSORS------------------------------------------------------------------------------//

        const Module& GetRootModule() const;
        Module& GetRootModule();
        
        //-OPERATIONS-----------------------------------------------------------------------------//

        void Register(Module& module);
        void Unregister(Module& module);
        void Start();
        void Update();

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _Initialize();
        void _Start();
        void _Finalize();
        void _WaitRegistering();

        //-FUNCTIONS------------------------------------------------------------------------------//

        static void _CheckModuleRegisteration(Module& module, void* data);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Module* _RootModule;
        basic::Clock* _Clock;
        ModuleManagerConfig _Config;

        //-VARIABLES------------------------------------------------------------------------------//

        static bool _ModuleRegisterationWaiting;
    };
}
}
#endif
