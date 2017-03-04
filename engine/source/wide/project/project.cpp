#include "wide/project/project.h"
#include "wide/ui/window/ui_window_manager.h"
#include "wide/application/application.h"
#include "system/scene/scene_world.h"
#include "coffee.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(Project);
        COFFEE_Attribute(storage::Path, _Path, meta::MODE_Serializeable);
        COFFEE_Attribute(scene::Resource, _StartScene, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(basic::String, _Camera, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(ui::Skin, _Skin, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(<plugins::Object*>, _Plugins, meta::MODE_Serializeable);
    COFFEE_EndType();

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Project::Project() :
        _ItIsInEditorMode(false)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Project::~Project()
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

    storage::PhysicalPath Project::GetFullPath() const
    {
        return storage::System::Get().GetRootPath() + _Path;
    }

    //--------------------------------------------------------------------------------------------//

    bool Project::IsPluginLoaded(const storage::Path& path) const
    {
        return _FindPlugin(path)!=NONE;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Project::Initialize()
    {
        _Skin = resource::Manager::Get().Load(COFFEE_GUI_DefaultSkin);
    }

    //--------------------------------------------------------------------------------------------//

    bool Project::MountBaseFolders()
    {
        storage::System::Get().UnMountAll();
        storage::System::Get().MountRoot();

        if (_ItIsInEditorMode && !storage::System::Get().Mount(basic::String("coffee_assets"),
            storage::System::Get().GetRootPath() + "/internals/assets", storage::Path("/coffee/assets/")))
        {
            return false;
        }

        storage::Path import_path = storage::System::Get().GetRootPath() + "/internals/import";
        
        // In the editor or unittest the import folder may not exist (manual delete or fresh setup/pull)
        if ((Engine::Get().HasMode(RUN_MODE_Editor) || Engine::Get().HasMode(RUN_MODE_UnitTest))
            && !storage::PhysicalSystem::Get().IsFolder(import_path))
        {
            storage::PhysicalSystem::Get().CreateFolder(import_path);
        }

        if (!storage::System::Get().Mount(basic::String("coffee_import"),
            import_path, storage::Path("/coffee/import/")))
        {
            return false;
        }

        if (!storage::System::Get().Mount(basic::String("coffee_resources"),
            storage::System::Get().GetRootPath() + "/internals/resources", storage::Path("/coffee/")))
        {
            return false;
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Project::MountFolders()
    {
        if (!storage::PhysicalSystem::Get().IsFolder(GetFullPath()))
            storage::PhysicalSystem::Get().CreateFolder(GetFullPath());
        
        if (!storage::PhysicalSystem::Get().IsFolder(GetFullPath()+"/resources"))
            storage::PhysicalSystem::Get().CreateFolder(GetFullPath()+"/resources");
        
        if (!storage::PhysicalSystem::Get().IsFolder(GetFullPath()+"/resources/editor"))
            storage::PhysicalSystem::Get().CreateFolder(GetFullPath()+"/resources/editor");
        
        if (!storage::PhysicalSystem::Get().IsFolder(GetFullPath()+"/import"))
            storage::PhysicalSystem::Get().CreateFolder(GetFullPath()+"/import");

        if (!storage::PhysicalSystem::Get().IsFolder(GetFullPath()+"/import/editor"))
            storage::PhysicalSystem::Get().CreateFolder(GetFullPath()+"/import/editor");
            
        if (!storage::PhysicalSystem::Get().IsFolder(GetFullPath()+"/packages"))
            storage::PhysicalSystem::Get().CreateFolder(GetFullPath()+"/packages");

        if (_ItIsInEditorMode)
        {
            if (!storage::PhysicalSystem::Get().IsFolder(GetFullPath()+"/assets"))
                storage::PhysicalSystem::Get().CreateFolder(GetFullPath()+"/assets");
            if (!storage::PhysicalSystem::Get().IsFolder(GetFullPath()+"/assets/editor"))
                storage::PhysicalSystem::Get().CreateFolder(GetFullPath()+"/assets/editor");
        }
        
        if (_ItIsInEditorMode && !storage::System::Get().Mount("assets", GetFullPath()+"/assets", "/assets/"))
            return false;
        
        if (!storage::System::Get().Mount("import", GetFullPath()+"/import", "/import/"))
            return false;

        if (!storage::System::Get().Mount("resources", GetFullPath()+"/resources", "/"))
            return false;
         
        resource::Manager::Get().ReloadInvalidResources();
        
        if (!_ItIsInEditorMode)
            ui::WindowManager::Get().SetSkin(_Skin);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    void Project::LoadPlugin(const storage::Path& path)
    {
        uint32 index = _FindPlugin(path);
        if (index==NONE)
        {
            plugins::Object* plugin = COFFEE_New(plugins::Object);
            *plugin = resource::Manager::Get().Load(path);
            _Plugins.AddItem(plugin);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Project::UnloadPlugin(const storage::Path& path)
    {
        uint32 index = _FindPlugin(path);
        if (index!=NONE)
            _Plugins.Remove(index);
    }

    //--------------------------------------------------------------------------------------------//

    void Project::Update(const basic::Time& time_step)
    {
        for (uint32 index=0 ; index<_Plugins.GetSize() ; ++index)
        {
            if (_Plugins[index]->IsReady())
                _Plugins[index]->GrabLibrary().Update(time_step);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Project::PushEditorPlugins()
    {
        for (int32 index=0 ; index<(int32)_Plugins.GetSize() ; ++index)
        {
            if (_Plugins[index]->GetFilePath().GetFileExtension()=="editor")
            {
                _EditorPlugins.AddItem(_Plugins[index]);
                _Plugins[index] = NULL;
                _Plugins.Remove(index--);
            }
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Project::PopEditorPlugins()
    {
        for (uint32 index=0 ; index<_EditorPlugins.GetSize() ; ++index)
            _Plugins.AddItem(_EditorPlugins[index]);
        _EditorPlugins.Erase();
    }

    //-QUERIES------------------------------------------------------------------------------------//

    uint32 Project::_FindPlugin(const storage::Path& path) const
    {
        for (uint32 index=0 ; index<_Plugins.GetSize() ; ++index)
        {
            if (_Plugins[index]->GetFilePath()==path)
                return index;
        }
        return NONE;
    }
        
}
