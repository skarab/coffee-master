#ifndef _EDITOR_WIDGET_SELECTION_CONTROLLER_H_
#define _EDITOR_WIDGET_SELECTION_CONTROLLER_H_

#include "coffee_editor_includes.h"
#include "document/document.h"

namespace coffee_editor
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Selection controller
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API SelectionController : public ui::Window
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SelectionController();
        ~SelectionController();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(ui::widget::ToolBar& tool_bar, Document& document);
        void Update();
        
        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(SelectionController);
        COFFEE_Event bool OnSelect(shell::Event& event);
        COFFEE_Event bool OnCopy(shell::Event& event);
        COFFEE_Event bool OnCut(shell::Event& event);
        COFFEE_Event bool OnPaste(shell::Event& event);
        COFFEE_Event bool OnDelete(shell::Event& event);
        
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Document* _Document;
        ui::widget::Button* _Select;
        ui::widget::Button* _Cut;
        ui::widget::Button* _Copy;
        ui::widget::Button* _Paste;
        ui::widget::Button* _Delete;
    };

}
}
#endif
