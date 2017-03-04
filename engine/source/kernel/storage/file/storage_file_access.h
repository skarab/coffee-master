#ifndef _COFFEE_STORAGE_FILE_ACCESS_H_
#define _COFFEE_STORAGE_FILE_ACCESS_H_

#include "coffee_includes.h"
#include "kernel/core/core.h"
#include "kernel/meta/meta_object.h"
#include "kernel/storage/physical/storage_physical_path.h"
#include "kernel/storage/data/storage_mode.h"

namespace coffee
{
namespace storage
{
    //--------------------------------------------------------------------------------------------//
    /// Physical access to a file
    ///
    /// It gives direct access to a file through standard stdio, this is mainly used by
    /// storage::Pack to not load all data at once.
    ///
    /// @see coffee::storage::Pack
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API FileAccess
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        FileAccess(const PhysicalPath& path);
        ~FileAccess();

        //-ACCESSORS------------------------------------------------------------------------------//

        const PhysicalPath& GetPath() const;
        uint32 GetMode() const;
        void SetOffset(ulong offset);
        ulong GetOffset() const;
        void SetSize(ulong size);
        ulong GetSize() const;

        //-QUERIES--------------------------------------------------------------------------------//

        bool IsOpen() const;
        basic::Date GetLastWriteDate() const;
        
        //-OPERATIONS-----------------------------------------------------------------------------//

        bool Open(uint32 mode);
        void Close();
        void Read(char* buffer, ulong size);
        void Write(const char* buffer, ulong size);
        void ReadString(basic::String& string);
        void WriteString(const basic::String& string);
        
    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool _Platform_Open();
        void _Platform_Close();
        void _Platform_SetOffset(ulong offset);
        void _Platform_Read(char* buffer, ulong size);
        void _Platform_Write(const char* buffer, ulong size);
        
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        PhysicalPath _Path;
        uint32 _Mode;
        ulong _Offset;
        ulong _Size;
        bool _ItIsOpen;

        #include "kernel/storage/file/storage_file_access_windows.h"
    };
}
}
#endif
