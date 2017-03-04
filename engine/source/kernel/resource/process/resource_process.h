#ifndef _COFFEE_RESOURCE_PROCESS_H_
#define _COFFEE_RESOURCE_PROCESS_H_

#include "coffee_includes.h"
#include "kernel/resource/chunk/resource_chunk.h"

namespace coffee
{
namespace resource
{
    //--------------------------------------------------------------------------------------------//
    /// Resource process - streamed and prepared resource data
    ///
    /// The resource process makes a pair of resource and LOD during the whole process.
    ///
    /// @see coffee::resource::Manager
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Process : public meta::Object
    {
        COFFEE_Type(Process);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Process();
        ~Process();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetChunk(Chunk& chunk);
        const Chunk& GetChunk() const;
        Chunk& GetChunk();
        void SetLODIndex(uint32 lod_index);
        uint32 GetLODIndex() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Destroy();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Chunk* _Chunk;
        uint32 _LODIndex;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Process);
}
}
#endif
