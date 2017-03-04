#include "document/scene_editor/nodes_handling/scene_editor_open_node.h"
#include "document/scene_editor/scene_editor.h"
#include "document/scene_editor/nodes_handling/scene_editor_set_root_undo.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(SceneEditorOpenNode);
        COFFEE_Ancestor(ApplicationCommand);
    COFFEE_EndType();

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SceneEditorOpenNode::SceneEditorOpenNode() :
        ApplicationCommand("Open", "Open node")
    {
    }

	//-QUERIES------------------------------------------------------------------------------------//

	bool SceneEditorOpenNode::IsUsable() const
	{
		return GetSelectionManager()->GetObjectCount()==1
            && !GetSelectionManager()->GetObject(0).IsKindOf<scene::Instance>();
	}

    //-HANDLERS-----------------------------------------------------------------------------------//

    void SceneEditorOpenNode::OnExecute()
    {
        SceneEditor* scene_editor((SceneEditor*) &GetParent().GetParent());
        edition::SelectionManager* selection_manager = GetSelectionManager();

        if (scene_editor->GetScene().GetState()==resource::HANDLER_STATE_Ready
            && selection_manager->GetObjectCount()>0)
        {
            edition::UndoManager* undo_manager = GetUndoManager();
			undo_manager->Begin();
            undo_manager->Add(COFFEE_New(SceneEditorSetRootUndo));
            undo_manager->Accept("Open Node");

            scene_editor->SetCurrentNode(static_cast<scene::Node*>(
                &selection_manager->GetObject(0)));
            scene_editor->UpdateExplorer();
        }
    }

}
