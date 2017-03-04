#include "coffee.h"
#include "kernel/core/memory/core_allocator_default.h"
#include "kernel/core/memory/core_memory_manager.h"
#include "kernel/shell/shell.h"

namespace coffee
{
namespace core
{
    //-VARIABLES----------------------------------------------------------------------------------//

    shell::Mutex _MemoryManager_Mutex;
    
    //-META---------------------------------------------------------------------------------------//

    COFFEE_ImplementSingleton(MemoryManager);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    MemoryManager::MemoryManager() :
        _MemoryUsage(0),
        _MemoryPeak(0),
        _AllocationCount(0),
        _Allocations(NULL),
        _AllocationSize(0)
    {
        _Allocator = COFFEE_New(AllocatorDefault);
        COFFEE_CreateSingleton(MemoryManager);
    }

    //--------------------------------------------------------------------------------------------//

    MemoryManager::~MemoryManager()
    {
        COFFEE_DestroySingleton(MemoryManager);

        if (Engine::Get().HasMode(RUN_MODE_MemoryReport))
        {
            _LogState();
            COFFEE_Assert(_MemoryUsage==0 && _AllocationCount==0, core::ERROR_CODE_Memory, "Memory leak detected.");
        }

        COFFEE_Delete(_Allocator);
        if (_Allocations!=NULL)
            free(_Allocations);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void* MemoryManager::Allocate(ulong size, const char* file, uint32 line)
    {
        if (size==0) return NULL;
        shell::Locker lock(_MemoryManager_Mutex);
        void* location = _Allocator->Allocate(size);
        COFFEE_Assert(location!=NULL, core::ERROR_CODE_Memory, "Memory full.");
        if (Engine::Get().HasMode(RUN_MODE_MemoryReport))
        {
            COFFEE_Assert(size==_Allocator->GetSize(location), core::ERROR_CODE_Memory, "Memory system error.");
            ++_AllocationCount;
            _MemoryUsage += size;
            if (_MemoryUsage>_MemoryPeak)
                _MemoryPeak = _MemoryUsage;

            if (Engine::Get().HasMode(RUN_MODE_MemoryTrack))
            {
                for (ulong i=0 ; i<_AllocationCount-1 ; ++i)
                    COFFEE_Assert(_Allocations[i].Location!=location, core::ERROR_CODE_Memory, "Memory invalid operation.");
            
                ulong real_size = _Allocator->GetSize(location);
                COFFEE_Assert(real_size==size, core::ERROR_CODE_Memory, "Memory full.");
            
                if (_AllocationSize==0)
                {
                    _Allocations = (_Allocation*)malloc(20*sizeof(_Allocation));
                    _AllocationSize = 20;
                }
                else if (_AllocationCount>_AllocationSize)
                {
                    _AllocationSize = _AllocationCount*2;
                    _Allocations = (_Allocation*)realloc(_Allocations, sizeof(_Allocation)*_AllocationSize);
                }

                _Allocation* allocation = &_Allocations[_AllocationCount-1];
                allocation->Location = location;
                allocation->Size = size;

                size_t len = strlen(file)+1;
                allocation->Filename = (char*)malloc(len);
                memcpy(allocation->Filename, file, len);

                allocation->Line = line;
            }
        }
        return location;
    }

    //--------------------------------------------------------------------------------------------//

    void* MemoryManager::Reallocate(void* location, ulong size, const char* file, uint32 line)
    {
        if (location==NULL) return Allocate(size, file, line);
        if (size==0) { Free(location, file, line); return NULL; }
        shell::Locker lock(_MemoryManager_Mutex);

        if (Engine::Get().HasMode(RUN_MODE_MemoryReport))
        {
            ulong old_size = _Allocator->GetSize(location);
            void* new_location = _Allocator->Reallocate(location, size);
            COFFEE_Assert(new_location!=NULL, core::ERROR_CODE_Memory, "Memory full.");
        
            if (size>old_size)
            {
                _MemoryUsage += size-old_size;
                if (_MemoryUsage>_MemoryPeak)
                    _MemoryPeak = _MemoryUsage;
            }
            else
            {
                COFFEE_Assert(_MemoryUsage>=old_size-size, core::ERROR_CODE_Memory, "Memory error.");            
                _MemoryUsage -= old_size-size;
            }
            
            if (Engine::Get().HasMode(RUN_MODE_MemoryTrack))
            {
                ulong real_size = _Allocator->GetSize(new_location);
                COFFEE_Assert(real_size==size, core::ERROR_CODE_Memory, "Memory full.");
            
                if (new_location!=location)
                {
                    for (ulong i=0 ; i<_AllocationCount ; ++i)
                        COFFEE_Assert(_Allocations[i].Location!=new_location, core::ERROR_CODE_Memory, "Memory invalid operation.");
                }

                for (ulong i=0 ; i<_AllocationCount ; ++i)
                {
                    if (_Allocations[i].Location==location)
                    {
                        _Allocations[i].Location = new_location;
                        _Allocations[i].Size = size;
                        return new_location;
                    }
                }
                COFFEE_Error(core::ERROR_CODE_Memory, "Memory invalid operation.");
            }
            return new_location;
        }
        return _Allocator->Reallocate(location, size);
    }

    //--------------------------------------------------------------------------------------------//

    void MemoryManager::Free(void* location, const char* file, uint32 line)
    {
        if (location!=NULL)
        {
            shell::Locker lock(_MemoryManager_Mutex);
            if (Engine::Get().HasMode(RUN_MODE_MemoryReport))
            {
                ulong size = _Allocator->GetSize(location);
                COFFEE_Assert(_AllocationCount>0, core::ERROR_CODE_Memory, "Trying to delete object not allocated in the manager.");
                COFFEE_Assert(_MemoryUsage>=size, core::ERROR_CODE_Memory, "Memory free error.");
                _MemoryUsage -= size;
                                
                if (Engine::Get().HasMode(RUN_MODE_MemoryTrack))
                {
                    for (ulong i=0 ; i<_AllocationCount ; ++i)
                    {
                        if (_Allocations[i].Location==location)
                        {
                            COFFEE_Assert(_Allocations[i].Size==size, core::ERROR_CODE_Memory, "Memory error.");
                            --_AllocationCount;
                            for (ulong j=i ; j<_AllocationCount ; ++j)
                                memcpy(_Allocations+j, _Allocations+j+1, sizeof(_Allocation));
                            _Allocator->Free(location);
                            return;
                        }
                    }
                    COFFEE_Error(core::ERROR_CODE_Memory, "Trying to delete object not allocated in the manager.");
                }
                --_AllocationCount;
            }
            _Allocator->Free(location);
        }
    }

    //--------------------------------------------------------------------------------------------//

    ulong MemoryManager::GetSize(void* location)
    {
        shell::Locker lock(_MemoryManager_Mutex);
        return _Allocator->GetSize(location);
    }

    //--------------------------------------------------------------------------------------------//

    void MemoryManager::Set(void* location, int32 value, ulong size)
    {
        if (size>0) Processor::Get().MemorySet(location, value, size);
    }
    
    //--------------------------------------------------------------------------------------------//

    void MemoryManager::Copy(void* location_out, const void* location_in, ulong size)
    {
        if (size>0) Processor::Get().MemoryCopy(location_out, location_in, size);
    }

    //--------------------------------------------------------------------------------------------//

    int32 MemoryManager::Compare(const void* location_one, const void* location_two, ulong size)
    {
        if (size==0) return 0;
        return Processor::Get().MemoryCompare(location_one, location_two, size);
    }

    //-OPERATIONS-----------------------------------------------------------------------------//

    void MemoryManager::_LogState()
    {
        COFFEE_Log(core::Log::Debug, "[RUN_MODE_MemoryReport] Memory usage peak (Mb) : %.2f", _MemoryPeak/(1024.0f*1024.0f));
        COFFEE_Log(core::Log::Debug, "[RUN_MODE_MemoryReport] Memory leaks : %i", _AllocationCount);
        COFFEE_Log(core::Log::Debug, "[RUN_MODE_MemoryReport] Leaked size : %i", _MemoryUsage);
        
        if (Engine::Get().HasMode(RUN_MODE_MemoryTrack))
        {
            COFFEE_Log(core::Log::Debug, "[RUN_MODE_MemoryTrack] Memory leaks list :");

            for (ulong i=0 ; i<_AllocationCount ; ++i)
            {
                COFFEE_Log(core::Log::Debug, "%s(%i) : %d leaked bytes at location 0x%x",
                    _Allocations[i].Filename,
                    _Allocations[i].Line,
                    _Allocations[i].Size,
                    _Allocations[i].Location);
                free(_Allocations[i].Filename);
                _Allocations[i].Filename = NULL;
            }
        }
    }

}
}
