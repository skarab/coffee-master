#ifndef _EDITOR_WIDGET_CONFIG_GENERAL_H_
#define _EDITOR_WIDGET_CONFIG_GENERAL_H_

#include "coffee_editor_includes.h"

namespace coffee_editor
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// General editor settings
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API ConfigGeneral : public ui::Window
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ConfigGeneral();
        ~ConfigGeneral();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(ui::Window* tab_client);

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(ConfigGeneral);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//
    };
}
}
#endif
