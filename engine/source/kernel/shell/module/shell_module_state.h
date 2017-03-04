#ifndef _COFFEE_SHELL_MODULE_STATE_H_
#define _COFFEE_SHELL_MODULE_STATE_H_

#include "coffee_includes.h"

namespace coffee
{
namespace shell
{
    //--------------------------------------------------------------------------------------------//
    /// Module states
    //--------------------------------------------------------------------------------------------//
    enum MODULE_STATE
    {
        MODULE_STATE_Stopped,       ///< module is stopped
        MODULE_STATE_Sleeping,      ///< module is paused
        MODULE_STATE_Running,       ///< module is running
        MODULE_STATE_Unregistered,  ///< module is not registered
        MODULE_STATE_Destroyed      ///< module is destroyed
    };
}
}
#endif
