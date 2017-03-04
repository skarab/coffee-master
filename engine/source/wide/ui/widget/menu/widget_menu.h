#ifndef _COFFEE_UI_WIDGET_MENU_H_
#define _COFFEE_UI_WIDGET_MENU_H_

#include "coffee_includes.h"
#include "wide/ui/window/ui_window.h"
#include "wide/ui/widget/widget.h"
#include "wide/ui/widget/button/widget_button.h"
#include "wide/ui/widget/menu/widget_menu_style.h"
#include "wide/ui/widget/menu/widget_menu_item.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Menu widget
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Menu : public Widget
    {
        friend class MenuItem;

        COFFEE_Type(Menu);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Menu();
        virtual ~Menu();

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void Create(Window* parent, const basic::Vector2i& position,
            const basic::Vector2i& size, uint32 style=MENU_STYLE_PopupMenu);

        Menu* AddMenu(basic::String menu_name);
        Button* AddButton(basic::String button_name);
        Button* AddPushButton(basic::String button_name, bool it_is_pushed);
        void AddSeparator();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(Menu);
        COFFEE_Event bool OnShow(shell::Event& event);
        COFFEE_Event bool OnDeactivate(shell::Event& event);

    private:

        //-QUERIES--------------------------------------------------------------------------------//

        bool _IsWindowAChild(Window & window) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        Menu* _GetHeadPopupMenu();
        Menu* _GetHeadMenu();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        MenuItem* _Panel;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Menu);
}
}
}
#endif
