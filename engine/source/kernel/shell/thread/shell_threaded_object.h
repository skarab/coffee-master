#ifndef _COFFEE_SHELL_THREADED_OBJECT_H_
#define _COFFEE_SHELL_THREADED_OBJECT_H_

#include "coffee_includes.h"
#include "kernel/shell/thread/shell_mutex.h"
#include "kernel/shell/thread/shell_threaded_object_template.h"

namespace coffee
{
namespace shell
{
    //--------------------------------------------------------------------------------------------//
    /// Threaded object
    ///
    /// It defines an object accessor, which is thread-safe.
    /// It's an easy way to add an attribute in a class which can be accessed from everywhere.
    /// Usage is to Lock it before getting the access using Get, and UnLock it after.
    //--------------------------------------------------------------------------------------------//
    template< class type > \
    class COFFEE_TEMPLATE_API ThreadedObject
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ThreadedObject();
        ~ThreadedObject();

        //-ACCESSORS------------------------------------------------------------------------------//

        const type& Get() const;
        type& Get();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Lock();
        void Unlock();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        type _Object;
        Mutex _Mutex;
        bool _ItIsLocked;
    };

    #include "kernel/shell/thread/shell_threaded_object.hpp"
}
}
#endif
