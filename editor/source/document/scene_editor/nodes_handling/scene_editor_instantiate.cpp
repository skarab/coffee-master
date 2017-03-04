#include "document/scene_editor/nodes_handling/scene_editor_instantiate.h"
#include "document/scene_editor/scene_editor.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(SceneEditorInstantiate);
        COFFEE_Ancestor(ApplicationCommand);
    COFFEE_EndType();

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SceneEditorInstantiate::SceneEditorInstantiate() :
        ApplicationCommand("Instantiate..", "Instantiate...")
    {
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    void SceneEditorInstantiate::OnExecute()
    {
        SceneEditor* scene_editor((SceneEditor*) &GetParent().GetParent());
        
        if (scene_editor->GetScene().GetState()==resource::HANDLER_STATE_Ready)
        {
            ui::FileDialog* file_dialog;
            basic::Text extensions;
            extensions.AddLine("Scenes");
            extensions.AddLine("scene");
            file_dialog = COFFEE_New(ui::FileDialog);
            file_dialog->Create(basic::String("Instantiate scene..."),
                ui::FILE_DIALOG_FLAG_Open | ui::FILE_DIALOG_FLAG_FileMustExist,
                extensions);
            if (file_dialog->DoModal())
            {
                scene::Instance* node = COFFEE_New(scene::Instance, file_dialog->GetFilePath());
                
                node->AddComponent(COFFEE_New(scene::Transform));
                node->AddComponent(COFFEE_New(scene::Bounding));

			    edition::SelectionManager* selection_manager = GetSelectionManager();
			    edition::UndoManager* undo_manager = GetUndoManager();
			    selection_manager->Clear(false);
			    selection_manager->Select(*node, true, true, false);
			    undo_manager->Add(COFFEE_New(edition::PluginAttachNodeUndo, node));
			    undo_manager->Accept("Instantiate");
            
			    scene_editor->GetCurrentNode().Attach(*node);
			    scene_editor->UpdateExplorer();
                
                file_dialog->Destroy();
		    }
        }
    }

}
