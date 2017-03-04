#include "asset/asset_manager.h"
#include "coffee_editor.h"
#include "asset/font/asset_font_fnt.h"
#include "asset/font/asset_font_ttf.h"
#include "asset/texture/asset_texture.h"
#include "asset/texture/asset_texture_png.h"
#include "asset/texture/asset_texture_ies.h"
#include "asset/texture/asset_texture_hdr.h"
#include "asset/shader/asset_shader_glsl.h"
#include "asset/mesh/asset_mesh_obj.h"
#include "asset/plugin/asset_plugin.h"
#include "asset/plugin/asset_plugin_editor.h"
#include "asset/point_cloud/asset_point_cloud_ply.h"
#include "asset/component/asset_component.h"
#include "asset/sound/asset_sound_wav.h"
#include "asset/sound/asset_sound_ogg.h"

#define COFFEE_ASSET_MANAGER_RefreshRate   1.0f

namespace coffee_editor
{
namespace asset
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_ImplementSingleton(Manager);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Manager::Manager() :
        _Importer(NULL),
        _ItHasFinishedImport(false)
    {
        COFFEE_CreateSingleton(System);

        Register<FontFNT>();
        Register<FontTTF>();
        Register<ShaderGLSL>();
        Register<Texture>();
        Register<TexturePNG>();
        Register<TextureIES>();
        Register<TextureHDR>();
        Register<MeshOBJ>();
        Register<Plugin>();
        Register<PluginEditor>();
        Register<PointCloudPLY>();
        Register<Component>();
        Register<SoundWAV>();
        Register<SoundOGG>();

        _ImportThread.Start(*this, &ThreadedUpdate);
        _ImportThread.SetName("asset::Manager");
    }
    
    //--------------------------------------------------------------------------------------------//

    Manager::~Manager()
    {
        _ImportThread.Stop(true);
        COFFEE_DestroySingleton(System);
    }

    //-QUERIES------------------------------------------------------------------------------------//

    storage::Path Manager::GetAssetPath(const storage::Path& import_path) const
    {
        storage::Path import_root_path;
        COFFEE_Assert(storage::System::Get().GetFileMountPoint(import_root_path, import_path),
            core::ERROR_CODE_StorageSystem, "GetAssetPath called on unexisting import file");
        storage::Path asset_path = import_root_path
            + import_path.GetRight(import_path.GetLength()-import_root_path.GetLength());
        asset_path.CutRight(strlen(".import"));
        return asset_path;
    }
        
    //--------------------------------------------------------------------------------------------//

    storage::Path Manager::GetImportPath(const storage::Path& asset_path) const
    {
        storage::Path asset_root_path;
        COFFEE_Assert(storage::System::Get().GetFileMountPoint(asset_root_path, asset_path),
            core::ERROR_CODE_StorageSystem, "GetImportPath called on unexisting asset");
        storage::Path import_path = asset_root_path
            + asset_path.GetRight(asset_path.GetLength()-asset_root_path.GetLength());
        import_path += ".import";
        return import_path;
    }

    //--------------------------------------------------------------------------------------------//

    storage::Path Manager::GetStampPath(const storage::Path& asset_path) const
    {
        storage::Path asset_root_path;
        COFFEE_Assert(storage::System::Get().GetFileMountPoint(asset_root_path, asset_path),
            core::ERROR_CODE_StorageSystem, "GetStampPath called on unexisting asset");
        storage::Path stamp_path = (asset_root_path-strlen("/assets")) + "/import"
            + asset_path.GetRight(asset_path.GetLength()-asset_root_path.GetLength());
        stamp_path += ".stamp";
        return stamp_path;
    }

    //--------------------------------------------------------------------------------------------//

    storage::Path Manager::GetResourcePath(const storage::Path& asset_path) const
    {
        storage::Path asset_root_path;
        COFFEE_Assert(storage::System::Get().GetFileMountPoint(asset_root_path, asset_path),
            core::ERROR_CODE_StorageSystem, "GetResourcePath called on unexisting asset");
        storage::Path data_path = (asset_root_path-strlen("/assets")) + "/import"
            + asset_path.GetRight(asset_path.GetLength()-asset_root_path.GetLength());
        return data_path.GetPath();
    }

