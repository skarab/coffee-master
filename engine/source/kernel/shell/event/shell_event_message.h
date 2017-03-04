#ifndef _COFFEE_SHELL_EVENT_MESSAGE_H_
#define _COFFEE_SHELL_EVENT_MESSAGE_H_

#include "coffee_includes.h"

namespace coffee
{
namespace shell
{
    //--------------------------------------------------------------------------------------------//
    /// Event messages
    ///
    /// @see coffee::shell::EventHandler
    //--------------------------------------------------------------------------------------------//
    enum EVENT_MESSAGE
    {
        EVENT_MESSAGE_Enable,       ///< Enable/Disable handler
        EVENT_MESSAGE_Destroyed     ///< sent to parent before the handler become deleted
                                    ///  note than at this time ItIsDestroyed is already true.
    };
}
}
#endif
