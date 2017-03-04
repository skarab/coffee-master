#include "wide/edition/plugin/edition_plugin_node_controller.h"
#include "wide/edition/plugin/edition_plugin.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(edition::PluginNodeController);
        COFFEE_Ancestor(edition::GizmoController);
    COFFEE_EndType();
    
namespace edition
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PluginNodeController::PluginNodeController(basic::String name, basic::String help_text) :
        edition::GizmoController(name, help_text),
        _ItIsSelecting(false),
        _Node(NULL)
    {
    }
        
    //--------------------------------------------------------------------------------------------//

    PluginNodeController::~PluginNodeController()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void PluginNodeController::SetNode(scene::Node* node)
    {
        _Node = node;
        OnSelectionChanged();
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(PluginNodeController, GizmoController)
        COFFEE_RegisterEventHandler(input::EVENT_MouseMove, input::Handler, OnMouseMove)
        COFFEE_RegisterEventHandler(input::EVENT_MouseLeftButtonPressed, input::Handler, OnMouseLeftButtonPressed)
        COFFEE_RegisterEventHandler(input::EVENT_MouseLeftButtonReleased, input::Handler, OnMouseLeftButtonReleased)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool PluginNodeController::OnMouseMove(shell::Event& event)
    {
        input::EventMouse* parameter = (input::EventMouse*)
            event.GetParameters().GetCustomParameter();

        if (_ItIsSelecting)
        {
            _CursorPosition = GetParentViewport().ComputeScreenToViewportPoint(parameter->Position);
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool PluginNodeController::OnMouseLeftButtonPressed(shell::Event& event)
    {
        input::EventMouse* parameter = (input::EventMouse*)
            event.GetParameters().GetCustomParameter();

        if (!edition::GizmoController::OnMouseLeftButtonPressed(event))
        {
            _ItIsSelecting = true;
            _SelectionStart = GetParentViewport().ComputeScreenToViewportPoint(parameter->Position);
            _CursorPosition = GetParentViewport().ComputeScreenToViewportPoint(parameter->Position);
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool PluginNodeController::OnMouseLeftButtonReleased(shell::Event& event)
    {
        input::EventMouse* parameter = (input::EventMouse*)
            event.GetParameters().GetCustomParameter();

        if (_ItIsSelecting)
        {
            _ItIsSelecting = false;
            _HandleSelection(_SelectionStart, GetParentViewport().ComputeScreenToViewportPoint(parameter->Position));
            return true;
        }
        return false;
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    void PluginNodeController::OnRender(graphics::Viewport& viewport, bool it_is_transparent, bool it_is_hdr)
    {
        edition::GizmoController::OnRender(viewport, it_is_transparent, it_is_hdr);

        if (_ItIsSelecting && it_is_transparent && !it_is_hdr)
            _RenderRectangularSelection();
    }

    //--------------------------------------------------------------------------------------------//

    void PluginNodeController::OnDeactivate()
    {
        UndoManager* undo_manager = GetUndoManager();
        if (undo_manager->IsActive())
            undo_manager->Cancel();
         _ItIsSelecting = false;
        edition::GizmoController::OnDeactivate();
    }
        
    //--------------------------------------------------------------------------------------------//
    
    void PluginNodeController::OnQueryTransform()
    {
        UndoManager* undo_manager = GetUndoManager();
        SelectionManager* selection_manager = GetSelectionManager();
        COFFEE_Assert(selection_manager->GetObjectCount()>0, core::ERROR_CODE_Unexpected, "Invalid control state");
        
        if (undo_manager->IsActive())
            undo_manager->Cancel();

        undo_manager->Begin();
    }

    //--------------------------------------------------------------------------------------------//
    
    void PluginNodeController::OnAcceptTransform()
    {
        UndoManager* undo_manager = GetUndoManager();
        
        switch (GetMode())
        {
            case GIZMO_MODE_Translate:  undo_manager->Accept("Translate");  break;
            case GIZMO_MODE_Rotate:     undo_manager->Accept("Rotate");     break;
            case GIZMO_MODE_Scale:      undo_manager->Accept("Scale");      break;
        }
    }

    //--------------------------------------------------------------------------------------------//
    
    void PluginNodeController::OnCancelTransform()
    {
        UndoManager* undo_manager = GetUndoManager();
        undo_manager->Cancel();
    }

    //--------------------------------------------------------------------------------------------//
    
    void PluginNodeController::OnTranslate(const basic::Vector3& translation)
    {
        UndoManager* undo_manager = GetUndoManager();
        SelectionManager* selection_manager = GetSelectionManager();
        COFFEE_Assert(selection_manager->GetObjectCount()>0, core::ERROR_CODE_Unexpected, "Invalid control state");
        undo_manager->CancelObjects();
        
        for (uint32 i=0 ; i<selection_manager->GetObjectCount() ; ++i)
        {
            scene::Node* node = static_cast<scene::Node*>(&selection_manager->GetObject(i));
            undo_manager->Add(COFFEE_New(ui::PropertyUndo, &node->GetTransform(),
                (void*)&node->GetTransform().GetTranslation(), basic::Vector3::GetClassMetaType()));
            basic::Matrix transform;
            transform.Set(
                basic::Vector3(),
                node->GetTransform().GetMatrix(scene::TRS_World, scene::TRS_Parent).GetRotation(),
                node->GetTransform().GetMatrix(scene::TRS_World, scene::TRS_Parent).GetScale());
            basic::Vector3 local_translation = translation * transform;
            node->GetTransform().SetTranslation(node->GetTransform().GetTranslation()+local_translation);
        }
    }

    //--------------------------------------------------------------------------------------------//
    
    void PluginNodeController::OnRotate(const basic::Quaternion& rotation)
    {
        UndoManager* undo_manager = GetUndoManager();
        SelectionManager* selection_manager = GetSelectionManager();
        COFFEE_Assert(selection_manager->GetObjectCount()>0, core::ERROR_CODE_Unexpected, "Invalid control state");
        undo_manager->CancelObjects();
            
        for (uint32 i=0 ; i<selection_manager->GetObjectCount() ; ++i)
        {
            scene::Node* node = static_cast<scene::Node*>(&selection_manager->GetObject(i));
            undo_manager->Add(COFFEE_New(ui::PropertyUndo, &node->GetTransform(),
                (void*)&node->GetTransform().GetRotation(), basic::Quaternion::GetClassMetaType()));
            node->GetTransform().SetRotation(basic::Quaternion(node->GetTransform().GetRotation())*rotation);
        }
    }

    //--------------------------------------------------------------------------------------------//
    
    void PluginNodeController::OnScale(const basic::Vector3& scale)
    {
        UndoManager* undo_manager = GetUndoManager();
        SelectionManager* selection_manager = GetSelectionManager();
        COFFEE_Assert(selection_manager->GetObjectCount()>0, core::ERROR_CODE_Unexpected, "Invalid control state");
        undo_manager->CancelObjects();
        
        for (uint32 i=0 ; i<selection_manager->GetObjectCount() ; ++i)
        {
            scene::Node* node = static_cast<scene::Node*>(&selection_manager->GetObject(i));
            undo_manager->Add(COFFEE_New(ui::PropertyUndo, &node->GetTransform(),
                (void*)&node->GetTransform().GetScale(), basic::Vector3::GetClassMetaType()));
            basic::Vector3 local_scale = scale * node->GetTransform().GetMatrix(scene::TRS_World, scene::TRS_Parent).GetScale();
            node->GetTransform().SetScale(local_scale);
        }
    }

    //-OPERATIONS-----------------------------------------------------------------------------//

    void PluginNodeController::_RenderRectangularSelection()
    {
        graphics::Renderer& renderer = graphics::Renderer::Get();
        
        renderer.SetDefaultRenderState();
        renderer.SetFaceCullingMode(graphics::RENDER_STATE_FACE_CULLING_None);
        renderer.SetColor(basic::Color(1.0f, 1.0f, 1.0f, 0.1f));
        graphics::GeometricRenderer::RenderViewportRectangle(_SelectionStart, _CursorPosition);
    }

    //--------------------------------------------------------------------------------------------//
    
    void RenderPickerNode(graphics::Viewport& viewport, scene::Node& node, graphics::FramePickerContext& pick_context, uint32 picker_index)
    {
        scene::Node* scene_node = static_cast<scene::Node*>(&node);
        graphics::ComponentMesh* component = scene_node->FindComponent<graphics::ComponentMesh>();
        if (component!=NULL && component->IsFlagEnabled(graphics::COMPONENT_FLAG_Pickable))
        {
            pick_context.Register(picker_index);
            component->RenderPicker(viewport);
        }

        for (uint32 index=0 ; index<node.GetChildCount() ; ++index)
            RenderPickerNode(viewport, node.GetChild(index), pick_context, picker_index);
    }

    //--------------------------------------------------------------------------------------------//
    
    void PluginNodeController::_HandleSelection(const basic::Vector2i& point_a, const basic::Vector2i& point_b)
    {
        if (_Node==NULL)
            return;

        basic::Rectangle selection_box;
        selection_box.AddPoint(point_a, true);
        selection_box.AddPoint(point_b);
        graphics::FramePickerContext pick_context(selection_box);

        graphics::Viewport& viewport = GetParentViewport();
        pick_context.Begin(viewport);
        for (uint32 index=0 ; index<_Node->GetChildCount() ; ++index)
        {
            RenderPickerNode(viewport, _Node->GetChild(index), pick_context, index);
        }
        pick_context.End(viewport);

        bool it_is_adding = input::Keyboard::Get().IsButtonPressed(input::KEY_Shift);
        bool it_is_removing = input::Keyboard::Get().IsButtonPressed(input::KEY_Control);
        edition::SelectionManager* selection_manager = GetSelectionManager();

        if (!it_is_adding && !it_is_removing)
        {
            selection_manager->Clear(pick_context.GetHitCount()==0);
        }

        for (uint32 index=0 ; index<pick_context.GetHitCount() ; ++index)
        {
            if (pick_context.GetHitIndex(index)>=0 && pick_context.GetHitIndex(index)<_Node->GetChildCount())
            {
                scene::Node* node = static_cast<scene::Node*>(&_Node->GetChild(pick_context.GetHitIndex(index)));
                selection_manager->Select(*node, !it_is_removing, index==0);
            }
        }
        OnSelectionChanged();
    }

}
}
