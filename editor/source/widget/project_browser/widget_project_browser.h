#ifndef _EDITOR_WIDGET_PROJECT_BROWSER_H_
#define _EDITOR_WIDGET_PROJECT_BROWSER_H_

#include "coffee_editor_includes.h"

namespace coffee_editor
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Project browser
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API ProjectBrowser : public ui::Window
    {
        COFFEE_Type(ProjectBrowser);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ProjectBrowser();
        ~ProjectBrowser();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(ProjectBrowser);
        COFFEE_DeclareExternEventHandler(ProjectBrowser, OnAskProjectName);
        COFFEE_DeclareExternEventHandler(ProjectBrowser, OnCreateProject);
        COFFEE_Event bool OnOpenProject(shell::Event& event);
        
    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _UpdateContent();

        //-ATTRIBUTES-----------------------------------------------------------------------------//
        
        ui::widget::ListView* _ProjectList;
        ui::widget::TextBox* _WelcomeScreen;
        ui::widget::Dialog* _ProjectDialog;
        ui::widget::EditBox* _ProjectName;
        basic::Prow< storage::PhysicalPath *, true > _Projects;
        basic::Prow< storage::PhysicalPath *, true > _Tutorials;
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, ProjectBrowser);
}
}
#endif
