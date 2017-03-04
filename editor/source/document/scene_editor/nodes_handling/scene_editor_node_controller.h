#ifndef _EDITOR_DOCUMENT_SCENE_EDITOR_NODE_CONTROLLER_H_
#define _EDITOR_DOCUMENT_SCENE_EDITOR_NODE_CONTROLLER_H_

#include "coffee_editor_includes.h"
#include "document/scene_editor/nodes_handling/scene_editor_open_node.h"
#include "document/scene_editor/nodes_handling/scene_editor_close_node.h"
#include "document/scene_editor/nodes_handling/scene_editor_add_node.h"
#include "document/scene_editor/nodes_handling/scene_editor_group_nodes.h"
#include "document/scene_editor/nodes_handling/scene_editor_attach_node.h"
#include "document/scene_editor/nodes_handling/scene_editor_detach_node.h"
#include "document/scene_editor/nodes_handling/scene_editor_instantiate.h"

namespace coffee_editor
{
    //--------------------------------------------------------------------------------------------//
    /// Node controller
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API SceneEditorNodeController : public edition::PluginNodeController
    {
        COFFEE_Type(SceneEditorNodeController);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SceneEditorNodeController(basic::String name="", basic::String help_text="");        
        ~SceneEditorNodeController();

        //-HANDLERS-------------------------------------------------------------------------------//

        void OnInitialize();
        void OnSelectionChanged();  
        void KillPreview();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//
        
        ui::widget::Dialog* _CameraPreview;
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, SceneEditorNodeController);
}
#endif
