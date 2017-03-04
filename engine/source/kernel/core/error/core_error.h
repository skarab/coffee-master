#ifndef _COFFEE_CORE_ERROR_H_
#define _COFFEE_CORE_ERROR_H_

#include "coffee_includes.h"
#include "kernel/core/error/core_error_code.h"

namespace coffee
{
namespace core
{
    //--------------------------------------------------------------------------------------------//
    /// Error description
    ///
    /// This class shouldn't be accessed directly, it's for internal purpose only.
    ///
    /// When an Error instance is created, the application is killed and a crash dump is generated.
    ///
    /// To check and report bad cases, use the following macros:
    /// @see COFFEE_Error, COFFEE_Warning, COFFEE_Assert
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Error
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Error(const char* file, int32 line, const ERROR_CODE& code, const char* description);
        ~Error();

        //-QUERIES--------------------------------------------------------------------------------//

        char* GetFullDescription() const;
        
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        char _FileName[256];
        char _Description[512];
        int32 _Line;
        ERROR_CODE _Code;
    };
    
    //--------------------------------------------------------------------------------------------//
    /// Used internally to handle assertion.
    ///
    /// @see COFFEE_Assert
    //--------------------------------------------------------------------------------------------//
    void COFFEE_API Assert(bool it_requires, const char* file, int32 line, const ERROR_CODE& code,
            const char* description);

}
}
#endif
