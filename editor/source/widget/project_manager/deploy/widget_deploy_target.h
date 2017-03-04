#ifndef _EDITOR_WIDGET_DEPLOY_TARGET_H_
#define _EDITOR_WIDGET_DEPLOY_TARGET_H_

#include "coffee_editor_includes.h"
#include "project/project_config.h"

namespace coffee_editor
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Base control of a deployment target
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API DeployTarget : public ui::Window
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        DeployTarget(PROJECT_TARGET target);
        virtual ~DeployTarget();
    
        //-ACCESSORS------------------------------------------------------------------------------//

        PROJECT_TARGET GetTarget() const { return _Target; }

        //-QUERIES--------------------------------------------------------------------------------//

        virtual bool AreCoffeeFilesRequired() const { return true; }
        virtual bool IsDeployingAssetsOnly() const { return false; }
        virtual basic::String GetPackageName() const { return "package"; }
        virtual basic::String GetArchiveName() const { return ""; }

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(ui::Window* tab_client);

        //-HANDLERS-------------------------------------------------------------------------------//

        virtual bool OnDeploy(const storage::PhysicalPath& deployment_path) { return true; };
        virtual bool OnDeployArchive(const storage::PhysicalPath& deployment_path) { return true; };

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(DeployTarget);
        COFFEE_Event bool OnDeploy(shell::Event& event);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//
        
        bool _CopyProjectData(basic::String project_name, storage::PhysicalPath deployment_path);
        void _BuildFilesList(ui::Window* parent);

        //-FUNCTIONS------------------------------------------------------------------------------//
        
        static bool _Filter(meta::Object* user, const storage::PhysicalPath& path);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        PROJECT_TARGET _Target;
        ui::widget::TreeControl* _Files;
        ui::widget::Button* _DeployButton;
    };
}
}
#endif
