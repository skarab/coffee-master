#ifndef _EDITOR_WIDGET_PROJECT_GENERAL_H_
#define _EDITOR_WIDGET_PROJECT_GENERAL_H_

#include "coffee_editor_includes.h"

namespace coffee_editor
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Edit general project settings
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API ProjectGeneral : public ui::Window
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ProjectGeneral();
        ~ProjectGeneral();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(ui::Window* tab_client);

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(ProjectGeneral);
        
    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _UpdateProperties();

        //-ATTRIBUTES-----------------------------------------------------------------------------//
    
        ui::PropertyList* _Properties;
    };
}
}
#endif
