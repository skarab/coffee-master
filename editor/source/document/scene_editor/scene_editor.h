#ifndef _EDITOR_DOCUMENT_SCENE_EDITOR_H_
#define _EDITOR_DOCUMENT_SCENE_EDITOR_H_

#include "coffee_editor_includes.h"
#include "component/components.h"
#include "document/document.h"
#include "document/scene_editor/nodes_handling/scene_editor_node_controller.h"

namespace coffee_editor
{
    //--------------------------------------------------------------------------------------------//
    /// Scene Editor Document
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API SceneEditor : public Document
    {
        COFFEE_Type(SceneEditor);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SceneEditor();
        ~SceneEditor();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetCurrentNode(scene::Node* node);
        const scene::Node& GetCurrentNode() const;
        scene::Node& GetCurrentNode();
        const resource::Handler<scene::Resource>& GetScene() const { return _Scene; }
        resource::Handler<scene::Resource>& GetScene() { return _Scene; }
        
        //-QUERIES--------------------------------------------------------------------------------//

        bool IsAvailable() const { return _Scene.GetState()==resource::HANDLER_STATE_Ready; }
        bool HasTransparentToolBar() const { return true; }

        //-HANDLERS-------------------------------------------------------------------------------//

        void OnInitialize();
        void OnFinalize();
        void OnActivate();
        void OnDeactivate();
        void OnUpdate(const basic::Time& time_step);
        void OnRender(graphics::Viewport& viewport, bool it_is_transparent, bool it_is_hdr);
        void OnNew(const storage::Path& file_path);
        void OnOpen(const storage::Path& file_path);
        void OnSave();
        bool OnUpdateCopy();
        bool OnUpdateCut();
        bool OnUpdatePaste();
        bool OnUpdateDelete();
        void OnSelectItem(const storage::Path& path);
        bool OnRenameItem(const storage::Path& path, const storage::Path& new_path);
        void OnActivateItem(const storage::Path& path);

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(SceneEditor);
        COFFEE_Event bool OnMouseLeftButtonPressed(shell::Event& event);
        COFFEE_Event bool OnKeyPressed(shell::Event& event);
        COFFEE_Event bool OnKeyReleased(shell::Event& event);
        COFFEE_Event bool OnCommand(shell::Event& event);
        COFFEE_DeclareExternEventHandler(SceneEditor, OnRun);

        //-OPERATIONS-----------------------------------------------------------------------------//

        void FillToolbar(ui::widget::ToolBar& toolbar);
        bool IsFolderEmpty(const storage::Path& path);
        bool ListFolder(basic::Prow<storage::Path*, true>& pathes, const storage::Path& path);
        
    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _RenderGrid(graphics::Viewport& viewport);
        void _RenderHelpers(scene::Node& node);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        resource::Handler<scene::Resource> _Scene;
        scene::Node* _Camera;
        scene::Node* _CurrentNode;
        SceneEditorNodeController* _NodeController;
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, SceneEditor);
}
#endif
