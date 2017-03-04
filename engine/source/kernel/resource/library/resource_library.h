#ifndef _COFFEE_RESOURCE_LIBRARY_H_
#define _COFFEE_RESOURCE_LIBRARY_H_

#include "coffee_includes.h"
#include "kernel/shell/module/shell_module_manager.h"
#include "kernel/resource/resource_object.h"
#include "kernel/resource/process/resource_process.h"

namespace coffee
{
namespace resource
{
    //--------------------------------------------------------------------------------------------//
    /// Resource library - manages resource preparation
    ///
    /// The library prepares and keeps the resources by types, depending of the proper context.
    /// Libraries are registered at the modules initialization using COFFEE_RegisterResourceLibrary.
    ///
    /// @see COFFEE_RegisterResourceLibrary
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Library : public shell::Module
    {
        COFFEE_Type(Library);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Library();
        Library(basic::String resource_name);
        virtual ~Library();

        //-ACCESSORS------------------------------------------------------------------------------//

        const basic::String& GetResourceName() const;
        uint32 GetResourceCount() const;

        //-QUERIES--------------------------------------------------------------------------------//

        uint32 GetLoadingResourceCount() const;
        bool FindChunk(Chunk** chunk, const storage::Path& resource_path, uint32 lod_index);
        
        //-OPERATIONS-----------------------------------------------------------------------------//

        void OnInitialize();
        void OnFinalize();
        void OnUpdate(const basic::Time& time_step);
        void QueueProcess(Process& process);
        Chunk* PrepareReloadChunk(Chunk& chunk);

    private:

        //-QUERIES--------------------------------------------------------------------------------//

        Process* _GetNextProcess();
        Chunk* _GetNextChunkToRemove();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _RunProcess(Process& process);

    protected:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::String _ResourceName;
        basic::Prow< Chunk * > _ChunkArray;
        shell::Mutex _ChunkArrayMutex;
        basic::Prow< Process * > _ProcessingQueue;
        shell::Mutex _ProcessingQueueMutex;
        uint32 _MaximumProcessCount;
        uint32 _MaximumRemovedChunkCount;
        basic::Prow< Process* > _Processes;
        shell::Mutex _ProcessMutex;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Library);
}
}
#endif
