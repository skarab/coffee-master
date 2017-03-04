#ifndef _COFFEE_UI_WIDGET_TAB_CONTROL_H_
#define _COFFEE_UI_WIDGET_TAB_CONTROL_H_

#include "coffee_includes.h"
#include "wide/ui/widget/widget.h"
#include "wide/ui/widget/button/widget_button.h"
#include "wide/ui/widget/tab_control/widget_tab_control_event.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// TabControl widget
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API TabControl : public Widget
    {
        COFFEE_Type(TabControl);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        TabControl();
        ~TabControl();

        //-ACCESSORS------------------------------------------------------------------------------//

        const basic::String& GetActiveTab() const;
        const Window& GetClientWindow() const;
        Window& GetClientWindow();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(Window* parent, const basic::Vector2i& position,
            const basic::Vector2i& size, uint32 style = WINDOW_STYLE_DrawFrame
            | WINDOW_STYLE_DrawClientSunken);
        void AddTab(const basic::String& name);
        void AddSeparator(const basic::String& name="");
        bool ActivateTab(const basic::String& name);
        
        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(TabControl);
        COFFEE_Event bool OnTabButtonPressed(shell::Event& event);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Window* _TabPane;
        basic::Prow<Button*> _TabButtonArray;
        Window* _ClientWindow;
        Button* _ActiveTab;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, TabControl);
}
}
}
#endif
