#include "kernel/resource/chunk/resource_chunk.h"
#include "kernel/resource/resource_object.h"
#include "kernel/resource/resource_manager.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(resource::Chunk);
        COFFEE_Attribute(storage::Path, _FilePath, meta::MODE_Editable);
        COFFEE_Attribute(resource::CHUNK_STATE, _State, meta::MODE_Editable);
        COFFEE_Attribute(< resource::LOD * >, _LODArray, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace resource
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Chunk::Chunk() :
        _State(CHUNK_STATE_Unused),
        _InstancesCount(0),
        _LoadCount(0),
        _LoadStamp(0)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Chunk::~Chunk()
    {
        COFFEE_Assert(_InstancesCount==0, core::ERROR_CODE_ResourceManager,
            "Destroying referenced resource");
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Chunk::SetFilePath(const storage::Path & file_path)
    {
        _FilePath = file_path;
    }

    //--------------------------------------------------------------------------------------------//

    const storage::Path & Chunk::GetFilePath() const
    {
        return _FilePath;
    }

    //--------------------------------------------------------------------------------------------//

    void Chunk::SetState(const CHUNK_STATE & state)
    {
        _State = state;
    }

    //--------------------------------------------------------------------------------------------//

    const CHUNK_STATE & Chunk::GetState() const
    {
        return _State;
    }

    //--------------------------------------------------------------------------------------------//

    uint32 Chunk::GetLODCount() const
    {
        return _LODArray.GetSize();
    }

    //-QUERIES------------------------------------------------------------------------------------//

    uint32 Chunk::FindAvailableLOD() const
    {
        uint32 lod_index;

        for(lod_index = 0 ; lod_index < GetLODCount() ; ++ lod_index)
        {
            if(GetLOD(lod_index).IsLoaded() && GetLOD(lod_index).GetData().IsAvailable(lod_index))
                return lod_index;
        }

        return NONE;
    }

    //--------------------------------------------------------------------------------------------//

    const LOD & Chunk::GetLOD(uint32 lod_index) const
    {
        if(lod_index == NONE)
            lod_index = FindAvailableLOD();

        return *_LODArray[ lod_index ];
    }

    //--------------------------------------------------------------------------------------------//

    LOD & Chunk::GetLOD(uint32 lod_index)
    {
        if(lod_index == NONE)
            lod_index = FindAvailableLOD();

        COFFEE_Assert(lod_index != NONE, core::ERROR_CODE_Unexpected, "Unexpected error");

        return *_LODArray[ lod_index ];
    }

    //--------------------------------------------------------------------------------------------//

    bool Chunk::IsInvalid() const
    {
        return _State == CHUNK_STATE_Invalid; // || _LODArray.GetSize()==0;
    }

    //--------------------------------------------------------------------------------------------//

    bool Chunk::IsLoaded() const
    {
        return (_State == CHUNK_STATE_Loaded);
    }

    //--------------------------------------------------------------------------------------------//

    bool Chunk::HasInstances() const
    {
        return (_InstancesCount > 0);
    }

    //--------------------------------------------------------------------------------------------//

    bool Chunk::IsAvailable(uint32 lod_index) const
    {
        if(lod_index == NONE)
            return (FindAvailableLOD() != NONE);

        return (lod_index < _LODArray.GetSize()
            && _LODArray[ lod_index ] != NULL
            && GetLOD(lod_index).IsLoaded()
            && GetLOD(lod_index).HasData()
            && GetLOD(lod_index).GetData().IsAvailable(lod_index));
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool Chunk::Load()
    {
        meta::Stream stream;
        
        // TODO: Invalid chunk should be human-readable

        if (!IsLoaded())
        {
            if (_Pack.Open(_FilePath, storage::MODE_Input))
            {
                if (_Pack.GetFile(storage::Path("header"), stream.GetStream()))
                {
                    _LODArray.Erase();
                    stream.Open(storage::MODE_Input);
                    meta::Serializer* serializer = COFFEE_New(meta::Serializer);
                    serializer->Serialize(*this, stream);
                    COFFEE_Delete(serializer);
                    stream.Close();
                }
                _Pack.Close();
            }
        }

        _State = (GetLODCount()==0)? CHUNK_STATE_Invalid : CHUNK_STATE_Loaded;
        return IsLoaded();
    }

    //--------------------------------------------------------------------------------------------//

    void Chunk::UnLoad()
    {
        _State = CHUNK_STATE_Unused;
        _LODArray.Erase();
    }

    //--------------------------------------------------------------------------------------------//

    bool Chunk::Save()
    {
        if (IsLoaded() && _Pack.Open(_FilePath, storage::MODE_Output))
        {
            uint32 count = _InstancesCount;
            meta::Stream stream;
            stream.Open(storage::MODE_Output);
            meta::Serializer* serializer = COFFEE_New(meta::Serializer);
            serializer->Serialize(*this, stream);
            COFFEE_Delete(serializer);
            stream.Close();
            _Pack.AddFile(storage::Path("header"), stream.RetrieveStream());
            _Pack.Close();
            _InstancesCount = count;
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Chunk::LoadLOD(uint32 lod_index)
    {
        if(lod_index == NONE)
        {
            bool it_has_failed(false);

            for(lod_index = 0 ; lod_index < GetLODCount() ; ++ lod_index)
                it_has_failed |= !_InternalLoadLOD(lod_index);

            return it_has_failed;
        }

        return _InternalLoadLOD(lod_index);
    }

    //--------------------------------------------------------------------------------------------//

    bool Chunk::SaveLOD(uint32 lod_index)
    {
        if(lod_index == NONE)
        {
            bool it_has_failed(false);

            for(lod_index = 0 ; lod_index < GetLODCount() ; ++ lod_index)
                it_has_failed |= !_InternalSaveLOD(lod_index);

            return !it_has_failed;
        }

        return _InternalSaveLOD(lod_index);
    }

    //--------------------------------------------------------------------------------------------//

    void Chunk::AddLOD(resource::Object & resource_lod, uint32 lod_index, LODParameters * lod_parameters)
    {
        LOD * lod = COFFEE_New(LOD);
        lod->SetData(resource_lod);

        if(lod_parameters != NULL)
        {
            lod->SetParameters(*lod_parameters);
        }
        else if(resource_lod.HasResourceMode(MODE_LevelOfDetail))
        {
            lod_parameters = (LODParameters *) resource_lod.GetLODParamType().CreateObject();
            lod->SetParameters(*lod_parameters);
        }

        lod->SetState(LOD_STATE_Loaded);
        _LODArray.AddItem(lod, lod_index);

        for(uint32 index = 0 ; index < _LODArray.GetSize() ; index ++)
        {
            if(_LODArray[ index ]->HasData())
                _LODArray[ index ]->GetData().SetLODIndex(index);
        }

        resource_lod.PostCreateLOD(*this);
    }

    //--------------------------------------------------------------------------------------------//

    void Chunk::RemoveLOD(uint32 lod_index)
    {
        if(GetLOD(lod_index).IsLoaded() && GetLOD(lod_index).GetData().IsAvailable())
            GetLOD(lod_index).GetData().Finalize();

        COFFEE_Delete(_LODArray[lod_index]);
        _LODArray.Remove(lod_index);

        for (uint32 index=0 ; index<_LODArray.GetSize() ; ++index)
        {
            if (_LODArray[index]->HasData())
                _LODArray[index]->GetData().SetLODIndex(index);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Chunk::_NotifyInstanceCreation()
    {
        ++_InstancesCount;
    }

    //--------------------------------------------------------------------------------------------//

    void Chunk::_NotifyInstanceDestruction()
    {
        COFFEE_Assert(_InstancesCount>0, core::ERROR_CODE_Unexpected, "chunk is not instantiated");
        --_InstancesCount;
    }

    //--------------------------------------------------------------------------------------------//

    void Chunk::_NotifyInitialize()
    {
        uint32 lod_index;

        for(lod_index = 0 ; lod_index < GetLODCount() ; ++ lod_index)
        {
            if(GetLOD(lod_index).IsLoaded() && !GetLOD(lod_index).GetData().IsAvailable())
            {
                GetLOD(lod_index).GetData()._LODIndex = lod_index;
                GetLOD(lod_index).GetData()._LODChunk = this;
                GetLOD(lod_index).GetData()._BindProperties(lod_index);

                GetLOD(lod_index).GetData().SetFilePath(GetFilePath());

                if (GetLOD(lod_index).GetData().Initialize())
                {
                    GetLOD(lod_index).GetData().SetState(STATE_Available);
                }
                else
                {
                    GetLOD(lod_index).GetData().SetState(STATE_Invalid);
                }

                GetLOD(lod_index).GetData().SetFilePath("");
            }
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Chunk::_NotifyFinalize()
    {
        uint32 lod_index;

        for(lod_index = 0 ; lod_index < GetLODCount() ; ++ lod_index)
        {
            if (GetLOD(lod_index).IsLoaded() && GetLOD(lod_index).GetData().IsAvailable())
            {
                GetLOD(lod_index).GetData().SetFilePath(GetFilePath());
                GetLOD(lod_index).GetData().Finalize();
                GetLOD(lod_index).GetData().SetFilePath("");
            }
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Chunk::_NotifyLoadStart()
    {
        _LoadCount = 1;
    }

    //--------------------------------------------------------------------------------------------//

    void Chunk::_NotifyLoadEnd()
    {
        _LoadCount = 0;
    }
      
    //--------------------------------------------------------------------------------------------//

    bool Chunk::_IsLoading() const
    {
        return _LoadCount!=0;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool Chunk::_InternalLoadLOD(uint32 lod_index)
    {
        storage::Path file_path(basic::String("lod%i", lod_index));
        meta::Stream stream;
        meta::ObjectPointer object_reference;

        if (lod_index<GetLODCount())
        {
            if (GetLOD(lod_index).IsLoaded())
                return true;

            if (_Pack.Open(_FilePath, storage::MODE_Input)
                && _Pack.GetFile(file_path, stream.GetStream()))
            {
                stream.Open(storage::MODE_Input);
                meta::Serializer* serializer = COFFEE_New(meta::Serializer);
                serializer->Serialize(object_reference, stream);
                COFFEE_Delete(serializer);
                stream.Close();
                
                resource::Object* lod = static_cast<resource::Object*>(object_reference.GetObject());
                if (lod!=NULL)
                {   
                    COFFEE_Assert(lod->GetFilePath().IsEmpty(), core::ERROR_CODE_ResourceManager, "resource LOD shouldn't have filepath stored !");
                    GetLOD(lod_index).SetData(*lod);
                    GetLOD(lod_index).SetState(LOD_STATE_Loaded);
                    GetLOD(lod_index).GetData().SetState(STATE_Streamed);

                    GetLOD(lod_index).GetData()._Stamp += ++_LoadStamp;
                    if (GetLOD(lod_index).GetData()._Stamp==0)
                        GetLOD(lod_index).GetData()._Stamp = 1;
                    
                    _Pack.Close();
                    return true;
                }
            }

            _Pack.Close();
            GetLOD(lod_index).SetState(LOD_STATE_Invalid);
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Chunk::_InternalSaveLOD(uint32 lod_index)
    {
        if (lod_index<GetLODCount() && GetLOD(lod_index).IsLoaded() && GetLOD(lod_index).HasData())
        {
            storage::Path file_path(basic::String("lod%i", lod_index));
            meta::ObjectPointer object_reference;
            object_reference.SetObject(&GetLOD(lod_index).GetData());

            // LOD shouldn't have file path, else it auto instantiates itself at loading !
            GetLOD(lod_index).GetData().SetFilePath("");
            
            ++GetLOD(lod_index).GetData()._Stamp;
            if (GetLOD(lod_index).GetData()._Stamp==0)
                GetLOD(lod_index).GetData()._Stamp = 1;

            if (_Pack.Open(_FilePath, storage::MODE_Output))
            {
                meta::Stream stream;
                stream.Open(storage::MODE_Output);
                meta::Serializer* serializer = COFFEE_New(meta::Serializer);
                serializer->Serialize(object_reference, stream);
                COFFEE_Delete(serializer);
                stream.Close();
                _Pack.AddFile(file_path, stream.RetrieveStream());
                _Pack.Close();
                return true;
            }
        }
        return false;
    }

}
}
