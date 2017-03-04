#ifndef _COFFEE_CORE_ALLOCATOR_DEFAULT_H_
#define _COFFEE_CORE_ALLOCATOR_DEFAULT_H_

#include "coffee_includes.h"
#include "kernel/core/memory/core_allocator.h"

namespace coffee
{
namespace core
{
    //--------------------------------------------------------------------------------------------//
    /// Default allocator
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API AllocatorDefault : public Allocator
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        AllocatorDefault();
        ~AllocatorDefault();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void* Allocate(ulong size);
        void* Reallocate(void* location, ulong size);
        void Free(void* location);
        ulong GetSize(void* location);
    };
}
}
#endif
