#ifndef _COFFEE_UI_WIDGET_MENU_ITEM_H_
#define _COFFEE_UI_WIDGET_MENU_ITEM_H_

#include "coffee_includes.h"
#include "wide/ui/widget/widget.h"
#include "wide/ui/widget/menu/widget_menu_item_type.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    class Menu;

    //--------------------------------------------------------------------------------------------//
    /// MenuItem widget
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API MenuItem : public Widget
    {
        friend class Menu;

        COFFEE_Type(MenuItem);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        MenuItem();
        MenuItem(const MENU_ITEM_TYPE& type);
        virtual ~MenuItem();

        //-ACCESSORS------------------------------------------------------------------------------//

        const MENU_ITEM_TYPE& GetType() const;
        Menu* GetMenu();
        void SetText(const basic::String& text);
        const basic::String& GetText() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void Create(Window* parent, const basic::Vector2i& position,
            const basic::Vector2i& size, uint32 style=0);

        void SetupHandler();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(MenuItem);
        COFFEE_Event bool OnBeginCursorOver(shell::Event& event);
        COFFEE_Event bool OnMouseLeftButtonPressed(shell::Event& event);
        COFFEE_Event bool OnMouseLeftButtonReleased(shell::Event& event);
        COFFEE_DeclareExternEventHandler(MenuItem, OnItemEndAction);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _Activate();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        MENU_ITEM_TYPE _Type;
        Menu* _Menu;
        basic::String _Text;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, MenuItem);
}
}
}
#endif
