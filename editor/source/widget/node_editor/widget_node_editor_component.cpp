#include "widget/node_editor/widget_node_editor_component.h"
#include "widget/properties/widget_properties.h"

namespace coffee_editor
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    NodeEditorComponent::NodeEditorComponent() :
        _MenuButton(NULL),            
        _InstantiableButton(NULL),
        _AutomaticButton(NULL),
        _RunInEditorButton(NULL),
        _StateImage(NULL),
        _PropertyList(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    NodeEditorComponent::~NodeEditorComponent()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void NodeEditorComponent::Create(scene::Component& component, meta::ObjectInfo& object_info,
            NodeEditor& node_editor)
    {
        _Component = &component;
        ui::Window::Create(&node_editor, basic::Vector2i(), basic::Vector2i(), 0);
        GetLayout().SetStyle(ui::LAYOUT_STYLE_VerticalCanvas
            | ui::LAYOUT_STYLE_VerticalShrink
            | ui::LAYOUT_STYLE_StickChildren
            | ui::LAYOUT_STYLE_HorizontalExpand);

        // Create ToolBar
        uint32 height = 16;
        ui::Window* toolbar = COFFEE_New(ui::Window);
        toolbar->Create(this, basic::Vector2i(), basic::Vector2i(0, height+1),
            ui::WINDOW_STYLE_DrawFrame | ui::WINDOW_STYLE_DrawClientRaised);
        toolbar->GetLayout().SetStyle(ui::LAYOUT_STYLE_HorizontalCanvas | ui::LAYOUT_STYLE_HorizontalExpand
            | ui::LAYOUT_STYLE_StickChildren);

        _MenuButton = COFFEE_New(ui::widget::Button);
        _MenuButton->Create(toolbar, basic::Vector2i(), basic::Vector2i(height, height));
        _MenuButton->SetImage("/coffee/import/editor/icons/component.texture");
        _MenuButton->GetLayout().SetCanvas((int32)height, false);
        _MenuButton->SetHelpText("Component...");

        ui::Window* window = COFFEE_New(ui::Window);
        window->Create(toolbar, basic::Vector2i(), basic::Vector2i(0, 16), 0);
        window->GetLayout().SetCanvas(100, true);
        ui::widget::Label* label = COFFEE_New(ui::widget::Label);
        label->Create(window, basic::Vector2i(), basic::Vector2i(0, 0));
        label->GetLayout().SetStyle(ui::LAYOUT_STYLE_Expand);
        label->SetText(_Component->GetName());
        
        _InstantiableButton = COFFEE_New(ui::widget::Button);
        _InstantiableButton->Create(toolbar, basic::Vector2i(), basic::Vector2i(height, height), ui::widget::BUTTON_STYLE_PushLike);
        _InstantiableButton->GetLayout().SetCanvas((int32)height, false);
        _InstantiableButton->SetHelpText("Instantiable ?");
        _InstantiableButton->SetImage("/coffee/import/editor/icons/scene/flag_instantiable.texture");
        if (_Component->IsInstantiable())
            _InstantiableButton->SetState(ui::widget::BUTTON_STATE_On);

        _AutomaticButton = COFFEE_New(ui::widget::Button);
        _AutomaticButton->Create(toolbar, basic::Vector2i(), basic::Vector2i(height, height), ui::widget::BUTTON_STYLE_PushLike);
        _AutomaticButton->GetLayout().SetCanvas((int32)height, false);
        _AutomaticButton->SetHelpText("Automatic ?");
        _AutomaticButton->SetImage("/coffee/import/editor/icons/scene/flag_automatic.texture");
        if (_Component->IsAutomatic())
            _AutomaticButton->SetState(ui::widget::BUTTON_STATE_On);

        _RunInEditorButton = COFFEE_New(ui::widget::Button);
        _RunInEditorButton->Create(toolbar, basic::Vector2i(), basic::Vector2i(height, height), ui::widget::BUTTON_STYLE_PushLike);
        _RunInEditorButton->GetLayout().SetCanvas((int32)height, false);
        _RunInEditorButton->SetHelpText("Run in Editor ?");
        _RunInEditorButton->SetImage("/coffee/import/editor/icons/scene/flag_runineditor.texture");
        if (!_Component->IsStoppedInEditor())
            _RunInEditorButton->SetState(ui::widget::BUTTON_STATE_On);

        _StateImage = COFFEE_New(ui::widget::Image);
        _StateImage->Create(toolbar, basic::Vector2i(), basic::Vector2i(height, height));
        _StateImage->GetLayout().SetCanvas((int32)height, false);
        _StateImage->SetImage("/coffee/import/editor/icons/scene/flag_running_off.texture");

        _PropertyList = COFFEE_New(ui::PropertyList);
        _PropertyList->Create(component, basic::Vector2i(0, height), basic::Vector2i(), this, true);
    }

    //--------------------------------------------------------------------------------------------//

    void NodeEditorComponent::Update()
    {
        if (_StateImage!=NULL)
        {
            _StateImage->SetImage(_Component->IsRunning()?"/coffee/import/editor/icons/scene/flag_running_on.texture"
                :"/coffee/import/editor/icons/scene/flag_running_off.texture");
        }
        ui::Window::Update();
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(NodeEditorComponent, ui::Window)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _MenuButton, OnMenu)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _InstantiableButton, OnInstantiable)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _AutomaticButton, OnAutomatic)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _RunInEditorButton, OnRunInEditor)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool NodeEditorComponent::OnMenu(shell::Event& event)
    {
        ui::widget::Menu* menu = COFFEE_New(ui::widget::Menu);
        menu->Create(NULL, basic::Vector2i(
            (int32)input::Mouse::Get().GetPosition().X+10,
            (int32)input::Mouse::Get().GetPosition().Y+10), basic::Vector2i());
        
        COFFEE_RegisterExternEventHandler(
            ui::widget::EVENT_Pressed,
            ui::widget::Widget::GetClassMetaType(),
            *menu->AddButton("Delete"),
            OnDelete);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool NodeEditorComponent::OnDelete(shell::Event& event)
    {
        // TODO: Handle undo for components add remove

        NodeEditor* editor = static_cast<NodeEditor*>(&GetParent());
        scene::Node* node = (scene::Node*)editor->GetData();
        node->RemoveComponent(_Component);
        widget::Properties::Get().Edit(node->GetName(), *node);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool NodeEditorComponent::OnInstantiable(shell::Event& event)
    {
        // TODO: Easy creation of undos for properties

        edition::UndoManager& undo_manager = Application::Get().GetControlManager().GetEditionPlugin().GetUndoManager();
        undo_manager.Begin();
        undo_manager.Add(COFFEE_New(ui::PropertyUndo, _Component,
            (void*)&_Component->GetFlags(), meta::TYPE<uint32>().Get()));
        _Component->SetIsInstantiable(_InstantiableButton->GetState()==ui::widget::BUTTON_STATE_On);
        undo_manager.Accept("Set instantiable");
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool NodeEditorComponent::OnAutomatic(shell::Event& event)
    {
        // TODO: Easy creation of undos for properties

        edition::UndoManager& undo_manager = Application::Get().GetControlManager().GetEditionPlugin().GetUndoManager();
        undo_manager.Begin();
        undo_manager.Add(COFFEE_New(ui::PropertyUndo, _Component,
            (void*)&_Component->GetFlags(), meta::TYPE<uint32>().Get()));
        _Component->SetIsAutomatic(_AutomaticButton->GetState()==ui::widget::BUTTON_STATE_On);
        undo_manager.Accept("Set automatic");
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool NodeEditorComponent::OnRunInEditor(shell::Event& event)
    {
        // TODO: Easy creation of undos for properties

        edition::UndoManager& undo_manager = Application::Get().GetControlManager().GetEditionPlugin().GetUndoManager();
        undo_manager.Begin();
        undo_manager.Add(COFFEE_New(ui::PropertyUndo, _Component,
            (void*)&_Component->GetFlags(), meta::TYPE<uint32>().Get()));
        _Component->SetIsStoppedInEditor(_RunInEditorButton->GetState()==ui::widget::BUTTON_STATE_Off);
        undo_manager.Accept("Set run in editor");
        return true;
    }

}
}
