#include "asset/asset_importer.h"
#include "asset/asset_manager.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(asset::Importer);
        COFFEE_Attribute(coffee_editor::asset::MODE, _SynchronizationMode, meta::MODE_Serializeable | meta::MODE_Editable);        
        COFFEE_Attribute(storage::Path, _AssetPath, meta::MODE_Serializeable);
        COFFEE_Attribute(<storage::Path>, _ResourcePathes, meta::MODE_Serializeable);
    COFFEE_EndType();

namespace asset
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Importer::Importer() :
        _SynchronizationMode(MODE_Automatic),
        _Progress(0.0f)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Importer::~Importer()
    {
    }
	
    //-OPERATIONS---------------------------------------------------------------------------------//

    void Importer::Synchronize(const storage::Path& import_path, const storage::Path& asset_path, uint32 flags)
    {
        bool exist = storage::System::Get().HasPath(import_path);
        if (!exist)
            storage::System::Get().SetFileData(import_path, storage::Data(), true);
        
        SetAssetPath(asset_path);
        Serialize(import_path, exist?storage::MODE_Input:storage::MODE_Output);
        SetAssetPath(asset_path);
        
        if (GetSynchronizationMode()==MODE_Automatic)
            Manager::Get().Import(*this);
    }

    //--------------------------------------------------------------------------------------------//

    void Importer::SaveImportedResources()
    {
        for (uint32 i=0 ; i<_Resources.GetSize() ; ++i)
            resource::Manager::Get().Save(*_Resources[i]);
        OnPostSaveResources();
    }

    //--------------------------------------------------------------------------------------------//

    bool Importer::Delete()
    {
        bool result = Move();

        if (!storage::System::Get().RemoveFile(_AssetPath)
            || !storage::System::Get().RemoveFile(_AssetPath+".import"))
        {
            result = false;
        }
        return result;
    }

    //--------------------------------------------------------------------------------------------//

    bool Importer::Move()
    {
        bool result = true;
        for (uint32 i=0 ; i<_ResourcePathes.GetSize() ; ++i)
        {
            if (!storage::System::Get().RemoveFileAndEmptyFolder(_ResourcePathes[i]))
                result = false;
            storage::System::Get().RemoveFileAndEmptyFolder(Manager::Get().GetThumbnailPath(_ResourcePathes[i]));
        }
        storage::System::Get().RemoveFileAndEmptyFolder(Manager::Get().GetThumbnailPath(_AssetPath+".import"));
        return result;
    }

    //--------------------------------------------------------------------------------------------//

    bool Importer::BreakDependencies()
    {
        bool result = true;
        for (uint32 i=0 ; i<_ResourcePathes.GetSize() ; ++i)
        {
            storage::Path path(_ResourcePathes[i]);
            if (path.IsPrefixed("/coffee"))
            {
                path.CutLeft(strlen("/coffee/assets"));
                path = basic::String("/coffee")+path;
            }
            else
            {
                path.CutLeft(strlen("/assets"));
            }

            if (!storage::System::Get().MoveFile(_ResourcePathes[i], path, true))
                result = false;

            storage::System::Get().MoveFile(
                Manager::Get().GetThumbnailPath(_ResourcePathes[i]),
                Manager::Get().GetThumbnailPath(path), true);
        }
        
        if (!storage::System::Get().RemoveFile(_AssetPath)
            || !storage::System::Get().RemoveFile(_AssetPath+".import")
            || !storage::System::Get().RemoveFile(Manager::Get().GetStampPath(_AssetPath)))
        {
            result = false;
        }
        storage::System::Get().RemoveFile(Manager::Get().GetThumbnailPath(_AssetPath+".import"));
        return result;
    }

    //--------------------------------------------------------------------------------------------//

    void Importer::DeleteImportedResources()
    {
        // TODO: maybe delete files as well
        _ResourcePathes.Erase();
        _Resources.Erase();
    }

    //--------------------------------------------------------------------------------------------//

    void Importer::AddImportedResource(resource::Chunk* resource_chunk)
    {
        _ResourcePathes.AddItem(resource_chunk->GetFilePath());
        _Resources.AddItem(resource_chunk);
    }

    //--------------------------------------------------------------------------------------------//

    void Importer::AddThumbnail(resource::Chunk* resource_chunk)
    {
        _Resources.AddItem(resource_chunk);
    }

}
}
