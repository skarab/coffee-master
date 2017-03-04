#ifndef _COFFEE_CORE_MEMORY_H_
#define _COFFEE_CORE_MEMORY_H_

#include "kernel/core/memory/core_memory_manager.h"

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_Allocate
/// @brief Allocate a buffer and return a 'void *' pointer
//------------------------------------------------------------------------------------------------//
#define COFFEE_Allocate(_size_) COFFEE_CoreMemoryAllocate((ulong)_size_, __FILE__, __LINE__)
inline COFFEE_API void* COFFEE_CoreMemoryAllocate(ulong size, const char* file, uint32 line)
{
    if (coffee::core::MemoryManager::IsInstantiated())
        return coffee::core::MemoryManager::Get().Allocate(size, file, line);
    return malloc(size);
}

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_Free
/// @brief Free a buffer allocated with COFFEE_Allocate
//------------------------------------------------------------------------------------------------//
#define COFFEE_Free(_location_) COFFEE_CoreMemoryFree(_location_, __FILE__, __LINE__)
inline COFFEE_API void COFFEE_CoreMemoryFree(void* location, const char* file, uint32 line)
{
    if (coffee::core::MemoryManager::IsInstantiated())
        coffee::core::MemoryManager::Get().Free(location, file, line);
    else free(location);
}

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_Reallocate
/// @brief Reallocate a buffer allocated with COFFEE_Allocate
//------------------------------------------------------------------------------------------------//
#define COFFEE_Reallocate(_location_, _size_) COFFEE_CoreMemoryReallocate(_location_, (ulong)_size_, __FILE__, __LINE__)
inline COFFEE_API void* COFFEE_CoreMemoryReallocate(void* location, ulong size, const char* file, uint32 line)
{
    if (coffee::core::MemoryManager::IsInstantiated())
        return coffee::core::MemoryManager::Get().Reallocate(location, size, file, line);
    return realloc(location, size);
}

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_GetAllocationSize
/// @brief Get the size of the allocation done with COFFEE_Allocate
//------------------------------------------------------------------------------------------------//
inline COFFEE_API ulong COFFEE_GetAllocationSize(void* location)
{
    if (coffee::core::MemoryManager::IsInstantiated())
        return coffee::core::MemoryManager::Get().GetSize(location);
    return _msize(location);
}

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_Set
/// @brief Set the same value to each element of a buffer
//------------------------------------------------------------------------------------------------//
inline COFFEE_API void COFFEE_Set(void* location, int32 value, ulong size)
{
    if (coffee::core::MemoryManager::IsInstantiated())
        coffee::core::MemoryManager::Get().Set(location, value, size);
    else memset(location, value, size);
}

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_Copy
/// @brief Copy X bytes from an input buffer to an output buffer
//------------------------------------------------------------------------------------------------//
inline COFFEE_API void COFFEE_Copy(void* location_out, const void* location_in, ulong size)
{
    if (coffee::core::MemoryManager::IsInstantiated())
        coffee::core::MemoryManager::Get().Copy(location_out, location_in, size);
    else memcpy(location_out, location_in, size);
}

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_Compare
/// @brief Compare X bytes of two buffers
///
/// It returns 0 if they are equal, <0 if the first buffer is bigger (ex: "112" vs "012"),
/// >0 if the second one is bigger (ex: "012" vs "100")
//------------------------------------------------------------------------------------------------//
inline COFFEE_API int32 COFFEE_Compare(const void* location_one, const void* location_two, ulong size)
{
    if (coffee::core::MemoryManager::IsInstantiated())
        return coffee::core::MemoryManager::Get().Compare(location_one, location_two, size);
    return memcmp(location_one, location_two, size);
}

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_New
/// @brief Allocate a single object
/// @note It handles up to 6 constructor arguments
//------------------------------------------------------------------------------------------------//
#define COFFEE_New(_type_, ...) coffee_new< _type_ >(__FILE__, __LINE__, ##__VA_ARGS__)

template< typename type >
inline COFFEE_TEMPLATE_API type* coffee_new(const char* _file_, uint32 _line_) { return new(COFFEE_CoreMemoryAllocate(sizeof(type), _file_, _line_)) type(); }
template< typename type , typename t1>
inline COFFEE_TEMPLATE_API type* coffee_new(const char* _file_, uint32 _line_, const t1& p1) { return new(COFFEE_CoreMemoryAllocate(sizeof(type), _file_, _line_)) type(p1); }
template< typename type , typename t1, typename t2>
inline COFFEE_TEMPLATE_API type* coffee_new(const char* _file_, uint32 _line_, const t1& p1, const t2& p2) { return new(COFFEE_CoreMemoryAllocate(sizeof(type), _file_, _line_)) type(p1, p2); }
template< typename type , typename t1, typename t2, typename t3>
inline COFFEE_TEMPLATE_API type* coffee_new(const char* _file_, uint32 _line_, const t1& p1, const t2& p2, const t3& p3) { return new(COFFEE_CoreMemoryAllocate(sizeof(type), _file_, _line_)) type(p1, p2, p3); }
template< typename type , typename t1, typename t2, typename t3, typename t4>
inline COFFEE_TEMPLATE_API type* coffee_new(const char* _file_, uint32 _line_, const t1& p1, const t2& p2, const t3& p3, const t4& p4) { return new(COFFEE_CoreMemoryAllocate(sizeof(type), _file_, _line_)) type(p1, p2, p3, p4); }
template< typename type , typename t1, typename t2, typename t3, typename t4, typename t5>
inline COFFEE_TEMPLATE_API type* coffee_new(const char* _file_, uint32 _line_, const t1& p1, const t2& p2, const t3& p3, const t4& p4, const t5& p5) { return new(COFFEE_CoreMemoryAllocate(sizeof(type), _file_, _line_)) type(p1, p2, p3, p4, p5); }
template< typename type , typename t1, typename t2, typename t3, typename t4, typename t5, typename t6>
inline COFFEE_TEMPLATE_API type* coffee_new(const char* _file_, uint32 _line_, const t1& p1, const t2& p2, const t3& p3, const t4& p4, const t5& p5, const t6& p6) { return new(COFFEE_CoreMemoryAllocate(sizeof(type), _file_, _line_)) type(p1, p2, p3, p4, p5, p6); }

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_Delete
/// @brief Delete a single object
//------------------------------------------------------------------------------------------------//
#define COFFEE_Delete(_location_) coffee_delete(__FILE__, __LINE__, _location_)

