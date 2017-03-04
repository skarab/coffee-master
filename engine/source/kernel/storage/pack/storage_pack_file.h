#ifndef _COFFEE_STORAGE_PACK_FILE_H_
#define _COFFEE_STORAGE_PACK_FILE_H_

#include "coffee_includes.h"
#include "kernel/core/core.h"
#include "kernel/meta/meta_object.h"
#include "kernel/storage/logical/storage_path.h"
#include "kernel/storage/data/storage_stream.h"

namespace coffee
{
namespace storage
{
    //--------------------------------------------------------------------------------------------//
    /// Single file contained in a Pack
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PackFile
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PackFile();
        ~PackFile();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetPath(const Path& path);
        const Path& GetPath() const;
        void SetOffset(ulong offset);
        ulong GetOffset() const;
        void SetSize(ulong size);
        ulong GetSize() const;
        void SetStream(Stream* data_stream);
        const Stream& GetStream() const;
        Stream& GetStream();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Path _Path;
        ulong _Offset;
        ulong _Size;
        Stream* _Stream;
    };
}
}
#endif
