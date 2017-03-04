#include "kernel/storage/pack/storage_pack_file.h"
#include "kernel/core/core.h"

namespace coffee
{
namespace storage
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PackFile::PackFile() :
        _Offset(0),
        _Size(0),
        _Stream(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    PackFile::~PackFile()
    {
        SetStream(NULL);
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void PackFile::SetPath(const Path& path)
    {
        _Path = path;
    }

    //--------------------------------------------------------------------------------------------//

    const Path& PackFile::GetPath() const
    {
        return _Path;
    }

    //--------------------------------------------------------------------------------------------//

    void PackFile::SetOffset(ulong offset)
    {
        _Offset = offset;
    }

    //--------------------------------------------------------------------------------------------//

    ulong PackFile::GetOffset() const
    {
        return _Offset;
    }

    //--------------------------------------------------------------------------------------------//

    void PackFile::SetSize(ulong size)
    {
        _Size = size;
    }

    //--------------------------------------------------------------------------------------------//

    ulong PackFile::GetSize() const
    {
        return _Size;
    }

    //--------------------------------------------------------------------------------------------//

    void PackFile::SetStream(Stream* data_stream)
    {
        if (_Stream!=NULL)
            COFFEE_Delete(_Stream);
        _Stream = data_stream;
    }

    //--------------------------------------------------------------------------------------------//

    const Stream& PackFile::GetStream() const
    {
        return *_Stream;
    }

    //--------------------------------------------------------------------------------------------//

    Stream& PackFile::GetStream()
    {
        return *_Stream;
    }

}
}
