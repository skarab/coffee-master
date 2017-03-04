#include "wide/plugins/plugins_module.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(plugins::Module);
        COFFEE_Ancestor(shell::Module);
    COFFEE_EndType();

namespace plugins
{
    COFFEE_ImplementModuleSingleton(Module);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Module::Module()
    {
        COFFEE_CreateModuleSingleton(Module);
    }

    //--------------------------------------------------------------------------------------------//

    Module::~Module()
    {
        COFFEE_DestroyModuleSingleton(Module);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Module::OnInitialize()
    {
        COFFEE_RegisterResourceLibrary("plugin");
        COFFEE_RegisterResourceLibrary("editor");
        COFFEE_RegisterResourceLibrary("component");
    }

    //--------------------------------------------------------------------------------------------//

    void Module::OnFinalize()
    {
    }

    //--------------------------------------------------------------------------------------------//

    void Module::OnStart()
    {
    }

    //--------------------------------------------------------------------------------------------//

    void Module::OnStop()
    {
    }

    //--------------------------------------------------------------------------------------------//

    void Module::OnUpdate(const basic::Time& time_step)
    {
    }

}
}
