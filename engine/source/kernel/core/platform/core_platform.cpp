#include "kernel/core/error/core_error.h"
#include "kernel/core/log/core_log.h"
#include "kernel/core/platform/core_platform.h"
#include "kernel/core/platform/core_platform_unix.hpp"
#include "kernel/core/platform/core_platform_windows.hpp"
#include "kernel/basic/alpha/string/basic_string.h"
#include "kernel/storage/physical/storage_physical_system.h"

namespace coffee
{
namespace core
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_ImplementSingleton(Platform);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Platform::Platform()
    {
        COFFEE_CreateSingleton(Platform);
        _Initialize();
    }

    //--------------------------------------------------------------------------------------------//

    Platform::~Platform()
    {
        _Finalize();
        COFFEE_DestroySingleton(Platform);
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool Platform::GetBuildTargets(basic::String& platform, basic::String& compiler, basic::String& mode) const
    {
        const storage::PhysicalPath& build_path = storage::PhysicalSystem::Get().GetRootFolder();
        uint32 i = build_path.FindLast('/');
        if (i!=NONE)
        {
            basic::String build_informations = build_path.GetRight(build_path.GetLength()-i-1);
            int32 index = NONE;
            if (build_informations.GetNextWord(platform, index, '-')
                && build_informations.GetNextWord(compiler, index, '-')
                && build_informations.GetNextWord(mode, index, '-'))
            {
                return true;
            }
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    basic::String Platform::GetBuildPlatform() const
    {
        basic::String platform, compiler, mode;
        if (GetBuildTargets(platform, compiler, mode))
            return platform;
        return "";
    }

    //--------------------------------------------------------------------------------------------//

    basic::String Platform::GetBuildCompiler() const
    {
        basic::String platform, compiler, mode;
        if (GetBuildTargets(platform, compiler, mode))
            return compiler;
        return "";
    }

    //--------------------------------------------------------------------------------------------//

    basic::String Platform::GetBuildMode() const
    {
        basic::String platform, compiler, mode;
        if (GetBuildTargets(platform, compiler, mode))
            return mode;
        return "";
    }
    
}
}
