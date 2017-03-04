#ifndef _COFFEE_STORAGE_PHYSICAL_SYSTEM_H_
#define _COFFEE_STORAGE_PHYSICAL_SYSTEM_H_

#include "coffee_includes.h"
#include "kernel/basic/container/basic_containers.h"
#include "kernel/core/core.h"
#include "kernel/storage/data/storage_data.h"
#include "kernel/storage/file/storage_file_access.h"
#include "kernel/storage/physical/storage_physical_path.h"

namespace coffee
{
namespace storage
{
    //--------------------------------------------------------------------------------------------//
    /// Physical access to OS filesystem
    ///
    /// This singleton gives direct access to files, on hard-drive.
    /// The physical system is abstracted by the logical system, which works only on virtual
    /// directories and files.
    ///
    /// @see coffee::storage::System
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PhysicalSystem
    {
        COFFEE_DeclareSingleton(PhysicalSystem);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PhysicalSystem();
        ~PhysicalSystem();

        //-ACCESSORS------------------------------------------------------------------------------//

        const PhysicalPath& GetRootFolder() const;

        //-QUERIES--------------------------------------------------------------------------------//

        bool IsFolder(const PhysicalPath& path) const;
        bool IsFile(const PhysicalPath& path) const;
        bool IsReadOnly(const PhysicalPath& path) const;
        bool IsValidName(const basic::String& file_name) const;

        bool ListDrives(basic::Prow<PhysicalPath*, true> & drives) const;
        bool List(basic::Prow<PhysicalPath*, true> & pathes,
            const PhysicalPath& path, bool it_wants_folders, bool it_wants_files,
            basic::String extension="*.*", bool it_is_recursive=false) const;

        bool CreateFile(const PhysicalPath& path, bool it_replaces=false) const;
        bool RemoveFile(const PhysicalPath& path) const;
        bool SetFileData(const PhysicalPath& path, const Data& data) const;
        Data* GetFileData(const PhysicalPath& path) const;
        FileAccess* GetFileAccess(const PhysicalPath& path) const;
        bool CopyFile(const PhysicalPath& from, const PhysicalPath& to,
            bool it_replaces=false) const;
        bool MoveFile(const PhysicalPath& from, const PhysicalPath& to,
            bool it_replaces=false) const;

        bool CreateFolder(const PhysicalPath& path) const;
        bool RemoveFolder(const PhysicalPath& path) const;
        bool CopyFolder(const PhysicalPath& from, const PhysicalPath& to,
            bool it_replaces=false, bool (*filter)(meta::Object* user, const PhysicalPath& path)=NULL, meta::Object* user=NULL) const;
        bool MoveFolder(const PhysicalPath& from, const PhysicalPath& to,
            bool it_replaces=false) const;

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        PhysicalPath _RootFolder;
    };
}
}
#endif