    //--------------------------------------------------------------------------------------------//

    storage::Path Manager::GetThumbnailPath(const storage::Path& path) const
    {
        storage::Path thumb_path;
        if (path.IsFilePath())
            thumb_path = _GetThumbnailPath(path);
        return thumb_path;
    }
        
    //--------------------------------------------------------------------------------------------//

    graphics::Texture Manager::GetThumbnail(const storage::Path& path) const
    {
        storage::Path thumb_path;
        if (path.IsFilePath())
        {
            thumb_path = _GetThumbnailPath(path);
            if (!storage::System::Get().HasPath(thumb_path))
            {
                basic::String ext = path.GetFileExtension();
                if (path.IsSuffixed(".component.import")
                    || path.IsSuffixed(".plugin.import")
                    || path.IsSuffixed(".editor.import"))
                {
                    thumb_path = storage::Path("/coffee/import/editor/icons/file_script.texture");
                }
                else if (ext=="import") thumb_path = storage::Path("/coffee/import/editor/icons/file_asset.texture");
                else if (ext=="scene") thumb_path = storage::Path("/coffee/import/editor/icons/file_scene.texture");
                else if (ext=="graph") thumb_path = storage::Path("/coffee/import/editor/icons/file_graph.texture");
                else thumb_path = storage::Path("/coffee/import/editor/icons/file.texture");
            }
        }
        else
        {
            if (path=="/coffee") thumb_path = storage::Path("/coffee/import/editor/icons/folder_coffee.texture");
            else if (path=="/coffee/assets") thumb_path = storage::Path("/coffee/import/editor/icons/folder_asset.texture");
            else if (path=="/coffee/editor") thumb_path = storage::Path("/coffee/import/editor/icons/folder_editor.texture");
            else if (path=="/assets") thumb_path = storage::Path("/coffee/import/editor/icons/folder_asset.texture");
            else if (path=="/editor") thumb_path = storage::Path("/coffee/import/editor/icons/folder_editor.texture");
            else thumb_path = storage::Path("/coffee/import/editor/icons/folder.texture");
        }
        return resource::Manager::Get().Load(thumb_path);
    }

    //--------------------------------------------------------------------------------------------//

