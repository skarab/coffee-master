#ifndef _COFFEE_RESOURCE_HANDLER_STATE_H_
#define _COFFEE_RESOURCE_HANDLER_STATE_H_

#include "coffee_includes.h"

namespace coffee
{
namespace resource
{
    //--------------------------------------------------------------------------------------------//
    /// Resource handler states
    ///
    /// @see coffee::resource::Handler
    //--------------------------------------------------------------------------------------------//
    enum HANDLER_STATE
    {
        HANDLER_STATE_Null,
        HANDLER_STATE_BeginLoading,
        HANDLER_STATE_Loading,
        HANDLER_STATE_EndLoading,
        HANDLER_STATE_Ready,
        HANDLER_STATE_Invalid
    };
}
}
#endif
