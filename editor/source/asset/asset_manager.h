#ifndef _EDITOR_ASSET_MANAGER_H_
#define _EDITOR_ASSET_MANAGER_H_

#include "coffee_editor_includes.h"
#include "asset/asset_sync_flag.h"
#include "asset/asset_importer.h"
#include "asset/asset_widget.h"

namespace coffee_editor
{
namespace asset
{
    //--------------------------------------------------------------------------------------------//
    /// Manages asset importers
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API Manager : public meta::Object
    {
        COFFEE_DeclareSingleton(Manager);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Manager();
        ~Manager();

        //-QUERIES--------------------------------------------------------------------------------//

        storage::Path GetAssetPath(const storage::Path& import_path) const;
        storage::Path GetImportPath(const storage::Path& asset_path) const;
        storage::Path GetStampPath(const storage::Path& asset_path) const;
        storage::Path GetResourcePath(const storage::Path& asset_path) const;
        storage::Path GetThumbnailPath(const storage::Path& path) const;
        graphics::Texture GetThumbnail(const storage::Path& path) const;
        bool IsAssetSupported(const storage::PhysicalPath& path) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Update(const basic::Time& time_step);
        void Synchronize(uint32 flags=0);
        void Import(Importer& importer);
        Importer* LoadImporter(const storage::Path& path) const;
        bool CreateAsset(const storage::Path& asset_path);
        bool Delete(const storage::Path& path);
        bool Move(const storage::Path& path);
        bool BreakDependencies(const storage::Path& path);
        void ReImport(const storage::Path& path);
        void ActivateAsset(const storage::Path& path);
        void OnImport(const storage::Path& output_path);
        void OnImport(const storage::PhysicalPath& path, const storage::Path& output_path);
        resource::Chunk* GenerateThumbnail(const storage::Path& path, const basic::Image& source);

        template<class T> void Register()
        {
            _ImporterType* importer = COFFEE_New(_ImporterType);
            importer->_IsSupporting = &T::IsSupporting;
            importer->_MetaType = (meta::Class*)&meta::TYPE<T>().Get();
            _Importers.AddItem(importer);
        }

        template<class T> void Unregister()
        {
            for (uint32 index=0 ; index<_Importers.GetSize() ; ++index)
            {
                if (_Importers[index]->_MetaType==&meta::TYPE<T>().Get())
                {
                    _Importers.Remove(index);
                    return;
                }
            }
            COFFEE_Error(core::ERROR_CODE_IncorrectUsage, "Importer doesnt exist");
        }

    private:

        //-QUERIES--------------------------------------------------------------------------------//

        meta::Class* _FindImporterType(const basic::String& file_extension) const;
        storage::Path _GetThumbnailPath(const storage::Path& path) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _Synchronize(storage::Path root_path, uint32 flags);
		void _SynchronizeFolder(const storage::Path& folder, uint32 flags);
		void _SynchronizeAsset(const storage::Path& asset, uint32 flags);
        
        //-FUNCTIONS------------------------------------------------------------------------------//

        static void ThreadedUpdate(meta::Object* object);

        //-TYPES----------------------------------------------------------------------------------//

        struct _ImporterType
        {
            _ImporterType() : _IsSupporting(NULL), _MetaType(NULL) {}
            bool (*_IsSupporting)(const basic::String& file_extension);
            meta::Class* _MetaType;
        };

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Time _SynchronizationTime;
        basic::Prow<_ImporterType*, true> _Importers;
        bool _ForceReimport;
        shell::Thread _ImportThread;
        basic::Vector<storage::Path> _ImportQueue;
        Importer* _Importer;
        bool _ItHasFinishedImport;
        shell::Mutex _ImporterMutex;
    };

}
}
#endif
