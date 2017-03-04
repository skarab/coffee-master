#ifndef _COFFEE_STORAGE_FILE_H_
#define _COFFEE_STORAGE_FILE_H_

#include "coffee_includes.h"
#include "kernel/storage/logical/storage_path.h"
#include "kernel/storage/data/storage_mode.h"

namespace coffee
{
namespace storage
{
    class LogicalFileEntry;
    class Stream;
    class Data;

    //--------------------------------------------------------------------------------------------//
    /// Logical access to a file
    ///
    /// Read/Write into a file, using a storage::Stream.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API File
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        File();
        virtual ~File();

        //-ACCESSORS------------------------------------------------------------------------------//

        const Path& GetPath() const;
        MODE GetMode() const;

        //-QUERIES--------------------------------------------------------------------------------//

        bool IsOpened() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool Open(const Path& path, MODE mode);
        bool Close();
        void Stream(Stream& stream);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Path _Path;
        MODE _Mode;
        Data* _Data;
    };
}
}
#endif
