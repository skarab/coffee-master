#ifndef _EDITOR_WIDGET_UNDO_LIST_H_
#define _EDITOR_WIDGET_UNDO_LIST_H_

#include "coffee_editor_includes.h"
#include "widget/undo_controller/widget_undo_controller.h"

namespace coffee_editor
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Undo list
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API UndoList : public ui::Window
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        UndoList();
        ~UndoList();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(UndoController& controller, uint32 offset,
            const basic::Prow< edition::UndoGroup*, true >& list, bool it_is_undo);
        
        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(UndoList);
        COFFEE_Event bool OnSelectItem(shell::Event& event);
        COFFEE_Event bool OnDestroy(shell::Event& event);
        
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        UndoController* _Controller;
        ui::widget::ListView* _List;
        bool _ItIsUndo;
    };

}
}
#endif