    bool Manager::IsAssetSupported(const storage::PhysicalPath& path) const
    {
        return _FindImporterType(path.GetFileExtension())!=NULL;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//
 
    void Manager::Update(const basic::Time& time_step)
	{
        if (_ImportQueue.GetSize()>0 && _Importer==NULL)
        {
            storage::Path path = _ImportQueue[0];
            _ImportQueue.Remove(0);

            if (path=="/reload_resource")
            {
                resource::Manager::Get().ReloadResources();
                if (widget::Explorer::IsInstantiated())
	                widget::Explorer::Get().UpdateContent();
            }
            else if (path=="/reload_invalid_resource")
            {
                resource::Manager::Get().ReloadInvalidResources();
                if (widget::Explorer::IsInstantiated())
	                widget::Explorer::Get().UpdateContent();
            }
            else if (path=="/refresh_properties")
            {
                if (widget::Properties::IsInstantiated() && widget::Properties::Get().GetObjectPath().GetLength()>1)
                    widget::Properties::Get().Edit(widget::Properties::Get().GetObjectPath());
            }
            else
            {
                if (widget::Properties::IsInstantiated() && widget::Properties::Get().GetObjectPath()==path)
                    _ImportQueue.AddItem("/refresh_properties");
                
                shell::Locker lock(_ImporterMutex);
                _ItHasFinishedImport = false;
                _Importer = LoadImporter(path);
                COFFEE_Assert(_Importer!=NULL, core::ERROR_CODE_Unexpected, "Unexpected error");
            }
        }
        else if (_Importer!=NULL)
        {
            shell::Locker lock(_ImporterMutex);
            if (_Importer!=NULL)
            {
                coffee_editor::Application::Get().GetEditorFrame().SetProgress(
                    basic::String("importing ")+_Importer->GetAssetPath(),
                    _Importer->GetProgress());
            
                if (_ItHasFinishedImport)
                {
                    _Importer->SaveImportedResources();
                    _Importer->Serialize(_Importer->GetImportPath(), storage::MODE_Output);
                    storage::System::Get().SetFileData(GetStampPath(_Importer->GetAssetPath()), storage::Data(), true);
                    COFFEE_Delete(_Importer);
                    _Importer = NULL;
                }
            }
        }
        else
        {
            coffee_editor::Application::Get().GetEditorFrame().SetProgress(
                basic::String("ready"), 0.0f);
            coffee_editor::Application::Get().GetEditorFrame().SetSubProgress(0.0f);

            _SynchronizationTime += time_step;

            if (coffee_editor::Application::IsInstantiated() && !coffee_editor::Application::Get().HasFocus()
                && _SynchronizationTime.GetSecondCount()>COFFEE_ASSET_MANAGER_RefreshRate)
            {
		        Synchronize();
                _SynchronizationTime = 0.0f;
            }
        }
	}

    //--------------------------------------------------------------------------------------------//

    void Manager::Synchronize(uint32 flags)
    {
        bool it_has_to_sync_project = storage::System::Get().HasMountPoint("/assets");
        Application& editor = coffee_editor::Application::Get();
	        
        if (!editor.GetProject().MountBaseFolders())
            COFFEE_Error(core::ERROR_CODE_StorageSystem, "Failed to mount coffee root folders");

        _Synchronize("/coffee", flags);
        
        if (it_has_to_sync_project)
        {
            storage::System::Get().Mount("assets", editor.GetProject().GetFullPath()+"/assets", "/assets/");
            storage::System::Get().Mount("import", editor.GetProject().GetFullPath()+"/import", "/import/");
            storage::System::Get().Mount("resources", editor.GetProject().GetFullPath()+"/resources", "/");
            _Synchronize("/", flags);
        }

        if (COFFEE_IsFlagEnabled(flags, SYNC_FLAG_ForceAll)) _ImportQueue.AddItem("reload_resource");
        else _ImportQueue.AddItem("reload_invalid_resource");

        if (COFFEE_IsFlagEnabled(flags, SYNC_FLAG_Immediate))
        {
            basic::Time time;
            while(!_ImportQueue.IsEmpty())
                Update(time);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Manager::Import(Importer& importer)
    {
        importer.Serialize(importer.GetImportPath(), storage::MODE_Output);
        _ImportQueue.AddItem(importer.GetImportPath());
    }

    //--------------------------------------------------------------------------------------------//

    Importer* Manager::LoadImporter(const storage::Path& path) const
    {
        storage::Path asset_path = path - basic::String(".import").GetLength();
        meta::Class* importer_type = _FindImporterType(asset_path.GetFileExtension());
        if (!storage::System::Get().HasPath(path) || importer_type==NULL)
            return NULL;
        Importer* importer = static_cast<Importer*>(importer_type->CreateObject());
        importer->Serialize(path, storage::MODE_Input);
        importer->SetAssetPath(asset_path);
        return importer;
    }

    //--------------------------------------------------------------------------------------------//

    bool Manager::CreateAsset(const storage::Path& asset_path)
    {
        meta::Class* importer_type = _FindImporterType(asset_path.GetFileExtension());
        if (importer_type!=NULL)
        {
            Importer* importer = static_cast<Importer*>(importer_type->CreateObject());
            
            storage::Path asset(asset_path);
            storage::PhysicalPath path;
            basic::String project(Application::Get().GetProject().GetFullPath());
            if (asset.IsPrefixed("/coffee"))
            {
                asset.CutLeft(strlen("/coffee"));        
                project = storage::System::Get().GetRootPath()+"/internals";
            }

            if (asset.IsPrefixed("/resources/"))
                path = project + "/assets/" + (asset.GetBuffer()+strlen("/resources/"));
            else if (asset.IsPrefixed("/import/"))
                path = project + "/assets/" + (asset.GetBuffer()+strlen("/import/"));
            else if (asset.IsPrefixed("/assets/"))
                path = project + asset;
            else path = project + "/assets" + asset;
            
            if (storage::PhysicalSystem::Get().IsFolder(path)
                || storage::PhysicalSystem::Get().IsFile(path))
            {
                ui::DoMessageBox("Asset already exists !", "An asset is already using this name.");
                return false;
            }

            bool result = importer->Create(path, asset_path); 
            COFFEE_Delete(importer);

            if (result)
                Synchronize();
            return result;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Manager::Delete(const storage::Path& path)
    {
        shell::Locker lock(_ImporterMutex);
        Importer* importer = LoadImporter(path);
        if (importer!=NULL)
        {
            bool result = importer->Delete();
            COFFEE_Delete(importer);
            return result;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Manager::Move(const storage::Path& path)
    {
        shell::Locker lock(_ImporterMutex);
        Importer* importer = LoadImporter(path);
        if (importer!=NULL)
        {
            bool result = importer->Move();
            COFFEE_Delete(importer);
            return result;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Manager::BreakDependencies(const storage::Path& path)
    {
        shell::Locker lock(_ImporterMutex);
        Importer* importer = LoadImporter(path);
        if (importer!=NULL)
        {
            bool result = importer->BreakDependencies();
            COFFEE_Delete(importer);
            return result;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    void Manager::ReImport(const storage::Path& path)
    {
        shell::Locker lock(_ImporterMutex);
        Importer* importer = LoadImporter(path);
        if (importer!=NULL)
        {
            Import(*importer);
            COFFEE_Delete(importer);
        }
    }
     
    //--------------------------------------------------------------------------------------------//

    void Manager::ActivateAsset(const storage::Path& path)
    {
        shell::Locker lock(_ImporterMutex);
        Importer* importer = LoadImporter(path);
        if (importer!=NULL)
        {
            if (importer->IsKindOf<Plugin>())
            {
                Plugin* plugin = static_cast<Plugin*>(importer);
                if (plugin->GenerateWorkspace())
                    plugin->LaunchWorkspace();                
            }
            Import(*importer);
            COFFEE_Delete(importer);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Manager::OnImport(const storage::Path& output_path)
    {
        basic::String path;
        basic::Text extensions;
        extensions.AddLine("All"); extensions.AddLine("*.*");
        
        if (core::Platform::Get().AskForFile(path, extensions))
            OnImport(path, output_path);
    }

    //--------------------------------------------------------------------------------------------//

    void Manager::OnImport(const storage::PhysicalPath& path, const storage::Path& output_path)
    {
        if (_FindImporterType(path.GetFileExtension())!=NULL)
        {
            storage::PhysicalPath import_path = Application::Get().GetProject().GetFullPath()
                +output_path+"/"+path.GetFileName();
            if (storage::PhysicalSystem::Get().CopyFile(path, import_path, true))
                Synchronize();
        }
    }
    
    //--------------------------------------------------------------------------------------------//

    resource::Chunk* Manager::GenerateThumbnail(const storage::Path& path, const basic::Image& source)
    {
        if (source.IsEmpty())
            return NULL;

        storage::Path thumbnail_path = _GetThumbnailPath(path);
        basic::Image* thumbnail;
        thumbnail = COFFEE_New(basic::Image);
        thumbnail->Create(16, 16, 1, meta::SCALAR_FORMAT_UInt8, 4, source.IsBGR());
        
        const uint8* input8 = (const uint8 *)source.GetData();
        const uint16* input16 = (const uint16 *)source.GetData();
        const real* inputR = (const real *)source.GetData();
        uint8* output = (uint8 *)thumbnail->GetData();

        for (uint32 y=0 ; y<thumbnail->GetHeight() ; ++y)
        {
            uint32 sy = y*(source.GetHeight()-1)/(thumbnail->GetHeight()-1);

            for (uint32 x=0 ; x<thumbnail->GetWidth() ; ++x)
            {
                uint8 r, g, b, a(255);
                uint32 sx = x*(source.GetWidth()-1)/(thumbnail->GetWidth()-1);

                if (source.GetComponentType()==meta::SCALAR_FORMAT_UInt8)
                {
                    g = b = r = input8[(sy*source.GetWidth()+sx)*source.GetComponentCount()];
                    if (source.GetComponentCount()>1)
                        g = input8[(sy*source.GetWidth()+sx)*source.GetComponentCount()+1];
                    if (source.GetComponentCount()>2)
                        b = input8[(sy*source.GetWidth()+sx)*source.GetComponentCount()+2];
                }
                else if (source.GetComponentType()==meta::SCALAR_FORMAT_UInt16)
                {
                    g = b = r = (uint8)(((uint32)input16[(sy*source.GetWidth()+sx)*source.GetComponentCount()])*255/65535);
                    if (source.GetComponentCount()>1)
                        g = (uint8)(((uint32)input16[(sy*source.GetWidth()+sx)*source.GetComponentCount()+1])*255/65535);
                    if (source.GetComponentCount()>2)
                        b = (uint8)(((uint32)input16[(sy*source.GetWidth()+sx)*source.GetComponentCount()+2])*255/65535);
                }
                else if (source.GetComponentType()==meta::SCALAR_FORMAT_Real)
                {
                    g = b = r = (uint8)(inputR[(sy*source.GetWidth()+sx)*source.GetComponentCount()]/255.0f);
                    if (source.GetComponentCount()>1)
                        g = (uint8)(inputR[(sy*source.GetWidth()+sx)*source.GetComponentCount()+1]/255.0f);
                    if (source.GetComponentCount()>2)
                        b = (uint8)(inputR[(sy*source.GetWidth()+sx)*source.GetComponentCount()+2]/255.0f);
                }

                if (source.GetComponentCount()>3)
                {
                    if (source.GetComponentType()==meta::SCALAR_FORMAT_UInt8)
                        a = input8[(sy*source.GetWidth()+sx)*source.GetComponentCount()+3];
                    else if (source.GetComponentType()==meta::SCALAR_FORMAT_UInt16)
                        a = (uint8)(((uint32)input16[(sy*source.GetWidth()+sx)*source.GetComponentCount()+3])*255/65535);
                    else if (source.GetComponentType()==meta::SCALAR_FORMAT_Real)
                        a = (uint8)(inputR[(sy*source.GetWidth()+sx)*source.GetComponentCount()+3]/255.0f);
                    
                    real mask = (255.0f-a)*((x+y)%2)/2.0f;
                    r = (uint8)((r/255.0f)*a+mask*0.31f);
                    g = (uint8)((g/255.0f)*a+mask*0.53f);
                    b = (uint8)((b/255.0f)*a+mask*0.51f);
                    a = 255;
                }

                output[(y*thumbnail->GetWidth()+x)*4+0] = r;
                output[(y*thumbnail->GetWidth()+x)*4+1] = g;
                output[(y*thumbnail->GetWidth()+x)*4+2] = b;
                output[(y*thumbnail->GetWidth()+x)*4+3] = a;
            }
        }
 
        graphics::Texture2D* texture;
        texture = COFFEE_New(graphics::Texture2D);
        texture->SetImage(*thumbnail);
        texture->Initialize();
        texture->PreCreateLOD(0);
        resource::Chunk* resource_chunk;
        resource_chunk = resource::Manager::Get().Create(thumbnail_path);
        resource_chunk->AddLOD(*texture);
        return resource_chunk;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    meta::Class* Manager::_FindImporterType(const basic::String& file_extension) const
    {
        for (uint32 index=0 ; index<_Importers.GetSize() ; ++index)
        {
            if (_Importers[index]->_IsSupporting(file_extension))
                return _Importers[index]->_MetaType;
        }
        return NULL;
    }
    
    //--------------------------------------------------------------------------------------------//

    storage::Path Manager::_GetThumbnailPath(const storage::Path& path) const
    {
        if (path.IsPrefixed("/coffee"))
        {
            return basic::String("/coffee/editor/thumbnails/")
                + path.GetRight(path.GetLength()-strlen("/coffee/"))
                + ".texture";
        }        
        return basic::String("/editor/thumbnails/") + path + ".texture";
    }

    //-OPERATIONS---------------------------------------------------------------------------------//
    
	void Manager::_Synchronize(storage::Path root_path, uint32 flags)
	{
        COFFEE_Assert(storage::System::Get().HasPath(root_path+"/assets"),
            core::ERROR_CODE_StorageSystem, "Failed to synchronize assets");
		_SynchronizeFolder(root_path+"/assets", flags);
    }

	//--------------------------------------------------------------------------------------------//

	void Manager::_SynchronizeFolder(const storage::Path& folder, uint32 flags)
	{
        basic::Prow<storage::Path*, true> pathes;
        storage::System::Get().List(pathes, folder);
		for (uint32 entry_index=0 ; entry_index<pathes.GetSize() ; ++entry_index)
		{
			if (pathes[entry_index]->IsFilePath())
			{
				_SynchronizeAsset(*pathes[entry_index], flags);
			}
            else
			{
				_SynchronizeFolder(*pathes[entry_index], flags);
			}
		}
	}

	//--------------------------------------------------------------------------------------------//

	void Manager::_SynchronizeAsset(const storage::Path& asset_path, uint32 flags)
	{
        meta::Class* importer_type = _FindImporterType(asset_path.GetFileExtension());
        if (importer_type!=NULL)
		{
            bool force_script = COFFEE_IsFlagEnabled(flags, SYNC_FLAG_CheckScripts)
                && (asset_path.GetFileExtension()=="component"
                || asset_path.GetFileExtension()=="plugin"
                || asset_path.GetFileExtension()=="editor");

            storage::Path import_path = GetImportPath(asset_path);
            storage::Path stamp_path = GetStampPath(asset_path);

            // Reimport asset if:
            // . its a forced reimport
            // . import doesn't exist
            // . stamp doesn't exist
            // . asset is newer
            // . stamp is outdated
            basic::Date asset_time;
            asset_time = storage::System::Get().GetFileTimeStamp(asset_path);
            bool it_has_import_file = storage::System::Get().HasPath(import_path);
            basic::Date import_time;
            if (it_has_import_file)
                import_time = storage::System::Get().GetFileTimeStamp(import_path);
            bool it_has_stamp_file = storage::System::Get().HasPath(stamp_path);
            basic::Date stamp_time;
            if (it_has_stamp_file)
                stamp_time = storage::System::Get().GetFileTimeStamp(stamp_path);

            if (force_script || COFFEE_IsFlagEnabled(flags, SYNC_FLAG_ForceAll)
                || !it_has_import_file || !it_has_stamp_file
                || import_time<asset_time || stamp_time<asset_time
                || stamp_time<import_time)
            {
                Importer* importer = static_cast<Importer*>(importer_type->CreateObject());
                importer->Synchronize(import_path, asset_path, flags);
                COFFEE_Delete(importer);
            }
        }
	}

    //-FUNCTIONS----------------------------------------------------------------------------------//

    void Manager::ThreadedUpdate(meta::Object* object)
    {
        Manager* manager = static_cast<Manager*>(object);
        Importer* importer(NULL);
        {
            shell::Locker lock(manager->_ImporterMutex);
            if (!manager->_ItHasFinishedImport)
                importer = manager->_Importer;
        }

        if (importer!=NULL)
        {
            COFFEE_Log(core::Log::None, "Import %s", importer->GetAssetPath().GetBuffer());

            if (importer->Import())
            {
                manager->_ItHasFinishedImport = true;
            }
            else
            {
                COFFEE_Log(core::Log::Error, "Failed to import %s", importer->GetAssetPath().GetBuffer());

                shell::Locker lock(manager->_ImporterMutex);
                COFFEE_Delete(manager->_Importer);
                manager->_Importer = NULL;
            }
        }
    }

}
}
