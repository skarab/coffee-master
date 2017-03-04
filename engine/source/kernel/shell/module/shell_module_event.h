#ifndef _COFFEE_SHELL_MODULE_EVENT_H_
#define _COFFEE_SHELL_MODULE_EVENT_H_

#include "coffee_includes.h"

namespace coffee
{
namespace shell
{
    //--------------------------------------------------------------------------------------------//
    /// Module events
    //--------------------------------------------------------------------------------------------//
    enum MODULE_EVENT
    {
        MODULE_EVENT_Register,      ///< register event
        MODULE_EVENT_Unregister,    ///< unregister event
        MODULE_EVENT_Start,         ///< start event
        MODULE_EVENT_Stop,          ///< stop event
        MODULE_EVENT_Sleep,         ///< pause event
        MODULE_EVENT_Kill           ///< destroy event
    };
}
}
#endif
