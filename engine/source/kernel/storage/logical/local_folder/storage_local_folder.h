#ifndef _COFFEE_STORAGE_LOCAL_FOLDER_H_
#define _COFFEE_STORAGE_LOCAL_FOLDER_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "kernel/meta/meta.h"
#include "kernel/storage/logical/storage_logical_mount_point.h"
#include "kernel/storage/physical/storage_physical_system.h"

namespace coffee
{
namespace storage
{
    //--------------------------------------------------------------------------------------------//
    /// Physical local folder mount point
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API LocalFolder : public LogicalMountPoint
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        LocalFolder();
        LocalFolder(const basic::String& name, const PhysicalPath& physical_path,
            LogicalEntry* entry);
        ~LocalFolder();

        //-QUERIES--------------------------------------------------------------------------------//

        bool IsFileReadOnly(const LogicalFileEntry& file_entry) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool RetrievePhysicalPathArray(
            basic::Prow<PhysicalPath*, true> & physical_path_array);
        bool CreateFile(LogicalFileEntry& file_entry);
        bool RemoveFile(LogicalFileEntry& file_entry);
        bool SetFileData(LogicalFileEntry& file_entry, const Data& data);
        Data* GetFileData(LogicalFileEntry& file_entry);
        FileAccess* GetFileAccess(LogicalFileEntry& file_entry);
        basic::Date GetFileTimeStamp(const LogicalFileEntry& file_entry) const;
        bool CreateFolder(LogicalEntry& folder_entry);
        bool RemoveFolder(LogicalEntry& folder_entry);
    };
}
}
#endif
