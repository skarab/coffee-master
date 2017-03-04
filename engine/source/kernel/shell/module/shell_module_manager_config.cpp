#include "kernel/shell/module/shell_module_manager_config.h"
#include "kernel/shell/module/shell_module_manager.h"
#include "kernel/storage/storage.h"
#include "coffee.h"

namespace coffee
{
namespace shell
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_ImplementSingleton(ModuleManagerConfig);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ModuleManagerConfig::ModuleManagerConfig()
    {
        COFFEE_CreateSingleton(ModuleManagerConfig);
        _FilePath = basic::String("/root/")+Engine::Get().GetApplicationName()+".config";
    }

    //--------------------------------------------------------------------------------------------//

    ModuleManagerConfig::~ModuleManagerConfig()
    {
        COFFEE_DestroySingleton(ModuleManagerConfig);
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void ModuleManagerConfig::SetFilePath(const storage::Path& file_path)
    {
        _FilePath = file_path;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ModuleManagerConfig::Load()
    {
        if (!storage::System::Get().HasPath(_FilePath))
        {
            ModuleManager::Get().GetRootModule().ExecuteMethod(&_ModuleSetDefaultConfig);
            Save();
        }
        else
        {
            meta::Stream stream;
            stream.Open(_FilePath, storage::MODE_Input);
            ModuleManager::Get().GetRootModule().ExecuteMethod(&_SerializeModule, &stream);
            stream.Close();
        }
    }

    //--------------------------------------------------------------------------------------------//

    void ModuleManagerConfig::Save()
    {
        meta::Stream stream;
        stream.Open(_FilePath, storage::MODE_Output);
        ModuleManager::Get().GetRootModule().ExecuteMethod(&_SerializeModule, &stream);
        stream.Close();
    }

    //--------------------------------------------------------------------------------------------//

    bool ModuleManagerConfig::Configure()
    {
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    void ModuleManagerConfig::_SerializeModule(Module& module, void* data)
    {
        if (module.HasConfig())
        {
            meta::Serializer* serializer = COFFEE_New(meta::Serializer);
            serializer->Serialize(module.GetConfig(), *((meta::Stream*)data));
            COFFEE_Delete(serializer);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void ModuleManagerConfig::_ModuleSetDefaultConfig(Module& module, void* data)
    {
        if (module.HasConfig())
            module.GetConfig().SetDefaults();
    }

}
}
