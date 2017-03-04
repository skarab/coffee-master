#include "document/scene_editor/nodes_handling/scene_editor_node_controller.h"
#include "document/scene_editor/scene_editor.h"
#include "widget/widgets.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(SceneEditorNodeController);
        COFFEE_Ancestor(edition::PluginNodeController);
    COFFEE_EndType();

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SceneEditorNodeController::SceneEditorNodeController(basic::String name, basic::String help_text) :
        edition::PluginNodeController(name, help_text),
        _CameraPreview(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    SceneEditorNodeController::~SceneEditorNodeController()
    {
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    void SceneEditorNodeController::OnInitialize()
    {
        Register(*COFFEE_New(SceneEditorAddNode), COFFEE_New(input::Command, "", "", input::KEY_N));
        Register(*COFFEE_New(SceneEditorInstantiate), COFFEE_New(input::Command, "", "", input::KEY_I));
        Register(*COFFEE_New(SceneEditorAttachNode), COFFEE_New(input::Command, "", "", input::KEY_A));        
        Register(*COFFEE_New(SceneEditorDetachNode), COFFEE_New(input::Command, "", "", input::KEY_D));        
        Register(*COFFEE_New(SceneEditorGroupNodes), COFFEE_New(input::Command, "", "", input::KEY_G));
        Register(*COFFEE_New(SceneEditorOpenNode), COFFEE_New(input::Command, "", "", input::KEY_O));
        Register(*COFFEE_New(SceneEditorCloseNode), COFFEE_New(input::Command, "", "", input::KEY_C));
    }

    //--------------------------------------------------------------------------------------------//

    void SceneEditorNodeController::OnSelectionChanged()
    {
        edition::PluginNodeController::OnSelectionChanged();
        edition::SelectionManager* selection_manager = GetSelectionManager();
        SceneEditor* scene_editor((SceneEditor*)&GetParent());
        
        if (selection_manager->GetObjectCount()==0)
        {
            widget::Properties::Get().Clear();

            if (_CameraPreview!=NULL)
            {
                _CameraPreview->Destroy();
                _CameraPreview = NULL;
            }
        }
        else
        {
            scene::Node* node = static_cast<scene::Node*>(&selection_manager->GetObject(0));
            widget::Properties::Get().Edit(node->GetName(), *node);

            graphics::ComponentCamera* camera = node->FindComponentInChildren<graphics::ComponentCamera>();
            if (camera==NULL || camera->HasViewport())
            {
                if (_CameraPreview!=NULL)
                {
                    _CameraPreview->Destroy();
                    _CameraPreview = NULL;
                }
            }
            else
            {
                graphics::Viewport* viewport;
                if (_CameraPreview==NULL)
                {
                    _CameraPreview = COFFEE_New(ui::widget::Dialog);
                    _CameraPreview->Create(&GetParentViewport(), basic::Vector2i(20, 20), basic::Vector2i(328, 230), ui::widget::DIALOG_STYLE_None);

                    viewport = COFFEE_New(graphics::Viewport);
                    viewport->Create(_CameraPreview, basic::Vector2i(0, 0), basic::Vector2i(320, 200), ui::WINDOW_STYLE_None);
                    viewport->GetLayout().SetStyle(ui::LAYOUT_STYLE_Expand);
                }
                else
                {
                    viewport = &static_cast<graphics::Viewport&>(_CameraPreview->GetChildWindow(0));
                }
                viewport->AttachCamera(scene_editor->GetScene(), camera);
                _CameraPreview->SetTitleBarText(node->GetName());
            }
        }
    }
      
    //--------------------------------------------------------------------------------------------//

    void SceneEditorNodeController::KillPreview()
    {
        _CameraPreview = NULL;
    }

}
