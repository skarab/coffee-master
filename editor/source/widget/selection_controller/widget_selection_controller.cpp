#include "widget/selection_controller/widget_selection_controller.h"
#include "document/document.h"

namespace coffee_editor
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SelectionController::SelectionController() :
        _Document(NULL),
        _Select(NULL),
        _Copy(NULL),
        _Cut(NULL),
        _Paste(NULL),
        _Delete(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    SelectionController::~SelectionController()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void SelectionController::Create(ui::widget::ToolBar& tool_bar, Document& document)
    {
        _Document = &document;

        ui::Window* window = tool_bar.AddWindow(180);
        ui::Window::Create(
            window,
            basic::Vector2i(),
            basic::Vector2i(), ui::WINDOW_STYLE_None);
        GetLayout().SetStyle(ui::LAYOUT_STYLE_Expand | ui::LAYOUT_STYLE_HorizontalCanvas
            | ui::LAYOUT_STYLE_StickChildren);
        
        window = COFFEE_New(ui::Window);
        window->Create(this, basic::Vector2i(), basic::Vector2i(8, 30), 0);
        
        _Copy = COFFEE_New(ui::widget::Button);
        _Copy->Create(this, basic::Vector2i(), basic::Vector2i(30, 30),
            ui::widget::BUTTON_STYLE_HideFrame | ui::widget::BUTTON_STYLE_Default);
        _Copy->SetImage("/coffee/import/editor/icons/copy.texture");
        _Copy->SetHelpText(basic::String("Copy selected node(s) [")+edition::SelectionManager::CopyCommand->GetControlString()+"]");
        
        _Cut = COFFEE_New(ui::widget::Button);
        _Cut->Create(this, basic::Vector2i(), basic::Vector2i(30, 30),
            ui::widget::BUTTON_STYLE_HideFrame | ui::widget::BUTTON_STYLE_Default);
        _Cut->SetImage("/coffee/import/editor/icons/cut.texture");
        _Cut->SetHelpText(basic::String("Cut selected node(s) [")+edition::SelectionManager::CutCommand->GetControlString()+"]");

        _Paste = COFFEE_New(ui::widget::Button);
        _Paste->Create(this, basic::Vector2i(), basic::Vector2i(30, 30),
            ui::widget::BUTTON_STYLE_HideFrame | ui::widget::BUTTON_STYLE_Default);
        _Paste->SetImage("/coffee/import/editor/icons/paste.texture");
        _Paste->SetHelpText(basic::String("Paste node(s) from the clipboard [")+edition::SelectionManager::PasteCommand->GetControlString()+"]");
        
        _Delete = COFFEE_New(ui::widget::Button);
        _Delete->Create(this, basic::Vector2i(), basic::Vector2i(30, 30),
            ui::widget::BUTTON_STYLE_HideFrame | ui::widget::BUTTON_STYLE_Default);
        _Delete->SetImage("/coffee/import/editor/icons/delete.texture");
        _Delete->SetHelpText(basic::String("Delete selected node(s) [")+edition::SelectionManager::DeleteCommand->GetControlString()+"]");
        
        _Select = COFFEE_New(ui::widget::Button);
        _Select->Create(this, basic::Vector2i(), basic::Vector2i(70, 30),
            ui::widget::BUTTON_STYLE_HideFrame | ui::widget::BUTTON_STYLE_Default);
        _Select->SetText("Select...");
    }

    //--------------------------------------------------------------------------------------------//

    void SelectionController::Update()
    {
        bool it_has_copy_enabled(_Document->OnUpdateCopy());
        bool it_has_cut_enabled(_Document->OnUpdateCut());
        bool it_has_paste_enabled(_Document->OnUpdatePaste());
        bool it_has_delete_enabled(_Document->OnUpdateDelete());
    
        if (_Copy->IsEnabled()!=it_has_copy_enabled)
            _Copy->Enable(it_has_copy_enabled);
        if (_Cut->IsEnabled()!=it_has_cut_enabled)
            _Cut->Enable(it_has_cut_enabled);
        if (_Paste->IsEnabled()!=it_has_paste_enabled)
            _Paste->Enable(it_has_paste_enabled);
        if (_Delete->IsEnabled()!=it_has_delete_enabled)
            _Delete->Enable(it_has_delete_enabled);
        
        ui::Window::Update();
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(SelectionController, ui::Window)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _Select, OnSelect)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _Copy, OnCopy)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _Cut, OnCut)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _Paste, OnPaste)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _Delete, OnDelete)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool SelectionController::OnSelect(shell::Event& event)
    {
        ui::widget::Menu* menu = COFFEE_New(ui::widget::Menu);
        ui::WindowContext context;
        context.Create(_Select);
        menu->Create(NULL, basic::Vector2i(
            context.GetDesktopWindowRect().GetMinimum().X,
            context.GetDesktopWindowRect().GetMaximum().Y), basic::Vector2i());
        
        ui::widget::Button* button;

        button = menu->AddButton("None");
        button->SetSize(basic::Vector2i(70, 30));
        button->SetExtendedStyle(ui::widget::BUTTON_STYLE_HideFrame | ui::widget::BUTTON_STYLE_Default);
        button->SetHelpText("Clear selection");

        //COFFEE_RegisterExternEventHandler( ui::widget::EVENT_Pressed, ui::widget::Widget::GetClassMetaType(),
        //    *button, OnSetReferenceLocal);
        
        button = menu->AddButton("All");
        button->SetSize(basic::Vector2i(70, 30));
        button->SetExtendedStyle(ui::widget::BUTTON_STYLE_HideFrame | ui::widget::BUTTON_STYLE_Default);
        button->SetHelpText("Select all");

        //COFFEE_RegisterExternEventHandler( ui::widget::EVENT_Pressed, ui::widget::Widget::GetClassMetaType(),
        //    *button, OnSetReferenceLocal);

        button = menu->AddButton("Invert");
        button->SetSize(basic::Vector2i(70, 30));
        button->SetExtendedStyle(ui::widget::BUTTON_STYLE_HideFrame | ui::widget::BUTTON_STYLE_Default);
        button->SetHelpText("Invert selection");

        //COFFEE_RegisterExternEventHandler( ui::widget::EVENT_Pressed, ui::widget::Widget::GetClassMetaType(),
        //    *button, OnSetReferenceLocal);
        
        return true;
    }
    
    //--------------------------------------------------------------------------------------------//

    bool SelectionController::OnCopy(shell::Event& event)
    {
        input::System::Get().SendEvent(input::EVENT_Command, (void*)edition::SelectionManager::CopyCommand);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool SelectionController::OnCut(shell::Event& event)
    {
        input::System::Get().SendEvent(input::EVENT_Command, (void*)edition::SelectionManager::CutCommand);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool SelectionController::OnPaste(shell::Event& event)
    {
        input::System::Get().SendEvent(input::EVENT_Command, (void*)edition::SelectionManager::PasteCommand);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool SelectionController::OnDelete(shell::Event& event)
    {
        input::System::Get().SendEvent(input::EVENT_Command, (void*)edition::SelectionManager::DeleteCommand);
        return true;
    }

}
}
