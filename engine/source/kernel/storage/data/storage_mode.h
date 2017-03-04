#ifndef _COFFEE_STORAGE_MODE_H_
#define _COFFEE_STORAGE_MODE_H_

#include "coffee_includes.h"

namespace coffee
{
namespace storage
{
    //--------------------------------------------------------------------------------------------//
    /// Access modes
    //--------------------------------------------------------------------------------------------//
    enum MODE
    {
        MODE_None = 0,     ///< invalid
        MODE_Input = 1,    ///< input access mode
        MODE_Output = 2    ///< output access mode
    };
}
}
#endif
