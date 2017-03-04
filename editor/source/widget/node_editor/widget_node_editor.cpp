#include "widget/node_editor/widget_node_editor.h"
#include "widget/node_editor/widget_node_editor_component.h"
#include "coffee_editor.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(widget::NodeEditor);
        COFFEE_Ancestor(ui::Property);
    COFFEE_EndType();

namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    NodeEditor::NodeEditor() :
        _AddComponentButton(NULL),
        _InstantiableButton(NULL),
        _AutomaticButton(NULL),
        _RunInEditorButton(NULL),
        _StateImage(NULL),
        _PropertyList(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    NodeEditor::~NodeEditor()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void NodeEditor::CreateContent()
    {
        scene::Node* node = (scene::Node*)GetData();

        GetLayout().SetStyle(ui::LAYOUT_STYLE_VerticalCanvas
            | ui::LAYOUT_STYLE_VerticalShrink
            | ui::LAYOUT_STYLE_StickChildren
            | ui::LAYOUT_STYLE_HorizontalExpand);

        // Create ToolBar
        uint32 height = 24;
        ui::Window* toolbar = COFFEE_New(ui::Window);
        toolbar->Create(this, basic::Vector2i(), basic::Vector2i(0, 0),
            ui::WINDOW_STYLE_DrawFrame | ui::WINDOW_STYLE_DrawClientRaised);
        toolbar->GetLayout().SetCanvas((int32)height+1, false);
        toolbar->GetLayout().SetStyle(ui::LAYOUT_STYLE_HorizontalCanvas | ui::LAYOUT_STYLE_HorizontalExpand
            | ui::LAYOUT_STYLE_StickChildren);

        _AddComponentButton = COFFEE_New(ui::widget::Button);
        _AddComponentButton->Create(toolbar, basic::Vector2i(), basic::Vector2i(height, height));
        _AddComponentButton->SetImage("/coffee/import/editor/icons/add_component.texture");
        _AddComponentButton->GetLayout().SetCanvas((int32)height, false);
        _AddComponentButton->SetHelpText("Add component...");

        meta::ObjectInfo* components(NULL);
        for(uint32 child_index=0 ; child_index<GetObjectInfo().GetChildCount() ; ++child_index)
        {
            if (GetObjectInfo().GetChild(child_index).GetName()=="Components")
            {
                components = &GetObjectInfo().GetChild(child_index);
            }
            else
            {
                ui::PropertyList::CreateHierarchy(GetObjectInfo().GetChild(child_index), *this);
            }
        }

        if (components!=NULL)
        {
            for(uint32 child_index=0 ; child_index<components->GetChildCount() ; ++child_index)
            {
                NodeEditorComponent* component = COFFEE_New(NodeEditorComponent);
                component->Create(node->GetComponent(child_index), components->GetChild(child_index), *this);
            }
        }

        ui::Window* window = COFFEE_New(ui::Window);
        window->Create(toolbar, basic::Vector2i(), basic::Vector2i(), 0);
        window->GetLayout().SetCanvas(100, true);

        _InstantiableButton = COFFEE_New(ui::widget::Button);
        _InstantiableButton->Create(toolbar, basic::Vector2i(), basic::Vector2i(height, height), ui::widget::BUTTON_STYLE_PushLike);
        _InstantiableButton->GetLayout().SetCanvas((int32)height, false);
        _InstantiableButton->SetHelpText("Instantiable ?");
        _InstantiableButton->SetImage("/coffee/import/editor/icons/scene/flag_instantiable.texture");
        if (node->IsInstantiable())
            _InstantiableButton->SetState(ui::widget::BUTTON_STATE_On);

        _AutomaticButton = COFFEE_New(ui::widget::Button);
        _AutomaticButton->Create(toolbar, basic::Vector2i(), basic::Vector2i(height, height), ui::widget::BUTTON_STYLE_PushLike);
        _AutomaticButton->GetLayout().SetCanvas((int32)height, false);
        _AutomaticButton->SetHelpText("Automatic ?");
        _AutomaticButton->SetImage("/coffee/import/editor/icons/scene/flag_automatic.texture");
        if (node->IsAutomatic())
            _AutomaticButton->SetState(ui::widget::BUTTON_STATE_On);

        _RunInEditorButton = COFFEE_New(ui::widget::Button);
        _RunInEditorButton->Create(toolbar, basic::Vector2i(), basic::Vector2i(height, height), ui::widget::BUTTON_STYLE_PushLike);
        _RunInEditorButton->GetLayout().SetCanvas((int32)height, false);
        _RunInEditorButton->SetHelpText("Run in Editor ?");
        _RunInEditorButton->SetImage("/coffee/import/editor/icons/scene/flag_runineditor.texture");
        if (!node->IsStoppedInEditor())
            _RunInEditorButton->SetState(ui::widget::BUTTON_STATE_On);

        _StateImage = COFFEE_New(ui::widget::Image);
        _StateImage->Create(toolbar, basic::Vector2i(), basic::Vector2i(height, height));
        _StateImage->GetLayout().SetCanvas((int32)height, false);
        _StateImage->SetImage("/coffee/import/editor/icons/scene/flag_running_off.texture");
    }

    //--------------------------------------------------------------------------------------------//

    void NodeEditor::Update()
    {
        if (_StateImage!=NULL)
        {
            scene::Node* node = (scene::Node*)GetData();
            _StateImage->SetImage(node->IsRunning()?"/coffee/import/editor/icons/scene/flag_running_on.texture"
                :"/coffee/import/editor/icons/scene/flag_running_off.texture");
        }
        ui::Window::Update();
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(NodeEditor, ui::Property)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _AddComponentButton, OnComponentMenu)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _InstantiableButton, OnInstantiable)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _AutomaticButton, OnAutomatic)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _RunInEditorButton, OnRunInEditor)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    void _ParseComponentName(basic::Text& text, uint32 index)
    {
        int32 char_index=NONE;
        basic::String word;
        while (component::Types::Get().GetClassification(index).GetNextWord(
            word, char_index, '/'))
        {
            text.AddLine(word);
            ++char_index;
        }
        text.AddLine(component::Types::Get().GetName(index));
    }

    //--------------------------------------------------------------------------------------------//

    bool _IsComponentSmaller(const basic::Text& first, const basic::Text& second)
    {
        for (uint32 index=0 ; index<first.GetLineCount() ; ++index)
        {
            if (index>=second.GetLineCount())
                return false;
            if (first.GetLine(index)<second.GetLine(index))
                return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool NodeEditor::OnComponentMenu(shell::Event& event)
    {
        scene::Node* node = (scene::Node*)GetData();
        ui::widget::Menu* menu = COFFEE_New(ui::widget::Menu);
        ui::WindowContext context;
        context.Create(_AddComponentButton);
        menu->Create(NULL, basic::Vector2i(
            context.GetDesktopWindowRect().GetMinimum().X,
            context.GetDesktopWindowRect().GetMaximum().Y), basic::Vector2i());
        
        // Sort components based on the classification
        basic::Array<uint32> sorted_index;
        for (uint32 index=0 ; index<component::Types::Get().GetCount() ; ++index)
        {
            basic::Text first;
            _ParseComponentName(first, index);

            uint32 insert_index=0;
            for (insert_index=0 ; insert_index<sorted_index.GetSize() ; ++insert_index)
            {
                basic::Text second;
                _ParseComponentName(second, index);
                if (_IsComponentSmaller(first, second))
                    break;                
            }

            if (insert_index>=component::Types::Get().GetCount())
                insert_index = NONE;
            sorted_index.AddItem(index, insert_index);
        }

        // Create menus
        uint32 depth = 0;
        for (uint32 index=0 ; index<sorted_index.GetSize() ; ++index)
        {
            basic::Text component;
            _ParseComponentName(component, sorted_index[index]);
            
            ui::widget::Menu* current_menu = menu;
            for (uint32 i=0 ; i<component.GetLineCount()-1 ; ++i)
            {
                bool has_found_menu(false);
                for (uint32 j=0 ; j<current_menu->GetChildCount() ; ++j)
                {
                    ui::widget::MenuItem* item = static_cast<ui::widget::MenuItem*>(&current_menu->GetChild(j));
                    if (item->GetType()==ui::widget::MENU_ITEM_TYPE_Panel
                        && item->GetText()==component[i])
                    {
                        has_found_menu = true;
                        current_menu = item->GetMenu();
                        break;
                    }
                }
                if (!has_found_menu)
                    current_menu = current_menu->AddMenu(component[i]);
            }

            ui::widget::Button* menu_item = current_menu->AddButton(component[component.GetLineCount()-1]);
            menu_item->SetData((void*)sorted_index[index]);
            COFFEE_RegisterExternEventHandler(
                ui::widget::EVENT_Pressed,
                ui::widget::Widget::GetClassMetaType(),
                *menu_item, OnAddComponent);
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool NodeEditor::OnAddComponent(shell::Event& event)
    {
        // TODO: Handle undo for components add remove

        ui::widget::Button* menu_item = static_cast<ui::widget::Button*>(event.GetTarget());
        scene::Component* component = component::Types::Get().Create((uint32)menu_item->GetData());
        scene::Node* node = (scene::Node*)GetData();
        if (node->AddComponent(component))
        {
            widget::Properties::Get().Edit(node->GetName(), *node);
        }
        else
        {       
            COFFEE_Delete(component);
            ui::DoMessageBox("Failed to add component", "Nodes are restricted to a single component per type.");
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool NodeEditor::OnInstantiable(shell::Event& event)
    {
        // TODO: Easy creation of undos for properties

        scene::Node* node = (scene::Node*)GetData();
        edition::UndoManager& undo_manager = Application::Get().GetControlManager().GetEditionPlugin().GetUndoManager();
        undo_manager.Begin();
        undo_manager.Add(COFFEE_New(ui::PropertyUndo, node,
            (void*)&node->GetFlags(), meta::TYPE<uint32>().Get()));
        node->SetIsInstantiable(_InstantiableButton->GetState()==ui::widget::BUTTON_STATE_On);
        undo_manager.Accept("Set instantiable");
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool NodeEditor::OnAutomatic(shell::Event& event)
    {
        // TODO: Easy creation of undos for properties

        scene::Node* node = (scene::Node*)GetData();
        edition::UndoManager& undo_manager = Application::Get().GetControlManager().GetEditionPlugin().GetUndoManager();
        undo_manager.Begin();
        undo_manager.Add(COFFEE_New(ui::PropertyUndo, node,
            (void*)&node->GetFlags(), meta::TYPE<uint32>().Get()));
        node->SetIsAutomatic(_AutomaticButton->GetState()==ui::widget::BUTTON_STATE_On);
        undo_manager.Accept("Set automatic");
        return true;
    }
    
    //--------------------------------------------------------------------------------------------//

    bool NodeEditor::OnRunInEditor(shell::Event& event)
    {
        // TODO: Easy creation of undos for properties

        scene::Node* node = (scene::Node*)GetData();
        edition::UndoManager& undo_manager = Application::Get().GetControlManager().GetEditionPlugin().GetUndoManager();
        undo_manager.Begin();
        undo_manager.Add(COFFEE_New(ui::PropertyUndo, node,
            (void*)&node->GetFlags(), meta::TYPE<uint32>().Get()));
        node->SetIsStoppedInEditor(_RunInEditorButton->GetState()==ui::widget::BUTTON_STATE_Off);
        undo_manager.Accept("Set run in editor");
        return true;
    }

}
}
