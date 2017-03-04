#ifndef _EDITOR_WIDGET_NODE_EDITOR_H_
#define _EDITOR_WIDGET_NODE_EDITOR_H_

#include "coffee_editor_includes.h"

namespace coffee_editor
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Node editor
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API NodeEditor : public ui::Property
    {
        COFFEE_PropertyInterface(NodeEditor, "scene::Node", "", false);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        NodeEditor();
        ~NodeEditor();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void CreateContent();
        void Update();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(NodeEditor);
        COFFEE_Event bool OnComponentMenu(shell::Event& event);
        COFFEE_DeclareExternEventHandler(NodeEditor, OnAddComponent);
        COFFEE_Event bool OnInstantiable(shell::Event& event);
        COFFEE_Event bool OnAutomatic(shell::Event& event);
        COFFEE_Event bool OnRunInEditor(shell::Event& event);
        
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        ui::widget::Button* _AddComponentButton;
        ui::widget::Button* _InstantiableButton;
        ui::widget::Button* _AutomaticButton;
        ui::widget::Button* _RunInEditorButton;
        ui::widget::Image* _StateImage;
        ui::PropertyList* _PropertyList;
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, NodeEditor);
}
}
#endif
