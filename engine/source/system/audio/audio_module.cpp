#include "system/audio/audio_module.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(audio::Module);
        COFFEE_Ancestor(shell::Module);
    COFFEE_EndType();

namespace audio
{
    COFFEE_ImplementModuleSingleton(Module);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Module::Module() :
        shell::Module(shell::MODULE_ATTRIBUTE_Automatic)
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
        _Device = COFFEE_New(Device);
        _Device->Initialize();
        SetConfig(_Device->GetConfig());

        COFFEE_RegisterResourceLibrary("sound");        
    }

    //--------------------------------------------------------------------------------------------//

    void Module::OnFinalize()
    {
        _Device->Finalize();
        COFFEE_Delete(_Device);
        _Device = NULL;
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
        _Device->Update();
    }

}
}