template<typename type>
inline COFFEE_TEMPLATE_API void coffee_delete(const char* _file_, uint32 _line_, type* location)
{
    location->~type();
    COFFEE_CoreMemoryFree(location, _file_, _line_);
}

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_NewArray
/// @brief Allocate an array of objects
/// @note It handles up to 6 constructor arguments
//------------------------------------------------------------------------------------------------//
#define COFFEE_NewArray(_type_, _size_, ...) coffee_new_array< _type_ >(__FILE__, __LINE__, _size_, ##__VA_ARGS__)

template< typename type >
inline COFFEE_TEMPLATE_API type* coffee_new_array(const char* _file_, uint32 _line_, ulong count) { type* location = (type*)COFFEE_CoreMemoryAllocate(sizeof(type)*count, _file_, _line_);
for (ulong i=0 ; i<count ; ++i) new(location+i) type(); return location; }
template< typename type , typename t1>
inline COFFEE_TEMPLATE_API type* coffee_new_array(const char* _file_, uint32 _line_, ulong count, const t1& p1) { type* location = (type*)COFFEE_CoreMemoryAllocate(sizeof(type)*count, _file_, _line_);
for (ulong i=0 ; i<count ; ++i) new(location+i) type(p1); return location; }
template< typename type , typename t1, typename t2>
inline COFFEE_TEMPLATE_API type* coffee_new_array(const char* _file_, uint32 _line_, ulong count, const t1& p1, const t2& p2) { type* location = (type*)COFFEE_CoreMemoryAllocate(sizeof(type)*count, _file_, _line_);
for (ulong i=0 ; i<count ; ++i) new(location+i) type(p1, p2); return location; }
template< typename type , typename t1, typename t2, typename t3>
inline COFFEE_TEMPLATE_API type* coffee_new_array(const char* _file_, uint32 _line_, ulong count, const t1& p1, const t2& p2, const t3& p3) { type* location = (type*)COFFEE_CoreMemoryAllocate(sizeof(type)*count, _file_, _line_);
for (ulong i=0 ; i<count ; ++i) new(location+i) type(p1, p2, p3); return location; }
template< typename type , typename t1, typename t2, typename t3, typename t4>
inline COFFEE_TEMPLATE_API type* coffee_new_array(const char* _file_, uint32 _line_, ulong count, const t1& p1, const t2& p2, const t3& p3, const t4& p4) { type* location = (type*)COFFEE_CoreMemoryAllocate(sizeof(type)*count, _file_, _line_);
for (ulong i=0 ; i<count ; ++i) new(location+i) type(p1, p2, p3, p4); return location; }
template< typename type , typename t1, typename t2, typename t3, typename t4, typename t5>
inline COFFEE_TEMPLATE_API type* coffee_new_array(const char* _file_, uint32 _line_, ulong count, const t1& p1, const t2& p2, const t3& p3, const t4& p4, const t5& p5) { type* location = (type*)COFFEE_CoreMemoryAllocate(sizeof(type)*count, _file_, _line_);
for (ulong i=0 ; i<count ; ++i) new(location+i) type(p1, p2, p3, p4, p5); return location; }
template< typename type , typename t1, typename t2, typename t3, typename t4, typename t5, typename t6>
inline COFFEE_TEMPLATE_API type* coffee_new_array(const char* _file_, uint32 _line_, ulong count, const t1& p1, const t2& p2, const t3& p3, const t4& p4, const t5& p5, const t6& p6) { type* location = (type*)COFFEE_CoreMemoryAllocate(sizeof(type)*count, _file_, _line_);
for (ulong i=0 ; i<count ; ++i) new(location+i) type(p1, p2, p3, p4, p5, p6); return location; }

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_DeleteArray
/// @brief Delete an array of objects
//------------------------------------------------------------------------------------------------//
#define COFFEE_DeleteArray(_location_) coffee_delete_array(__FILE__, __LINE__, _location_)

template<typename type>
inline COFFEE_TEMPLATE_API void coffee_delete_array(const char* _file_, uint32 _line_, type* location)
{
    ulong count = COFFEE_GetAllocationSize(location)/sizeof(type);
    for (ulong i=0 ; i<count ; ++i)
        location[i].~type();
    COFFEE_CoreMemoryFree(location, _file_, _line_);
}

#endif
