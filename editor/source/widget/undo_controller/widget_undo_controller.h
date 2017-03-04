#ifndef _EDITOR_WIDGET_UNDO_CONTROLLER_H_
#define _EDITOR_WIDGET_UNDO_CONTROLLER_H_

#include "coffee_editor_includes.h"
#include "document/document.h"

namespace coffee_editor
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Undo controller
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API UndoController : public ui::Window
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        UndoController();
        ~UndoController();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(ui::widget::ToolBar& tool_bar, Document& document);
        void Update();
        void Undo(uint32 count, bool it_is_undo);

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(UndoController);
        COFFEE_Event bool OnUndo(shell::Event& event);
        COFFEE_Event bool OnUndoList(shell::Event& event);
        COFFEE_Event bool OnRedo(shell::Event& event);
        COFFEE_Event bool OnRedoList(shell::Event& event);
        
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Document* _Document;
        ui::widget::Button* _Undo;
        ui::widget::Button* _UndoList;
        ui::widget::Button* _Redo;
        ui::widget::Button* _RedoList;
    };

}
}
#endif
