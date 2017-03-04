#include "asset/plugin/asset_plugin.h"
#include "coffee_editor.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(asset::Plugin);
        COFFEE_Ancestor(asset::Importer);
    COFFEE_EndType();

namespace asset
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

	Plugin::Plugin()
    {
    }

    //--------------------------------------------------------------------------------------------//

    Plugin::~Plugin()
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool Plugin::IsSupporting(const basic::String& file_extension)
    {
        return file_extension=="plugin";
    }

    //--------------------------------------------------------------------------------------------//

    plugins::Object* Plugin::CreatePlugin() const
    {
        return COFFEE_New(plugins::Object);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Plugin::Synchronize(const storage::Path& import_path, const storage::Path& asset_path, uint32 flags)
    {
        SetAssetPath(asset_path);
            
        // Generate workspace and build if required
        if (COFFEE_IsFlagEnabled(flags, SYNC_FLAG_CheckScripts))
        {
            if (GenerateWorkspace())
                Build();
        }

        storage::PhysicalPath library_path = _GetBuildLibraryPath(asset_path);
        storage::FileAccess* file = storage::PhysicalSystem::Get().GetFileAccess(library_path);
        basic::Date date;
        if (file!=NULL)
        {
            date = file->GetLastWriteDate();
            COFFEE_Delete(file);
        }

        bool it_has_import(storage::System::Get().HasPath(import_path));
        if (!it_has_import || storage::System::Get().GetFileTimeStamp(import_path)<date
            || COFFEE_IsFlagEnabled(flags, SYNC_FLAG_CheckScripts))
        {
            if (!it_has_import)
                storage::System::Get().SetFileData(import_path, storage::Data(), true);
    
            Serialize(import_path, it_has_import?storage::MODE_Input:storage::MODE_Output);
            
            if (GetSynchronizationMode()==MODE_Automatic && (Import() || it_has_import))
            {
                Serialize(import_path, storage::MODE_Output);
                SaveImportedResources();
            }
        }
    }
     
    //--------------------------------------------------------------------------------------------//

    bool Plugin::Import()
    {
        storage::Path file_path = Manager::Get().GetResourcePath(GetAssetPath())
            + "/" + GetAssetPath().GetFileNameWithoutExtension() + "." + _GetExtension();
        
        plugins::Object* plugin = CreatePlugin();
        plugin->SetLibraryPath(file_path);
        resource::Chunk* resource_chunk;
        resource_chunk = resource::Manager::Get().Create(file_path);
        resource_chunk->AddLOD(*plugin);
        
        DeleteImportedResources();
        AddImportedResource(resource_chunk);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    void Plugin::OnPostSaveResources()
    {
        storage::PhysicalPath build_library_path = _GetBuildLibraryPath(GetAssetPath());
        storage::PhysicalSystem::Get().CopyFile(build_library_path,
            storage::PhysicalPath(_GetLibraryPath(GetAssetPath())), true);
    }

    //--------------------------------------------------------------------------------------------//

    bool Plugin::Create(const storage::PhysicalPath& asset_path, const storage::Path& logical_path)
    {
        storage::PhysicalPath root = storage::System::Get().GetRootPath()
            + "/internals/templates/template." + _GetExtension();

        SetAssetPath(logical_path);
        
        return storage::System::Get().CreateFolder(logical_path, true)
            && storage::PhysicalSystem::Get().CreateFolder(asset_path+"/build")
            && storage::PhysicalSystem::Get().CreateFolder(asset_path+"/source")
            && _ProcessFile("/build/Jamfile.jam", asset_path, root)
            && _ProcessFile("/build/workspace.config", asset_path, root)
            && _ProcessFile("/source/plugin.cpp", asset_path, root)
            && _ProcessFile("/source/plugin.h", asset_path, root)
            && GenerateWorkspace() && LaunchWorkspace();
    }

    //--------------------------------------------------------------------------------------------//

    bool Plugin::Delete()
    {
        return false;
    }
    
    //--------------------------------------------------------------------------------------------//

    bool Plugin::Move()
    {
        return false;
    }
    
    //--------------------------------------------------------------------------------------------//

    bool Plugin::BreakDependencies()
    {
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Plugin::Build()
    {
        basic::String platform, compiler, mode;
        if (!core::Platform::Get().GetBuildTargets(platform, compiler, mode))
            return false;
        
        COFFEE_Log(core::Log::None, "Build %s", GetAssetPath().GetBuffer());

        return core::Platform::Get().Run(storage::System::Get().GetRootPath()+"/build.cmd "
            + platform + " " + compiler + " " + mode + " workspace "
            + storage::System::Get().GetPhysicalFilePath(GetAssetPath()),
            storage::System::Get().GetRootPath()+'/');
    }

    //--------------------------------------------------------------------------------------------//

    bool Plugin::GenerateWorkspace()
    {
        basic::String platform, compiler, mode;
        if (!core::Platform::Get().GetBuildTargets(platform, compiler, mode))
            return false;

        basic::String asset_name = GetAssetPath().GetFileNameWithoutExtension();
        basic::String parameters = compiler;

        COFFEE_Log(core::Log::None, "Generate workspace %s", GetAssetPath().GetBuffer());

        if (core::Platform::Get().Run(storage::System::Get().GetRootPath()+"/generate_workspace.cmd "
            + compiler + " plugin " + storage::System::Get().GetPhysicalFilePath(GetAssetPath()).GetPath()
            + " " + GetAssetPath().GetFileName(),
            storage::System::Get().GetRootPath()+'/'))
        {
            basic::String extension = "vcproj";
            if (compiler=="mingw") extension = "cbp";
            else if (compiler=="vs2010") extension = "vcxproj";

            while (!storage::PhysicalSystem::Get().IsFile(
                storage::System::Get().GetPhysicalFilePath(GetAssetPath())+"/workspace/"
                + asset_name + '.' + extension))
            {
                Sleep(10);
            }
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Plugin::LaunchWorkspace()
    {
        basic::String platform, compiler, mode;
        if (!core::Platform::Get().GetBuildTargets(platform, compiler, mode))
            return false;
        basic::String extension = "vcproj";
        if (compiler=="mingw") extension = "cbp";
        else if (compiler=="vs2010") extension = "vcxproj";

        basic::String asset_name = GetAssetPath().GetFileNameWithoutExtension();
        return core::Platform::Get().Launch(storage::System::Get().GetPhysicalFilePath(GetAssetPath())
            +"/workspace/" + asset_name + '.' + extension,
            "", storage::System::Get().GetPhysicalFilePath(GetAssetPath())+"/workspace/");
    }

    //-QUERIES--------------------------------------------------------------------------------//

    basic::String Plugin::_GetExtension() const
    {
        return "plugin";
    }

    //--------------------------------------------------------------------------------------------//

    basic::String Plugin::_GetLibraryPath(const storage::Path& asset_path) const
    {
        basic::String project(storage::System::Get().GetRootPath()+"/internals");
        if (!asset_path.IsPrefixed("/coffee/"))
            project = Application::Get().GetProject().GetFullPath();
        storage::Path folder = Manager::Get().GetResourcePath(GetAssetPath())
            + "/" + asset_path.GetFileNameWithoutExtension() + ".dll";
        return project+folder;                     
    }

    //--------------------------------------------------------------------------------------------//

    storage::PhysicalPath Plugin::_GetBuildLibraryPath(const storage::Path& asset_path) const
    {
        basic::String platform, compiler, mode;
        if (core::Platform::Get().GetBuildTargets(platform, compiler, mode))
        {
            basic::String project(storage::System::Get().GetRootPath()+"/internals");
            if (!asset_path.IsPrefixed("/coffee/"))
                project = Application::Get().GetProject().GetFullPath();
            return project + basic::String(asset_path) + "/binaries/"
                + platform + '-' + compiler + '-' + mode + '/'
                + asset_path.GetFileNameWithoutExtension() + ".dll";           
        }
        return "";
    }

    //--------------------------------------------------------------------------------------------//

    bool Plugin::_ProcessFile(basic::String file, const storage::PhysicalPath& asset_path,
        const storage::PhysicalPath& root)
    {
        storage::PhysicalSystem& system = storage::PhysicalSystem::Get();
        storage::Data* data = system.GetFileData(root+file);
        if (data==NULL)
            return false;
        basic::String asset_name = asset_path.GetFileNameWithoutExtension();
        char end = 0;
        data->Push(&end, 1);
        basic::String content;
        content = data->GetBuffer();
        content.Replace("coffee_replace", asset_name);
        content.Replace("COFFEE_REPLACE", asset_name.ToUpperCase());
        data->Erase();
        data->Push(content.GetBuffer(), content.GetLength());
        bool result = system.SetFileData(asset_path+file, *data);
        COFFEE_Delete(data);
        return result;
    }

}
}
