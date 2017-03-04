#include "coffee.h"
#include "kernel/core/memory/core_allocator_default.h"

namespace coffee
{
namespace core
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    AllocatorDefault::AllocatorDefault()
    {
    }

    //--------------------------------------------------------------------------------------------//

    AllocatorDefault::~AllocatorDefault()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void* AllocatorDefault::Allocate(ulong size)
    {
        return malloc(size);
    }

    //--------------------------------------------------------------------------------------------//

    void* AllocatorDefault::Reallocate(void* location, ulong size)
    {
        return realloc(location, size);
    }

    //--------------------------------------------------------------------------------------------//

    void AllocatorDefault::Free(void* location)
    {
        free(location);
    }

    //--------------------------------------------------------------------------------------------//

    ulong AllocatorDefault::GetSize(void* location)
    {
        return (ulong)_msize(location);
    }

}
}
