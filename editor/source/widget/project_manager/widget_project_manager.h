#ifndef _EDITOR_WIDGET_PROJECT_MANAGER_H_
#define _EDITOR_WIDGET_PROJECT_MANAGER_H_

#include "coffee_editor_includes.h"

namespace coffee_editor
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Manages all project settings and deployment
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API ProjectManager : public ui::widget::Dialog
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ProjectManager();
        ~ProjectManager();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create();
        
        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(ProjectManager);
        COFFEE_Event bool OnActivateTab(shell::Event& event);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        ui::widget::TabControl* _TabControl;
    };
}
}
#endif
