#ifndef _COFFEE_CORE_ERROR_CODE_H_
#define _COFFEE_CORE_ERROR_CODE_H_

#include "coffee_includes.h"

namespace coffee
{
namespace core
{
    //--------------------------------------------------------------------------------------------//
    /// Error codes
    ///
    /// @see coffee::core::Error
    //--------------------------------------------------------------------------------------------//
    enum ERROR_CODE
    {
        ERROR_CODE_Unexpected,              ///< error which shouldn't happen
        ERROR_CODE_IncorrectUsage,          ///< forbidden usage or case
        ERROR_CODE_Unimplemented,           ///< not implemented functionality
        ERROR_CODE_Memory,                  ///< memory problem
        ERROR_CODE_Thread,                  ///< thread problem
        ERROR_CODE_WindowManager,           ///< GUI error
        ERROR_CODE_ResourceManager,         ///< resource problem
        ERROR_CODE_StorageSystem,           ///< storage system error
        ERROR_CODE_MetaSystem,              ///< meta object problem
        ERROR_CODE_UnsupportedExtension,    ///< video card unsupported extension
        ERROR_CODE_GraphicsDriver,          ///< graphic driver/device problem
        ERROR_CODE_GraphicsSystem,          ///< graphic system problem
        ERROR_CODE_AudioDriver,             ///< audio driver/device problem
        ERROR_CODE_AudioSystem,             ///< audio system problem
        ERROR_CODE_Count
    };

    //--------------------------------------------------------------------------------------------//
    /// Retrieve text version of enum value
    //--------------------------------------------------------------------------------------------//
    COFFEE_API const char* ERROR_CODE_GetDescription(const ERROR_CODE& error_code);
}
}
#endif
