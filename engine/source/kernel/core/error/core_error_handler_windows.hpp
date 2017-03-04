#ifdef COFFEE_OS_WINDOWS

#include "kernel/basic/alpha/string/basic_string.h"
#include "kernel/basic/time/basic_date.h"

namespace coffee
{
namespace core
{
    //-OPERATIONS---------------------------------------------------------------------------------//
    
    void ErrorHandler::_PlatformInitialize()
    {
        _DebugLibrary = LoadLibrary("DBGHELP.DLL");
        _MiniDumpWriteDump = (MINIDUMP_WRITE_DUMP)GetProcAddress(_DebugLibrary, "MiniDumpWriteDump");
    }

    //--------------------------------------------------------------------------------------------//

    void ErrorHandler::_PlatformFinalize()
    {
        FreeLibrary(_DebugLibrary);
    }

    //--------------------------------------------------------------------------------------------//

    void ErrorHandler::_PlatformHandle(const Error& error)
    {
        #ifdef COFFEE_DEBUG
            #ifdef COFFEE_COMPILER_MINGW        
                raise(SIGINT);
            #endif
            #ifdef COFFEE_COMPILER_MSVC2008
                DebugBreak();
            #endif
            #ifdef COFFEE_COMPILER_MSVC2010
                DebugBreak();
            #endif
        #endif

        _GenerateMiniDump();
        exit(0);
    }

    //--------------------------------------------------------------------------------------------//

    void ErrorHandler::_GenerateMiniDump()
    {
        if (_MiniDumpWriteDump==NULL)
	        return;

	    HANDLE dump_file;
	    CHAR dump_path[MAX_PATH];
        GetModuleFileName(NULL, dump_path, sizeof(dump_path));

        basic::String file_path = dump_path;
        file_path -= 4;
        basic::Date date;
        file_path += basic::String("_%.4d-%.2d-%.2d_%.2d-%.2d-%.2d",
            date._Year, date._Month, date._Day, date._Hour, date._Minute, date._Second);
        file_path += ".dmp";

	    dump_file = CreateFile(file_path.GetBuffer(),
		    GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	    _MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), dump_file,
		    MiniDumpNormal, NULL, NULL, NULL);
	    CloseHandle(dump_file);
    }

}
}
#endif
