#ifndef _COFFEE_CORE_PLATFORM_TYPES_H_
#define _COFFEE_CORE_PLATFORM_TYPES_H_

#include "kernel/core/platform/core_platform_unix_includes.h"
#include "kernel/core/platform/core_platform_windows_includes.h"
#include "coffee_externals.h"
#include <float.h>

//-DEFINES----------------------------------------------------------------------------------------//

//------------------------------------------------------------------------------------------------//
/// @def real
/// @brief Floating point number
///
/// This is the choice for all floating point computations.
//------------------------------------------------------------------------------------------------//
#define real            float
#define real_minimum    -FLT_MAX
#define real_maximum    FLT_MAX

//------------------------------------------------------------------------------------------------//
/// @def real64
/// @brief 64 bits floating point number
///
/// It's used only for high precision timer, preferably use 'real'.
//------------------------------------------------------------------------------------------------//
#define real64      double

//------------------------------------------------------------------------------------------------//
/// @def uint8
/// @brief 8 bits unsigned integer
//------------------------------------------------------------------------------------------------//
#define uint8       unsigned char

//------------------------------------------------------------------------------------------------//
/// @def uint16
/// @brief 16 bits unsigned integer
//------------------------------------------------------------------------------------------------//
#define uint16      unsigned short

//------------------------------------------------------------------------------------------------//
/// @def uint32
/// @brief 32 bits unsigned integer
///
/// This is the choice for all containers (indexes, count).
//------------------------------------------------------------------------------------------------//
#define uint32      unsigned int

//------------------------------------------------------------------------------------------------//
/// @def int8
/// @brief 8 bits signed integer
//------------------------------------------------------------------------------------------------//
#define int8        signed char

//------------------------------------------------------------------------------------------------//
/// @def int16
/// @brief 16 bits signed integer
//------------------------------------------------------------------------------------------------//
#define int16       short

//------------------------------------------------------------------------------------------------//
/// @def int32
/// @brief 32 bits signed integer
//------------------------------------------------------------------------------------------------//
#define int32       int

//------------------------------------------------------------------------------------------------//
/// @def ulong
/// @brief size type
/// @note near deprecated
///
/// Actually it's used for all size handling functions. It'll be renamed in a near future.
//------------------------------------------------------------------------------------------------//
#define ulong       unsigned long

//------------------------------------------------------------------------------------------------//
/// @def ulong_ptr
/// @brief pointer type
/// @note near deprecated
///
/// Actually it's used for all pointer operations (meta system mainly).
/// It'll be renamed in a near future.
//------------------------------------------------------------------------------------------------//
#define ulong_ptr   ULONG_PTR

//------------------------------------------------------------------------------------------------//
/// @def NULL
/// @brief null pointer value
///
/// When pointers are used, NULL is the value the set when "it's empty", using 0 is forbidden.
//------------------------------------------------------------------------------------------------//
#undef NULL
#define NULL    0

//------------------------------------------------------------------------------------------------//
/// @def NULL_CHAR
/// @brief null character value
/// @note near deprecated
///
/// Actually it's not that used, and will be removed in a near future.
//------------------------------------------------------------------------------------------------//
#define NULL_CHAR   '\0'

//------------------------------------------------------------------------------------------------//
/// @def NONE
/// @brief index null value
///
/// Used by all indexed functionalities (containers, search functions and so).
/// Note that since index type is uint32, and NONE value could change, it have to be carefully
/// taken into account when writing functions/operators about NONE.
//------------------------------------------------------------------------------------------------//
#define NONE ((unsigned int)(-1))

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_IsFlagEnabled
/// @brief Helper which query if a _flag_ is enabled on a uint32 _flags_ (bitarray).
//------------------------------------------------------------------------------------------------//
#define COFFEE_IsFlagEnabled(_flags_, _flag_) \
    (((_flags_)&(uint32)(_flag_))>0)

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_EnableFlag
/// @brief Helper to set the state of a _flag_ on a uint32 _flags_ (bitarray).
//------------------------------------------------------------------------------------------------//
#define COFFEE_EnableFlag(_flags_, _flag_, _bool_) \
    if(_bool_) (_flags_) |= (uint32)(_flag_); \
    else (_flags_) &= ~(uint32)(_flag_);

#endif
