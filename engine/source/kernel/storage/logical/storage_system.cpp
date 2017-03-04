#include "kernel/storage/logical/storage_system.h"
#include "kernel/storage/logical/local_folder/storage_local_folder.h"
#include "kernel/storage/physical/storage_physical_system.h"

namespace coffee
{
namespace storage
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_ImplementSingleton(System);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    System::System() :
        _RootEntry(NULL),
        _ItIsMounting(false)
    {
        COFFEE_CreateSingleton(System);        
        
        if (PhysicalSystem::Get().IsFolder(PhysicalSystem::Get().GetRootFolder()+"/internals/"))
        {
            _RootPath = PhysicalSystem::Get().GetRootFolder() + "/";
        }
        else
        {
            COFFEE_Assert(PhysicalSystem::Get().IsFolder(
                PhysicalSystem::Get().GetRootFolder()+"/../../internals/"),
                core::ERROR_CODE_StorageSystem, "Invalid folders");

            _RootPath = PhysicalSystem::Get().GetRootFolder() + "/../../";
        }
        
        MountRoot();
    }

    //--------------------------------------------------------------------------------------------//

    System::~System()
    {
        UnMountAll();
        COFFEE_DestroySingleton(System);
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const PhysicalPath& System::GetRootPath() const
    {
        return _RootPath;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool System::HasMountPoint(const Path& logical_path)
    {
        shell::Locker locker(_Mutex);
        for(uint32 mount_index=0 ; mount_index<_MountPointArray.GetSize() ; ++mount_index)
        {
            if(_MountPointArray[mount_index]->GetPath()==logical_path)
                return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool System::HasPath(const Path& path)
    {
        shell::Locker locker(_Mutex);
        return _GetEntry(path)!=NULL;
    }

    //--------------------------------------------------------------------------------------------//

    PhysicalPath System::GetPhysicalFilePath(const Path& logical_file_path)
    {
        shell::Locker locker(_Mutex);
        COFFEE_Assert(logical_file_path.IsFilePath(), core::ERROR_CODE_IncorrectUsage,
            "System::GetPhysicalFilePath requires a file path");
        LogicalFileEntry* entry = static_cast<LogicalFileEntry*>(_GetEntry(logical_file_path));
        if (entry!=NULL)
            return entry->GetMountPoint().GetPhysicalPath(logical_file_path);
        return PhysicalPath();
    }

    //--------------------------------------------------------------------------------------------//

    bool System::GetFileMountPoint(Path& mount_point, const Path& logical_file_path)
    {
        shell::Locker locker(_Mutex);
        COFFEE_Assert(logical_file_path.IsFilePath(), core::ERROR_CODE_IncorrectUsage,
            "System::GetFileMountPoint requires a file path");
        LogicalFileEntry* entry = static_cast<LogicalFileEntry*>(_GetEntry(logical_file_path));
        if (entry!=NULL)
        {
            mount_point = entry->GetMountPoint().GetPath();
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool System::SetFileData(const Path& file_path, const Data& data,
        bool it_has_to_create)
    {
        shell::Locker locker(_Mutex);
        COFFEE_Assert(file_path.IsFilePath(), core::ERROR_CODE_StorageSystem, "Invalid path");
        LogicalFileEntry* file = static_cast<LogicalFileEntry*>(_GetEntry(file_path));
        if (file!=NULL)
            return file->SetData(data);
        if (it_has_to_create)
        {
            file = static_cast<LogicalFileEntry*>(_CreateEntry(file_path));
            if (file!=NULL)
                return file->SetData(data);
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    Data* System::GetFileData(const Path& file_path)
    {
        shell::Locker locker(_Mutex);
        COFFEE_Assert(file_path.IsFilePath(), core::ERROR_CODE_StorageSystem, "Invalid path");
        LogicalFileEntry* file = static_cast<LogicalFileEntry*>(_GetEntry(file_path));
        if (file!=NULL)
            return file->GetData();
        return NULL;
    }

    //--------------------------------------------------------------------------------------------//

    FileAccess* System::GetFileAccess(const Path& file_path)
    {
        shell::Locker locker(_Mutex);
        COFFEE_Assert(file_path.IsFilePath(), core::ERROR_CODE_StorageSystem, "Invalid path");
        LogicalFileEntry* file = static_cast<LogicalFileEntry*>(_GetEntry(file_path));
        if (file!=NULL)
            return file->GetFileAccess();
        return NULL;
    }

    //--------------------------------------------------------------------------------------------//

    basic::Date System::GetFileTimeStamp(const Path& file_path)
    {
        shell::Locker locker(_Mutex);
        COFFEE_Assert(file_path.IsFilePath(), core::ERROR_CODE_StorageSystem, "Invalid path");
        LogicalFileEntry* file = static_cast<LogicalFileEntry*>(_GetEntry(file_path));
        if (file!=NULL)
            return file->GetTimeStamp();
        return basic::Date();
    }

    //--------------------------------------------------------------------------------------------//

    bool System::RemoveFile(const Path& file_path)
    {
        shell::Locker locker(_Mutex);
        COFFEE_Assert(file_path.IsFilePath(), core::ERROR_CODE_StorageSystem, "Invalid path");
        LogicalFileEntry* file = static_cast<LogicalFileEntry*>(_GetEntry(file_path));
        if (file!=NULL)
            return file->RemoveFile();
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool System::RemoveFileAndEmptyFolder(const Path& file_path)
    {
        if (RemoveFile(file_path))
        {
            Path folder = file_path.GetPath();
            LogicalEntry* entry = _GetEntry(folder);
            if (entry!=NULL && entry->GetChildCount()==0)
                RemoveFolder(folder);
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool System::CopyFile(const Path& from_path, const Path& to_path, bool it_replaces)
    {
        shell::Locker locker(_Mutex);
        COFFEE_Assert(from_path.IsFilePath(), core::ERROR_CODE_StorageSystem, "Invalid path");
        COFFEE_Assert(to_path.IsFilePath(), core::ERROR_CODE_StorageSystem, "Invalid path");
        LogicalFileEntry* from_file = static_cast<LogicalFileEntry*>(_GetEntry(from_path));
        if (from_file==NULL)
            return false;
        LogicalFileEntry* to_file = static_cast<LogicalFileEntry*>(_GetEntry(to_path));
        if (!it_replaces && to_file!=NULL)
            return false;
        if (to_file==NULL)
            to_file = static_cast<LogicalFileEntry*>(_CreateEntry(to_path));
        if (to_file!=NULL)
        {
            Data* data = from_file->GetData();
            if (data!=NULL)
            {
                to_file->SetData(*data);
                COFFEE_Delete(data);
                return true;
            }
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool System::MoveFile(const Path& from_path, const Path& to_path, bool it_replaces)
    {
        if (CopyFile(from_path, to_path, it_replaces))
            return RemoveFile(from_path);
        return false;
    }
    
    //--------------------------------------------------------------------------------------------//

    bool System::CreateFolder(const Path& path, bool force_inconsistent)
    {
        COFFEE_Assert(force_inconsistent || !path.IsFilePath(), core::ERROR_CODE_StorageSystem, "Invalid path");
        return _CreateEntry(path, force_inconsistent)!=NULL;
    }

    //--------------------------------------------------------------------------------------------//

    bool System::RemoveFolder(const Path& path)
    {
        shell::Locker locker(_Mutex);
        COFFEE_Assert(!path.IsFilePath(), core::ERROR_CODE_StorageSystem, "Invalid path");
        LogicalEntry* folder = _GetEntry(path);
        if (folder!=NULL && !folder->IsFile())
        {
            uint32 index = _FindMountPoint(path);
            COFFEE_Assert(index!=NONE, core::ERROR_CODE_StorageSystem, "Invalid path");
            return _MountPointArray[index]->RemoveFolder(*folder);
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool System::CopyFolder(const Path& from_path, const Path& to_path, bool it_preserves_files, bool it_replaces)
    {
        shell::Locker locker(_Mutex);
        COFFEE_Assert(!from_path.IsFilePath(), core::ERROR_CODE_StorageSystem, "Invalid path");
        COFFEE_Assert(!to_path.IsFilePath(), core::ERROR_CODE_StorageSystem, "Invalid path");
        LogicalEntry* from_folder = _GetEntry(from_path);
        LogicalEntry* to_folder = _GetEntry(to_path);
        if (from_folder==NULL)
            return false;
        if (!it_replaces && to_folder!=NULL)
            return false;
        if (!it_preserves_files && to_folder!=NULL)
        {
            if (!RemoveFolder(to_path))
                return false;
            to_folder = NULL;
        }
        if (to_folder==NULL)
            to_folder = _CreateEntry(to_path);
        if (to_folder!=NULL)
        {
            bool result = true;
            for (uint32 i=0 ; i<from_folder->GetChildCount() ; ++i)
            {
                if (from_folder->GetChild(i).IsFile())
                {
                    if (!CopyFile(from_folder->GetChild(i).GetPath(),
                        to_path+"/"+from_folder->GetChild(i).GetName(),
                        it_replaces))
                    {
                        result = false;
                    }
                }
                else
                {
                    if (!CopyFolder(from_folder->GetChild(i).GetPath(),
                        to_path+"/"+from_folder->GetChild(i).GetName(),
                        it_replaces))
                    {
                        result = false;
                    }
                }
            }
            return result;
        }
        return false;
    }
        
    //--------------------------------------------------------------------------------------------//

    bool System::MoveFolder(const Path& from_path, const Path& to_path, bool it_preserves_files, bool it_replaces)
    {
        if (CopyFolder(from_path, to_path, it_preserves_files, it_replaces))
            return RemoveFolder(from_path);
        return false;
    }
        
    //--------------------------------------------------------------------------------------------//

    bool System::List(basic::Prow<Path*, true>& pathes, const Path& path, bool it_wants_folders,
            bool it_wants_files, basic::String extension, bool it_is_recursive, bool it_adds)
    {
        shell::Locker locker(_Mutex);
        if (!it_adds) pathes.Erase();
        LogicalEntry* folder = _GetEntry(path);
        if (folder!=NULL && !folder->IsFile())
        {
            _ListFolder(pathes, *folder, it_wants_folders, it_wants_files, extension, it_is_recursive);
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool System::Mount(const basic::String& name, const PhysicalPath& physical_path,
        const Path& logical_path, bool high_priority)
    {
        shell::Locker locker(_Mutex);
        _ItIsMounting = true;
        LogicalEntry* entry = _CreateEntry(logical_path);
        if (entry==NULL)
        {
            _ItIsMounting = false;
            return false;
        }

        if (PhysicalSystem::Get().IsFolder(physical_path))
        {
            LocalFolder* local_folder = COFFEE_New(LocalFolder, name, physical_path, entry);
            _MountPointArray.AddItem(local_folder, high_priority?0:NONE);
            basic::Prow<Path*, true> logical_path_array;
            basic::Prow<PhysicalPath*, true> physical_path_array;
            if (local_folder->RetrievePathArray(logical_path_array)
                || local_folder->RetrievePhysicalPathArray(physical_path_array))
            {
                for (uint32 index=0 ; index<physical_path_array.GetSize() ; ++index)
                {
                    logical_path_array.AddItem(COFFEE_New(Path, 
                        local_folder->GetPath(*physical_path_array[index])));
                }
            
                for (uint32 index=0 ; index<logical_path_array.GetSize() ; ++index)
                    _CreateEntry(*logical_path_array[index]);

                _ItIsMounting = false;
                return true;
            }

            _MountPointArray.RemoveItem(local_folder);
            COFFEE_Delete(local_folder);
        }
        _ItIsMounting = false;
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool System::UnMount(const PhysicalPath& physical_path)
    {
        shell::Locker locker(_Mutex);
        uint32 mount_point_index = _FindMountPoint(physical_path);
        if (mount_point_index != NONE)
        {
            _GetEntry(_MountPointArray[mount_point_index]->GetPath())->Destroy();
            _MountPointArray.Remove(mount_point_index);
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool System::ReMount(PhysicalPath physical_path)
    {
        shell::Locker locker(_Mutex);
        uint32 index = _FindMountPoint(physical_path);
        if (index!=NONE)
        {
            basic::String mount_name(_MountPointArray[index]->GetName());
            Path logical_path(_MountPointArray[index]->GetPath());
            _GetEntry(_MountPointArray[index]->GetPath())->Destroy();
            _MountPointArray.Remove(index);
            return Mount(mount_name, physical_path, logical_path);
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    void System::MountRoot()
    {
        _RootEntry = COFFEE_New(LogicalEntry);
        _RootEntry->SetName(basic::String(""));
        
        if (!Mount("Root", PhysicalSystem::Get().GetRootFolder() + "/", "/root/"))
            COFFEE_Error(core::ERROR_CODE_StorageSystem, "Failed to initialize");
    }

    //--------------------------------------------------------------------------------------------//

    void System::UnMountAll()
    {
        shell::Locker locker(_Mutex);
        _RootEntry->Destroy();
        _RootEntry = NULL;
        _MountPointArray.Clear();
    }

    //--------------------------------------------------------------------------------------------//

    void System::Lock()
    {
        _Mutex.Lock();
    }

    //--------------------------------------------------------------------------------------------//

    void System::Unlock()
    {
        _Mutex.Unlock();
    }

    //-QUERIES------------------------------------------------------------------------------------//

    uint32 System::_FindMountPoint(const PhysicalPath& physical_path) const
    {
        for(uint32 index=0 ; index<_MountPointArray.GetSize() ; ++index)
        {
            if (_MountPointArray[index]->GetPhysicalPath()==physical_path)
                return index;
        }
        return NONE;
    }

    //--------------------------------------------------------------------------------------------//

    uint32 System::_FindMountPoint(const Path& path) const
    {
        Path folder = path.GetPath();
        for (uint32 index=0 ; index<_MountPointArray.GetSize() ; ++index)
        {
            Path path = _MountPointArray[index]->GetPath();
            if (folder.GetLeft(path.GetLength())==path)
                return index;
        }
        return NONE;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    LogicalEntry* System::_CreateEntry(const Path& logical_path, bool force_folder)
    {
        basic::Text hierarchy = logical_path.GetHierarchy();
        uint32 index;
        LogicalEntry* entry = _RootEntry;
        LogicalMountPoint* mount_point = NULL;

        if (hierarchy.GetLineCount()==0)
            return NULL;

        if (hierarchy.GetLine(0)!=_RootEntry->GetName())
            return NULL;

        index = _FindMountPoint(logical_path);
        COFFEE_Assert(_ItIsMounting || index!=NONE, core::ERROR_CODE_StorageSystem, "Invalid path");
        if (index!=NONE)
            mount_point = _MountPointArray[index];
        
        for (index=1 ; index<hierarchy.GetLineCount() ; ++index)
        {
            LogicalEntry* current_entry = entry->FindChild(hierarchy.GetLine(index));
            if (current_entry==NULL)
            {
                if (!PhysicalSystem::Get().IsValidName(hierarchy.GetLine(index)))
                    return NULL;
    
                if (hierarchy.GetLine(index).IsContaining('.'))
                {
                    LogicalFileEntry* file_entry;
                    file_entry = COFFEE_New(LogicalFileEntry);
                    file_entry->SetName(hierarchy.GetLine(index));
                    file_entry->SetMountPoint(*mount_point);
                    entry->Attach(*file_entry);

                    if (!_ItIsMounting)
                    {
                        if (!force_folder) file_entry->CreateFile();
                        else mount_point->CreateFolder(*file_entry);
                    }
                    return file_entry;
                }
                else
                {
                    current_entry = COFFEE_New(LogicalEntry);
                    current_entry->SetName(hierarchy.GetLine(index));
                    entry->Attach(*current_entry);

                    if (!_ItIsMounting)
                        mount_point->CreateFolder(*current_entry);
                }
            }
            entry = current_entry;
        }
        return entry;
    }

    //--------------------------------------------------------------------------------------------//

    LogicalEntry* System::_GetEntry(const Path& logical_path)
    {
        basic::Text hierarchy = logical_path.GetHierarchy();
        uint32 index;
        LogicalEntry* entry = _RootEntry;

        if (entry==NULL)
            return NULL;
        if (hierarchy.GetLineCount()==0)
            return NULL;
        if (hierarchy.GetLine(0)!=_RootEntry->GetName())
            return NULL;

        for (index=1 ; index<hierarchy.GetLineCount() ; ++index)
        {
            if (hierarchy.GetLine(index)=="..")
            {
                if (!entry->HasParent())
                    return NULL;
                entry = &entry->GetParent();
            }
            else
            {
                LogicalEntry* current_entry = entry->FindChild(hierarchy.GetLine(index));
                if (current_entry==NULL)
                    return NULL;
                entry = current_entry;
            }
        }
        if (logical_path.IsFilePath()!=entry->IsFile())
            return NULL;
        return entry;
    }

    //--------------------------------------------------------------------------------------------//

    void System::_ListFolder(basic::Prow<Path*, true>& pathes, LogicalEntry& folder,
        bool it_wants_folders, bool it_wants_files, basic::String extension, bool it_is_recursive)
    {
        for (uint32 index=0 ; index<folder.GetChildCount() ; ++index)
        {
            LogicalEntry& entry = static_cast<LogicalEntry&>(folder.GetChild(index));
            if (entry.IsFile())
            {
                if (it_wants_files && (extension=="*"
                    || entry.GetPath().GetFileExtension()==extension))
                {
                    pathes.AddItem(COFFEE_New(Path, entry.GetPath()));
                }
            }
            else
            {
                if (it_wants_folders)
                    pathes.AddItem(COFFEE_New(Path, entry.GetPath()));
                if (it_is_recursive)
                {
                    _ListFolder(pathes, entry, it_wants_folders, it_wants_files,
                        extension, it_is_recursive);
                }
            }
        }
    }
        
}
}
