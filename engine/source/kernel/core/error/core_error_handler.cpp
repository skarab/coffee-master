#include "kernel/core/error/core_error_handler.h"
#include "kernel/core/log/core_log.h"
#include "kernel/core/error/core_error_handler_windows.hpp"

namespace coffee
{
namespace core
{
    ErrorHandler* ErrorHandler::_Instance = NULL;
    ErrorHandler& ErrorHandler::Get() { return *_Instance; }

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ErrorHandler::ErrorHandler()
    {
        COFFEE_Assert(_Instance == NULL, coffee::core::ERROR_CODE_IncorrectUsage,
            "An instance of ErrorHandler already exist.");
        _Instance = this;

        _PlatformInitialize();
    }

    //--------------------------------------------------------------------------------------------//

    ErrorHandler::~ErrorHandler()
    {
        _PlatformFinalize();
        _Instance = NULL;
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    void ErrorHandler::OnError(const Error& error)
    {
        char* full_description = error.GetFullDescription();

        COFFEE_Log(core::Log::FatalError, full_description);
        free(full_description);

        // Note: close log file to ensure exception will be saved.
        Log::Get()._Close();
        
        _PlatformHandle(error);
    }

}
}
