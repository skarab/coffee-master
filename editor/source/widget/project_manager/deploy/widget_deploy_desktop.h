#ifndef _EDITOR_WIDGET_DEPLOY_DESKTOP_H_
#define _EDITOR_WIDGET_DEPLOY_DESKTOP_H_

#include "coffee_editor_includes.h"
#include "widget/project_manager/deploy/widget_deploy_target.h"

namespace coffee_editor
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Control desktop deployment
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API DeployDesktop : public DeployTarget
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        DeployDesktop();
        ~DeployDesktop();

        //-QUERIES--------------------------------------------------------------------------------//

        basic::String GetPackageName() const;
        basic::String GetArchiveName() const;

        //-HANDLERS-------------------------------------------------------------------------------//

        bool OnDeploy(const storage::PhysicalPath& deployment_path);
        bool OnDeployArchive(const storage::PhysicalPath& deployment_path);
    };
}
}
#endif
