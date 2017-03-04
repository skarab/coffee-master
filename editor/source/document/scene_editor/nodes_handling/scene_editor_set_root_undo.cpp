//------------------------------------------------------------------------------------------------//
/// @file document/scene_editor/nodes_handling/scene_editor_set_root_undo.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "document/scene_editor/nodes_handling/scene_editor_set_root_undo.h"
#include "document/scene_editor/scene_editor.h"
//------------------------------------------------------------------------------------------------//

namespace coffee_editor
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SceneEditorSetRootUndo::SceneEditorSetRootUndo()
    {
        _Node = &static_cast<SceneEditor&>(
            coffee::Application::Get().GetControlManager().GetActiveControl()).GetCurrentNode();
    }

    //--------------------------------------------------------------------------------------------//

    SceneEditorSetRootUndo::~SceneEditorSetRootUndo()
    {
    }

    //-OPERATIONS-----------------------------------------------------------------------------//

    void SceneEditorSetRootUndo::Undo()
    {
        SceneEditor& scene_editor(static_cast<SceneEditor&>(
            coffee::Application::Get().GetControlManager().GetActiveControl()));
        scene::Node* node = &scene_editor.GetCurrentNode();
        scene_editor.SetCurrentNode(_Node);
        _Node = node;
    }

    //--------------------------------------------------------------------------------------------//

    void SceneEditorSetRootUndo::Redo()
    {
		SceneEditor& scene_editor(static_cast<SceneEditor&>(
            coffee::Application::Get().GetControlManager().GetActiveControl()));
        scene::Node* node = &scene_editor.GetCurrentNode();
        scene_editor.SetCurrentNode(_Node);
        _Node = node;
    }

}
//------------------------------------------------------------------------------------------------//
