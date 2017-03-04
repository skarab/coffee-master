#ifndef _EDITOR_WIDGET_CONFIG_DIALOG_H_
#define _EDITOR_WIDGET_CONFIG_DIALOG_H_

#include "coffee_editor_includes.h"

namespace coffee_editor
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Configuration Dialog
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API ConfigDialog : public ui::widget::Dialog
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ConfigDialog();
        ~ConfigDialog();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create();
        
        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(ConfigDialog);
        COFFEE_Event bool OnActivateTab(shell::Event& event);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        ui::widget::TabControl* _TabControl;
    };
}
}
#endif
