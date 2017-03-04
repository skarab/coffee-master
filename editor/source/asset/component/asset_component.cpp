#include "asset/component/asset_component.h"
#include "coffee_editor.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(asset::Component);
        COFFEE_Ancestor(asset::Plugin);
    COFFEE_EndType();

namespace asset
{
    //-OPERATIONS---------------------------------------------------------------------------------//

    bool Component::Import()
    {
        storage::Path file_path = Manager::Get().GetResourcePath(GetAssetPath())
            + "/" + GetAssetPath().GetFileNameWithoutExtension() + "." + _GetExtension();
        
        plugins::Object* component = _CreateComponent();
        component->SetLibraryPath(file_path);
        resource::Chunk* resource_chunk;
        resource_chunk = resource::Manager::Get().Create(file_path);
        resource_chunk->AddLOD(*component);
        
        DeleteImportedResources();
        AddImportedResource(resource_chunk);
        return true;
    }
        
    //--------------------------------------------------------------------------------------------//

    bool Component::Create(const storage::PhysicalPath& asset_path, const storage::Path& logical_path)
    {
        storage::PhysicalPath root = storage::System::Get().GetRootPath()
            + "/internals/templates/template." + _GetExtension();
        if (storage::PhysicalSystem::Get().IsFolder(asset_path))
            return false;

        SetAssetPath(logical_path);
        
        return storage::System::Get().CreateFolder(logical_path, true)
            && storage::PhysicalSystem::Get().CreateFolder(asset_path+"/build")
            && storage::PhysicalSystem::Get().CreateFolder(asset_path+"/source")
            && _ProcessFile("/build/Jamfile.jam", asset_path, root)
            && _ProcessFile("/build/workspace.config", asset_path, root)
            && _ProcessFile("/source/component.cpp", asset_path, root)
            && _ProcessFile("/source/component.h", asset_path, root)
            && GenerateWorkspace() && LaunchWorkspace();
    }
    
}
}
