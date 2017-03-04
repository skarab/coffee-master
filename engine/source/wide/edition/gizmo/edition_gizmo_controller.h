#ifndef _COFFEE_EDITION_GIZMO_CONTROLLER_H_
#define _COFFEE_EDITION_GIZMO_CONTROLLER_H_

#include "coffee_includes.h"
#include "wide/application/control/application_control.h"
#include "wide/edition/gizmo/edition_gizmo.h"

namespace coffee
{
namespace edition
{
    //--------------------------------------------------------------------------------------------//
    /// Gizmo controller
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API GizmoController : public ApplicationControl
    {
        COFFEE_Type(GizmoController);
        
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        GizmoController(basic::String name="", basic::String help_text="");        
        ~GizmoController();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetMode(GIZMO_MODE mode);
        GIZMO_MODE GetMode() const;
        void SetReference(scene::TRS reference);
        scene::TRS GetReference() const;

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(GizmoController);
        COFFEE_Event bool OnKeyPressed(shell::Event& event);
        COFFEE_Event bool OnMouseMove(shell::Event& event);
        COFFEE_Event bool OnMouseLeftButtonPressed(shell::Event& event);
        COFFEE_Event bool OnMouseLeftButtonReleased(shell::Event& event);
        
        //-HANDLERS-------------------------------------------------------------------------------//

        virtual void OnUpdate(const basic::Time& time_step);
        virtual void OnRender(graphics::Viewport& viewport, bool it_is_transparent, bool it_is_hdr);
        virtual void OnActivate();
        virtual void OnDeactivate();
        virtual void OnChildActivate(ApplicationControl& control);
        virtual void OnChildDeactivate(ApplicationControl& control);

        virtual void OnSelectionChanged();
        virtual void OnQueryTransform();
        virtual void OnAcceptTransform();
        virtual void OnCancelTransform();
        virtual void OnTranslate(const basic::Vector3& translation);
        virtual void OnRotate(const basic::Quaternion& rotation);
        virtual void OnScale(const basic::Vector3& scale);
        
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Gizmo _Gizmo;
        scene::TRS _Reference;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, GizmoController);
}
}
#endif
