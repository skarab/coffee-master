#include "widget/project_manager/deploy/widget_deploy_package.h"
#include "coffee_editor.h"

namespace coffee_editor
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    DeployPackage::DeployPackage() :
        DeployTarget(PROJECT_TARGET_Package)
    {
    }

    //--------------------------------------------------------------------------------------------//

    DeployPackage::~DeployPackage()
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

    basic::String DeployPackage::GetArchiveName() const
    {
        return Application::Get().GetProject().GetFullPath().GetFileName()
            +".coffee_package";
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    bool DeployPackage::OnDeploy(const storage::PhysicalPath& deployment_path)
    {
        basic::String project_name = Application::Get().GetProject().GetFullPath().GetFileName();
        storage::PhysicalPath root_path = storage::PhysicalSystem::Get().GetRootFolder();
        return storage::PhysicalSystem::Get().CopyFile(root_path+"/" COFFEE_ProjectConfigFile, deployment_path+"/" COFFEE_ProjectConfigFile);
    }

    //--------------------------------------------------------------------------------------------//

    bool DeployPackage::OnDeployArchive(const storage::PhysicalPath& deployment_path)
    {
        return true;
    }

}
}
