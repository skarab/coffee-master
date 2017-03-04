//------------------------------------------------------------------------------------------------//
/// @file document/scene_editor/nodes_handling/scene_editor_group_nodes.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "document/scene_editor/nodes_handling/scene_editor_group_nodes.h"
#include "document/scene_editor/scene_editor.h"
//------------------------------------------------------------------------------------------------//

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(SceneEditorGroupNodes);
        COFFEE_Ancestor(ApplicationCommand);
    COFFEE_EndType();

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SceneEditorGroupNodes::SceneEditorGroupNodes() :
        ApplicationCommand("Group", "Group selected node(s)")
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

	bool SceneEditorGroupNodes::IsUsable() const
	{
		return GetSelectionManager()->GetObjectCount()>0;
	}    

    //-HANDLERS-----------------------------------------------------------------------------------//

    void SceneEditorGroupNodes::OnExecute()
    {
        SceneEditor* scene_editor((SceneEditor*) &GetParent().GetParent());
        
        if (scene_editor->GetScene().GetState()==resource::HANDLER_STATE_Ready)
        {
            edition::SelectionManager* selection_manager = GetSelectionManager();
            basic::Prow<meta::Object*> objects = selection_manager->GetObjectArray();
            edition::UndoManager* undo_manager = GetUndoManager();
			
            scene::Node* node = COFFEE_New(scene::Node, "Group");
            node->AddComponent(COFFEE_New(scene::Transform));
            node->AddComponent(COFFEE_New(scene::Bounding));

            selection_manager->Clear(false);
            selection_manager->Select(*node, true, true, false);
			undo_manager->Add(COFFEE_New(edition::PluginAttachNodeUndo, node));
			scene_editor->GetCurrentNode().Attach(*node);
			
            for (uint32 index=0 ; index<objects.GetSize() ; ++index)
            {
                scene::Node* child = static_cast<scene::Node*>(objects[index]);
                undo_manager->Add(COFFEE_New(edition::PluginDetachNodeUndo, child));
			    child->Detach();
                undo_manager->Add(COFFEE_New(edition::PluginAttachNodeUndo, child));
			    node->Attach(*child);
            }

            selection_manager->Select(*node, true, true, false);
			undo_manager->Accept("Create Group");        
			scene_editor->UpdateExplorer();
		}
    }

}
//------------------------------------------------------------------------------------------------//
