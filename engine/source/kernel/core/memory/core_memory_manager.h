#ifndef _COFFEE_CORE_MEMORY_MANAGER_H_
#define _COFFEE_CORE_MEMORY_MANAGER_H_

#include "coffee_includes.h"
#include "kernel/core/memory/core_allocator.h"

namespace coffee
{
namespace core
{
    //--------------------------------------------------------------------------------------------//
    /// Memory manager
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API MemoryManager
    {
        COFFEE_DeclareSingleton(MemoryManager);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        MemoryManager();
        ~MemoryManager();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void* Allocate(ulong size, const char* file=NULL, uint32 line=0);
        void* Reallocate(void* location, ulong size, const char* file=NULL, uint32 line=0);
        void Free(void* location, const char* file=NULL, uint32 line=0);
        ulong GetSize(void* location);
        void Set(void* location, int32 value, ulong size);
        void Copy(void* location_out, const void* location_in, ulong size);
        int32 Compare(const void* location_one, const void* location_two, ulong size);

    private:

        //-TYPES----------------------------------------------------------------------------------//

        struct _Allocation
        {
            void* Location;
            ulong Size;
            char* Filename;
            uint32 Line;
        };

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _LogState();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Allocator* _Allocator;
        ulong _MemoryUsage;
        ulong _MemoryPeak;
        ulong _AllocationCount;
        _Allocation* _Allocations;
        ulong _AllocationSize;
    };
}
}
#endif
