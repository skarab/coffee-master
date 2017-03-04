#ifndef _COFFEE_RESOURCE_MANAGER_H_
#define _COFFEE_RESOURCE_MANAGER_H_

#include "coffee_includes.h"
#include "kernel/shell/module/shell_module_manager.h"
#include "kernel/resource/resource_object.h"
#include "kernel/resource/chunk/resource_chunk.h"
#include "kernel/resource/library/resource_library.h"
#include "kernel/resource/process/resource_process.h"
#include "kernel/resource/handler/resource_handler.h"

namespace coffee
{
namespace resource
{
    //--------------------------------------------------------------------------------------------//
    /// Resource manager module
    ///
    /// This is the entry point of the resource system.
    /// Usage is to call Object = Load to instantiate the resource,
    /// IsAvailable() will tell if the resource is ready, it can even check for a specific LOD.
    ///
    /// @see coffee::resource::Object, coffee::resource::Library, coffee::resource::Chunk, coffee::resource::LOD
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Manager : public shell::Module
    {
        friend class resource::Object;
        
        COFFEE_Type(Manager);
        COFFEE_DeclareModuleSingleton(Manager);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Manager();
        ~Manager();

        //-ACCESSORS------------------------------------------------------------------------------//

        const basic::Prow< Library* >& GetLibraryArray() const;

        //-QUERIES--------------------------------------------------------------------------------//

        uint32 GetLoadingResourceCount() const;
        uint32 GetResourceCount() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void OnInitialize();
        void OnFinalize();
        void OnUpdate(const basic::Time& time_step);

        Chunk& Load(const storage::Path& resource_path, uint32 lod_index = 0);
        bool Save(resource::Object& resource, uint32 lod_index = NONE);
        bool Save(Chunk& chunk);
        bool Reload(resource::Object& resource, uint32 lod_index = NONE);
        Chunk* Create(const storage::Path& resource_path);

        void ReloadResources();
        void ReloadInvalidResources();

        void RegisterLibrary(Library& library);
        void UnregisterLibrary(Library& library);

        void NotifyQuit();

    protected:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _RegisterResource(resource::Object& resource);
        void _UnregisterResource(resource::Object& resource);
        
    private:

        //-QUERIES--------------------------------------------------------------------------------//

        Library* _FindResourceLibrary(const storage::Path& resource_path) const;
        bool _FindChunk(Chunk** chunk, const storage::Path& resource_path, uint32 lod_index);
        Process* _GetNextProcess();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _RunProcess();
        void _UpdateResources();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Prow< Library* > _LibraryArray;
        basic::Prow< Process* > _ProcessingQueue;
        shell::Mutex _ProcessingQueueMutex;
        Process* _Process;
        shell::Mutex _ProcessMutex;
        basic::Prow< resource::Object* > _ResourceArray;
        shell::Mutex _ResourceMutex;
        shell::Mutex _UpdateMutex;
        bool _ItHasToQuit;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Manager);
}
}
#endif
