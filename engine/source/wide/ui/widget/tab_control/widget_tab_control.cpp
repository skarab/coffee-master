#include "wide/ui/widget/tab_control/widget_tab_control.h"
#include "wide/ui/widget/label/widget_label.h"

namespace coffee
{
    COFFEE_BeginType(ui::widget::TabControl);
        COFFEE_Ancestor(ui::widget::Widget);
    COFFEE_EndType();

namespace ui
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    TabControl::TabControl() :
        _TabPane(NULL),
        _ClientWindow(NULL),
        _ActiveTab(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    TabControl::~TabControl()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const basic::String& TabControl::GetActiveTab() const
    {
        return _ActiveTab->GetText();
    }

    //--------------------------------------------------------------------------------------------//

    const Window& TabControl::GetClientWindow() const
    {
        return *_ClientWindow;
    }

    //--------------------------------------------------------------------------------------------//

    Window& TabControl::GetClientWindow()
    {
        return *_ClientWindow;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void TabControl::Create(Window* parent, const basic::Vector2i& position,
        const basic::Vector2i& size, uint32 style)
    {
        Window::Create(parent, position, size, style);

        GetLayout().SetStyle(LAYOUT_STYLE_HorizontalCanvas
            | LAYOUT_STYLE_StickChildren);

        _TabPane = COFFEE_New(Window);
        _TabPane->Create(this, basic::Vector2i(), basic::Vector2i(),
            WINDOW_STYLE_DrawFrame | WINDOW_STYLE_DrawClientSunken);
        _TabPane->GetLayout().SetCanvas(100, false);
        _TabPane->GetLayout().SetStyle(LAYOUT_STYLE_VerticalCanvas
            | LAYOUT_STYLE_StickChildren
            | LAYOUT_STYLE_VerticalExpand);
        
        _ClientWindow = COFFEE_New(Window);
        _ClientWindow->Create(this, basic::Vector2i(), basic::Vector2i(),
            WINDOW_STYLE_DrawFrame | WINDOW_STYLE_DrawClientSunken);
        _ClientWindow->GetLayout().SetCanvas(100, true);
        _ClientWindow->GetLayout().SetStyle(LAYOUT_STYLE_VerticalCanvas
            | LAYOUT_STYLE_StickChildren
            | LAYOUT_STYLE_Expand);
    }

    //--------------------------------------------------------------------------------------------//

    void TabControl::AddTab(const basic::String& name)
    {
        Button* tab_button;
        tab_button = COFFEE_New(Button);
        tab_button->Create(_TabPane, basic::Vector2i(0, 0), basic::Vector2i(100, 35),
            BUTTON_STYLE_PushLike);
        tab_button->SetText(name);
        tab_button->SetState(BUTTON_STATE_Off);
        _TabButtonArray.AddItem(tab_button);
    }

    //--------------------------------------------------------------------------------------------//

    void TabControl::AddSeparator(const basic::String& name)
    {
        Label* separator = COFFEE_New(Label);
        separator->Create(_TabPane, basic::Vector2i(0, 0), basic::Vector2i(100, 15));
        separator->SetText(name);
    }

    //--------------------------------------------------------------------------------------------//

    bool TabControl::ActivateTab(const basic::String& name)
    {
        Button* tab(NULL);

        for (uint32 index=0 ; index<_TabButtonArray.GetSize() ; ++index)
        {
            if (_TabButtonArray[index]->GetText()==name)
            {
                tab = _TabButtonArray[index];
                break;
            }
        }

        if (tab!=NULL)
        {
            if (tab==_ActiveTab)
                return true;

            for (uint32 index=0 ; index<_TabButtonArray.GetSize() ; ++index)
            {
                if (_TabButtonArray[index]!=tab)
                    _TabButtonArray[index]->SetState(BUTTON_STATE_Off);
            }

            tab->SetState(BUTTON_STATE_On);
            _ClientWindow->DestroyChildren();
            _ActiveTab = tab;

            shell::EventCode event_code((uint32)TAB_CONTROL_EVENT_Activate, GetClassMetaType());
            shell::EventParameters event_parameters;
            shell::Event event;
            event.Set(event_code, event_parameters,
                shell::EVENT_FLAG_StopWhenHandled|shell::EVENT_FLAG_ForwardToParent);
            shell::EventHandler::SendEvent(event);
            return true;
        }

        return false;
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(TabControl, Widget)
        COFFEE_RegisterEventHandler(EVENT_Pressed, Widget, OnTabButtonPressed)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool TabControl::OnTabButtonPressed(shell::Event& event)
    {
        for (uint32 index=0 ; index<_TabButtonArray.GetSize() ; ++index)
        {
            if (_TabButtonArray[index]==event.GetTarget())
                return ActivateTab(_TabButtonArray[index]->GetText());
        }
        return false;
    }

}
}
}
