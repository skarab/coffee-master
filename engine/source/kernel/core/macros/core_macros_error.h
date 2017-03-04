#ifndef _COFFEE_CORE_MACROS_ERROR_H_
#define _COFFEE_CORE_MACROS_ERROR_H_

#include "kernel/core/macros/core_macros_log.h"

//-DEFINES----------------------------------------------------------------------------------------//

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_Warning
/// @brief Report a warning
//------------------------------------------------------------------------------------------------//
#define COFFEE_Warning(_description_) \
    coffee::core::Log::Get().Write(core::Log::Warning, "%s(%i): Warning : %s", __FILE__, __LINE__, _description_) \

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_Error
/// @brief Report an error
///
/// Launches a fatal error : kill the application and generate a crash dump
//------------------------------------------------------------------------------------------------//
#define COFFEE_Error(_error_code_, _description_) \
    coffee::core::Error(__FILE__, __LINE__, _error_code_, _description_)

//------------------------------------------------------------------------------------------------//
/// @def COFFEE_Assert
/// @brief Launch an error if the condition is false.
///
/// If the _condition_ isn't met, it writes the _description_ to the log file,
/// generate a crash dump and kill the application.
/// See coffee::core::ERROR_CODE for _error_code_ specification.
//------------------------------------------------------------------------------------------------//
#define COFFEE_Assert(_condition_, _error_code_, _description_) \
    coffee::core::Assert(_condition_, __FILE__, __LINE__, _error_code_, _description_)

#endif
