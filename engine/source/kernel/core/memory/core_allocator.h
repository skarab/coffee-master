#ifndef _COFFEE_CORE_ALLOCATOR_H_
#define _COFFEE_CORE_ALLOCATOR_H_

#include "coffee_includes.h"

namespace coffee
{
namespace core
{
    //--------------------------------------------------------------------------------------------//
    /// Allocator interface
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Allocator
    {
    public:

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void* Allocate(ulong size) = 0;
        virtual void* Reallocate(void* location, ulong size) = 0;
        virtual void Free(void* location) = 0;
        virtual ulong GetSize(void* location) = 0;
    };
}
}
#endif
