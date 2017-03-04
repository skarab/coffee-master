#include "kernel/storage/pack/storage_pack.h"
#include "kernel/core/core.h"
#include "kernel/storage/logical/storage_system.h"

namespace coffee
{
namespace storage
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Pack::Pack() :
        _FileAccess(NULL),
        _ItIsOpen(false)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Pack::~Pack()
    {
        if (_FileAccess!=NULL)
            COFFEE_Delete(_FileAccess);
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    bool Pack::IsOpen() const
    {
        return _ItIsOpen;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    uint32 Pack::FindFile(const Path& file_path) const
    {
        for (uint32 file_index=0 ; file_index<_FileArray.GetSize() ; ++file_index)
        {
            if (_FileArray[file_index]->GetPath()==file_path)
                return file_index;
        }
        return NONE;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool Pack::Open(const Path& path, const MODE& mode)
    {
        if (_ItIsOpen)
            return true;

        COFFEE_Assert(_FileAccess==NULL, core::ERROR_CODE_Unexpected, "Unexpected error");
        if (mode==MODE_Output && !System::Get().HasPath(path))
            System::Get().SetFileData(path, Data(), true);
        _FileAccess = System::Get().GetFileAccess(path);
        if (_FileAccess==NULL)
            return false;
        _Mode = mode;

        if (mode==MODE_Output)
        {
            if (!System::Get().HasPath(path))
                System::Get().SetFileData(path, Data(), true);
            if (!_FileAccess->Open(MODE_Input))
                return false;
            _ReadFileList();
            _FileAccess->Close();
            if (!_FileAccess->Open(MODE_Output))
                return false;
        }
        else
        {
            if (!_FileAccess->Open(MODE_Input))
                return false;
            _ReadFileList();
        }
        _ItIsOpen = true;
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    void Pack::Close()
    {
        if (_ItIsOpen)
        {
            if (_Mode==MODE_Output)
                _WriteFileList();
            _ItIsOpen = false;
            _FileAccess->Close();
            COFFEE_Delete(_FileAccess);
            _FileAccess = NULL;
            _FileArray.Erase();
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Pack::AddFile(const Path& file_path, Stream& data_stream)
    {
        COFFEE_Assert(_Mode==MODE_Output, core::ERROR_CODE_IncorrectUsage, "Failed to write pack");

        uint32 file_index = FindFile(file_path);
        PackFile* file;
        if (file_index!=NONE)
        {
            file = _FileArray[file_index];
        }
        else
        {
            file = COFFEE_New(PackFile);
            _FileArray.AddItem(file);
        }

        file->SetPath(file_path);
        file->SetStream(&data_stream);
    }

    //--------------------------------------------------------------------------------------------//

    void Pack::RemoveFile(const Path& file_path)
    {
        COFFEE_Assert(_Mode==MODE_Output, core::ERROR_CODE_IncorrectUsage, "Failed to write pack");

        uint32 file_index = FindFile(file_path);
        if (file_index!=NONE)
            _FileArray.Remove(file_index);
    }

    //--------------------------------------------------------------------------------------------//

    bool Pack::GetFile(const Path& file_path, Stream& data_stream)
    {
        COFFEE_Assert(_Mode==MODE_Input, core::ERROR_CODE_IncorrectUsage, "Failed to read pack");

        uint32 file_index = FindFile(file_path);

        if (file_index!=NONE)
        {
            PackFile* file = _FileArray[file_index];
            _FileAccess->SetOffset(file->GetOffset());
            if (!data_stream.HasData())
                data_stream.SetData(COFFEE_New(Data));
            data_stream.GetData().Resize(file->GetSize());
            _FileAccess->Read(data_stream.GetData().GetBuffer(), file->GetSize());
            return true;
        }
        return false;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Pack::_ReadFileList()
    {
        while (_FileAccess->GetOffset()<_FileAccess->GetSize())
        {
            PackFile* file;
            basic::String path;
            ulong size;

            _FileAccess->ReadString(path);
            _FileAccess->Read((char*) &size, sizeof(ulong));

            file = COFFEE_New(PackFile);
            file->SetPath(path);
            file->SetOffset(_FileAccess->GetOffset());
            file->SetSize(size);

            if (_Mode==MODE_Output)
            {
                Stream* data_stream = COFFEE_New(Stream);
                data_stream->SetData(COFFEE_New(Data));
                data_stream->GetData().Resize(file->GetSize());
                _FileAccess->Read(data_stream->GetData().GetBuffer(), file->GetSize());
                file->SetStream(data_stream);
            }
            else
            {
                _FileAccess->SetOffset(file->GetOffset() + size);
            }
            _FileArray.AddItem(file);
        }
        _FileAccess->SetOffset(0);
    }

    //--------------------------------------------------------------------------------------------//

    void Pack::_WriteFileList()
    {
        COFFEE_Assert(_Mode==MODE_Output, core::ERROR_CODE_IncorrectUsage, "Failed to write pack");

        for (uint32 file_index=0 ; file_index<_FileArray.GetSize() ; ++file_index)
        {
            PackFile* file = _FileArray[file_index];
            basic::String path = file->GetPath();
            ulong size = file->GetStream().GetSize();

            _FileAccess->WriteString(path);
            _FileAccess->Write((char *) &size, sizeof(ulong));
            _FileAccess->Write(file->GetStream().GetData().GetBuffer(), size);
        }
    }

}
}
