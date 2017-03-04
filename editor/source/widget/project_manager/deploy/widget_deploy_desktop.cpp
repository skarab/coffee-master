#include "widget/project_manager/deploy/widget_deploy_desktop.h"
#include "coffee_editor.h"

namespace coffee_editor
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    DeployDesktop::DeployDesktop() :
        DeployTarget(PROJECT_TARGET_Desktop)
    {
    }

    //--------------------------------------------------------------------------------------------//

    DeployDesktop::~DeployDesktop()
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

    basic::String DeployDesktop::GetPackageName() const
    {
        return Application::Get().GetProject().GetFullPath().GetFileName();
    }
     
    //--------------------------------------------------------------------------------------------//

    basic::String DeployDesktop::GetArchiveName() const
    {
        return GetPackageName()+".7z";
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    bool DeployDesktop::OnDeploy(const storage::PhysicalPath& deployment_path)
    {
        basic::String project_name = Application::Get().GetProject().GetFullPath().GetFileName();
        storage::PhysicalPath root_path = storage::PhysicalSystem::Get().GetRootFolder();
        return storage::PhysicalSystem::Get().CopyFile(root_path+"/player.exe", deployment_path+"/"+project_name+".exe")
            && storage::PhysicalSystem::Get().CopyFile(root_path+"/coffee_player.dll", deployment_path+"/coffee_player.dll")
            && storage::PhysicalSystem::Get().CopyFile(root_path+"/coffee_engine.dll", deployment_path+"/coffee_engine.dll")
            && storage::PhysicalSystem::Get().CopyFile(root_path+"/" COFFEE_ProjectConfigFile, deployment_path+"/" COFFEE_ProjectConfigFile);
    }

    //--------------------------------------------------------------------------------------------//

    bool DeployDesktop::OnDeployArchive(const storage::PhysicalPath& deployment_path)
    {
        return true;
    }
}
}
