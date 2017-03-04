#ifndef _EDITOR_WIDGET_DEPLOY_PACKAGE_H_
#define _EDITOR_WIDGET_DEPLOY_PACKAGE_H_

#include "coffee_editor_includes.h"
#include "widget/project_manager/deploy/widget_deploy_target.h"

namespace coffee_editor
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Control package deployment
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API DeployPackage : public DeployTarget
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        DeployPackage();
        ~DeployPackage();

        //-QUERIES--------------------------------------------------------------------------------//

        bool AreCoffeeFilesRequired() const { return false; }
        bool IsDeployingAssetsOnly() const { return true; }
        basic::String GetArchiveName() const;

        //-HANDLERS-------------------------------------------------------------------------------//

        bool OnDeploy(const storage::PhysicalPath& deployment_path);
        bool OnDeployArchive(const storage::PhysicalPath& deployment_path);
    };
}
}
#endif
