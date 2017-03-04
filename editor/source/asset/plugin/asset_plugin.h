#ifndef _EDITOR_ASSET_PLUGIN_H_
#define _EDITOR_ASSET_PLUGIN_H_

#include "coffee_editor_includes.h"
#include "asset/asset_importer.h"
#include "asset/asset_manager.h"

namespace coffee_editor
{
namespace asset
{
    //--------------------------------------------------------------------------------------------//
    /// Plugin asset
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API Plugin : public Importer
    {
        COFFEE_Type(Plugin);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Plugin();
        virtual ~Plugin();

        //-QUERIES--------------------------------------------------------------------------------//

        static bool IsSupporting(const basic::String& file_extension);
        virtual plugins::Object* CreatePlugin() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Synchronize(const storage::Path& import_path, const storage::Path& asset_path, uint32 flags);
        virtual bool Import();
        void OnPostSaveResources();
        virtual bool Create(const storage::PhysicalPath& asset_path, const storage::Path& logical_path);
        virtual bool Delete();
        virtual bool Move();
        virtual bool BreakDependencies();

        bool Build();
        bool GenerateWorkspace();
        bool LaunchWorkspace();
        
    protected:

        //-QUERIES--------------------------------------------------------------------------------//

        virtual basic::String _GetExtension() const;
        basic::String _GetLibraryPath(const storage::Path& asset_path) const;
        storage::PhysicalPath _GetBuildLibraryPath(const storage::Path& asset_path) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool _ProcessFile(basic::String file, const storage::PhysicalPath& asset_path,
            const storage::PhysicalPath& root);        
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, Plugin);
}
}
#endif
