#ifndef _EDITOR_WIDGET_GIZMO_CONTROLLER_H_
#define _EDITOR_WIDGET_GIZMO_CONTROLLER_H_

#include "coffee_editor_includes.h"
#include "document/document.h"

namespace coffee_editor
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Gizmo controller
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API GizmoController : public ui::Window
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        GizmoController();
        ~GizmoController();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(ui::widget::ToolBar& tool_bar, Document& document);
        void Update();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(GizmoController);
        COFFEE_Event bool OnPick(shell::Event& event);
        COFFEE_Event bool OnTranslate(shell::Event& event);
        COFFEE_Event bool OnRotate(shell::Event& event);
        COFFEE_Event bool OnScale(shell::Event& event);
        COFFEE_Event bool OnReference(shell::Event& event);
        COFFEE_DeclareExternEventHandler(GizmoController, OnSetReferenceLocal);
        COFFEE_DeclareExternEventHandler(GizmoController, OnSetReferenceParent);
        COFFEE_DeclareExternEventHandler(GizmoController, OnSetReferenceWorld);
        
    private:

        //-QUERIES--------------------------------------------------------------------------------//

        bool IsActive() const;
        bool IsEnabled() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void SetMode(edition::GIZMO_MODE mode);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Document* _Document;
        ui::widget::Button* _Pick;
        ui::widget::Button* _Translate;
        ui::widget::Button* _Rotate;
        ui::widget::Button* _Scale;
        ui::widget::Button* _Reference;
    };

}
}
#endif
