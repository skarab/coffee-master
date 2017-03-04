#ifndef _COFFEE_SHELL_THREAD_H_
#define _COFFEE_SHELL_THREAD_H_

#include "coffee_includes.h"
#include "kernel/meta/meta.h"
#include "kernel/shell/thread/shell_mutex.h"
#include "kernel/shell/thread/shell_locker.h"
#include "kernel/shell/thread/shell_threaded_object.h"

namespace coffee
{
namespace shell
{
    //--------------------------------------------------------------------------------------------//
    /// Thread class
    ///
    /// It manages a thread which belongs to a meta::Object.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Thread
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Thread();
        ~Thread();

        //-ACCESSORS------------------------------------------------------------------------------//

        const meta::Object& GetOwner() const;
        meta::Object& GetOwner();

        //-QUERIES--------------------------------------------------------------------------------//

        bool IsRunning() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Start(meta::Object& owner, void (*threaded_method)(meta::Object*));
        void Stop(bool it_has_to_wait=false);
        void CallThreadedMethod();
        void NotifyStop();
        void SetName(basic::String name);

        //-FUNCTIONS------------------------------------------------------------------------------//

        static void Sleep();
        static void SetMainThreadName(basic::String name);
        static bool IsMainThread();

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _PlatformStart();
        void _PlatformStop(bool it_has_to_wait);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        meta::Object * _Owner;
        void (* _ThreadedMethod)(meta::Object *);

        #include "kernel/shell/thread/shell_thread_windows.h"
    };
}
}
#endif
