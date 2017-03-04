#include "coffee.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_ImplementSingleton(Engine);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Engine::Engine(const char* command_line, uint32 modes) :
        _Modes(modes),
        _ItHasToQuit(false)
    {
        COFFEE_CreateSingleton(Engine);

        _ParseApplicationParameters(command_line);

        _Log = COFFEE_New(core::Log);
        _Log->Write(core::Log::None, "Coffee started");
        _Processor = COFFEE_New(core::Processor);
        _MemoryManager = new core::MemoryManager();
        _Platform = COFFEE_New(core::Platform);
        _Meta = COFFEE_New(meta::Types);
        _PhysicalSystem = COFFEE_New(storage::PhysicalSystem);
        _System = COFFEE_New(storage::System);
        _ModuleManager = COFFEE_New(shell::ModuleManager);

        if (!HasMode(RUN_MODE_UnitTest))
        {
            #include "coffee_modules.hpp"
        }

        shell::ModuleManager::Get().Start();
    }

    //--------------------------------------------------------------------------------------------//

    Engine::~Engine()
    {
        COFFEE_Delete(_ModuleManager);
        COFFEE_Delete(_System);
        COFFEE_Delete(_PhysicalSystem);
        COFFEE_Delete(_Meta);
        COFFEE_Delete(_Platform);
        delete _MemoryManager;
        COFFEE_Delete(_Processor);
        _Log->Write(core::Log::None, "Coffee stopped");
        COFFEE_Delete(_Log);
        COFFEE_DestroySingleton(Engine);
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool Engine::HasMode(const RUN_MODE& mode) const
    {
        return (_Modes&(uint32)mode)>0;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool Engine::Update()
    {
        if (_ItHasToQuit)
            return false;

        _ModuleManager->Update();        
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    void Engine::Quit()
    {
        _Log->Write(core::Log::None, "Quit requested");
        _ItHasToQuit = true;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Engine::_ParseApplicationParameters(const char* command_line)
    {
        const char* end_path1 = strrchr(command_line, '/');
        const char* end_path2 = strrchr(command_line, '\\');
        size_t size1 = end_path1==NULL?0:(size_t)(end_path1-command_line);
        size_t size2 = end_path2==NULL?0:(size_t)(end_path2-command_line);
        size_t path_length = Maximum(size1, size2);
        if (path_length==0)
        {
            GetCurrentDirectory(2048, _ApplicationPath);
        }
        else
        {
            strncpy(_ApplicationPath, command_line[0]=='"'?command_line+1:command_line, path_length);        
            _ApplicationPath[command_line[0]=='"'?path_length-1:path_length] = '\0';
        }

        const char* dot = strrchr(command_line, '.');
        COFFEE_Assert(dot!=NULL, core::ERROR_CODE_Unexpected, "Failed to parse command line");
        size_t name_size = (size_t)(dot-command_line-path_length-(path_length>0?1:0));
        strncpy(_ApplicationName, command_line+path_length+(path_length>0?1:0), name_size);
        _ApplicationName[name_size] = '\0';
    }

}
