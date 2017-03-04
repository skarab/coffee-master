#ifndef _COFFEE_CORE_INSTRUCTION_SET_H_
#define _COFFEE_CORE_INSTRUCTION_SET_H_

#include "coffee_includes.h"

namespace coffee
{
namespace core
{
    //--------------------------------------------------------------------------------------------//
    /// Generic instruction set class
    ///
    /// It defaults instructions using C/C++ standards functions.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API InstructionSet
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        InstructionSet();
        virtual ~InstructionSet();

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void MemoryCopy(void * out, const void * in, ulong size);
        virtual void MemorySet(void * ptr, int32 value, ulong size);
        virtual int32 MemoryCompare(const void * first, const void * second, ulong size);
    };
}
}
#endif
