#include "system/graphics/graphics.h"
#include "kernel/resource/resource_manager.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::Module);
        COFFEE_Ancestor(shell::Module);
    COFFEE_EndType();

namespace graphics
{
    //--------------------------------------------------------------------------------------------//

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
        _Device = COFFEE_New(Device);
        SetConfig(_Device->GetConfig());
        _Device->Initialize();
        
        COFFEE_RegisterResourceLibrary("sky");
        COFFEE_RegisterResourceLibrary("mesh");
        COFFEE_RegisterResourceLibrary("material");
        COFFEE_RegisterResourceLibrary("shader");
        COFFEE_RegisterResourceLibrary("texture");
        COFFEE_RegisterResourceLibrary("font");
    }

    //--------------------------------------------------------------------------------------------//

    void Module::OnFinalize()
    {
        _Device->Finalize();
        COFFEE_Delete(_Device);
    }

    //--------------------------------------------------------------------------------------------//

    void Module::OnStart()
    {
        _Renderer = COFFEE_New(Renderer);
    }

    //--------------------------------------------------------------------------------------------//

    void Module::OnStop()
    {
        COFFEE_Delete(_Renderer);
    }

    //--------------------------------------------------------------------------------------------//

    void Module::OnUpdate(const basic::Time& time_step)
    {
        COFFEE_GRAPHICS_Debug();
    }

}
}
