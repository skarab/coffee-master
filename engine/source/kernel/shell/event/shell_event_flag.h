#ifndef _COFFEE_SHELL_EVENT_FLAG_H_
#define _COFFEE_SHELL_EVENT_FLAG_H_

#include "coffee_includes.h"

namespace coffee
{
namespace shell
{
    //--------------------------------------------------------------------------------------------//
    /// Event flags
    ///
    /// @see coffee::shell::EventHandler
    //--------------------------------------------------------------------------------------------//
    enum EVENT_FLAG
    {
        EVENT_FLAG_StopWhenHandled = 1<<0,      ///< event is stopped when an handler method returns true
        EVENT_FLAG_Immediate = 1<<1,            ///< event is dispatched immediately instead of forwarded
        EVENT_FLAG_ForwardToChildren = 1<<2,    ///< event is forwarded from parent to children
        EVENT_FLAG_ForwardToParent = 1<<3       ///< event is forwarded from child to parent
    };

}    
}
#endif
