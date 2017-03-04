#ifndef _COFFEE_SHELL_MODULE_MANAGER_CONFIG_H_
#define _COFFEE_SHELL_MODULE_MANAGER_CONFIG_H_

#include "coffee_includes.h"
#include "kernel/meta/meta.h"
#include "kernel/shell/module/shell_module.h"
#include "kernel/storage/logical/storage_path.h"

namespace coffee
{
namespace shell
{
    //--------------------------------------------------------------------------------------------//
    /// Aggregates the config of all modules
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ModuleManagerConfig
    {
        COFFEE_DeclareSingleton(ModuleManagerConfig);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ModuleManagerConfig();
        virtual ~ModuleManagerConfig();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetFilePath(const storage::Path& file_path);

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Load();
        void Save();
        virtual bool Configure();

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        static void _SerializeModule(Module& module, void* data);
        static void _ModuleSetDefaultConfig(Module& module, void* data);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        storage::Path _FilePath;
    };
}
}
#endif
