#include "kernel/shell/module/shell_module_manager.h"
#include "coffee.h"

namespace coffee
{
namespace shell
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_ImplementSingleton(ModuleManager);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ModuleManager::ModuleManager() :
        _Clock(NULL)
    {
        COFFEE_CreateSingleton(ModuleManager);
        _Initialize();
    }

    //--------------------------------------------------------------------------------------------//

    ModuleManager::~ModuleManager()
    {
        _Finalize();
        COFFEE_DestroySingleton(ModuleManager);
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const Module & ModuleManager::GetRootModule() const
    {
        return *_RootModule;
    }

    //--------------------------------------------------------------------------------------------//

    Module & ModuleManager::GetRootModule()
    {
        return *_RootModule;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ModuleManager::Register(Module & module)
    {
        COFFEE_SendEventParams(*_RootModule, MODULE_EVENT_Register,
            Module, EventParameters(NULL, &module));
    }

    //--------------------------------------------------------------------------------------------//

    void ModuleManager::Unregister(Module & module)
    {
        COFFEE_SendEvent(module, MODULE_EVENT_Unregister, Module);
    }

    //--------------------------------------------------------------------------------------------//

    void ModuleManager::Start()
    {
        _WaitRegistering();

        _Config.Load();

        if (_Config.Configure())
        {
            _Start();
        }
        else
        {
            Engine::Get().Quit();
        }
    }

    //--------------------------------------------------------------------------------------------//

    void ModuleManager::Update()
    {
        _Clock->Update();
        _RootModule->Update(_Clock->GetTimeStep());
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ModuleManager::_Initialize()
    {
        Thread::SetMainThreadName("coffee::Application");
        _RootModule = COFFEE_New(Module);

        COFFEE_SendEvent(*_RootModule, MODULE_EVENT_Stop, Module);

        while(_RootModule->GetState() != MODULE_STATE_Stopped)
            _RootModule->Update(basic::Time());
    }

    //--------------------------------------------------------------------------------------------//

    void ModuleManager::_Start()
    {
        COFFEE_SendEvent(*_RootModule, MODULE_EVENT_Start, Module);

        while(_RootModule->GetState() != MODULE_STATE_Running)
            _RootModule->Update(basic::Time());

        _Clock = COFFEE_New(basic::Clock);
    }

    //--------------------------------------------------------------------------------------------//

    void ModuleManager::_Finalize()
    {
        if (resource::Manager::IsInstantiated())
            resource::Manager::Get().NotifyQuit();
        
        _Config.Save();
        
        if (_Clock!=NULL)
            COFFEE_Delete(_Clock);

        while (_RootModule->GetChildCount()>0)
        {
            int32 size = _RootModule->GetChildCount();
            Module* module((Module*)&_RootModule->GetChild(size-1));
            COFFEE_SendEvent(*module, MODULE_EVENT_Kill, Module);
            while ((int32)_RootModule->GetChildCount()>=size)
            {
                // Requires to update cause of modal windows!
                if (ui::WindowManager::IsInstantiated() && ui::WindowManager::Get().IsModuleAvailable())
                    ui::WindowManager::Get().Update(basic::Time(1.0f));
                if (!module->IsThreadRunning())
                    module->Update(basic::Time(1.0f));
            }
        }
        _RootModule->Destroy();
    }

    //--------------------------------------------------------------------------------------------//

    void ModuleManager::_WaitRegistering()
    {
        do
        {
            _ModuleRegisterationWaiting = false;
            _RootModule->ExecuteMethod(&_CheckModuleRegisteration);
            _RootModule->Update(basic::Time());
        } while(_ModuleRegisterationWaiting);
    }

    //--------------------------------------------------------------------------------------------//

    void ModuleManager::_CheckModuleRegisteration(Module & module, void * data)
    {
        if(module.GetState() != MODULE_STATE_Stopped || !module.IsQueueEmpty())
            _ModuleRegisterationWaiting = true;
    }

    //-VARIABLES----------------------------------------------------------------------------------//

    bool ModuleManager::_ModuleRegisterationWaiting = false;
}
}
