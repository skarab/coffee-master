#ifndef _COFFEE_EDITION_PLUGIN_NODE_CONTROLLER_H_
#define _COFFEE_EDITION_PLUGIN_NODE_CONTROLLER_H_

#include "coffee_includes.h"
#include "wide/edition/gizmo/edition_gizmo_controller.h"
#include "system/scene/scene.h"
#include "wide/edition/plugin/edition_plugin_attach_node_undo.h"
#include "wide/edition/plugin/edition_plugin_detach_node_undo.h"

namespace coffee
{
namespace edition
{
    //--------------------------------------------------------------------------------------------//
    /// Node controller
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PluginNodeController : public GizmoController
    {
        COFFEE_Type(PluginNodeController);
        
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PluginNodeController(basic::String name="", basic::String help_text="");        
        ~PluginNodeController();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetNode(scene::Node* node);

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(GizmoController);
        COFFEE_Event bool OnMouseMove(shell::Event& event);
        COFFEE_Event bool OnMouseLeftButtonPressed(shell::Event& event);
        COFFEE_Event bool OnMouseLeftButtonReleased(shell::Event& event);
        
        //-HANDLERS-------------------------------------------------------------------------------//

        virtual void OnRender(graphics::Viewport& viewport, bool it_is_transparent, bool it_is_hdr);
        virtual void OnDeactivate();
        
        virtual void OnQueryTransform();
        virtual void OnAcceptTransform();
        virtual void OnCancelTransform();
        virtual void OnTranslate(const basic::Vector3& translation);
        virtual void OnRotate(const basic::Quaternion& rotation);
        virtual void OnScale(const basic::Vector3& scale);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _RenderRectangularSelection();
        void _HandleSelection(const basic::Vector2i& point_a, const basic::Vector2i& point_b);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        bool _ItIsSelecting;
        scene::Node* _Node;
        basic::Vector2i _SelectionStart;
        basic::Vector2i _CursorPosition;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, PluginNodeController);
}
}
#endif
