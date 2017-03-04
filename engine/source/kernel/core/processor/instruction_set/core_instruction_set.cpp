#include "kernel/core/processor/instruction_set/core_instruction_set.h"

namespace coffee
{
namespace core
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    InstructionSet::InstructionSet()
    {
    }

    //--------------------------------------------------------------------------------------------//

    InstructionSet::~InstructionSet()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void InstructionSet::MemoryCopy(void * out, const void * in, ulong size)
    {
        memcpy(out, in, size);
    }

    //--------------------------------------------------------------------------------------------//

    void InstructionSet::MemorySet(void * ptr, int32 value, ulong size)
    {
        memset(ptr, value, size);
    }

    //--------------------------------------------------------------------------------------------//

    int32 InstructionSet::MemoryCompare(const void * first, const void * second, ulong size)
    {
        return memcmp(first, second, size);
    }

}
}
