#include "wide/edition/gizmo/edition_gizmo_controller.h"
#include "wide/edition/selection/edition_selection_manager.h"
#include "wide/edition/undo/edition_undo_manager.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(edition::GizmoController);
        COFFEE_Ancestor(ApplicationControl);
    COFFEE_EndType();
    
namespace edition
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    GizmoController::GizmoController(basic::String name, basic::String help_text) :
        ApplicationControl(name, help_text),
        _Reference(scene::TRS_Local)
    {
        _Gizmo._Controller = this;
    }
        
    //--------------------------------------------------------------------------------------------//

    GizmoController::~GizmoController()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void GizmoController::SetMode(GIZMO_MODE mode)
    {
        _Gizmo.SetMode(mode);
        OnSelectionChanged();
    }

    //--------------------------------------------------------------------------------------------//

    GIZMO_MODE GizmoController::GetMode() const
    {
        return _Gizmo.GetMode();
    }

    //--------------------------------------------------------------------------------------------//

    void GizmoController::SetReference(scene::TRS reference)
    {
        _Reference = reference;
        OnSelectionChanged();
    }

    //--------------------------------------------------------------------------------------------//

    scene::TRS GizmoController::GetReference() const
    {
        return _Reference;
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(GizmoController, ApplicationControl)
        COFFEE_RegisterEventHandler(input::EVENT_KeyPressed, input::Handler, OnKeyPressed)
        COFFEE_RegisterEventHandler(input::EVENT_MouseMove, input::Handler, OnMouseMove)
        COFFEE_RegisterEventHandler(input::EVENT_MouseLeftButtonPressed, input::Handler, OnMouseLeftButtonPressed)
        COFFEE_RegisterEventHandler(input::EVENT_MouseLeftButtonReleased, input::Handler, OnMouseLeftButtonReleased)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool GizmoController::OnKeyPressed(shell::Event& event)
    {
        input::EventKey* parameter = (input::EventKey*)
            event.GetParameters().GetCustomParameter();   
        return _Gizmo.OnKeyPressed(parameter->Key, parameter->ItIsRepeating);
    }

    //--------------------------------------------------------------------------------------------//

    bool GizmoController::OnMouseMove(shell::Event& event)
    {
        input::EventMouse* parameter = (input::EventMouse*)
            event.GetParameters().GetCustomParameter();
        return _Gizmo.OnMouseMove(GetParentViewport().ComputeScreenToViewportPoint(parameter->Position));
    }

    //--------------------------------------------------------------------------------------------//

    bool GizmoController::OnMouseLeftButtonPressed(shell::Event& event)
    {
        input::EventMouse* parameter = (input::EventMouse*)
            event.GetParameters().GetCustomParameter();
        return _Gizmo.OnMouseLeftButtonPressed(GetParentViewport().ComputeScreenToViewportPoint(parameter->Position));
    }

    //--------------------------------------------------------------------------------------------//

    bool GizmoController::OnMouseLeftButtonReleased(shell::Event& event)
    {
        input::EventMouse* parameter = (input::EventMouse*)
            event.GetParameters().GetCustomParameter();
        return _Gizmo.OnMouseLeftButtonReleased(GetParentViewport().ComputeScreenToViewportPoint(parameter->Position));
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    void GizmoController::OnUpdate(const basic::Time& time_step)
    {
        //UndoManager* undo_manager = GetUndoManager();
        //if (!undo_manager->IsActive())
        //    GizmoController::OnSelectionChanged();
    }

    //--------------------------------------------------------------------------------------------//

    void GizmoController::OnRender(graphics::Viewport& viewport, bool it_is_transparent, bool it_is_hdr)
    {
        if (!it_is_hdr && it_is_transparent)
            _Gizmo.Render();
    }

    //--------------------------------------------------------------------------------------------//

    void GizmoController::OnActivate()
    {
        OnSelectionChanged();
        ApplicationControl::OnActivate();
    }
    
    //--------------------------------------------------------------------------------------------//

    void GizmoController::OnDeactivate()
    {
        _Gizmo.SetIsEnabled(false);
        ApplicationControl::OnDeactivate();
    }

    //--------------------------------------------------------------------------------------------//

    void GizmoController::OnChildActivate(ApplicationControl& control)
    {
        _Gizmo.SetIsEnabled(false);
        ApplicationControl::OnChildActivate(control);
    }

    //--------------------------------------------------------------------------------------------//

    void GizmoController::OnChildDeactivate(ApplicationControl& control)
    {
        ApplicationControl::OnChildDeactivate(control);
        OnSelectionChanged();
    }

    //--------------------------------------------------------------------------------------------//

    void GizmoController::OnSelectionChanged()
    {
        edition::SelectionManager* selection_manager = GetSelectionManager();
        scene::Node* node = NULL;

        if (selection_manager->GetObjectCount()>0
            && selection_manager->GetObject(0).IsKindOf<scene::Node>())
        {
            node = static_cast<scene::Node*>(&selection_manager->GetObject(0));
        }

        _Gizmo.SetIsEnabled(node!=NULL && node->HasTransform());
        if (_Gizmo.IsEnabled())
        {
            basic::Matrix local_to_world = node->GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World);
            basic::Matrix parent_to_world = node->GetTransform().GetMatrix(scene::TRS_Parent, scene::TRS_World);
            switch (_Reference)
            {
                case scene::TRS_Local:
                    _Gizmo.SetPosition(
                        local_to_world.GetTranslation(),
                        local_to_world.GetRotation(),
                        local_to_world.GetScale());
                    break;
                case scene::TRS_Parent:
                    _Gizmo.SetPosition(
                        local_to_world.GetTranslation(),
                        parent_to_world.GetRotation(),
                        parent_to_world.GetScale());
                    break;
                case scene::TRS_World:
                    _Gizmo.SetPosition(
                        local_to_world.GetTranslation(),
                        basic::Quaternion(),
                        basic::Vector3::One);
                    break;
                default:
                    break;
            }
        }
    }

    //--------------------------------------------------------------------------------------------//

    void GizmoController::OnQueryTransform()
    {
    }

    //--------------------------------------------------------------------------------------------//

    void GizmoController::OnAcceptTransform()
    {
    }

    //--------------------------------------------------------------------------------------------//

    void GizmoController::OnCancelTransform()
    {
    }

    //--------------------------------------------------------------------------------------------//

    void GizmoController::OnTranslate(const basic::Vector3& translation)
    {
    }

    //--------------------------------------------------------------------------------------------//

    void GizmoController::OnRotate(const basic::Quaternion& rotation)
    {
    }

    //--------------------------------------------------------------------------------------------//

    void GizmoController::OnScale(const basic::Vector3& scale)
    {
    }

}
}
