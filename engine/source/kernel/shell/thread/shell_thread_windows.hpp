#ifdef COFFEE_OS_WINDOWS

#include "coffee.h"
#include "process.h"

namespace coffee
{
namespace shell
{
    HANDLE Thread::_MainThreadHandle = 0;
    uint32 Thread::_MainThreadID = 0;
    
    //-FUNCTIONS----------------------------------------------------------------------------------//

    uint32 __stdcall _ThreadWin32(void* arguments);

#ifdef COFFEE_COMPILER_MINGW
    void SetThreadName(uint32 dwThreadID, char* threadName)
    {
    }
#else
    const DWORD MS_VC_EXCEPTION=0x406D1388;

    // SetThreadName coming from http://msdn.microsoft.com/en-us/library/xcb2z8hs.aspx
    #pragma pack(push,8)
    typedef struct tagTHREADNAME_INFO
    {
       DWORD dwType; // Must be 0x1000.
       LPCSTR szName; // Pointer to name (in user addr space).
       DWORD dwThreadID; // Thread ID (-1=caller thread).
       DWORD dwFlags; // Reserved for future use, must be zero.
    } THREADNAME_INFO;
    #pragma pack(pop)

    void SetThreadName(uint32 dwThreadID, char* threadName)
    {
       THREADNAME_INFO info;
       info.dwType = 0x1000;
       info.szName = threadName;
       info.dwThreadID = dwThreadID;
       info.dwFlags = 0;
       __try { RaiseException( MS_VC_EXCEPTION, 0, sizeof(info)/sizeof(ULONG_PTR), (ULONG_PTR*)&info ); }
       __except(EXCEPTION_EXECUTE_HANDLER) {}
    }
#endif

    //-QUERIES------------------------------------------------------------------------------------//

    bool Thread::HasToStop() const
    {
        return _ItHasToStop;
    }

     //-OPERATIONS---------------------------------------------------------------------------------//

    void Thread::SetName(basic::String name)
    {
        SetThreadName(_ThreadID, name.GetBuffer());
    }

    //--------------------------------------------------------------------------------------------//

    void Thread::_PlatformStart()
    {
        _ItHasToStop = false;
        _ThreadHandle = (HANDLE) _beginthreadex(NULL, 0, &_ThreadWin32, this, 0, &_ThreadID);
    }

    //--------------------------------------------------------------------------------------------//

    void Thread::_PlatformStop(bool it_has_to_wait)
    {
        _ItHasToStop = true;

        if (it_has_to_wait)
            WaitForSingleObject(_ThreadHandle, INFINITE);
    }

    //--------------------------------------------------------------------------------------------//

    void Thread::Sleep()
    {
        ::Sleep(1);
    }

    //-FUNCTIONS----------------------------------------------------------------------------------//

    void Thread::SetMainThreadName(basic::String name)
    {
        SetThreadName(-1, name.GetBuffer());
        _MainThreadHandle = GetCurrentThread();
        _MainThreadID = GetCurrentThreadId();
    }

    //--------------------------------------------------------------------------------------------//

    bool Thread::IsMainThread()
    {
        return _MainThreadHandle==GetCurrentThread()
            && _MainThreadID==GetCurrentThreadId();
    }

    //--------------------------------------------------------------------------------------------//

    uint32 __stdcall _ThreadWin32(void * arguments)
    {
        Thread * thread((Thread *) arguments);

        while(!thread->HasToStop())
        {
            thread->CallThreadedMethod();
            thread->Sleep();
        }

        thread->NotifyStop();
        _endthread();

        return 0;
    }

}
}
#endif
