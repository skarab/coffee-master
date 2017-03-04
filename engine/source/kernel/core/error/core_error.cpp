#include "kernel/core/error/core_error.h"
#include "kernel/core/error/core_error_handler.h"

namespace coffee
{
namespace core
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Error::Error(const char* file, int32 line, const ERROR_CODE& code,
        const char* description)
    {
        _snprintf(_FileName, 256, "%s", file);
        _snprintf(_Description, 512, "%s", description);
        _Line = line;
        _Code = code;

        ErrorHandler::Get().OnError(*this);
    }

    //--------------------------------------------------------------------------------------------//

    Error::~Error()
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

    char* Error::GetFullDescription() const
    {
        char* full_description = (char*)malloc(1024);

        _snprintf(
            full_description,
            1024,
            "%s(%i) : %s: %s",
            _FileName,
            _Line,
            ERROR_CODE_GetDescription(_Code),
            _Description);

        return full_description;
    }

    //-FUNCTIONS----------------------------------------------------------------------------------//

    void Assert(bool it_requires, const char* file, int32 line, const ERROR_CODE& code,
            const char* description)
    {
        if (!it_requires)
            Error(file, line, code, description==NULL?"":description);
    }

}
}
