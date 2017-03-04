//------------------------------------------------------------------------------------------------//
/// @file document/scene_editor/nodes_handling/scene_editor_detach_node.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "document/scene_editor/nodes_handling/scene_editor_detach_node.h"
#include "document/scene_editor/scene_editor.h"
//------------------------------------------------------------------------------------------------//

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(SceneEditorDetachNode);
        COFFEE_Ancestor(ApplicationCommand);
    COFFEE_EndType();

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SceneEditorDetachNode::SceneEditorDetachNode() :
        ApplicationCommand("Detach", "Detach the selected node(s)")
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

	bool SceneEditorDetachNode::IsUsable() const
	{
        SceneEditor* scene_editor((SceneEditor*) &GetParent().GetParent());
        
		return GetSelectionManager()->GetObjectCount()>0
            && scene_editor->GetScene().GetState()==resource::HANDLER_STATE_Ready
            && scene_editor->GetCurrentNode().HasParent();
	}    

    //-HANDLERS-----------------------------------------------------------------------------------//

    void SceneEditorDetachNode::OnExecute()
    {
        SceneEditor* scene_editor((SceneEditor*) &GetParent().GetParent());

        if (scene_editor->GetScene().GetState()==resource::HANDLER_STATE_Ready)
        {
            edition::SelectionManager* selection_manager = GetSelectionManager();
            basic::Prow<meta::Object*> objects = selection_manager->GetObjectArray();
            edition::UndoManager* undo_manager = GetUndoManager();
			
            undo_manager->Begin();
            
            for (uint32 index=0 ; index<objects.GetSize() ; ++index)
            {
                scene::Node* node = static_cast<scene::Node*>(objects[index]);
                if (node!=&scene_editor->GetCurrentNode())
                {
                    basic::Matrix transform(node->GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World));
                    undo_manager->Add(COFFEE_New(edition::PluginDetachNodeUndo, node));
			        node->Detach();
                    undo_manager->Add(COFFEE_New(edition::PluginAttachNodeUndo, node));
                    transform *= scene_editor->GetCurrentNode().GetParent().GetTransform().GetMatrix(scene::TRS_World, scene::TRS_Local);
			        node->GetTransform().SetPosition(transform.GetTranslation(), transform.GetRotation(), transform.GetScale());
                    scene_editor->GetCurrentNode().GetParent().Attach(*node);
                }
            }
            undo_manager->Accept(objects.GetSize()>1?"Detach Nodes":"Detach Node");
            scene_editor->UpdateExplorer();
		}
    }

}
//------------------------------------------------------------------------------------------------//
