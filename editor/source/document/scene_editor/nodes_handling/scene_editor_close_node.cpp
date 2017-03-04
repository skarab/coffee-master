//------------------------------------------------------------------------------------------------//
/// @file document/scene_editor/nodes_handling/scene_editor_close_node.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "document/scene_editor/nodes_handling/scene_editor_close_node.h"
#include "document/scene_editor/scene_editor.h"
#include "document/scene_editor/nodes_handling/scene_editor_set_root_undo.h"
//------------------------------------------------------------------------------------------------//

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(SceneEditorCloseNode);
        COFFEE_Ancestor(ApplicationCommand);
    COFFEE_EndType();

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SceneEditorCloseNode::SceneEditorCloseNode() :
        ApplicationCommand("Close", "Close node")
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

	bool SceneEditorCloseNode::IsUsable() const
	{
		SceneEditor* scene_editor((SceneEditor*) &GetParent().GetParent());
        return scene_editor->GetScene().GetState()==resource::HANDLER_STATE_Ready
            && scene_editor->GetCurrentNode().HasParent();
	}

    //-HANDLERS-----------------------------------------------------------------------------------//

    void SceneEditorCloseNode::OnExecute()
    {
        SceneEditor* scene_editor((SceneEditor*) &GetParent().GetParent());
        
        if (scene_editor->GetScene().GetState()==resource::HANDLER_STATE_Ready
            && scene_editor->GetCurrentNode().HasParent())
        {
            edition::UndoManager* undo_manager = GetUndoManager();
			undo_manager->Begin();
            undo_manager->Add(COFFEE_New(SceneEditorSetRootUndo));
            undo_manager->Accept("Close Node");

            scene_editor->SetCurrentNode(static_cast<scene::Node*>(
                &scene_editor->GetCurrentNode().GetParent()));
            scene_editor->UpdateExplorer();
        }
    }

}
//------------------------------------------------------------------------------------------------//
