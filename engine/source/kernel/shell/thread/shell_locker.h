#ifndef _COFFEE_SHELL_THREAD_LOCKER_H_
#define _COFFEE_SHELL_THREAD_LOCKER_H_

#include "coffee_includes.h"
#include "kernel/shell/thread/shell_mutex.h"

namespace coffee
{
namespace shell
{
    //--------------------------------------------------------------------------------------------//
    /// Lock a mutex in a scope
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Locker
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Locker(Mutex& mutex);
        ~Locker();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//
        
        Mutex* _Mutex;
    };
}
}
#endif
