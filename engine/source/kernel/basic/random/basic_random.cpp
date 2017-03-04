#include "kernel/basic/random/basic_random.h"
#include "kernel/kernel.h"

namespace coffee
{
namespace basic
{
    //-FUNCTIONS----------------------------------------------------------------------------------//

    uint32 GetRandom(uint32 maximum)
    {
        return rand() % (maximum+1);
    }
    
    //--------------------------------------------------------------------------------------------//

    uint32 GetRandom(uint32 minimum, uint32 maximum)
    {
        COFFEE_Assert(maximum>=minimum, core::ERROR_CODE_IncorrectUsage, "maximum is less than minimum");
        return minimum + rand() % (maximum-minimum+1);
    }

}
}
