#include "kernel/storage/file/storage_file.h"
#include "kernel/storage/logical/storage_system.h"
#include "kernel/storage/data/storage_data.h"
#include "kernel/storage/data/storage_stream.h"

namespace coffee
{
namespace storage
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    File::File() :
        _Mode(MODE_None),
        _Data(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    File::~File()
    {
        COFFEE_Assert(!IsOpened(), core::ERROR_CODE_StorageSystem, "storage::File destructor called while opened");
        if (_Data!=NULL)
            COFFEE_Delete(_Data);
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const Path& File::GetPath() const
    {
        return _Path;
    }

    //--------------------------------------------------------------------------------------------//

    MODE File::GetMode() const
    {
        return _Mode;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool File::IsOpened() const
    {
        return (_Mode!=MODE_None && (_Mode==MODE_Input || _Data!=NULL));
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool File::Open(const Path& path, MODE mode)
    {
        COFFEE_Assert(!IsOpened(), core::ERROR_CODE_StorageSystem, "File::Open() failed");
        COFFEE_Assert(mode!=MODE_None, core::ERROR_CODE_StorageSystem, "File::Open() incorrect usage");

        _Path = path;
        _Mode = mode;
        
        if (_Mode==MODE_Output)
        {
            _Data = COFFEE_New(Data);
            if (!System::Get().SetFileData(_Path, *_Data, true))
            {
                COFFEE_Delete(_Data);
                _Data = NULL;
                _Mode = MODE_None;
                return false;
            }
        }
        else if (_Mode==MODE_Input)
        {
            _Data = System::Get().GetFileData(_Path);
            if (_Data==NULL)
            {
                _Mode = MODE_None;
                return false;
            }
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool File::Close()
    {
        COFFEE_Assert(IsOpened(), core::ERROR_CODE_StorageSystem, "File::Close() failed");
        if (_Mode==MODE_Output && !System::Get().SetFileData(_Path, *_Data))
            return false;
        if (_Data!=NULL)
        {
            COFFEE_Delete(_Data);
            _Data = NULL;
        }
        _Mode = MODE_None;
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    void File::Stream(storage::Stream& stream)
    {
        COFFEE_Assert(IsOpened(), core::ERROR_CODE_StorageSystem, "File::Stream() failed");

        if (_Mode==MODE_Output)
        {
            if(!stream.HasData())
                return;

            if (_Data!=NULL)
                COFFEE_Delete(_Data);

            _Data = stream.PopData();
        }
        else if (_Mode==MODE_Input)
        {
            stream.SetData(_Data);
            _Data = NULL;
        }
        else
        {
            COFFEE_Error(core::ERROR_CODE_Unexpected, "storage::File unexpected error");
        }
    }

}
}
