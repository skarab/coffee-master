#include "kernel/core/log/core_log.h"
#include "kernel/core/error/core_error.h"
#include "kernel/shell/thread/shell_mutex.h"
#include "coffee.h"

namespace coffee
{
namespace core
{
    //-VARIABLES----------------------------------------------------------------------------------//

    shell::Mutex _LogMutex;

    //-META---------------------------------------------------------------------------------------//

    COFFEE_ImplementSingleton(Log);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Log::Log()
    {
        COFFEE_CreateSingleton(Log);

        char filename[2048];
        strcpy(filename, Engine::Get().GetApplicationPath());
        strcpy(filename+strlen(filename), "/");
        strcpy(filename+strlen(filename), Engine::Get().GetApplicationName());
        strcpy(filename+strlen(filename), ".log");

        _File = fopen(filename, "wt");
    }

    //--------------------------------------------------------------------------------------------//

    Log::~Log()
    {
        _Close();
        COFFEE_DestroySingleton(Log);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Log::Write(Type type, const char* text, ...)
    {
        _LogMutex.Lock();

        va_list va_array;
        char line[4096];
        va_start(va_array, text);
            _vsnprintf(line, 4096, text, va_array);
        va_end(va_array);

        if (_File!=NULL)
            fprintf(_File, "%s\n", line);

        // Note: it displays the text in the IDE output window if supported.
        #ifdef COFFEE_OS_WINDOWS
            char output[4096];
            _snprintf(output, 4096, "%s\n", line);
            OutputDebugString(output);
        #endif

        if (type!=FatalError && Application::IsAvailable() && Application::Get().IsRunning())
            Application::Get().OnLog(type, line);
        
        _LogMutex.Unlock();
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Log::_Close()
    {
        if (_File!=NULL)
        {
            fclose(_File);
            _File = NULL;
        }
    }

}
}
