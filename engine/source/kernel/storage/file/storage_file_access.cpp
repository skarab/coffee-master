#include "kernel/storage/file/storage_file_access.h"
#include "kernel/core/core.h"
#include "kernel/basic/basic.h"
#include "kernel/storage/file/storage_file_access_windows.hpp"
#include "kernel/storage/logical/storage_system.h"

namespace coffee
{
namespace storage
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    FileAccess::FileAccess(const PhysicalPath& path) :
        _Path(path),
        _Mode(0),
        _Offset(0),
        _Size(0),
        _ItIsOpen(false)
    {
    }

    //--------------------------------------------------------------------------------------------//

    FileAccess::~FileAccess()
    {
        if (IsOpen())
            Close();
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const PhysicalPath& FileAccess::GetPath() const
    {
        return _Path;
    }

    //--------------------------------------------------------------------------------------------//

    uint32 FileAccess::GetMode() const
    {
        return _Mode;
    }

    //--------------------------------------------------------------------------------------------//

    void FileAccess::SetOffset(ulong offset)
    {
        _Offset = offset;
        _Platform_SetOffset(offset);
    }

    //--------------------------------------------------------------------------------------------//

    ulong FileAccess::GetOffset() const
    {
        return _Offset;
    }

    //--------------------------------------------------------------------------------------------//

    void FileAccess::SetSize(ulong size)
    {
        _Size = size;
    }

    //--------------------------------------------------------------------------------------------//

    ulong FileAccess::GetSize() const
    {
        return _Size;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool FileAccess::IsOpen() const
    {
        return _ItIsOpen;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool FileAccess::Open(uint32 mode)
    {
        System::Get().Lock();
        _Mode = mode;
        if (!_Platform_Open())
            return false;
        _ItIsOpen = true;
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    void FileAccess::Close()
    {
        _ItIsOpen = false;
        _Platform_Close();
        System::Get().Unlock();
    }

    //--------------------------------------------------------------------------------------------//

    void FileAccess::Read(char* buffer, ulong size)
    {
        _Platform_Read(buffer, size);
        _Offset += size;
    }

    //--------------------------------------------------------------------------------------------//

    void FileAccess::Write(const char* buffer, ulong size)
    {
        _Platform_Write(buffer, size);
        _Offset += size;
        if (_Offset>_Size)
            _Size = _Offset;
    }

    //--------------------------------------------------------------------------------------------//

    void FileAccess::ReadString(basic::String& string)
    {
        char read_char;
        string = "";
        do
        {
            Read(&read_char, 1);
            string += read_char;
        }
        while (read_char!=NULL_CHAR);
    }

    //--------------------------------------------------------------------------------------------//

    void FileAccess::WriteString(const basic::String& string)
    {
        Write(string.GetBuffer(), string.GetLength() + 1);
    }

}
}
