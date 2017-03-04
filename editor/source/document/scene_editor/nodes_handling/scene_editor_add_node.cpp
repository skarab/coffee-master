#include "document/scene_editor/nodes_handling/scene_editor_add_node.h"
#include "document/scene_editor/scene_editor.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(SceneEditorAddNode);
        COFFEE_Ancestor(ApplicationCommand);
    COFFEE_EndType();

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SceneEditorAddNode::SceneEditorAddNode() :
        ApplicationCommand("Add", "Create a new empty node")
    {
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    void SceneEditorAddNode::OnExecute()
    {
        SceneEditor* scene_editor((SceneEditor*) &GetParent().GetParent());
        
        if (scene_editor->GetScene().GetState()==resource::HANDLER_STATE_Ready)
        {
            scene::Node* node = COFFEE_New(scene::Node);
            
			edition::SelectionManager* selection_manager = GetSelectionManager();
			edition::UndoManager* undo_manager = GetUndoManager();
			selection_manager->Clear(false);
			selection_manager->Select(*node, true, true, false);
			undo_manager->Add(COFFEE_New(edition::PluginAttachNodeUndo, node));
			undo_manager->Accept("Add Node");
        
			scene_editor->GetCurrentNode().Attach(*node);

            node->AddComponent(COFFEE_New(scene::Transform));
            node->AddComponent(COFFEE_New(scene::Bounding));

			scene_editor->UpdateExplorer();
		}
    }

}
