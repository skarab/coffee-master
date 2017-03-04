#ifndef _COFFEE_UI_PROPERTY_TEXT_DIALOG_H_
#define _COFFEE_UI_PROPERTY_TEXT_DIALOG_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/widget/widgets.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Text editor
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PropertyTextDialog : public widget::Dialog
    {
        COFFEE_Type(PropertyTextDialog);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyTextDialog();
        ~PropertyTextDialog();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetText(const basic::Text& text);
        const basic::Text& GetText() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void Create(Window* parent, const basic::Vector2i& position,
            const basic::Vector2i& size, uint32 style = widget::DIALOG_STYLE_CloseButton);
        
        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(PropertyTextDialog);
        COFFEE_Event bool OnNew(shell::Event& event);
        COFFEE_Event bool OnSave(shell::Event& event);
        COFFEE_Event bool OnDisplayNumbers(shell::Event& event);
        COFFEE_Event bool OnTextChanged(shell::Event& event);
        COFFEE_Event bool OnUndo(shell::Event& event);
        COFFEE_Event bool OnRedo(shell::Event& event);
        COFFEE_Event bool OnKeyPressed(shell::Event& event);
        COFFEE_Event bool OnCommand(shell::Event& event);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _OnModify();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        widget::ToolBar* _ToolBar;
        widget::TextBox* _TextBox;
        widget::Button* _ButtonNew;
        widget::Button* _ButtonSave;
        widget::Button* _ButtonDisplayNumbers;
        widget::Button* _ButtonUndo;
        widget::Button* _ButtonRedo;
        bool _ItIsModified;
        basic::List< basic::Text > _ChangeArray;
        uint32 _ChangeIndex;
        bool _ItHasReachedUndoLimit;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, PropertyTextDialog);
}
}
#endif
