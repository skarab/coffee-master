#ifndef _COFFEE_CORE_ERROR_HANDLER_H_
#define _COFFEE_CORE_ERROR_HANDLER_H_

#include "coffee_includes.h"
#include "kernel/core/error/core_error.h"

namespace coffee
{
namespace core
{
    //--------------------------------------------------------------------------------------------//
    /// Error handler
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ErrorHandler
    {
    private: static ErrorHandler* _Instance;
    public: static ErrorHandler& Get();    
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ErrorHandler();
        ~ErrorHandler();

        //-HANDLERS-------------------------------------------------------------------------------//

        void OnError(const Error& error);

    private:

        //-PLATFORM-------------------------------------------------------------------------------//

        void _PlatformInitialize();
        void _PlatformFinalize();
        void _PlatformHandle(const Error& error);

        #include "kernel/core/error/core_error_handler_windows.h"
    };
}
}
#endif
