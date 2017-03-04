#include "kernel/core/error/core_error.h"
#include "kernel/core/log/core_log.h"
#include "kernel/core/processor/core_processor.h"

namespace coffee
{
namespace core
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_ImplementSingleton(Processor);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Processor::Processor() :
        _VendorName(NULL),
        _ModelName(NULL),
        _InstructionSet(NULL)
    {
        COFFEE_CreateSingleton(Processor);

        _DetectType();

        if (_ID & PROCESSOR_TYPE_Unsupported)
            COFFEE_Error(core::ERROR_CODE_Unexpected, "Unsupported processor");

        //COFFEE_Log(core::Log::None, "Vendor : %s", _VendorName);
        //COFFEE_Log(core::Log::None, "Model  : %s", _ModelName);

        _InstructionSet = COFFEE_New(InstructionSet);
        COFFEE_Log(core::Log::None, "Choosing instructionset : GENERIC");
    }

    //--------------------------------------------------------------------------------------------//

    Processor::~Processor()
    {
        if (_VendorName!=NULL) free(_VendorName);
        if (_ModelName!=NULL) free(_ModelName);
        if (_InstructionSet!=NULL) COFFEE_Delete(_InstructionSet);

        COFFEE_DestroySingleton(Processor);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Processor::MemoryCopy(void * out, const void * in, ulong size)
    {
        _InstructionSet->MemoryCopy(out, in, size);
    }

    //--------------------------------------------------------------------------------------------//

    void Processor::MemorySet(void * ptr, int32 value, ulong size)
    {
        _InstructionSet->MemorySet(ptr, value, size);
    }

    //--------------------------------------------------------------------------------------------//

    int32 Processor::MemoryCompare(const void * first, const void * second, ulong size)
    {
        return _InstructionSet->MemoryCompare(first, second, size);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Processor::_DetectType()
    {
        _ID = PROCESSOR_TYPE_Generic;

        // TODO: Detect processor and add instructions sets
    }

}
}
