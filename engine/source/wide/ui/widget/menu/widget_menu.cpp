#include "wide/ui/widget/menu/widget_menu.h"
#include "wide/ui/widget/widgets.h"
#include "wide/ui/window/ui_window_manager.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::widget::Menu);
        COFFEE_Ancestor(ui::widget::Widget);
    COFFEE_EndType();

namespace ui
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Menu::Menu() :
        _Panel(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Menu::~Menu()
    {
        if (_Panel!=NULL)
            _Panel->_Menu=NULL;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Menu::Create(Window* parent, const basic::Vector2i& position,
        const basic::Vector2i& size, uint32 style)
    {
        Window::Create(parent, position, basic::Vector2i(),
            WINDOW_STYLE_Activable | WINDOW_STYLE_DrawFrame
            | WINDOW_STYLE_DrawClientSunken);

        SetExtendedStyle(style);

        if (HasExtendedStyle(MENU_STYLE_PopupMenu))
        {
            GetLayout().SetStyle(LAYOUT_STYLE_Shrink
                | LAYOUT_STYLE_VerticalCanvas
                | LAYOUT_STYLE_StickChildren);
        }
        else
        {
            GetLayout().SetStyle(LAYOUT_STYLE_HorizontalExpand
                | LAYOUT_STYLE_VerticalShrink
                | LAYOUT_STYLE_HorizontalCanvas
                | LAYOUT_STYLE_StickChildren);
        }
    }

    //--------------------------------------------------------------------------------------------//

    Menu* Menu::AddMenu(basic::String menu_name)
    {
        MenuItem* menu_item = COFFEE_New(MenuItem, MENU_ITEM_TYPE_Panel);
        menu_item->SetText(menu_name);
        menu_item->Create(this, basic::Vector2i(), basic::Vector2i());
        return menu_item->GetMenu();
    }

    //--------------------------------------------------------------------------------------------//

    Button* Menu::AddButton(basic::String button_name)
    {
        MenuItem* menu_item = COFFEE_New(MenuItem, MENU_ITEM_TYPE_Item);
        menu_item->Create(this, basic::Vector2i(), basic::Vector2i());

        Button* button = COFFEE_New(Button);
        button->SetText(button_name);

        button->Create(
            menu_item,
            basic::Vector2i(),
            basic::Vector2i(118, 20),
            BUTTON_STYLE_Default);

        menu_item->SetupHandler();
        return button;
    }

    //--------------------------------------------------------------------------------------------//

    Button* Menu::AddPushButton(basic::String button_name, bool it_is_pushed)
    {
        MenuItem* menu_item = COFFEE_New(MenuItem, MENU_ITEM_TYPE_Item);
        menu_item->Create(this, basic::Vector2i(), basic::Vector2i());

        Button* button = COFFEE_New(Button);
        button->SetText(button_name);
        button->Create(menu_item, basic::Vector2i(), basic::Vector2i(118, 20), BUTTON_STYLE_PushLike);
        button->SetState(it_is_pushed ? BUTTON_STATE_On : BUTTON_STATE_Off);
        menu_item->SetupHandler();
        return button;
    }

    //--------------------------------------------------------------------------------------------//

    void Menu::AddSeparator()
    {
        MenuItem* separator_item = COFFEE_New(MenuItem, MENU_ITEM_TYPE_Separator);
        separator_item->Create(this, basic::Vector2i(), basic::Vector2i());
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(Menu, Widget)
        COFFEE_RegisterEventHandler(WINDOW_EVENT_Show, Window, OnShow)
        COFFEE_RegisterEventHandler(WINDOW_EVENT_Deactivate, Window, OnDeactivate)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool Menu::OnShow(shell::Event& event)
    {
        if (HasExtendedStyle(MENU_STYLE_PopupMenu) && event.GetBoolean())
        {
            PositionToDesktop();
            Activate();
        }

        if (!event.GetBoolean())
        {
            for (uint32 i=0 ; i<GetChildCount() ; ++i)
            {
                MenuItem* menu_item = static_cast<MenuItem*>(&GetChild(i));
                if (menu_item->GetType()==MENU_ITEM_TYPE_Panel)
                    menu_item->GetMenu()->Show(false);
            }
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Menu::OnDeactivate(shell::Event& event)
    {
        Menu* head_popup_menu;

        head_popup_menu = _GetHeadPopupMenu();

        if (head_popup_menu!=NULL)
        {
            if (WindowManager::Get().HasActiveWindow()
                && head_popup_menu->_IsWindowAChild(WindowManager::Get().GetActiveWindow()))
            {
                return false;
            }

            if (_GetHeadMenu()->HasExtendedStyle(MENU_STYLE_PopupMenu))
            {
                head_popup_menu->Destroy();
            }
            else
            {
                head_popup_menu->Show(false);
            }
        }

        return true;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool Menu::_IsWindowAChild(Window& window) const
    {
        if(window.GetMetaType().GetName()==Menu::GetClassMetaType().GetName())
        {
            Menu* menu = (Menu*) &window;

            if(menu==this)
                return true;

            if(menu->_Panel != NULL)
            {
                if(&menu->_Panel->GetParentWindow()==this)
                    return true;

                return _IsWindowAChild(menu->_Panel->GetParentWindow());
            }
        }

        return false;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    Menu* Menu::_GetHeadPopupMenu()
    {
        if (!HasExtendedStyle(MENU_STYLE_PopupMenu))
            return NULL;

        if(_Panel!=NULL)
        {
            Menu* parent_menu;

            parent_menu = (Menu*)&_Panel->GetParentWindow();

            if (parent_menu->HasExtendedStyle(MENU_STYLE_PopupMenu))
                return parent_menu->_GetHeadPopupMenu();
        }

        return this;
    }

    //--------------------------------------------------------------------------------------------//

    Menu* Menu::_GetHeadMenu()
    {
        if(_Panel != NULL)
        {
            Menu* parent_menu;
            parent_menu = ((Menu *) &_Panel->GetParentWindow());
            return parent_menu->_GetHeadMenu();
        }
        return this;
    }

}
}
}
