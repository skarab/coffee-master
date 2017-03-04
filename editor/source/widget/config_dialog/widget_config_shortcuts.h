#ifndef _EDITOR_WIDGET_CONFIG_SHORTCUTS_H_
#define _EDITOR_WIDGET_CONFIG_SHORTCUTS_H_

#include "coffee_editor_includes.h"

namespace coffee_editor
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Shortcuts configuration window
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API ConfigShortcuts : public ui::Window
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ConfigShortcuts();
        ~ConfigShortcuts();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(ui::Window* tab_client);

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(ConfigShortcuts);
        COFFEE_Event bool OnApply(shell::Event& event);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _UpdateProperties();

        //-ATTRIBUTES-----------------------------------------------------------------------------//
    
        ui::PropertyList* _Properties;
        ui::widget::Button* _ApplyButton;
    };
}
}
#endif
