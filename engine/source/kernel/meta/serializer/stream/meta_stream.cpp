#include "kernel/meta/serializer/stream/meta_stream.h"
#include "kernel/meta/serializer/meta_serializer.h"
#include "kernel/core/core.h"
#include "kernel/storage/storage.h"

namespace coffee
{
namespace meta
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Stream::Stream() :
        _ItIsUsingEncoder(true),
        _Serializer(NULL),
        _Stream(COFFEE_New(storage::Stream)),
        _File(NULL),
        _Object(NULL),
        _ObjectOffset(0)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Stream::~Stream()
    {
        if (_Stream!=NULL)
            COFFEE_Delete(_Stream);
        COFFEE_Assert(_File==NULL, core::ERROR_CODE_MetaSystem, "meta::Stream require to be closed");
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    Serializer& Stream::GetSerializer()
    {
        return *_Serializer;
    }

    //--------------------------------------------------------------------------------------------//

    storage::Stream& Stream::GetStream()
    {
        return *_Stream;
    }

    //--------------------------------------------------------------------------------------------//

    storage::MODE Stream::GetMode() const
    {
        return _Mode;
    }

    //--------------------------------------------------------------------------------------------//

    void Stream::SetObject(void* object)
    {
        _Object = object;
        SetObjectOffset(0);
    }

    //--------------------------------------------------------------------------------------------//

    void* Stream::GetObject()
    {
        return (void*)((ulong_ptr)_Object+_ObjectOffset);
    }

    //--------------------------------------------------------------------------------------------//

    void* Stream::GetRootObject()
    {
        return _Object;
    }

    //--------------------------------------------------------------------------------------------//

    void Stream::SetObjectOffset(ulong_ptr offset)
    {
        _ObjectOffset = offset;
    }

    //--------------------------------------------------------------------------------------------//

    ulong_ptr Stream::GetObjectOffset() const
    {
        return _ObjectOffset;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool Stream::Open(const storage::Path& file_path, const storage::MODE& mode)
    {
        COFFEE_Assert(_File==NULL, core::ERROR_CODE_MetaSystem, "meta::Stream require to be closed");
        basic::String meta_version("1.0");

        _Mode = mode;
        _File = COFFEE_New(storage::File);

        if (!_File->Open(file_path, mode))
        {
            COFFEE_Delete(_File);
            _File = NULL;
            return false;
        }

        if (mode==storage::MODE_Input)
        {
            _File->Stream(*_Stream);
            _Decode();
            _Stream->PopString(meta_version);
        }
        else if (mode==storage::MODE_Output)
        {
            _Stream->PushString(meta_version);
        }
        else
        {
            COFFEE_Error(core::ERROR_CODE_IncorrectUsage, "meta::Stream open with incorrect mode");
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Stream::Open(const storage::MODE& mode)
    {
        COFFEE_Assert(_File==NULL, core::ERROR_CODE_MetaSystem, "meta::Stream require to be closed");
        basic::String meta_version("1.0");

        _Mode = mode;

        if (mode==storage::MODE_Input)
        {
            _Decode();
            _Stream->PopString(meta_version);
        }
        else if (mode==storage::MODE_Output)
        {
            _Stream->PushString(meta_version);
        }
        else
        {
            COFFEE_Error(core::ERROR_CODE_IncorrectUsage, "meta::Stream open with incorrect mode");
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Stream::Close()
    {
        if (_Mode==storage::MODE_Output)
        {
            _Encode();

            if (_File!=NULL)
                _File->Stream(*_Stream);
        }

        if (_File!=NULL)
        {
            _File->Close();
            COFFEE_Delete(_File);
            _File = NULL;
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    storage::Stream& Stream::RetrieveStream()
    {
        storage::Stream* stream = _Stream;
        _Stream = NULL;
        return *stream;
    }
    
    //--------------------------------------------------------------------------------------------//

    void Stream::DisableEncoder()
    {
        _ItIsUsingEncoder = false;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Stream::_Encode()
    {
        if (!_ItIsUsingEncoder)
            return;

        basic::String header("CLZ");        
        ulong uncompressed_size = _Stream->GetData().GetSize();
        ulong compressed_size = LZ4_compressBound(uncompressed_size);        
        storage::Data* data = COFFEE_New(storage::Data);
        data->Resize(compressed_size);

        compressed_size = LZ4_compressHC(
            _Stream->GetData().GetBuffer(),
            data->GetBuffer(),
            uncompressed_size);

        COFFEE_Assert(compressed_size>0, core::ERROR_CODE_MetaSystem, "Failed to compress meta::Stream");
    
        data->Resize(compressed_size);
        _Stream->Flush();
        _Stream->PushString(header);
        _Stream->Push(&uncompressed_size, sizeof(ulong));
        _Stream->Push(*data);
        COFFEE_Delete(data);
    }

    //--------------------------------------------------------------------------------------------//

    void Stream::_Decode()
    {
        if (!_ItIsUsingEncoder)
            return;

        basic::String header;        
        ulong uncompressed_size(0);        
        _Stream->PopString(header);
        _Stream->Pop(&uncompressed_size, sizeof(ulong));
        storage::Data* data = COFFEE_New(storage::Data);
        data->Resize(uncompressed_size);

        if (header=="Coffee")
        {
            COFFEE_Assert(uncompress(
                (Bytef*) data->GetBuffer(),
                (ulong*) &uncompressed_size,
                (const Bytef*) _Stream->Pop(),
                (ulong)_Stream->GetData().GetSize()-sizeof(ulong)-(ulong)(header.GetLength()+1))==Z_OK,
                core::ERROR_CODE_MetaSystem, "Failed to uncompress meta::Stream");
        }
        else if (header=="CLZ")
        {
            COFFEE_Assert(LZ4_decompress_safe_partial(
                _Stream->Pop(),
                data->GetBuffer(),
                _Stream->GetSize()-_Stream->GetOffset(),
                uncompressed_size,
                uncompressed_size)==uncompressed_size,
                core::ERROR_CODE_MetaSystem, "Failed to uncompress meta::Stream");
        }
        else
        {
            COFFEE_Error(core::ERROR_CODE_MetaSystem, "meta::Stream is corrupted");
        }

        _Stream->Flush();
        _Stream->Push(*data);
        COFFEE_Delete(data);
    }

}
}
