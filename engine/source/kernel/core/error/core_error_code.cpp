#include "kernel/core/error/core_error_code.h"

namespace coffee
{
namespace core
{
    //-FUNCTIONS----------------------------------------------------------------------------------//

    const char* ERROR_CODE_GetDescription(const ERROR_CODE& error_code)
    {
        static const char error_code_string_array[ERROR_CODE_Count][64] =
        {
            "ERROR_CODE_Unexpected",
            "ERROR_CODE_IncorrectUsage",
            "ERROR_CODE_Unimplemented",
            "ERROR_CODE_Memory",
            "ERROR_CODE_Thread",
            "ERROR_CODE_WindowManager",
            "ERROR_CODE_ResourceManager",
            "ERROR_CODE_StorageSystem",
            "ERROR_CODE_MetaSystem",
            "ERROR_CODE_UnsupportedExtension",
            "ERROR_CODE_GraphicsDriver",
            "ERROR_CODE_GraphicsSystem",
            "ERROR_CODE_AudioDriver",
            "ERROR_CODE_AudioSystem"
        };

        return error_code_string_array[(uint32) error_code];
    }

}
}
