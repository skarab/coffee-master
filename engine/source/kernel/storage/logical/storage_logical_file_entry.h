#ifndef _COFFEE_STORAGE_LOGICAL_FILE_ENTRY_H_
#define _COFFEE_STORAGE_LOGICAL_FILE_ENTRY_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "kernel/basic/alpha/basic_alpha.h"
#include "kernel/storage/logical/storage_logical_entry.h"
#include "kernel/storage/logical/storage_logical_mount_point.h"
#include "kernel/storage/file/storage_file_access.h"

namespace coffee
{
namespace storage
{
    //--------------------------------------------------------------------------------------------//
    /// Logical file entry
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API LogicalFileEntry : public LogicalEntry
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        LogicalFileEntry();
        virtual ~LogicalFileEntry();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetMountPoint(LogicalMountPoint& mount_point);
        const LogicalMountPoint& GetMountPoint() const;
        LogicalMountPoint& GetMountPoint();

        //-QUERIES--------------------------------------------------------------------------------//

        bool IsFile() const;
        bool IsReadOnly() const;
		basic::String GetExtension() const;
        basic::Date GetTimeStamp() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool CreateFile();
        bool RemoveFile();
        bool SetData(const Data& data);
        Data* GetData();
        FileAccess* GetFileAccess();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        LogicalMountPoint* _MountPoint;
    };
}
}
#endif
