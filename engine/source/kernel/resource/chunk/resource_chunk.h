#ifndef _COFFEE_RESOURCE_CHUNK_H_
#define _COFFEE_RESOURCE_CHUNK_H_

#include "coffee_includes.h"
#include "kernel/meta/meta.h"
#include "kernel/storage/storage.h"
#include "kernel/resource/chunk/resource_chunk_state.h"
#include "kernel/resource/lod/resource_lod.h"
#include "kernel/storage/pack/storage_pack.h"

namespace coffee
{
namespace resource
{
    //--------------------------------------------------------------------------------------------//
    /// Resource chunk - instancing and LOD manager
    ///
    /// The resource chunk hide the instancing and LOD processes.
    /// It manages resource saving, referencing, instancing and LOD on resource and properties.
    ///
    /// @see coffee::resource::Object
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Chunk : public meta::Object
    {
        COFFEE_Type(Chunk);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Chunk();
        ~Chunk();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetFilePath(const storage::Path & file_path);
        const storage::Path & GetFilePath() const;
        void SetState(const CHUNK_STATE & state);
        const CHUNK_STATE & GetState() const;
        uint32 GetLODCount() const;

        //-QUERIES--------------------------------------------------------------------------------//

        uint32 FindAvailableLOD() const;
        const LOD & GetLOD(uint32 lod_index) const;
        LOD & GetLOD(uint32 lod_index);

        bool IsInvalid() const;
        bool IsLoaded() const;
        bool HasInstances() const;
        bool IsAvailable(uint32 lod_index = NONE) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        //----------------------------------------------------------------------------------------//
        /// Load the chunk
        ///
        /// It loads the chunk header only, since lod information may be needed before
        /// loading any lod.
        //----------------------------------------------------------------------------------------//
        bool Load();

        //----------------------------------------------------------------------------------------//
        /// UnLoad the chunk
        ///
        /// It unloads the chunk, and delete all lods, this is used only for resource
        /// reloading actually.
        //----------------------------------------------------------------------------------------//
        void UnLoad();

        //----------------------------------------------------------------------------------------//
        /// Save the chunk
        ///
        /// It saves the chunk header only.
        //----------------------------------------------------------------------------------------//
        bool Save();

        //----------------------------------------------------------------------------------------//
        /// Load the lod
        ///
        /// It loads one or all lods, chunk has to be loaded before.
        //----------------------------------------------------------------------------------------//
        bool LoadLOD(uint32 lod_index = NONE);

        //----------------------------------------------------------------------------------------//
        /// Save the lod
        ///
        /// It saves one or all lods, chunk header has to be saved too.
        //----------------------------------------------------------------------------------------//
        bool SaveLOD(uint32 lod_index = NONE);

        //----------------------------------------------------------------------------------------//
        /// Add a lod
        ///
        /// Used to manually add a lod in the chunk. Saving the chunk is recommended after
        /// this operation.
        //----------------------------------------------------------------------------------------//
        void AddLOD(resource::Object & resource_lod, uint32 lod_index = NONE, LODParameters * lod_parameters = NULL);

        //----------------------------------------------------------------------------------------//
        /// Remove a lod
        ///
        /// Used to manually remove a lod in the chunk. Saving the chunk is recommended after
        /// this operation.
        //----------------------------------------------------------------------------------------//
        void RemoveLOD(uint32 lod_index);

        // internal methods (garbage collecting and initialization)
        void _NotifyInstanceCreation();
        void _NotifyInstanceDestruction();
        void _NotifyInitialize();
        void _NotifyFinalize();

        // loading token, used to be sure the chunk isnt destroyed when being loaded (no mutex lock)
        void _NotifyLoadStart();
        void _NotifyLoadEnd();
        bool _IsLoading() const;

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool _InternalLoadLOD(uint32 lod_index);
        bool _InternalSaveLOD(uint32 lod_index);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        storage::Path _FilePath;                    ///< file path of the resource
        CHUNK_STATE _State;                         ///< current chunk state
        uint32 _InstancesCount;                     ///< how many times is this chunk instantiated
        uint32 _LoadCount;                          ///< used to know if some LODs are loading
        basic::Prow< LOD *, true > _LODArray;       ///< loaded LODs
        storage::Pack _Pack;                        ///< LOD data are packed into a single file
        uint32 _LoadStamp;                          ///< increase LOD data stamps at each loading
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Chunk);
}
}
#endif
