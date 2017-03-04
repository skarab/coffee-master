#include "wide/ui/widget/menu/widget_menu_item.h"
#include "wide/ui/widget/menu/widget_menu.h"
#include "wide/ui/window/ui_window_context.h"
#include "wide/ui/window/ui_window_manager.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::widget::MenuItem);
        COFFEE_Ancestor(ui::widget::Widget);
    COFFEE_EndType();

namespace ui
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    MenuItem::MenuItem() :
        _Type(MENU_ITEM_TYPE_None),
        _Menu(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    MenuItem::MenuItem(const MENU_ITEM_TYPE& type) :
        _Type(type),
        _Menu(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    MenuItem::~MenuItem()
    {
        if (_Menu!=NULL)
        {
            _Menu->_Panel = NULL;
            _Menu->Destroy();
        }
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const MENU_ITEM_TYPE& MenuItem::GetType() const
    {
        return _Type;
    }

    //--------------------------------------------------------------------------------------------//

    Menu* MenuItem::GetMenu()
    {
        return _Menu;
    }

    //--------------------------------------------------------------------------------------------//

    void MenuItem::SetText(const basic::String& text)
    {
        _Text = text;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::String& MenuItem::GetText() const
    {
        return _Text;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void MenuItem::Create(Window* parent, const basic::Vector2i& position,
        const basic::Vector2i& size, uint32 style)
    {
        switch(GetType())
        {
            case MENU_ITEM_TYPE_Panel:
            {
                Window::Create(parent, position, basic::Vector2i(120, 20),
                    WINDOW_STYLE_Focusable);

                WindowContext context;
                context.Create(this);

                basic::Vector2i menu_position;
                menu_position.X=(context.GetDesktopWindowRect().Position.X
                    + GetRect().Size.X + GetParentWindow().GetBorders().X * 4);
                menu_position.Y=context.GetDesktopWindowRect().Position.Y;

                _Menu = COFFEE_New(Menu);
                _Menu->Create(NULL, menu_position, basic::Vector2i());
                _Menu->Show(false);
                _Menu->_Panel = this;
            } break;

            case MENU_ITEM_TYPE_Item:
            {
                Window::Create(parent, position, basic::Vector2i(120, 0),
                    WINDOW_STYLE_Focusable);
                GetLayout().SetStyle(LAYOUT_STYLE_VerticalCanvas
                    | LAYOUT_STYLE_Shrink);
            } break;

            case MENU_ITEM_TYPE_Separator:
            {
                Window::Create(parent, position, basic::Vector2i(120, 3),
                    WINDOW_STYLE_Focusable | WINDOW_STYLE_DrawFrame
                    | WINDOW_STYLE_DrawClientSunken);
            }
        }
    }

    //--------------------------------------------------------------------------------------------//

    void MenuItem::SetupHandler()
    {
        if(GetType()==MENU_ITEM_TYPE_Item)
        {
            COFFEE_RegisterExternEventHandler(
                EVENT_Pressed,
                Widget::GetClassMetaType(),
                *(shell::EventHandler*) &GetChild(0),
                OnItemEndAction);
        }
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(MenuItem, Widget)
        COFFEE_RegisterEventHandler(WINDOW_EVENT_BeginCursorOver, Window, OnBeginCursorOver)
        COFFEE_RegisterEventHandler(input::EVENT_MouseLeftButtonPressed, input::Handler, OnMouseLeftButtonPressed)
        COFFEE_RegisterEventHandler(input::EVENT_MouseLeftButtonReleased, input::Handler, OnMouseLeftButtonReleased)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool MenuItem::OnBeginCursorOver(shell::Event& event)
    {
        Menu* menu = (Menu*) &GetParentWindow();

        if (!menu->HasExtendedStyle(MENU_STYLE_PopupMenu)
            && (!WindowManager::Get().HasActiveWindow()
                || !menu->_IsWindowAChild(WindowManager::Get().GetActiveWindow())))
        {
            return false;
        }

        _Activate();
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool MenuItem::OnItemEndAction(shell::Event& event)
    {
        WindowManager::Get().GetDesktopWindow().Activate();
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool MenuItem::OnMouseLeftButtonPressed(shell::Event& event)
    {
        if (_Menu!=NULL && GetMenu()->HasExtendedStyle(MENU_STYLE_PopupMenu))
        {
            _Activate();
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool MenuItem::OnMouseLeftButtonReleased(shell::Event& event)
    {
        if(GetType()==MENU_ITEM_TYPE_Panel)
        {
            shell::Event event;
            OnBeginCursorOver(event);
        }
        return false;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void MenuItem::_Activate()
    {
        Menu* menu = (Menu*) &GetParentWindow();
        uint32 menu_item_index;

        if(GetType()==MENU_ITEM_TYPE_Panel
            && &WindowManager::Get().GetActiveWindow()==_Menu
            && _Menu->IsVisible())
        {
            return;
        }

        for(menu_item_index=0 ; menu_item_index<menu->GetChildCount() ; ++menu_item_index)
        {
            MenuItem* menu_item = (MenuItem*) &menu->GetChild(menu_item_index);

            if(menu_item->GetType()==MENU_ITEM_TYPE_Panel)
                menu_item->GetMenu()->Show(false);
        }

        if(GetType()==MENU_ITEM_TYPE_Panel)
        {
            WindowContext context;
            basic::Vector2i menu_position;

            context.Create(this);
            
            if (menu->HasExtendedStyle(MENU_STYLE_PopupMenu))
            {
                menu_position.X=(context.GetDesktopWindowRect().Position.X
                    + GetRect().Size.X + GetParentWindow().GetBorders().X * 4);
                menu_position.Y=context.GetDesktopWindowRect().Position.Y;
            }
            else
            {
                menu_position.X=(context.GetDesktopWindowRect().Position.X);
                menu_position.Y=context.GetDesktopWindowRect().Position.Y
                    + GetRect().Size.Y + GetParentWindow().GetBorders().Y * 4;
            }

            _Menu->SetPosition(menu_position);
            _Menu->PositionToDesktop();
            _Menu->Show(true);
        }
        else if(!GetParentWindow().IsActiveWindow())
        {
            GetParentWindow().Activate();
        }
    }

}
}
}
