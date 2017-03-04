#ifndef _COFFEE_CORE_MACROS_LOG_H_
#define _COFFEE_CORE_MACROS_LOG_H_

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_Log
/// @brief Log text
///
/// Usage is similar to C printf function.
//------------------------------------------------------------------------------------------------//
#define COFFEE_Log coffee::core::Log::Get().Write

#endif
