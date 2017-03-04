#include "kernel/resource/resource_object.h"
#include "kernel/resource/resource_manager.h"
#include "kernel/resource/resource_manager.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(resource::Object);
        COFFEE_Attribute(storage::Path, _FilePath, meta::MODE_Serializeable);
        COFFEE_Attribute(uint32, _Stamp, meta::MODE_Serializeable);
    COFFEE_EndType();

namespace resource
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Object::Object() :
        _State(STATE_Unused),
        _Chunk(NULL),
        _LODIndex(12),
        _WantedLODIndex(0),
        _ChunkState(CHUNK_STATE_None),
        _LODChunk(NULL),
        _Stamp(0),
        _IsInstanceInitialized(false)
    {
        if (Manager::IsAvailable())
            Manager::Get()._RegisterResource(*this);
    }

    //--------------------------------------------------------------------------------------------//

    Object::Object(const resource::Object& resource) :
        _State(STATE_Unused),
        _Chunk(NULL),
        _LODIndex(12),
        _WantedLODIndex(0),
        _ChunkState(CHUNK_STATE_None),
        _LODChunk(NULL),
        _Stamp(0),
        _IsInstanceInitialized(false)
    {
        COFFEE_Assert(resource.IsInstantiated(), core::ERROR_CODE_ResourceManager,
                "Instantiating invalid resource");
        _Instantiate(*(Chunk*)resource._Chunk);
    }

    //--------------------------------------------------------------------------------------------//

    Object::Object(Chunk& chunk) :
        _State(STATE_Unused),
        _Chunk(NULL),
        _LODIndex(0),
        _WantedLODIndex(0),
        _ChunkState(CHUNK_STATE_None),
        _LODChunk(NULL),
        _Stamp(0),
        _IsInstanceInitialized(false)
    {
        _Instantiate(chunk);
    }

    //--------------------------------------------------------------------------------------------//

    Object::~Object()
    {
        COFFEE_Assert(!_IsInstanceInitialized, core::ERROR_CODE_IncorrectUsage,
            "Resources should call _Destroy from destructor");
        _Destroy();
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    Object& Object::operator =(const resource::Object& resource)
    {
        COFFEE_Assert(resource.IsInstantiated(), core::ERROR_CODE_ResourceManager,
                "Instantiating invalid resource");
        _Instantiate(*(Chunk*)resource._Chunk);
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    resource::Object& Object::operator =(Chunk& chunk)
    {
        _Instantiate(chunk);
        return *this;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    basic::String Object::GetResourceName() const
    {
        return "";
    }

    //--------------------------------------------------------------------------------------------//

    basic::String Object::GetResourceType() const
    {
        return "";
    }

    //--------------------------------------------------------------------------------------------//

    uint32 Object::GetResourceModes() const
    {
        return 0;
    }

    //--------------------------------------------------------------------------------------------//

    bool Object::IsInstantiated() const
    {
        return (_State==STATE_Instantiated);
    }

    //--------------------------------------------------------------------------------------------//

    bool Object::IsInvalid() const
    {
        if (IsInstantiated())
            return _Chunk->IsInvalid();

        return (_State==STATE_Invalid);
    }

    //--------------------------------------------------------------------------------------------//

    bool Object::IsAvailable(uint32 lod_index) const
    {
        if (IsInstantiated())
        {
            return (_ChunkState==CHUNK_STATE_Loaded)
                && (_Chunk->IsAvailable(_LODIndex))
                && (_LODIndex==_WantedLODIndex)
                && (_ChunkState==_Chunk->GetState());
        }
        return (_State==STATE_Available);
    }

    //--------------------------------------------------------------------------------------------//

    bool Object::HasResourceMode(const MODE& mode) const
    {
        return ((GetResourceModes() & (uint32) mode) > 0);
    }

    //--------------------------------------------------------------------------------------------//

    const meta::Type& Object::GetLODParamType() const
    {
        return LODParameters::GetClassMetaType();
    }

    //--------------------------------------------------------------------------------------------//

    bool Object::IsReadyToInitialize() const
    {
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Object::HasChunk() const
    {
        return (_Chunk!=NULL);
    }

    //--------------------------------------------------------------------------------------------//

    const resource::Object& Object::GetResource() const
    {
        if(IsInstantiated())
            return _Chunk->GetLOD(_LODIndex).GetData();

        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    resource::Object& Object::GetResource()
    {
        if(IsInstantiated())
            return _Chunk->GetLOD(_LODIndex).GetData();

        return *this;
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    bool Object::Initialize()
    {
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Object::Finalize()
    {
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    void Object::ConstructInstance()
    {
    }

    //--------------------------------------------------------------------------------------------//

    bool Object::InitializeInstance()
    {
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Object::FinalizeInstance()
    {
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    void Object::Update()
    {
        Chunk* chunk;

        if(_Chunk==NULL) chunk = _LODChunk;
        else chunk = _Chunk;

        if (chunk!=NULL && _Chunk!=NULL && _Chunk->IsAvailable(_WantedLODIndex)
            && (_LODIndex!=_WantedLODIndex || _Stamp!=_Chunk->GetLOD(_LODIndex).GetData()._Stamp))
        {
            if (_IsInstanceInitialized)
            {
                FinalizeInstance();
                _IsInstanceInitialized = false;
            }
        
            _BindProperties(_WantedLODIndex);
            _LODIndex = _WantedLODIndex;
            _Stamp = _Chunk->GetLOD(_LODIndex).GetData()._Stamp;

            if (_ChunkState!=chunk->GetState())
                _ChunkState = chunk->GetState();

            if (!_IsInstanceInitialized)
            {
                COFFEE_Assert(IsInstantiated(), core::ERROR_CODE_ResourceManager, "Not an instance.");
                if (InitializeInstance())
                    _IsInstanceInitialized = true;
            }
        }
        else if(chunk!=NULL && _ChunkState!=chunk->GetState()
            && (chunk->GetState()!=CHUNK_STATE_Loaded || chunk->IsAvailable(_LODIndex)))
        {
            _ChunkState = chunk->GetState();

            if (_IsInstanceInitialized)
            {
                FinalizeInstance();
                _IsInstanceInitialized = false;
            }
        
            _BindProperties(_LODIndex);
        }
        else if (chunk!=NULL && _Chunk!=NULL && !_Chunk->IsAvailable(_WantedLODIndex))
        {
            _Stamp = -1;
        }
    }

    //--------------------------------------------------------------------------------------------//

    bool Object::OnInstantiateProperty(PropertyBase& property, PropertyBase& source_property, bool it_is_instantiating)
    {
        return true;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Object::PreCreateLOD(uint32 lod_index)
    {
        _BindProperties(lod_index);
        _LODIndex = lod_index;
    }

    //--------------------------------------------------------------------------------------------//

    void Object::PostCreateLOD(Chunk& chunk)
    {
        SetState(STATE_Available);
    }

    //--------------------------------------------------------------------------------------------//

    void Object::QueryLOD(uint32 lod_index)
    {
        _WantedLODIndex = lod_index;
        Manager::Get().Load(GetFilePath(), lod_index);
    }

    //--------------------------------------------------------------------------------------------//

    void Object::PreSaveLOD(uint32 lod_index)
    {
        if (lod_index==NONE)
        {
            for (uint32 index=0 ; index<GetChunk().GetLODCount() ; ++index)
                PreSaveLOD(index);
        }
        else
        {
            _Stamp = GetChunk().GetLOD(lod_index).GetData()._Stamp + 1;
            GetChunk().GetLOD(lod_index).GetData()._PostInstantiate(*this);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Object::PostSerialize(storage::MODE mode)
    {
        if (mode==storage::MODE_Input && _FilePath.GetLength()>0)
            _Instantiate(Manager::Get().Load(_FilePath));
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Object::_Destroy()
    {
        if (Manager::IsAvailable())
            Manager::Get()._UnregisterResource(*this);
        
        if (IsInstantiated())
        {
            if (_IsInstanceInitialized)
            {
                FinalizeInstance();
                _IsInstanceInitialized = false;
            }

            _FilePath.Set("");
            _Chunk->_NotifyInstanceDestruction();
            _Chunk = NULL;
        }

        COFFEE_Assert(!_IsInstanceInitialized, core::ERROR_CODE_ResourceManager, "Bad instance handling");
        _State = STATE_Unused;
        _BindProperties(_LODIndex);
    }

    //--------------------------------------------------------------------------------------------//
    
    void Object::_PostInstantiate(const resource::Object& object)
    {
        shell::Locker lock(resource::Manager::Get()._UpdateMutex);

        if (&GetMetaType()!=&object.GetMetaType())
            return;

        if (_IsInstanceInitialized)
        {
            FinalizeInstance();
            _IsInstanceInitialized = false;
        }

        meta::Class * meta_type = (meta::Class*) &GetMetaType();
        uint32 ancestor_index(0);
        uint32 attribute_index(0);
        meta::Attribute* attribute;
        ulong_ptr attribute_offset;

        while (meta_type->FindNextAttribute(ancestor_index, attribute_index,
            &attribute, attribute_offset))
        {
            if (attribute->_Type==&PropertyBase::GetClassMetaType())
            {
                PropertyBase* prop = (PropertyBase*)((ulong_ptr)this+attribute_offset);
                PropertyBase* source_prop = (PropertyBase*)((ulong_ptr)&object+attribute_offset);
                if (prop->IsFlagEnabled(PROPERTY_FLAG_Instantiable))
                {
                    if (source_prop->IsFlagEnabled(PROPERTY_FLAG_Enabled))
                    {
                        if (OnInstantiateProperty(*prop, *source_prop, source_prop->IsFlagEnabled(PROPERTY_FLAG_Enabled)))
                        {
                            prop->EnableFlag(PROPERTY_FLAG_Enabled, source_prop->IsFlagEnabled(PROPERTY_FLAG_Enabled));
                        }
                    }
                    else if (prop->IsFlagEnabled(PROPERTY_FLAG_Enabled))
                    {
                        if (OnInstantiateProperty(*prop, *source_prop, false))
                        {
                            prop->EnableFlag(PROPERTY_FLAG_Enabled, false);
                        }
                        else
                        {
                            COFFEE_Error(core::ERROR_CODE_IncorrectUsage, "Instantiable property not handled correctly");
                        }
                    }
                }
            }
        }

        if (!_IsInstanceInitialized && IsInstantiated())
        {
            if (InitializeInstance())
                _IsInstanceInitialized = true;
        }
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Object::_Instantiate(Chunk& chunk)
    {
        _Destroy();
        _FilePath = chunk.GetFilePath();
        _State = STATE_Instantiated;
        _Chunk = &chunk;
        _Chunk->_NotifyInstanceCreation();
        _ChunkState = CHUNK_STATE_Unused;
        _Chunk->_NotifyLoadEnd();

        if (Manager::IsAvailable())
            Manager::Get()._RegisterResource(*this);

        if (HasResourceMode(MODE_ImmediateLoad))
        {
            while(!IsAvailable() && !IsInvalid())
            {
                basic::Time time_step;
                Manager::Get()._FindResourceLibrary(GetFilePath())->Update(time_step);
                shell::Thread::Sleep();
            }
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Object::_BindProperties(uint32 binded_lod)
    {
        meta::Class * meta_type = (meta::Class*) &GetMetaType();
        uint32 ancestor_index(0);
        uint32 attribute_index(0);
        meta::Attribute* attribute;
        ulong_ptr attribute_offset;

        while (meta_type->FindNextAttribute(ancestor_index, attribute_index,
            &attribute, attribute_offset))
        {
            if (attribute->_Type==&PropertyBase::GetClassMetaType())
            {
                PropertyBase * prop;
                uint32 flags;
                uint32 lod_index;

                prop = (PropertyBase*)((ulong_ptr)this+attribute_offset);
                flags = prop->GetFlags();
                prop->SetFlags(((meta::ParamProperty*)attribute->_Param)->GetFlags());

                if(IsInstantiated())
                {
                    prop->EnableFlag(
                        PROPERTY_FLAG_Enabled,
                        prop->IsFlagEnabled(PROPERTY_FLAG_Instantiable)
                            && (flags&PROPERTY_FLAG_Enabled)>0);

                    lod_index = prop->IsFlagEnabled(PROPERTY_FLAG_LOD)?binded_lod:0;

                    if(GetChunk().IsAvailable(lod_index))
                    {
                        PropertyBase* source_prop = (PropertyBase*)(
                            (ulong_ptr)&GetChunk().GetLOD(lod_index).GetData() + attribute_offset);
                        prop->SetSourceProperty(source_prop);

                        if (prop->IsFlagEnabled(PROPERTY_FLAG_Instantiable)
                            && prop->IsFlagEnabled(PROPERTY_FLAG_AutoInstantiate)
                            && OnInstantiateProperty(*prop, *source_prop, true))
                        {
                            prop->EnableFlag(PROPERTY_FLAG_Enabled, true);
                        }
                    }
                    else
                    {
                        prop->SetSourceProperty(NULL);
                    }
                }
                else if(_LODChunk!=NULL)
                {
                    if(binded_lod==0)
                    {
                        prop->EnableFlag(PROPERTY_FLAG_Enabled, true);
                        prop->SetSourceProperty(NULL);
                    }
                    else
                    {
                        prop->EnableFlag(
                            PROPERTY_FLAG_Enabled,
                            prop->IsFlagEnabled(PROPERTY_FLAG_LOD)
                                && (flags&PROPERTY_FLAG_Enabled)>0);

                        if(_LODChunk->IsAvailable(0))
                        {
                            prop->SetSourceProperty(
                                (PropertyBase*)((ulong_ptr)&_LODChunk->GetLOD(0).GetData()
                                + attribute_offset));
                        }
                        else
                        {
                            prop->SetSourceProperty(NULL);
                        }
                    }
                }
                else
                {
                    prop->EnableFlag(
                        PROPERTY_FLAG_Enabled,
                        (flags&PROPERTY_FLAG_Enabled)>0);

                    prop->SetSourceProperty(NULL);
                }
            }
        }
    }

}
}
