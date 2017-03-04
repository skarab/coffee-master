#include "wide/ui/property/basic/text/ui_property_text_dialog.h"
#include "wide/ui/window/ui_window_manager.h"
#include "wide/ui/component/message_box/ui_message_box.h"

#define COFFEE_UI_PROPERTY_TEXT_MaximumUndoCount     15

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::PropertyTextDialog);
        COFFEE_Ancestor(ui::widget::Dialog);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PropertyTextDialog::PropertyTextDialog() :
        _ToolBar(NULL),
        _TextBox(NULL),
        _ButtonNew(NULL),
        _ButtonSave(NULL),
        _ButtonDisplayNumbers(NULL),
        _ButtonUndo(NULL),
        _ButtonRedo(NULL),
        _ItIsModified(false),
        _ChangeIndex(0),
        _ItHasReachedUndoLimit(false)
    {
    }

    //--------------------------------------------------------------------------------------------//

    PropertyTextDialog::~PropertyTextDialog()
    {
    }

    //--------------------------------------------------------------------------------------------//

    void PropertyTextDialog::SetText(const basic::Text& text)
    {
        _TextBox->SetText(text);
        _OnModify();
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Text& PropertyTextDialog::GetText() const
    {
        return _TextBox->GetText();
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void PropertyTextDialog::Create(Window* parent, const basic::Vector2i& position,
        const basic::Vector2i& size, uint32 style)
    {
        widget::Dialog::Create(parent, position, size);

        Window* window;

        window = COFFEE_New(Window);
        window->Create(this, basic::Vector2i(), basic::Vector2i(20, 20), WINDOW_STYLE_Activable);
        window->GetLayout().SetStyle(LAYOUT_STYLE_VerticalCanvas | LAYOUT_STYLE_StickChildren
            | LAYOUT_STYLE_Expand);
        
        _ToolBar = COFFEE_New(widget::ToolBar);
        _ToolBar->Create(window, 20);
        
        _ButtonNew = _ToolBar->AddButton("Empty", SKIN_ICON_Empty);
        _ButtonSave = _ToolBar->AddButton("Save", SKIN_ICON_Save);
        _ToolBar->AddSeparator();
        _ButtonDisplayNumbers = _ToolBar->AddButton("Display numbers", SKIN_ICON_DisplayLines);
        _ButtonDisplayNumbers->SetExtendedStyle(widget::BUTTON_STYLE_PushLike);
        _ToolBar->AddSeparator();
        _ButtonUndo = _ToolBar->AddButton("Undo", SKIN_ICON_Undo);
        _ButtonUndo->Enable(false);
        _ButtonRedo = _ToolBar->AddButton("Redo", SKIN_ICON_Redo);
        _ButtonRedo->Enable(false);

        _TextBox = COFFEE_New(widget::TextBox);
        _TextBox->Create(window, basic::Vector2i(),
            basic::Vector2i(20, 20), widget::TEXT_BOX_STYLE_Default);
        _TextBox->GetLayout().SetStyle(_TextBox->GetLayout().GetStyle() | LAYOUT_STYLE_Expand);
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(PropertyTextDialog, widget::Dialog)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Pressed, widget::Widget, _ButtonNew, OnNew)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Pressed, widget::Widget, _ButtonSave, OnSave)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Pressed, widget::Widget, _ButtonDisplayNumbers, OnDisplayNumbers)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Pressed, widget::Widget, _ButtonUndo, OnUndo)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Pressed, widget::Widget, _ButtonRedo, OnRedo)
        COFFEE_RegisterEventHandler(input::EVENT_KeyPressed, input::Handler, OnKeyPressed)
        COFFEE_RegisterEventHandler(input::EVENT_Command, input::Handler, OnCommand)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Changed, widget::Widget, _TextBox, OnTextChanged)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool PropertyTextDialog::OnNew(shell::Event& event)
    {
        if(GetText().GetLineCount() > 0)
            SetText(basic::Text());

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool PropertyTextDialog::OnSave(shell::Event& event)
    {
        if(_ItIsModified)
        {
            basic::String dialog_name(GetTitleBarText());

            _ItIsModified = false;
            --dialog_name;
            SetTitleBarText(dialog_name);
            SendEvent(widget::EVENT_Changed);
        }

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool PropertyTextDialog::OnDisplayNumbers(shell::Event& event)
    {
        if(_ButtonDisplayNumbers->GetState()==widget::BUTTON_STATE_On)
        {
            _TextBox->SetExtendedStyle(widget::TEXT_BOX_STYLE_DrawLines
                | widget::TEXT_BOX_STYLE_DrawNumbers);
        }
        else
        {
            _TextBox->SetExtendedStyle(widget::TEXT_BOX_STYLE_Default);
        }

        _TextBox->ForceUpdate();
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool PropertyTextDialog::OnTextChanged(shell::Event& event)
    {
        _OnModify();
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool PropertyTextDialog::OnUndo(shell::Event& event)
    {
        --_ChangeIndex;
        _TextBox->SetText(_ChangeArray[_ChangeIndex-1]);

        if(_ChangeIndex==1)
        {
            _ButtonUndo->Enable(false);
        }
        else if(!_ItIsModified)
        {
            _ItIsModified = true;
            SetTitleBarText(GetTitleBarText() + '*');
        }

        _ButtonRedo->Enable(true);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool PropertyTextDialog::OnRedo(shell::Event& event)
    {
        _ButtonUndo->Enable(true);
        _TextBox->SetText(_ChangeArray[_ChangeIndex]);

        if(!_ItIsModified)
        {
            _ItIsModified = true;
            SetTitleBarText(GetTitleBarText() + '*');
        }

        ++_ChangeIndex;

        if(_ChangeIndex==_ChangeArray.GetSize())
            _ButtonRedo->Enable(false);

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool PropertyTextDialog::OnKeyPressed(shell::Event& event)
    {
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool PropertyTextDialog::OnCommand(shell::Event& event)
    {
        return true;
    }
    
    //-OPERATIONS---------------------------------------------------------------------------------//

    void PropertyTextDialog::_OnModify()
    {
        uint32 change_index;

        if(_ChangeIndex>0 && !_ItIsModified)
        {
            _ItIsModified = true;
            SetTitleBarText(GetTitleBarText() + '*');
            _ButtonUndo->Enable(true);
        }

        _ButtonRedo->Enable(false);

        for(change_index=_ChangeIndex ; change_index<_ChangeArray.GetSize() ; ++change_index)
            _ChangeArray.Remove(_ChangeIndex);

        _ChangeArray.AddItem(GetText());
        ++_ChangeIndex;

        if(_ChangeIndex>COFFEE_UI_PROPERTY_TEXT_MaximumUndoCount)
        {
            _ItHasReachedUndoLimit = true;
            --_ChangeIndex;
            _ChangeArray.Remove(0);
        }
    }

}
}
