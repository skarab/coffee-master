//------------------------------------------------------------------------------------------------//
/// @file kernel/storage/logical/storage_logical_mount_point.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "kernel/storage/logical/storage_logical_mount_point.h"
#include "kernel/storage/logical/storage_system.h"
#include "kernel/storage/logical/storage_logical_file_entry.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
namespace storage
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    LogicalMountPoint::LogicalMountPoint()
    {
    }

    //--------------------------------------------------------------------------------------------//

    LogicalMountPoint::LogicalMountPoint(const basic::String& name,
        const PhysicalPath& physical_path, LogicalEntry* entry) :
        _Name(name),
        _PhysicalPath(physical_path),
        _LogicalEntry(entry)
    {
    }

    //--------------------------------------------------------------------------------------------//

    LogicalMountPoint::~LogicalMountPoint()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const basic::String& LogicalMountPoint::GetName() const
    {
        return _Name;
    }

    //--------------------------------------------------------------------------------------------//

    const PhysicalPath& LogicalMountPoint::GetPhysicalPath() const
    {
        return _PhysicalPath;
    }

    //--------------------------------------------------------------------------------------------//

    const LogicalEntry& LogicalMountPoint::GetLogicalEntry() const
    {
        return *_LogicalEntry;
    }

    //--------------------------------------------------------------------------------------------//

    LogicalEntry& LogicalMountPoint::GetLogicalEntry()
    {
        return *_LogicalEntry;
    }

    //--------------------------------------------------------------------------------------------//

    Path LogicalMountPoint::GetPath() const
    {
        return _LogicalEntry->GetPath();
    }

    //-QUERIES------------------------------------------------------------------------------------//

    Path LogicalMountPoint::GetPath(const PhysicalPath & physical_path) const
    {
        basic::String path(physical_path);
        if (path.GetLength()>GetPhysicalPath().GetLength()+1)
        {
            path = GetPath()+'/'+path.GetRight(path.GetLength()
                -GetPhysicalPath().GetLength()-1);
            return Path(path);
        }
        return Path();
    }

    //--------------------------------------------------------------------------------------------//

    PhysicalPath LogicalMountPoint::GetPhysicalPath(const Path& logical_path) const
    {
        basic::String path(logical_path);
        if (path.GetLength()>GetPath().GetLength()+1)
        {
            path = GetPhysicalPath()+'/'+path.GetRight(path.GetLength()
                -GetPath().GetLength()-1);
            return PhysicalPath(path);
        }
        return PhysicalPath();
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool LogicalMountPoint::RetrievePathArray(
        basic::Prow< Path *, true > & logical_path_array)
    {
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool LogicalMountPoint::RetrievePhysicalPathArray(
        basic::Prow< PhysicalPath *, true > & physical_path_array)
    {
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool LogicalMountPoint::IsFileReadOnly(const LogicalFileEntry & file_entry) const
    {
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool LogicalMountPoint::CreateFile(LogicalFileEntry & file_entry)
    {
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool LogicalMountPoint::RemoveFile(LogicalFileEntry & file_entry)
    {
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool LogicalMountPoint::SetFileData(LogicalFileEntry& file_entry, const Data& data)
    {
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    Data* LogicalMountPoint::GetFileData(LogicalFileEntry& file_entry)
    {
        return NULL;
    }

    //--------------------------------------------------------------------------------------------//

    FileAccess* LogicalMountPoint::GetFileAccess(LogicalFileEntry& file_entry)
    {
        return NULL;
    }

    //--------------------------------------------------------------------------------------------//

    basic::Date LogicalMountPoint::GetFileTimeStamp(const LogicalFileEntry& file_entry) const
    {
        return basic::Date();
    }

    //--------------------------------------------------------------------------------------------//

    bool LogicalMountPoint::CreateFolder(LogicalEntry & folder_entry)
    {
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool LogicalMountPoint::RemoveFolder(LogicalEntry & folder_entry)
    {
        return false;
    }

}
}
//------------------------------------------------------------------------------------------------//
