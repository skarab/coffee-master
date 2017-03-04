#include "widget/undo_controller/widget_undo_list.h"

namespace coffee_editor
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    UndoList::UndoList() :
        _Controller(NULL),
        _List(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    UndoList::~UndoList()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void UndoList::Create(UndoController& controller, uint32 offset,
        const basic::Prow< edition::UndoGroup*, true >& list, bool it_is_undo)
    {
        _ItIsUndo = it_is_undo;
        _Controller = &controller;

        ui::Window::Create(
            &controller, basic::Vector2i(offset, 20), basic::Vector2i(120, 160),
            ui::WINDOW_STYLE_DrawFrame | ui::WINDOW_STYLE_DrawClientRaised
            | ui::WINDOW_STYLE_NoParentClip | ui::WINDOW_STYLE_Activable);
        
        _List = COFFEE_New(ui::widget::ListView);
        _List->Create(this, basic::Vector2i(), basic::Vector2i());
        _List->GetLayout().SetStyle(ui::LAYOUT_STYLE_Expand);

        for (uint32 index=list.GetSize() ; index>0 ; --index)
            _List->AddItem(list[index-1]->GetName());
        
        Activate();
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(UndoList, ui::Window)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Select, ui::widget::Widget, _List, OnSelectItem)
        COFFEE_RegisterEventHandler(ui::WINDOW_EVENT_Deactivate, ui::Window, OnDestroy)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool UndoList::OnSelectItem(shell::Event& event)
    {
        if (_List->GetSelectedIndex()!=NONE)
        {
            _Controller->Undo(_List->GetSelectedIndex()+1, _ItIsUndo);
        }
        
        Destroy();
        return true;
    }
    
    //--------------------------------------------------------------------------------------------//

    bool UndoList::OnDestroy(shell::Event& event)
    {
        Destroy();
        return true;
    }        
        
}
}
