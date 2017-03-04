#include "kernel/storage/logical/storage_logical_file_entry.h"

namespace coffee
{
namespace storage
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    LogicalFileEntry::LogicalFileEntry() :
        _MountPoint(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    LogicalFileEntry::~LogicalFileEntry()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void LogicalFileEntry::SetMountPoint(LogicalMountPoint & mount_point)
    {
        _MountPoint = &mount_point;
    }

    //--------------------------------------------------------------------------------------------//

    const LogicalMountPoint & LogicalFileEntry::GetMountPoint() const
    {
        return *_MountPoint;
    }

    //--------------------------------------------------------------------------------------------//

    LogicalMountPoint & LogicalFileEntry::GetMountPoint()
    {
        return *_MountPoint;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool LogicalFileEntry::IsFile() const
    {
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool LogicalFileEntry::IsReadOnly() const
    {
        return GetMountPoint().IsFileReadOnly(*this);
    }

    //--------------------------------------------------------------------------------------------//

	basic::String LogicalFileEntry::GetExtension() const
	{
		return GetPath().GetFileExtension();
	}

    //--------------------------------------------------------------------------------------------//

    basic::Date LogicalFileEntry::GetTimeStamp() const
    {
        return GetMountPoint().GetFileTimeStamp(*this);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool LogicalFileEntry::CreateFile()
    {
        return GetMountPoint().CreateFile(*this);
    }

    //--------------------------------------------------------------------------------------------//

    bool LogicalFileEntry::RemoveFile()
    {
        return GetMountPoint().RemoveFile(*this);
    }

    //--------------------------------------------------------------------------------------------//

    bool LogicalFileEntry::SetData(const Data& data)
    {
        return GetMountPoint().SetFileData(*this, data);
    }

    //--------------------------------------------------------------------------------------------//

    Data* LogicalFileEntry::GetData()
    {
        return GetMountPoint().GetFileData(*this);
    }

    //--------------------------------------------------------------------------------------------//

    FileAccess* LogicalFileEntry::GetFileAccess()
    {
        return GetMountPoint().GetFileAccess(*this);
    }

}
}
