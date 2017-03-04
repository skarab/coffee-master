#include "kernel/basic/container/prow/basic_prow.h"

namespace coffee
{
namespace basic
{
    //-OPERATIONS---------------------------------------------------------------------------------//

    template<>
    void Prow< void*, false >::_HardDeleteItem(uint32 item_index)
    {
        COFFEE_Error(core::ERROR_CODE_IncorrectUsage, "Can't delete a void* object");
    }

}
}
