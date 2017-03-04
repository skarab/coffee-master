#ifndef _COFFEE_STORAGE_SYSTEM_H_
#define _COFFEE_STORAGE_SYSTEM_H_

#include "coffee_includes.h"
#include "kernel/basic/container/basic_containers.h"
#include "kernel/core/core.h"
#include "kernel/storage/logical/storage_logical_entry.h"
#include "kernel/storage/logical/storage_logical_file_entry.h"
#include "kernel/storage/logical/storage_logical_mount_point.h"
#include "kernel/storage/physical/storage_physical_system.h"
#include "kernel/shell/thread/shell_locker.h"

namespace coffee
{
namespace storage
{
    //--------------------------------------------------------------------------------------------//
    /// Logical file system
    ///
    /// This singleton gives abstracted access to files.
    /// It works using relative logical file pathes, based on physical mount points.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API System
    {
        COFFEE_DeclareSingleton(System);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        System();
        ~System();

        //-ACCESSORS------------------------------------------------------------------------------//

        const PhysicalPath& GetRootPath() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool HasMountPoint(const Path& logical_path);
        bool HasPath(const Path& path);
        PhysicalPath GetPhysicalFilePath(const Path& logical_file_path);
        bool GetFileMountPoint(Path& mount_point, const Path& logical_file_path);
        bool SetFileData(const Path& file_path, const Data& data, bool it_has_to_create=false);
        Data* GetFileData(const Path& file_path);
        FileAccess* GetFileAccess(const Path& file_path);
        basic::Date GetFileTimeStamp(const Path& file_path);
        bool RemoveFile(const Path& file_path);
        bool RemoveFileAndEmptyFolder(const Path& file_path);
        bool CopyFile(const Path& from_path, const Path& to_path, bool it_replaces=false);
        bool MoveFile(const Path& from_path, const Path& to_path, bool it_replaces=false);
        bool CreateFolder(const Path& path, bool force_inconsistent=false);
        bool RemoveFolder(const Path& path);
        bool CopyFolder(const Path& from_path, const Path& to_path, bool it_preserves_files=true, bool it_replaces=false);
        bool MoveFolder(const Path& from_path, const Path& to_path, bool it_preserves_files=true, bool it_replaces=false);
        bool List(basic::Prow<Path*, true>& pathes, const Path& path, bool it_wants_folders=true,
            bool it_wants_files=true, basic::String extension="*", bool it_is_recursive=false, bool it_adds=false);
        bool Mount(const basic::String& name, const PhysicalPath& physical_path,
            const Path& logical_path, bool high_priority=false);
        bool UnMount(const PhysicalPath& physical_path);
        bool ReMount(PhysicalPath physical_path);
        void MountRoot();
        void UnMountAll();
        
        void Lock();
        void Unlock();

    private:

        //-QUERIES--------------------------------------------------------------------------------//

        uint32 _FindMountPoint(const PhysicalPath& physical_path) const;
        uint32 _FindMountPoint(const Path& path) const;
        
        //-OPERATIONS-----------------------------------------------------------------------------//

        LogicalEntry* _CreateEntry(const Path& logical_path, bool force_folder=false);
        LogicalEntry* _GetEntry(const Path& logical_path);
        void _ListFolder(basic::Prow<Path*, true>& pathes, LogicalEntry& folder, bool it_wants_folders,
            bool it_wants_files, basic::String extension, bool it_is_recursive);
        
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        PhysicalPath _RootPath;
        LogicalEntry* _RootEntry;
        basic::Prow< LogicalMountPoint*, true > _MountPointArray;
        bool _ItIsMounting;
        shell::Mutex _Mutex;
    };
}
}
#endif
