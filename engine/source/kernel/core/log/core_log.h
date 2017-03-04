#ifndef _COFFEE_CORE_LOG_H_
#define _COFFEE_CORE_LOG_H_

#include "coffee_includes.h"

namespace coffee
{
namespace core
{
    class ErrorHandler;

    //--------------------------------------------------------------------------------------------//
    /// Simple logger class
    ///
    /// This logger write text in file "engine.log" and display it in in the IDE output as well.
    /// Use macro COFFEE_Log(...).
    ///
    /// @see COFFEE_Log
    /// @note It's thread safe.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Log
    {
        friend class ErrorHandler;

        COFFEE_DeclareSingleton(Log);

    public:

        enum Type
        {
            None,
            Warning,
            Error,
            FatalError,
            Debug
        };

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Log();
        ~Log();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Write(Type type, const char* text, ...);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _Close();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        FILE* _File;
     };
}
}
#endif
