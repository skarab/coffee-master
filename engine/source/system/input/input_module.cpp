#include "kernel/core/log/core_log.h"
#include "kernel/core/error/core_error.h"
#include "system/input/input_module.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(input::Module);
        COFFEE_Ancestor(shell::Module);
    COFFEE_EndType();

namespace input
{
    //--------------------------------------------------------------------------------------------//

    COFFEE_ImplementModuleSingleton(Module);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Module::Module() :
        _System(NULL)
    {
        COFFEE_CreateModuleSingleton(Module);
    }

    //--------------------------------------------------------------------------------------------//

    Module::~Module()
    {
        COFFEE_DestroyModuleSingleton(Module);
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const System& Module::GetSystem() const
    {
        return *_System;
    }

    //--------------------------------------------------------------------------------------------//

    System& Module::GetSystem()
    {
        return *_System;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Module::OnInitialize()
    {
        SetConfig(_Config);
        _System = COFFEE_New(System);
        COFFEE_RegisterChildModule(Keyboard);
        COFFEE_RegisterChildModule(Mouse);
    }

    //--------------------------------------------------------------------------------------------//

    void Module::OnFinalize()
    {
        _System->Destroy();
    }

    //--------------------------------------------------------------------------------------------//

    void Module::OnUpdate(const basic::Time& time_step)
    {
        _System->Update(time_step);
    }

}
}
