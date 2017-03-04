#ifndef _COFFEE_EDITOR_H_
#define _COFFEE_EDITOR_H_

#include "coffee_editor_includes.h"
#include "config/config.h"
#include "project/project_config.h"
#include "widget/widgets.h"
#include "asset/asset_manager.h"
#include "component/components.h"
#include "document/document.h"

namespace coffee_editor
{
    //--------------------------------------------------------------------------------------------//
    /// Editor Application
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API Application : public coffee::Application
    {
        COFFEE_DeclareSingleton(Application);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Application();
        ~Application();

        //-ACCESSORS------------------------------------------------------------------------------//

        const Config& GetConfig() const { return _Config; }
        Config& GetConfig() { return _Config; }
        const ProjectConfig& GetProjectConfig() const { return _ProjectConfig; }
        ProjectConfig& GetProjectConfig() { return _ProjectConfig; }
        const widget::EditorFrame& GetEditorFrame() const;
        widget::EditorFrame& GetEditorFrame();
        const basic::Prow< Document*, true >& GetDocumentInterfaces() const { return _DocumentInterfaces; }
        ui::Window* GetWindow();

        //-QUERIES--------------------------------------------------------------------------------//

        storage::Path GetDocumentRootPath(const storage::Path& path) const;
        bool IsDocument(const storage::Path& path) const;
        
        //-OPERATIONS-----------------------------------------------------------------------------//

        void RegisterDocumentInterface(Document* document_interface);
        Document* FindDocument(const storage::Path& path);
        Document* GetActiveDocument();
        bool IsDocumentAvailable(const storage::Path& path);
        bool IsDocumentFolderEmpty(const storage::Path& path);
        void ListFolder(basic::Prow<storage::Path*, true>& pathes, const storage::Path& path);
        void OnSelectDocumentItem(const storage::Path& path);
        bool OnRenameDocumentItem(const storage::Path& path, const storage::Path& new_path);
        void OnActivateDocumentItem(const storage::Path& path);
        bool OpenDocument(const storage::Path& document_path);
        bool CloseDocument(const storage::Path& document_path);
        bool CreateDocument(const storage::Path& document_path);
        
        void SaveConfiguration(bool it_saves_runtime=false);
        bool SetProgress(basic::String text, float percentage=0.0f);
        
        void OnInitialize();
        void OnFinalize();
        void OnUpdate(const basic::Time& time_step);

        void OnActivateControl(ApplicationControl& control);
        void OnBeginCursorOverControl(ApplicationControl& control, ui::Window& widget);
        
        void OnLog(core::Log::Type type, const char* message);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _UpdateDocumentToolBar();
        
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Config _Config;
        ProjectConfig _ProjectConfig;
        widget::EditorFrame _EditorFrame;
        asset::Manager _AssetManager;
        basic::Clock _Clock;
        basic::Time _LastUpdate;
        basic::Prow< Document*, true > _DocumentInterfaces;
        component::Types* _ComponentTypes;
    };
}
#endif
