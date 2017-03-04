#ifndef _EDITOR_WIDGET_EXPLORER_H_
#define _EDITOR_WIDGET_EXPLORER_H_

#include "coffee_editor_includes.h"
#include "widget/explorer/path_info/path_info.h"

namespace coffee_editor
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Explorer
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API Explorer : public ui::Window
    {
        COFFEE_DeclareSingleton(Explorer);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Explorer();
        ~Explorer();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(ui::Window& panel);
        void Update();
		void UpdateContent();
        
        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(Explorer);
        COFFEE_Event bool OnOpenItem(shell::Event& event);
        COFFEE_Event bool OnSelectItem(shell::Event& event);
        COFFEE_Event bool OnActivateItem(shell::Event& event);
        COFFEE_Event bool OnCheckRenameItem(shell::Event& event);
        COFFEE_Event bool OnRenameItem(shell::Event& event);
        COFFEE_Event bool OnMenu(shell::Event& event);
        COFFEE_Event bool OnContextMenu(shell::Event& event);
        COFFEE_Event bool OnCommand(shell::Event& event);
        COFFEE_Event bool OnQueryDrag(shell::Event& event);
        COFFEE_Event bool OnQueryDrop(shell::Event& event);
        COFFEE_Event bool OnDrop(shell::Event& event);
        
        COFFEE_DeclareExternEventHandler(Explorer, OnCreate);
        COFFEE_DeclareExternEventHandler(Explorer, OnImport);
        COFFEE_DeclareExternEventHandler(Explorer, OnReimport);
        COFFEE_DeclareExternEventHandler(Explorer, OnDelete);
        COFFEE_DeclareExternEventHandler(Explorer, OnBreakAssets);
        
        COFFEE_DeclareExternEventHandler(Explorer, OnRun);
        COFFEE_DeclareExternEventHandler(Explorer, OnProjectManager);
        COFFEE_DeclareExternEventHandler(Explorer, OnSettings);
        COFFEE_DeclareExternEventHandler(Explorer, OnExit);
        COFFEE_DeclareExternEventHandler(Explorer, OnImportPackage);
        COFFEE_DeclareExternEventHandler(Explorer, OnBrowsePackages);
        COFFEE_DeclareExternEventHandler(Explorer, OnReimportAll);
        
    private:

        //-QUERIES--------------------------------------------------------------------------------//

        bool _Filter(const storage::Path& path) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _CreateToolBar();
        void _FillMenu(ui::widget::Menu& menu);
        void _SyncFolder(const storage::Path& path, ui::widget::TreeControlItem* item);
        void _ImportPackage(const storage::PhysicalPath& filepath);
        bool _MoveFolder(const storage::Path& path, const storage::Path& new_path);
        bool _MoveFile(const storage::Path& path, const storage::Path& new_path);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        ui::widget::Button* _MainMenu;
        ui::widget::TreeControl* _TreeControl;
        bool _ItNeedsUpdate;
    };
}
}
#endif
