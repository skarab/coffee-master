#ifndef _EDITOR_ASSET_IMPORTER_H_
#define _EDITOR_ASSET_IMPORTER_H_

#include "coffee_editor_includes.h"
#include "asset/asset_mode.h"

namespace coffee_editor
{
namespace asset
{
    //--------------------------------------------------------------------------------------------//
    /// Importer manages a specific asset and stores its import settings
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API Importer : public meta::Object
    {
        COFFEE_Type(Importer);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Importer();
        virtual ~Importer();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetSynchronizationMode(MODE mode) { _SynchronizationMode = mode; }
        MODE GetSynchronizationMode() const { return _SynchronizationMode; }
        void SetAssetPath(storage::Path asset_path) { _AssetPath = asset_path; }
        const storage::Path& GetAssetPath() const { return _AssetPath; }
        storage::Path GetImportPath() const { return _AssetPath+".import"; }
        const basic::Vector<storage::Path>& GetResourcePathes() const { return _ResourcePathes; }
        void SetProgress(real progress) { _Progress = progress; }
        real GetProgress() const { return _Progress; }

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void Synchronize(const storage::Path& import_path, const storage::Path& asset_path, uint32 flags);
        virtual bool Import() { return false; }
        void SaveImportedResources();
        virtual void OnPostSaveResources() {};
        virtual bool Create(const storage::PhysicalPath& asset_path, const storage::Path& logical_path)  { return false; }
        virtual bool Delete();
        virtual bool Move();
        virtual bool BreakDependencies();
        void DeleteImportedResources();
        void AddImportedResource(resource::Chunk* resource_chunk);
        void AddThumbnail(resource::Chunk* resource_chunk);

    protected:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Prow<resource::Chunk*, true> _Resources;

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        MODE _SynchronizationMode;
        storage::Path _AssetPath;
        real _Progress;
        basic::Vector<storage::Path> _ResourcePathes;
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, Importer);
}
}
#endif
