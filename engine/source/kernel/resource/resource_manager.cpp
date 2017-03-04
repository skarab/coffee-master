#include "kernel/core/log/core_log.h"
#include "kernel/core/error/core_error.h"
#include "kernel/resource/resource_manager.h"
#include "system/graphics/graphics.h"
#include "coffee.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(resource::Manager);
        COFFEE_Ancestor(shell::Module);
    COFFEE_EndType();
    
namespace resource
{
    COFFEE_ImplementModuleSingleton(Manager);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Manager::Manager() :
        shell::Module(shell::MODULE_ATTRIBUTE_Automatic | shell::MODULE_ATTRIBUTE_Threaded),
        _Process(NULL),
        _ItHasToQuit(false)
    {
        COFFEE_CreateModuleSingleton(Manager);
    }

    //--------------------------------------------------------------------------------------------//

    Manager::~Manager()
    {
        COFFEE_DestroyModuleSingleton(Manager);
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const basic::Prow< Library * > & Manager::GetLibraryArray() const
    {
        return _LibraryArray;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    uint32 Manager::GetLoadingResourceCount() const
    {
        uint32 count = _ProcessingQueue.GetSize();
        for (uint32 index=0 ; index<_LibraryArray.GetSize() ; ++index)
            count += _LibraryArray[index]->GetLoadingResourceCount();        
        return count;
    }

    //--------------------------------------------------------------------------------------------//

    uint32 Manager::GetResourceCount() const
    {
        uint32 count(0);
        for (uint32 index=0 ; index<_LibraryArray.GetSize() ; ++index)
            count += _LibraryArray[index]->GetResourceCount();
        return count;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Manager::OnInitialize()
    {
    }

    //--------------------------------------------------------------------------------------------//

    void Manager::OnFinalize()
    {
        _ProcessingQueueMutex.Lock();
        for (uint32 process_index=0 ; process_index<_ProcessingQueue.GetSize() ; ++process_index)
        {
            Chunk* chunk(NULL);
            Library* library = _FindResourceLibrary(_ProcessingQueue[process_index]->GetChunk().GetFilePath());
            if (library!=NULL)
                library->FindChunk(&chunk, _ProcessingQueue[process_index]->GetChunk().GetFilePath(), NONE);
            if (chunk==NULL)
                _ProcessingQueue[process_index]->Destroy();
            COFFEE_Delete(_ProcessingQueue[process_index]);
        }
        _ProcessingQueueMutex.Unlock();
    }

    //--------------------------------------------------------------------------------------------//

    void Manager::OnUpdate(const basic::Time& time_step)
    {
        if (!_ItHasToQuit)
        {
            _ProcessMutex.Lock();
            _Process = _GetNextProcess();

            if (_Process!=NULL)
            {
                _ProcessMutex.Unlock();        
                _RunProcess();
                _ProcessMutex.Lock();
                _Process = NULL;
            }
            _ProcessMutex.Unlock();    
        }
        _UpdateResources();
    }

    //--------------------------------------------------------------------------------------------//

    Chunk& Manager::Load(const storage::Path& resource_path, uint32 lod_index)
    {
        Chunk* chunk(NULL);
        if (_FindResourceLibrary(resource_path)->FindChunk(&chunk, resource_path, lod_index))
            return *chunk;
        if (_FindChunk(&chunk, resource_path, lod_index))
            return *chunk;
            
        if (chunk==NULL)
        {
            chunk = COFFEE_New(Chunk);
            chunk->SetFilePath(resource_path);
        }

        chunk->SetState(CHUNK_STATE_Loading);
        chunk->_NotifyInstanceCreation();
        Process* process = COFFEE_New(Process);
        process->SetChunk(*chunk);
        process->SetLODIndex(lod_index);

        _ProcessingQueueMutex.Lock();
        _ProcessingQueue.AddItem(process);
        _ProcessingQueueMutex.Unlock();
        return *chunk;
    }

    //--------------------------------------------------------------------------------------------//

    bool Manager::Save(resource::Object& resource, uint32 lod_index)
    {
        COFFEE_Assert(shell::Thread::IsMainThread(), core::ERROR_CODE_ResourceManager,
            "Trying to save resource from other thread.");

        bool result = false;
        _UpdateMutex.Lock();
        if (resource.IsInstantiated())
        {
            resource.PreSaveLOD(lod_index);
            result = resource.GetChunk().Save() && resource.GetChunk().SaveLOD(lod_index);
        }
        _UpdateMutex.Unlock();
        return result;
    }

    //--------------------------------------------------------------------------------------------//

    bool Manager::Save(Chunk& chunk)
    {
        COFFEE_Assert(shell::Thread::IsMainThread(), core::ERROR_CODE_ResourceManager,
            "Trying to save resource from other thread.");

        shell::Locker lock(_UpdateMutex);
        if (chunk.Save() && chunk.SaveLOD())
        {
            // Reload to refresh instances if required
            Chunk* loaded_chunk(NULL);
            if (_FindResourceLibrary(chunk.GetFilePath())->FindChunk(&loaded_chunk, chunk.GetFilePath(), 0)
                || _FindChunk(&loaded_chunk, chunk.GetFilePath(), 0))
            {    
                resource::Object instance = Load(chunk.GetFilePath());
                Reload(instance);
            }
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Manager::Reload(resource::Object& resource, uint32 lod_index)
    {
        COFFEE_Assert(shell::Thread::IsMainThread(), core::ERROR_CODE_ResourceManager,
            "Trying to reload resource from other thread.");

        if (resource.IsInstantiated())
        {
            Library* library = _FindResourceLibrary(resource.GetFilePath());

            if (library!=NULL)
            {
                Chunk* chunk = library->PrepareReloadChunk(resource.GetChunk());
                Process* process;

                if (chunk!=NULL)
                {
                    chunk->UnLoad();
                    chunk->_NotifyInstanceCreation();
                    resource.SetWantedLODIndex(lod_index);
                    _UpdateResources();

                    process = COFFEE_New(Process);
                    process->SetChunk(*chunk);
                    process->SetLODIndex(lod_index);

                    _ProcessingQueueMutex.Lock();
                    _ProcessingQueue.AddItem(process);
                    _ProcessingQueueMutex.Unlock();
                    return true;
                }
            }
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    Chunk* Manager::Create(const storage::Path & resource_path)
    {
        Chunk* chunk = COFFEE_New(Chunk);
        chunk->SetFilePath(resource_path);
        chunk->SetState(CHUNK_STATE_Loaded);
        return chunk;
    }

    //--------------------------------------------------------------------------------------------//

    void Manager::ReloadResources()
    {
        COFFEE_Assert(shell::Thread::IsMainThread(), core::ERROR_CODE_ResourceManager,
            "Trying to reload resources from other thread.");

        _UpdateMutex.Lock();
        _ResourceMutex.Lock();
        _ProcessMutex.Lock();
        for (uint32 index=0 ; index<_ResourceArray.GetSize() ; ++index)
        {
            resource::Object* resource = _ResourceArray[index];
            Reload(*resource);
        }
        _ProcessMutex.Unlock();
        _ResourceMutex.Unlock();
        _UpdateMutex.Unlock();
    }

    //--------------------------------------------------------------------------------------------//

    void Manager::ReloadInvalidResources()
    {
        COFFEE_Assert(shell::Thread::IsMainThread(), core::ERROR_CODE_ResourceManager,
            "Trying to reload invalid resources from other thread.");

        _UpdateMutex.Lock();
        _ResourceMutex.Lock();
        for (uint32 index=0 ; index<_ResourceArray.GetSize() ; ++index)
        {
            resource::Object* resource = _ResourceArray[index];
            if (resource->IsInvalid() || !resource->IsAvailable())
                Reload(*resource);
        }
        _ResourceMutex.Unlock();
        _UpdateMutex.Unlock();
    }

    //--------------------------------------------------------------------------------------------//

    void Manager::RegisterLibrary(Library& library)
    {
        _ProcessingQueueMutex.Lock();
        _LibraryArray.AddItem(&library);
        _ProcessingQueueMutex.Unlock();
    }

    //--------------------------------------------------------------------------------------------//

    void Manager::UnregisterLibrary(Library& library)
    {
        _ProcessingQueueMutex.Lock();
        uint32 index = _LibraryArray.FindItem(&library);
        COFFEE_Assert(index!=NONE, core::ERROR_CODE_ResourceManager, "Library isn't registered!");
        for (int32 process_index=0 ; process_index<(int32)_ProcessingQueue.GetSize() ; ++process_index)
        {
            Library* lib = _FindResourceLibrary(_ProcessingQueue[process_index]->GetChunk().GetFilePath());
            if (lib==&library)
            {
                Chunk* chunk(NULL);
                lib->FindChunk(&chunk, _ProcessingQueue[process_index]->GetChunk().GetFilePath(), NONE);
                if (chunk!=NULL)
                {
                    _ProcessingQueue[process_index]->Destroy();
                    COFFEE_Delete(_ProcessingQueue[process_index]);
                    _ProcessingQueue.Remove(process_index--);
                }
            }
        }            
        _LibraryArray.Remove(index);
        _ProcessingQueueMutex.Unlock();
    }

    //--------------------------------------------------------------------------------------------//

    void Manager::NotifyQuit()
    {
        _ItHasToQuit = true;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Manager::_RegisterResource(resource::Object & resource)
    {
        _ResourceMutex.Lock();
        if (_ResourceArray.FindItem(&resource)==NONE)
            _ResourceArray.AddItem(&resource);
        _ResourceMutex.Unlock();
    }

    //--------------------------------------------------------------------------------------------//

    void Manager::_UnregisterResource(resource::Object& resource)
    {
        _ResourceMutex.Lock();
        _ResourceArray.RemoveItem(&resource);
        _ResourceMutex.Unlock();
    }
    
    //-QUERIES------------------------------------------------------------------------------------//

    Library* Manager::_FindResourceLibrary(const storage::Path& resource_path) const
    {
        basic::String resource_extension = resource_path.GetFileExtension();
        for (uint32 index=0 ; index<_LibraryArray.GetSize() ; ++index)
        {
            if (_LibraryArray[index]->GetResourceName()==resource_extension)
                return _LibraryArray[index];
        }
        return NULL;
    }

    //--------------------------------------------------------------------------------------------//

    bool Manager::_FindChunk(Chunk** chunk, const storage::Path& resource_path, uint32 lod_index)
    {
        _ProcessingQueueMutex.Lock();
        for(uint32 process_index=0 ; process_index<_ProcessingQueue.GetSize() ; ++process_index)
        {
            if (_ProcessingQueue[process_index]->GetChunk().GetFilePath()==resource_path)
            {
                *chunk = &_ProcessingQueue[process_index]->GetChunk();
                if (_ProcessingQueue[ process_index ]->GetLODIndex()==lod_index
                    || _ProcessingQueue[ process_index ]->GetLODIndex()==NONE)
                {
                    _ProcessingQueueMutex.Unlock();
                    return true;
                }
            }
        }
        _ProcessingQueueMutex.Unlock();
        _ProcessMutex.Lock();
        if (_Process!=NULL && _Process->GetChunk().GetFilePath()==resource_path)
        {
            *chunk = &_Process->GetChunk();
            if (_Process->GetLODIndex()==lod_index || _Process->GetLODIndex()==NONE)
            {
                _ProcessMutex.Unlock();
                return !(*chunk)->IsInvalid();
            }
        }
        _ProcessMutex.Unlock();
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    Process* Manager::_GetNextProcess()
    {
        Process* process(NULL);
        _ProcessingQueueMutex.Lock();
        if (_ProcessingQueue.GetSize()>0)
        {
            process = _ProcessingQueue[0];
            _ProcessingQueue.Remove(0);
        }
        _ProcessingQueueMutex.Unlock();
        return process;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Manager::_RunProcess()
    {
        _UpdateMutex.Lock();
        if (_Process->GetChunk().Load())
            _Process->GetChunk().LoadLOD(_Process->GetLODIndex());
        _FindResourceLibrary(_Process->GetChunk().GetFilePath())->QueueProcess(*_Process);
        _UpdateMutex.Unlock();
    }

    //--------------------------------------------------------------------------------------------//

    void Manager::_UpdateResources()
    {
        uint32 resource_index=0;
        while(1)
        {
            shell::Locker update_locker(_UpdateMutex);
            shell::Locker resource_locker(_ResourceMutex);
            if (resource_index>=_ResourceArray.GetSize())
                break;
            resource::Object* resource = _ResourceArray[resource_index];
            resource->Update();       
            ++resource_index;
        }
    }

}
}
