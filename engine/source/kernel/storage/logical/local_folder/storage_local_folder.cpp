#include "kernel/storage/logical/local_folder/storage_local_folder.h"
#include "kernel/storage/logical/storage_system.h"

namespace coffee
{
namespace storage
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    LocalFolder::LocalFolder()
    {
    }

    //--------------------------------------------------------------------------------------------//

    LocalFolder::LocalFolder(const basic::String& name, const PhysicalPath& physical_path,
        LogicalEntry* entry) :
        LogicalMountPoint(name, physical_path, entry)
    {
    }
        
    //--------------------------------------------------------------------------------------------//

    LocalFolder::~LocalFolder()
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool LocalFolder::IsFileReadOnly(const LogicalFileEntry& file_entry) const
    {
        return PhysicalSystem::Get().IsReadOnly(GetPhysicalPath(file_entry.GetPath()));
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool LocalFolder::RetrievePhysicalPathArray(
        basic::Prow<PhysicalPath*, true> & physical_path_array)
    {
        return PhysicalSystem::Get().List(
            physical_path_array, GetPhysicalPath(), true, true, "*.*", true);
    }

    //--------------------------------------------------------------------------------------------//

    bool LocalFolder::CreateFile(LogicalFileEntry& file_entry)
    {
        return PhysicalSystem::Get().CreateFile(GetPhysicalPath(file_entry.GetPath()));
    }

    //--------------------------------------------------------------------------------------------//

    bool LocalFolder::RemoveFile(LogicalFileEntry& file_entry)
    {
        if (PhysicalSystem::Get().RemoveFile(GetPhysicalPath(file_entry.GetPath())))
        {
            file_entry.Destroy();
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool LocalFolder::SetFileData(LogicalFileEntry& file_entry, const Data& data)
    {
        return PhysicalSystem::Get().SetFileData(
            GetPhysicalPath(file_entry.GetPath()), data);
    }

    //--------------------------------------------------------------------------------------------//

    Data* LocalFolder::GetFileData(LogicalFileEntry& file_entry)
    {
        return PhysicalSystem::Get().GetFileData(GetPhysicalPath(file_entry.GetPath()));
    }

    //--------------------------------------------------------------------------------------------//

    FileAccess* LocalFolder::GetFileAccess(LogicalFileEntry& file_entry)
    {
        return PhysicalSystem::Get().GetFileAccess(GetPhysicalPath(file_entry.GetPath()));
    }

    //--------------------------------------------------------------------------------------------//

    basic::Date LocalFolder::GetFileTimeStamp(const LogicalFileEntry& file_entry) const
    {
        FileAccess* file = PhysicalSystem::Get().GetFileAccess(GetPhysicalPath(file_entry.GetPath()));
        if (file==NULL)   
            return basic::Date();
        basic::Date date = file->GetLastWriteDate();
        COFFEE_Delete(file);
        return date;
    }
        
    //--------------------------------------------------------------------------------------------//

    bool LocalFolder::CreateFolder(LogicalEntry& folder_entry)
    {
        return PhysicalSystem::Get().CreateFolder(GetPhysicalPath(folder_entry.GetPath()));
    }

    //--------------------------------------------------------------------------------------------//

    bool LocalFolder::RemoveFolder(LogicalEntry& folder_entry)
    {
        if (PhysicalSystem::Get().RemoveFolder(GetPhysicalPath(folder_entry.GetPath())))
        {
            folder_entry.Destroy();
            return true;
        }
        return false;
    }

}
}
