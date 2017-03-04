#include "kernel/resource/library/resource_library.h"
#include "kernel/resource/resource_manager.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(resource::Library);
        COFFEE_Ancestor(shell::Module);
    COFFEE_EndType();

namespace resource
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Library::Library()
    {
    }

    //--------------------------------------------------------------------------------------------//

    Library::Library(basic::String resource_name) :
        _ResourceName(resource_name),
        _MaximumProcessCount(5),
        _MaximumRemovedChunkCount(5)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Library::~Library()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const basic::String& Library::GetResourceName() const
    {
        return _ResourceName;
    }

    //--------------------------------------------------------------------------------------------//

    uint32 Library::GetResourceCount() const
    {
        return _ChunkArray.GetSize();
    }

    //-QUERIES------------------------------------------------------------------------------------//

    uint32 Library::GetLoadingResourceCount() const
    {
        return _ProcessingQueue.GetSize() + _Processes.GetSize();
    }

    //--------------------------------------------------------------------------------------------//

    bool Library::FindChunk(Chunk** chunk, const storage::Path& resource_path, uint32 lod_index)
    {
        {
            shell::Locker locked(_ProcessingQueueMutex);
            for(uint32 index=0 ; index<_ProcessingQueue.GetSize() ; ++index)
            {
                if(_ProcessingQueue[index]->GetChunk().GetFilePath()==resource_path)
                {
                    *chunk = &_ProcessingQueue[index]->GetChunk();
                    (*chunk)->_NotifyLoadStart();
                    if(_ProcessingQueue[index]->GetLODIndex()==lod_index
                        || _ProcessingQueue[index]->GetLODIndex()==NONE)
                    {
                        return !(*chunk)->IsInvalid();
                    }
                }
            }
        }

        {
            shell::Locker locked(_ProcessMutex);
            for (uint32 index=0 ; index<_Processes.GetSize() ; ++index)
            {
                if (_Processes[index]->GetChunk().GetFilePath()==resource_path)
                {
                    *chunk = &_Processes[index]->GetChunk();
                    (*chunk)->_NotifyLoadStart();
                    if (_Processes[index]->GetLODIndex()==lod_index || _Processes[index]->GetLODIndex()==NONE)
                        return !(*chunk)->IsInvalid();
                }
            }
        }

        {
            shell::Locker locked(_ChunkArrayMutex);
            for (uint32 chunk_index=0 ; chunk_index<_ChunkArray.GetSize() ; ++chunk_index)
            {
                if (_ChunkArray[chunk_index]->GetFilePath()==resource_path)
                {
                    *chunk = _ChunkArray[chunk_index];
                    (*chunk)->_NotifyLoadStart();
                    if (_ChunkArray[chunk_index]->IsAvailable(lod_index))
                        return true;
                    break;
                }
            }
        }
        return false;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Library::OnInitialize()
    {
    }

    //--------------------------------------------------------------------------------------------//

    void Library::OnFinalize()
    {
        shell::Locker chunks_lock(_ChunkArrayMutex);
        shell::Locker processing_lock(_ProcessingQueueMutex);
        shell::Locker process_lock(_ProcessMutex);

        if (Manager::IsInstantiated())
            Manager::Get().UnregisterLibrary(*this);

        for (uint32 process_index=0 ; process_index<_ProcessingQueue.GetSize() ; ++process_index)
        {
            _ProcessingQueue[process_index]->Destroy();
            COFFEE_Delete(_ProcessingQueue[process_index]);
        }
        
        for (int32 index=_Processes.GetSize()-1 ; index>=0 ; --index)
            COFFEE_Delete(_Processes[index]);
        _Processes.Erase();

        for (int32 chunk_index=(int32)_ChunkArray.GetSize()-1 ; chunk_index>=0 ; --chunk_index)
        {
            if (_ChunkArray[chunk_index]->IsLoaded())
                _ChunkArray[chunk_index]->_NotifyFinalize();
            COFFEE_Delete(_ChunkArray[chunk_index]);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Library::OnUpdate(const basic::Time& time_step)
    {
        _ProcessMutex.Lock();
        uint32 process_count(0);
        Process* process; 
        while (process_count<_MaximumProcessCount
            && ((process=_GetNextProcess()) != NULL))
        {
            uint32 index = _Processes.AddItem(process);
            _ProcessMutex.Unlock();
            _RunProcess(*process);
            _ProcessMutex.Lock();
            _Processes.Remove(index);
            process->GetChunk()._NotifyInstanceDestruction();
            COFFEE_Delete(process);
            ++process_count;
        }
        _ProcessMutex.Unlock();

        uint32 removed_chunk_count(0);
        Chunk* chunk;
        while (removed_chunk_count<_MaximumRemovedChunkCount
            && ((chunk=_GetNextChunkToRemove())!=NULL))
        {
            if (chunk->IsLoaded())
                chunk->_NotifyFinalize();
            COFFEE_Delete(chunk);
            ++removed_chunk_count;
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Library::QueueProcess(Process& process)
    {
        _ProcessingQueueMutex.Lock();
        _ProcessingQueue.AddItem(&process);
        _ProcessingQueueMutex.Unlock();
    }

    //--------------------------------------------------------------------------------------------//

    Chunk* Library::PrepareReloadChunk(Chunk& chunk)
    {
        // Finish processing all chunks, else we may miss some!
        while (_ProcessingQueue.GetSize()>0)
            OnUpdate(basic::Time());
        
        _ChunkArrayMutex.Lock();
        for (uint32 chunk_index=0 ; chunk_index<_ChunkArray.GetSize() ; ++chunk_index)
        {
            if (_ChunkArray[chunk_index]==&chunk)
            {
                Chunk* chunk = _ChunkArray[chunk_index];
                _ChunkArray.Remove(chunk_index);
                _ChunkArrayMutex.Unlock();
                if(chunk->IsLoaded())
                    chunk->_NotifyFinalize();
                return chunk;
            }
        }
        _ChunkArrayMutex.Unlock();
        return NULL;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    Process* Library::_GetNextProcess()
    {
        Process* process(NULL);
        _ProcessingQueueMutex.Lock();
        for (uint32 process_index=0 ; process_index<_ProcessingQueue.GetSize() ; ++process_index)
        {
            process = _ProcessingQueue[ process_index ];
            if (!process->GetChunk().IsInvalid() && process->GetChunk().GetState()==CHUNK_STATE_Loaded)
            {
                if (process->GetLODIndex()==NONE)
                {
                    for (uint32 lod_index=0 ; lod_index<process->GetChunk().GetLODCount() ; ++lod_index)
                    {
                        if (process->GetLODIndex()==NONE)
                            process->SetLODIndex(0);

                        if (process->GetChunk().GetLOD(process->GetLODIndex()).HasData()
                            && !process->GetChunk().GetLOD(process->GetLODIndex()).GetData().IsReadyToInitialize())
                        {
                            process = NULL;
                            break;
                        }
                    }
                }
                else
                {
                    if (process->GetChunk().GetLOD(process->GetLODIndex()).HasData()
                        && !process->GetChunk().GetLOD(process->GetLODIndex()).GetData().IsReadyToInitialize())
                    {
                        process = NULL;
                    }
                }
            }

            if (process!=NULL)
            {
                _ProcessingQueue.Remove(process_index);
                break;
            }
        }        
        _ProcessingQueueMutex.Unlock();
        return process;
    }

    //--------------------------------------------------------------------------------------------//

    Chunk* Library::_GetNextChunkToRemove()
    {
        shell::Locker lock(_ChunkArrayMutex);        
        for (uint32 chunk_index=0 ; chunk_index<_ChunkArray.GetSize() ; ++chunk_index)
        {
            if (!_ChunkArray[chunk_index]->HasInstances() && !_ChunkArray[chunk_index]->_IsLoading())
            {
                Chunk* chunk = _ChunkArray[chunk_index];
                _ChunkArray.Remove(chunk_index);
                return chunk;
            }
        }
        return NULL;
    }

    //--------------------------------------------------------------------------------------------//

    void Library::_RunProcess(Process& process)
    {
        if (process.GetChunk().IsLoaded())
            process.GetChunk()._NotifyInitialize();
        _ChunkArrayMutex.Lock();
        bool it_has_chunk(false);
        for (uint32 chunk_index=0 ; chunk_index<_ChunkArray.GetSize() ; ++chunk_index)
        {
            if (_ChunkArray[chunk_index]==&process.GetChunk())
                it_has_chunk = true;
        }
        if (!it_has_chunk)
            _ChunkArray.AddItem(&process.GetChunk());        
        _ChunkArrayMutex.Unlock();
    }

}
}
