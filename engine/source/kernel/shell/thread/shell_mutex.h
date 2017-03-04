#ifndef _COFFEE_SHELL_THREAD_MUTEX_H_
#define _COFFEE_SHELL_THREAD_MUTEX_H_

#include "coffee_includes.h"

namespace coffee
{
namespace shell
{
    //--------------------------------------------------------------------------------------------//
    /// Mutex
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Mutex
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Mutex();
        ~Mutex();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Lock();
        void Unlock();

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _PlatformCreate();
        void _PlatformDestroy();
        void _PlatformLock();
        void _PlatformUnlock();

        #include "kernel/shell/thread/shell_mutex_windows.h"
    };
}
}
#endif
