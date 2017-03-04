//------------------------------------------------------------------------------------------------//
/// @file kernel/resource/process/resource_process.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "kernel/resource/process/resource_process.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(resource::Process);
        COFFEE_Attribute(resource::Chunk *, _Chunk, meta::MODE_Editable);
        COFFEE_Attribute(uint32, _LODIndex, meta::MODE_Editable);
    COFFEE_EndType();

namespace resource
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Process::Process() :
        _Chunk(NULL),
        _LODIndex(NONE)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Process::~Process()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Process::SetChunk(Chunk & chunk)
    {
        _Chunk = &chunk;
    }

    //--------------------------------------------------------------------------------------------//

    const Chunk & Process::GetChunk() const
    {
        return *_Chunk;
    }

    //--------------------------------------------------------------------------------------------//

    Chunk & Process::GetChunk()
    {
        return *_Chunk;
    }

    //--------------------------------------------------------------------------------------------//

    void Process::SetLODIndex(uint32 lod_index)
    {
        _LODIndex = lod_index;
    }

    //--------------------------------------------------------------------------------------------//

    uint32 Process::GetLODIndex() const
    {
        return _LODIndex;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Process::Destroy()
    {
        _Chunk->_NotifyInstanceDestruction();
        COFFEE_Delete(_Chunk);
        _Chunk = NULL;
        _LODIndex = NONE;
    }

}
}
//------------------------------------------------------------------------------------------------//
