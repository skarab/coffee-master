#ifndef _COFFEE_STORAGE_LOGICAL_MOUNT_POINT_H_
#define _COFFEE_STORAGE_LOGICAL_MOUNT_POINT_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "kernel/meta/meta.h"
#include "kernel/storage/logical/storage_logical_entry.h"
#include "kernel/storage/physical/storage_physical_path.h"
#include "kernel/storage/file/storage_file_access.h"

namespace coffee
{
namespace storage
{
    class LogicalFileEntry;

    //--------------------------------------------------------------------------------------------//
    /// Logical mount point
    ///
    /// @see coffee::storage::System
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API LogicalMountPoint
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        LogicalMountPoint();
        LogicalMountPoint(const basic::String& name, const PhysicalPath& physical_path,
            LogicalEntry* entry);
        virtual ~LogicalMountPoint();

        //-ACCESSORS------------------------------------------------------------------------------//

        const basic::String& GetName() const;
        const PhysicalPath& GetPhysicalPath() const;
        const LogicalEntry& GetLogicalEntry() const;
        LogicalEntry& GetLogicalEntry();
        Path GetPath() const;

        //-QUERIES--------------------------------------------------------------------------------//

        virtual Path GetPath(const PhysicalPath& physical_path) const;
        virtual PhysicalPath GetPhysicalPath(const Path& logical_path) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual bool RetrievePathArray(
            basic::Prow<Path*, true> & logical_path_array);
        virtual bool RetrievePhysicalPathArray(
            basic::Prow<PhysicalPath*, true> & physical_path_array);
        virtual bool IsFileReadOnly(const LogicalFileEntry& file_entry) const;
        virtual bool CreateFile(LogicalFileEntry& file_entry);
        virtual bool RemoveFile(LogicalFileEntry& file_entry);
        virtual bool SetFileData(LogicalFileEntry& file_entry, const Data& data);
        virtual Data* GetFileData(LogicalFileEntry& file_entry);
        virtual FileAccess* GetFileAccess(LogicalFileEntry& file_entry);
        virtual basic::Date GetFileTimeStamp(const LogicalFileEntry& file_entry) const;
        virtual bool CreateFolder(LogicalEntry& folder_entry);
        virtual bool RemoveFolder(LogicalEntry& folder_entry);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::String _Name;
        PhysicalPath _PhysicalPath;
        LogicalEntry* _LogicalEntry;
    };
}
}
#endif
