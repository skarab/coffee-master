#ifndef _EDITOR_WIDGET_NODE_EDITOR_COMPONENT_H_
#define _EDITOR_WIDGET_NODE_EDITOR_COMPONENT_H_

#include "coffee_editor_includes.h"
#include "widget/node_editor/widget_node_editor.h"

namespace coffee_editor
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Node component editor
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API NodeEditorComponent : public ui::Window
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        NodeEditorComponent();
        ~NodeEditorComponent();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(scene::Component& component, meta::ObjectInfo& object_info,
            NodeEditor& node_editor);
        void Update();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(NodeEditorComponent);
        COFFEE_Event bool OnMenu(shell::Event& event);
        COFFEE_DeclareExternEventHandler(NodeEditorComponent, OnDelete);
        COFFEE_Event bool OnInstantiable(shell::Event& event);
        COFFEE_Event bool OnAutomatic(shell::Event& event);
        COFFEE_Event bool OnRunInEditor(shell::Event& event);
        
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        scene::Component* _Component;
        ui::widget::Button* _MenuButton;
        ui::widget::Button* _InstantiableButton;
        ui::widget::Button* _AutomaticButton;
        ui::widget::Button* _RunInEditorButton;
        ui::widget::Image* _StateImage;
        ui::PropertyList* _PropertyList;
    };
}
}
#endif
