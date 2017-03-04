#include "widget/undo_controller/widget_undo_controller.h"
#include "widget/undo_controller/widget_undo_list.h"

namespace coffee_editor
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    UndoController::UndoController() :
        _Document(NULL),
        _Undo(NULL),
        _UndoList(NULL),
        _Redo(NULL),
        _RedoList(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    UndoController::~UndoController()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void UndoController::Create(ui::widget::ToolBar& tool_bar, Document& document)
    {
        _Document = &document;

        ui::Window* window = tool_bar.AddWindow(124);
        ui::Window::Create(
            window,
            basic::Vector2i(),
            basic::Vector2i(), ui::WINDOW_STYLE_None);
        GetLayout().SetStyle(ui::LAYOUT_STYLE_Expand | ui::LAYOUT_STYLE_HorizontalCanvas
            | ui::LAYOUT_STYLE_StickChildren);
        
        window = COFFEE_New(ui::Window);
        window->Create(this, basic::Vector2i(), basic::Vector2i(8, 30), 0);
        
        _Undo = COFFEE_New(ui::widget::Button);
        _Undo->Create(this, basic::Vector2i(), basic::Vector2i(30, 30),
            ui::widget::BUTTON_STYLE_HideFrame | ui::widget::BUTTON_STYLE_Default);
        _Undo->SetImage(ui::SKIN_ICON_Undo);
        _Undo->SetHelpText(basic::String("Undo [")+edition::UndoManager::UndoCommand->GetControlString()+"]");
        
        _UndoList = COFFEE_New(ui::widget::Button);
        _UndoList->Create(this, basic::Vector2i(), basic::Vector2i(18, 30),
            ui::widget::BUTTON_STYLE_HideFrame | ui::widget::BUTTON_STYLE_Default);
        _UndoList->SetImage(ui::SKIN_ICON_Down);
        _UndoList->SetHelpText("Undo...");
        
        window = COFFEE_New(ui::Window);
        window->Create(this, basic::Vector2i(), basic::Vector2i(8, 30), 0);
        
        _Redo = COFFEE_New(ui::widget::Button);
        _Redo->Create(this, basic::Vector2i(), basic::Vector2i(30, 30),
            ui::widget::BUTTON_STYLE_HideFrame | ui::widget::BUTTON_STYLE_Default);
        _Redo->SetImage(ui::SKIN_ICON_Redo);
        _Redo->SetHelpText(basic::String("Redo [")+edition::UndoManager::RedoCommand->GetControlString()+"]");
        
        _RedoList = COFFEE_New(ui::widget::Button);
        _RedoList->Create(this, basic::Vector2i(), basic::Vector2i(18, 30),
            ui::widget::BUTTON_STYLE_HideFrame | ui::widget::BUTTON_STYLE_Default);
        _RedoList->SetImage(ui::SKIN_ICON_Down);
        _RedoList->SetHelpText("Redo...");
        
        window = COFFEE_New(ui::Window);
        window->Create(this, basic::Vector2i(), basic::Vector2i(8, 30), 0);
    }

    //--------------------------------------------------------------------------------------------//

    void UndoController::Update()
    {
        const edition::UndoManager& undo_manager = _Document->GetUndoManager();
        bool it_has_undo_enabled = undo_manager.HasUndoGroup() && !undo_manager.IsActive();
        bool it_has_redo_enabled = undo_manager.HasRedoGroup() && !undo_manager.IsActive();

        if (_Undo->IsEnabled()!=it_has_undo_enabled)
        {
            _Undo->Enable(it_has_undo_enabled);
            _UndoList->Enable(it_has_undo_enabled);
        }

        if (_Redo->IsEnabled()!=it_has_redo_enabled)
        {
            _Redo->Enable(it_has_redo_enabled);
            _RedoList->Enable(it_has_redo_enabled);
        }

        ui::Window::Update();
    }

    //--------------------------------------------------------------------------------------------//

    void UndoController::Undo(uint32 count, bool it_is_undo)
    {
        edition::UndoManager& undo_manager = _Document->GetUndoManager();
        for (uint32 index=0 ; index<count ; ++index)
        {
            if (it_is_undo) undo_manager.Undo();
            else undo_manager.Redo();
        }
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(UndoController, ui::Window)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _Undo, OnUndo)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _UndoList, OnUndoList)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _Redo, OnRedo)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _RedoList, OnRedoList)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool UndoController::OnUndo(shell::Event& event)
    {
        input::System::Get().SendEvent(input::EVENT_Command, (void*)edition::UndoManager::UndoCommand);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool UndoController::OnUndoList(shell::Event& event)
    {
        edition::UndoManager& undo_manager = _Document->GetUndoManager();
        UndoList* list = COFFEE_New(UndoList);
        list->Create(*this, _UndoList->GetPosition().X, undo_manager.GetUndoGroupArray(), true);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool UndoController::OnRedo(shell::Event& event)
    {
        input::System::Get().SendEvent(input::EVENT_Command, (void*)edition::UndoManager::RedoCommand);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool UndoController::OnRedoList(shell::Event& event)
    {
        edition::UndoManager& undo_manager = _Document->GetUndoManager();
        UndoList* list = COFFEE_New(UndoList);
        list->Create(*this, _RedoList->GetPosition().X, undo_manager.GetRedoGroupArray(), false);
        return true;
    }
        
}
}
