#ifndef _COFFEE_RESOURCE_H_
#define _COFFEE_RESOURCE_H_

#include "coffee_includes.h"
#include "kernel/resource/chunk/resource_chunk.h"
#include "kernel/resource/state/resource_state.h"
#include "kernel/resource/mode/resource_mode.h"
#include "kernel/resource/property/resource_property.h"

namespace coffee
{
namespace resource
{
    //--------------------------------------------------------------------------------------------//
    /// Resource object base class
    ///
    /// The resource base class is used as a resource instance and a resource.
    /// This class manages resource instancing and properties instancing, LOD and more internal
    /// functionalities are managed by the resource chunk.
    ///
    /// @see coffee::resource::Chunk
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Object : public meta::Object
    {
        friend class Chunk;
        
        COFFEE_Type(Object);
        
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Object();
        Object(const resource::Object& resource);
        Object(Chunk& chunk);
        virtual ~Object();

        //-OPERATORS------------------------------------------------------------------------------//

        resource::Object& operator =(const resource::Object& resource);
        resource::Object& operator =(Chunk& chunk);

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetFilePath(const storage::Path& file_path) { _FilePath = file_path; }
        const storage::Path& GetFilePath() const { return _FilePath; }
        void SetState(const STATE& state) { _State = state; }
        const STATE& GetState() const { return _State; }
        const Chunk& GetChunk() const { return *_Chunk; }
        Chunk& GetChunk() { return *_Chunk; }
        void SetLODIndex(uint32 lod_index) { _LODIndex = lod_index; }
        uint32 GetLODIndex() const { return _LODIndex; }
        void SetWantedLODIndex(uint32 lod_index) { _WantedLODIndex = lod_index; }
        void SetChunkState(const CHUNK_STATE& chunk_state) { _ChunkState = chunk_state; }
        uint32 GetStamp() const { return _Stamp; }

        //-QUERIES--------------------------------------------------------------------------------//

        virtual basic::String GetResourceName() const;
        virtual basic::String GetResourceType() const;
        virtual uint32 GetResourceModes() const;
        bool HasResourceMode(const MODE& mode) const;
        virtual const meta::Type& GetLODParamType() const;
        virtual bool IsReadyToInitialize() const;
        bool HasChunk() const;

        bool IsInstantiated() const;
        bool IsInvalid() const;
        bool IsAvailable(uint32 lod_index = NONE) const;

        const resource::Object& GetResource() const;
        resource::Object& GetResource();
       
        //-HANDLERS-------------------------------------------------------------------------------//

        virtual bool Initialize();              ///< initialize source only
        virtual bool Finalize();                ///< finalize source only
        virtual void ConstructInstance();       ///< instance constructor, used for non-default constructors
        virtual bool InitializeInstance();      ///< initialize instance only
        virtual bool FinalizeInstance();        ///< finalize instance only
        virtual void Update();
        virtual bool OnInstantiateProperty(PropertyBase& property, PropertyBase& source_property, bool it_is_instantiating);

        //-OPERATIONS-----------------------------------------------------------------------------//

        void PreCreateLOD(uint32 lod_index);
        void PostCreateLOD(Chunk& chunk);
        void QueryLOD(uint32 lod_index);
        void PreSaveLOD(uint32 lod_index);
        virtual void PostSerialize(storage::MODE mode);

    protected:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _Destroy();
        void _PostInstantiate(const resource::Object& object);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _Instantiate(Chunk& chunk);
        void _Copy(resource::Object& resource);
        void _BindProperties(uint32 binded_lod);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        storage::Path _FilePath;
        STATE _State;
        Chunk* _Chunk;
        uint32 _LODIndex;
        uint32 _WantedLODIndex;
        CHUNK_STATE _ChunkState;
        Chunk* _LODChunk;
        uint32 _Stamp;
        bool _IsInstanceInitialized;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Object);
}
}
#endif
