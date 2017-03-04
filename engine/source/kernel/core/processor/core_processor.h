#ifndef _COFFEE_CORE_PROCESSOR_H_
#define _COFFEE_CORE_PROCESSOR_H_

#include "coffee_includes.h"
#include "kernel/core/processor/core_processor_type.h"
#include "kernel/core/processor/instruction_set/core_instruction_set.h"

namespace coffee
{
namespace core
{
    //--------------------------------------------------------------------------------------------//
    /// Processor
    ///
    /// The processor detects the current CPU features and choose the right instruction set to use.
    ///
    /// @see CORE_PROCESSOR_TYPE, CCoreProcessorInstructionSet
    ///
    /// Actually, only the following operations go by this class :
    /// @see COFFEE_Set, COFFEE_Copy
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Processor
    {
        COFFEE_DeclareSingleton(Processor);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Processor();
        ~Processor();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void MemoryCopy(void * out, const void * in, ulong size);
        void MemorySet(void * ptr, int32 value, ulong size);
        int32 MemoryCompare(const void * first, const void * second, ulong size);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _DetectType();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        char * _VendorName;
        char * _ModelName;
        ulong _Family;
        ulong _Model;
        int32 _ID;
        InstructionSet * _InstructionSet;
    };
}
}
#endif
