#ifndef _COFFEE_UI_WIDGET_DIALOG_H_
#define _COFFEE_UI_WIDGET_DIALOG_H_

#include "coffee_includes.h"
#include "wide/ui/widget/widget.h"
#include "wide/ui/widget/dialog/widget_dialog_style.h"
#include "wide/ui/widget/button/widget_button.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Dialog widget
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Dialog : public Widget
    {
        COFFEE_Type(Dialog);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Dialog();
        virtual ~Dialog();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetTitleBarText(const basic::String& title_bar_text);
        const basic::String& GetTitleBarText();
        int32 GetTitleBarHeight() const;
        const Button& GetCloseButton() const;
        Button& GetCloseButton();

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void Create(Window* parent, const basic::Vector2i& position,
            const basic::Vector2i& size, uint32 style=DIALOG_STYLE_CloseButton);

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(Dialog);
        COFFEE_Event bool OnClose(shell::Event& event);

    protected:

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void _UpdateClientArea();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::String _TitleBarText;
        int32 _TitleBarHeight;
        Button* _CloseButton;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Dialog);
}
}
}
#endif
