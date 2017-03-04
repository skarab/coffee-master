#ifndef _COFFEE_CORE_PROCESSOR_TYPE_H_
#define _COFFEE_CORE_PROCESSOR_TYPE_H_

#include "coffee_includes.h"

namespace coffee
{
namespace core
{
    //--------------------------------------------------------------------------------------------//
    /// Processor types
    ///
    /// @see coffee::core::Processor
    //--------------------------------------------------------------------------------------------//
    enum PROCESSOR_TYPE
    {
        PROCESSOR_TYPE_Generic      = 0,        ///< Default value
        PROCESSOR_TYPE_Unsupported  = 1 << 0,   ///< Unsupported processor detected
        PROCESSOR_TYPE_Intel        = 1 << 1,   ///< Intel processor detected
        PROCESSOR_TYPE_Amd          = 1 << 2,   ///< Amd processor detected
        PROCESSOR_TYPE_Mmx          = 1 << 3,   ///< Mmx instruction set support
        PROCESSOR_TYPE_3dNow        = 1 << 4    ///< 3dNow instruction set support
    };
}
}
#endif
