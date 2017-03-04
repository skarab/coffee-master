#include "kernel/shell/thread/shell_thread.h"
#include "kernel/shell/thread/shell_thread_windows.hpp"

namespace coffee
{
namespace shell
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Thread::Thread() :
        _Owner(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Thread::~Thread()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const meta::Object & Thread::GetOwner() const
    {
        return *_Owner;
    }

    //--------------------------------------------------------------------------------------------//

    meta::Object & Thread::GetOwner()
    {
        return *_Owner;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool Thread::IsRunning() const
    {
        return (_Owner != NULL);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Thread::Start(meta::Object& owner, void (* threaded_method)(meta::Object *))
    {
        _Owner = &owner;
        _ThreadedMethod = threaded_method;
        _PlatformStart();
    }

    //--------------------------------------------------------------------------------------------//

    void Thread::Stop(bool it_has_to_wait)
    {
        _PlatformStop(it_has_to_wait);
    }

    //--------------------------------------------------------------------------------------------//

    void Thread::CallThreadedMethod()
    {
        (*_ThreadedMethod)(_Owner);
    }

    //--------------------------------------------------------------------------------------------//

    void Thread::NotifyStop()
    {
        _Owner = NULL;
    }

}
}
