#ifndef _COFFEE_SHELL_MODULE_ATTRIBUTE_H_
#define _COFFEE_SHELL_MODULE_ATTRIBUTE_H_

#include "coffee_includes.h"

namespace coffee
{
namespace shell
{
    //--------------------------------------------------------------------------------------------//
    /// Module attributes
    //--------------------------------------------------------------------------------------------//
    enum MODULE_ATTRIBUTE
    {
        MODULE_ATTRIBUTE_Automatic = 1 << 0,        ///< the module is automatically started & stopped
        MODULE_ATTRIBUTE_Manual = 1 << 1,           ///< the module need to be started/stopped manually
        MODULE_ATTRIBUTE_Threaded = 1 << 2,         ///< the module automatically runs in another thread
        MODULE_ATTRIBUTE_FixedTimeStep = 1 << 3,    ///< the module requires a fixed time step update
        MODULE_ATTRIBUTE_Defaults = MODULE_ATTRIBUTE_Automatic
    };
}
}
#endif
