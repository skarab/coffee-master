#ifdef COFFEE_OS_WINDOWS

#include "kernel/basic/time/basic_date.h"
#include "kernel/basic/alpha/string/basic_string.h"
#include "kernel/basic/alpha/text/basic_text.h"
#include "kernel/shell/thread/shell_thread.h"
#include "system/input/mouse/input_mouse.h"

namespace coffee
{
namespace core
{
    //-ACCESSORS----------------------------------------------------------------------------------//

    HINSTANCE Platform::GetDllInstance()
    {
        return _DllInstance;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    real Platform::GetTime() const
    {
        if (_ItHasPerformanceTimerEnabled)
        {
            LARGE_INTEGER performance_time;
            ::QueryPerformanceCounter(&performance_time);
            return real(real64(performance_time.QuadPart - _TimeStart.QuadPart)
                / _PerformanceTimePerSecond);
        }
        return GetTickCount() * 0.001f - _TickCountStart;
    }

    //--------------------------------------------------------------------------------------------//

    void Platform::GetDate(basic::Date& date) const
    {
        SYSTEMTIME system_date;
        GetSystemTime(&system_date);
        ConvertDate(date, system_date);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Platform::ConvertDate(basic::Date& date, const SYSTEMTIME& system_date) const
    {
        date._Year = system_date.wYear;
        date._Month = system_date.wMonth;
        date._DayOfWeek = system_date.wDayOfWeek;
        date._Day = system_date.wDay;
        date._Hour = system_date.wHour;
        date._Minute = system_date.wMinute;
        date._Second = system_date.wSecond;
        date._Millisecond = system_date.wMilliseconds;
    }

    //--------------------------------------------------------------------------------------------//

    bool Platform::Launch(const basic::String& executable_path, const basic::String& parameters,
        const basic::String& work_folder)
    {
        SHELLEXECUTEINFO info;    
        memset(&info, 0, sizeof(info));            
        info.cbSize = sizeof(info);
        info.lpVerb = "open";
        info.lpFile = executable_path.GetBuffer();
        info.lpParameters = parameters.GetBuffer();
        info.lpDirectory = work_folder.GetBuffer();
        info.nShow = SW_SHOW;
        info.hInstApp = 0;

        if (ShellExecuteEx(&info)==FALSE)
            return false;

        return true;
    }
    
    //--------------------------------------------------------------------------------------------//

    bool Platform::Run(const basic::String& command, const basic::String& work_folder)
    {
        return RunPipe(command, work_folder, true, false);
    }
    
    //--------------------------------------------------------------------------------------------//

    bool Platform::RunPipe(const basic::String& command, const basic::String& work_folder,
        bool it_has_to_wait, bool it_has_to_show)
    {
        GetPipeOutput();
        _PipeCode = -1;

        COFFEE_Assert(_PipeRead==NULL && _PipeWrite==NULL,
            core::ERROR_CODE_IncorrectUsage, "Can't launch more than one pipe command.");

        SECURITY_ATTRIBUTES attr;
        attr.nLength = sizeof(SECURITY_ATTRIBUTES); 
        attr.bInheritHandle = TRUE; 
        attr.lpSecurityDescriptor = NULL; 

        if (!CreatePipe(&_PipeRead, &_PipeWrite, &attr, 0))
            return false;

        ZeroMemory(&_PipeProcess, sizeof(PROCESS_INFORMATION));

        STARTUPINFO startup_info;
        ZeroMemory(&startup_info, sizeof(STARTUPINFO));
        startup_info.cb = sizeof(STARTUPINFO);
        startup_info.hStdOutput = _PipeWrite;
        startup_info.dwFlags |= STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
        startup_info.wShowWindow = it_has_to_show?SW_SHOW:SW_HIDE;

        basic::String cmd = command;
        cmd.Replace("\\", "/");
        basic::String wrk = work_folder;
        wrk.Replace("\\", "/");

        if (!CreateProcess(NULL, (char*)cmd.GetBuffer(), NULL, NULL, TRUE, 0, NULL, wrk.GetBuffer(),
            &startup_info, &_PipeProcess))
        {
            CloseHandle(_PipeRead);
            CloseHandle(_PipeWrite);
            _PipeRead = NULL;
            _PipeWrite = NULL;
            return false;
        }

        _PipeThread->Start(*(meta::Object*)this, &_PipeUpdate);

        if (it_has_to_wait)
        {
            while (_PipeThread->IsRunning())
                shell::Thread::Sleep();
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Platform::IsPipeRunning() const
    {
        return _PipeRead!=NULL;
    }

    //--------------------------------------------------------------------------------------------//

    basic::String Platform::GetPipeOutput()
    {
        basic::String output;
        _PipeMutex->Lock();
        output = *_PipeOutput;
        _PipeOutput->SetEmpty();
        _PipeMutex->Unlock();
        output.Replace("%", "%%");
        return output;
    }

    //--------------------------------------------------------------------------------------------//

    uint32 Platform::GetPipeReturnCode()
    {
        return _PipeCode;
    }
        
    //--------------------------------------------------------------------------------------------//

    static bool _HasToExit = false;

    void _KillProcess(DWORD process_id)
    {
        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, process_id);
        PROCESSENTRY32 process;
        ZeroMemory(&process, sizeof(process));
        process.dwSize = sizeof(process);
        Process32First(snapshot, &process);
        do
        {
            if (process.th32ParentProcessID==process_id)
                _KillProcess(process.th32ProcessID);
        } while (Process32Next(snapshot, &process));

        HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, process_id);
        if (handle)
        {
            TerminateProcess(handle, 0);
            CloseHandle(handle);

            DWORD code;
            if (GetExitCodeProcess(handle, &code) && code==STILL_ACTIVE)
                _KillProcess(process_id);
        }     
    }

    void Platform::StopPipe()
    {
        if (_PipeRead!=NULL && _PipeThread->IsRunning())
        {
            _HasToExit = true;
            while (_PipeThread->IsRunning())
                shell::Thread::Sleep();
            _HasToExit = false;
            _KillProcess(_PipeProcess.dwProcessId);            
        }
    }

    //--------------------------------------------------------------------------------------------//

    bool Platform::AskForFile(basic::String& path, const basic::Text& extensions)
    {
        input::Mouse::Get().ShowMouseCursor(true);

        // generate extensions string
        basic::String ext;
        for (uint32 i=0 ; i<extensions.GetLineCount()/2 ; ++i)
        {
            ext += extensions.GetLine(i*2);
            ext += 'a';
            ext.GetBuffer()[ext.GetLength()-1] = '\0';
            ext += extensions.GetLine(i*2+1);
            ext += 'a';
            ext.GetBuffer()[ext.GetLength()-1] = '\0';
            
        }
        ext += 'a';
        ext.GetBuffer()[ext.GetLength()-1] = '\0';

        // prepare filepath
        char filepath[MAX_PATH+1];
        filepath[0] = '\0';

        // initialize windows struct
        OPENFILENAME str;
        memset(&str, 0, sizeof(OPENFILENAME));
        str.lStructSize = sizeof(OPENFILENAME);
        str.lpstrFile = filepath;
        str.nMaxFile = MAX_PATH;
        str.lpstrFilter = ext.GetBuffer();
        str.nFilterIndex = 0;
        str.lpstrFileTitle = NULL;
        str.nMaxFileTitle = 0;
        str.lpstrInitialDir = NULL;
        str.Flags = OFN_NOCHANGEDIR | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

        // launch the windows dialog
        if (GetOpenFileName(&str))
        {
            path = filepath;
            return true;
        }
        return false;
    }
    
    //-FUNCTIONS----------------------------------------------------------------------------------//

    void Platform::_PipeUpdate(meta::Object* platform)
    {
        Platform* me = (Platform*)platform;
        DWORD code;
        bool it_is_running = GetExitCodeProcess(me->_PipeProcess.hProcess, &code)
            && (code==STILL_ACTIVE);

        char buffer[128];
        DWORD size;
        DWORD dw;
        PeekNamedPipe(me->_PipeRead, NULL, 0, NULL, &dw, NULL);
        if (dw!=0 && ReadFile(me->_PipeRead, buffer, 127, &size, NULL))
        {
            buffer[size] = '\0';
            me->_PipeMutex->Lock();
            *me->_PipeOutput += buffer;
            me->_PipeMutex->Unlock();
        }

        if (!it_is_running || _HasToExit)
        {
            me->_PipeCode = code;
            CloseHandle(me->_PipeRead);
            CloseHandle(me->_PipeWrite);
            CloseHandle(me->_PipeProcess.hProcess);
            CloseHandle(me->_PipeProcess.hThread);
            me->_PipeThread->Stop(); 
            me->_PipeRead = NULL;
            me->_PipeWrite = NULL;
        }
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Platform::_Initialize()
    {
        LARGE_INTEGER performance_time_per_second;

        _DllInstance = GetModuleHandle("engine.dll");

        if(::QueryPerformanceFrequency(&performance_time_per_second) == 0
            || ::QueryPerformanceCounter(&_TimeStart) == 0
           )
        {
            _ItHasPerformanceTimerEnabled = false;
            _TickCountStart = GetTickCount() * 0.001f;
        }
        else
        {
            _ItHasPerformanceTimerEnabled = true;
            _PerformanceTimePerSecond = real64(performance_time_per_second.QuadPart);
        }

        _PipeCode = -1;
        _PipeThread = COFFEE_New(shell::Thread);
        _PipeMutex = COFFEE_New(shell::Mutex);
        _PipeOutput = COFFEE_New(basic::String);
        _PipeRead = NULL;
        _PipeWrite = NULL;

        timeBeginPeriod(1);

        _LogPlatform();
    }

    //--------------------------------------------------------------------------------------------//

    void Platform::_Finalize()
    {
        StopPipe();
        COFFEE_Delete(_PipeThread);
        COFFEE_Delete(_PipeMutex);
        COFFEE_Delete(_PipeOutput);

        timeEndPeriod(1);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Platform::_LogPlatform()
    {
        OSVERSIONINFOEX	V = {sizeof(OSVERSIONINFOEX)};	//EX for NT 5.0 and later

	    if (!GetVersionEx((POSVERSIONINFO)&V))
	    {
		    ZeroMemory(&V, sizeof(V));
		    V.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		    GetVersionEx((POSVERSIONINFO)&V);
	    }

	    if (V.dwPlatformId != VER_PLATFORM_WIN32_NT)
        {
		    V.dwBuildNumber = LOWORD(V.dwBuildNumber);	//for 9x HIWORD(dwBuildNumber) = 0x04xx
        }

        COFFEE_Log(core::Log::None, "Windows:  %d.%d.%d, Service pack %d.%d, Product Type %d",
		    V.dwMajorVersion, V.dwMinorVersion, V.dwBuildNumber, V.wServicePackMajor,
            V.wServicePackMinor, V.wProductType);
    }

}
}
#endif
