#ifndef _COFFEE_UI_WIDGET_CHECK_BOX_H_
#define _COFFEE_UI_WIDGET_CHECK_BOX_H_

#include "coffee_includes.h"
#include "wide/ui/widget/widget.h"
#include "wide/ui/widget/check_box/widget_check_box_style.h"
#include "wide/ui/widget/check_box/widget_check_box_state.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// CheckBox widget
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API CheckBox : public Widget
    {
        COFFEE_Type(CheckBox);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        CheckBox();
        ~CheckBox();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetState(const CHECK_BOX_STATE& state);
        const CHECK_BOX_STATE& GetState();
        void SetText(const basic::String& text);
        const basic::String& GetText() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(Window* parent, const basic::Vector2i& position,
            const basic::Vector2i& size, uint32 style=CHECK_BOX_STYLE_Default);

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(CheckBox);
        COFFEE_Event bool OnMouseLeftButtonReleased(shell::Event& event);
        
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        CHECK_BOX_STATE _State;
        basic::String _Text;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, CheckBox);
}
}
}
#endif
