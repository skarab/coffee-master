#ifndef _COFFEE_STORAGE_PACK_H_
#define _COFFEE_STORAGE_PACK_H_

#include "coffee_includes.h"
#include "kernel/core/core.h"
#include "kernel/meta/meta_object.h"
#include "kernel/basic/container/prow/basic_prow.h"
#include "kernel/storage/pack/storage_pack_file.h"
#include "kernel/storage/logical/storage_path.h"
#include "kernel/storage/file/storage_file_access.h"

namespace coffee
{
namespace storage
{
    //--------------------------------------------------------------------------------------------//
    /// Pack of multiple files
    ///
    /// Store several files and directories into a single file.
    /// Actually AddFile and RemoveFile need Pack to be open in mode MODE_Output,
    /// and GetFile in mode MODE_Input.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Pack
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Pack();
        ~Pack();

        //-ACCESSORS------------------------------------------------------------------------------//

        bool IsOpen() const;

        //-QUERIES--------------------------------------------------------------------------------//

        uint32 FindFile(const Path& file_path) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool Open(const Path& path, const MODE& mode);
        void Close();
        void AddFile(const Path& file_path, Stream& data_stream);
        void RemoveFile(const Path& file_path);
        bool GetFile(const Path& file_path, Stream& data_stream);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _ReadFileList();
        void _WriteFileList();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Path _Path;
        FileAccess* _FileAccess;
        basic::Prow<PackFile*, true> _FileArray;
        bool _ItIsOpen;
        MODE _Mode;
    };
}
}
#endif
