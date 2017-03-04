#include "kernel/storage/data/storage_stream.h"
#include "kernel/core/core.h"
#include "kernel/basic/alpha/basic_alpha.h"

namespace coffee
{
namespace storage
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Stream::Stream() :
        _Data(NULL),
        _Offset(0)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Stream::~Stream()
    {
        if (_Data!=NULL)
            COFFEE_Delete(_Data);
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Stream::SetData(Data* data)
    {
        if (_Data!=NULL)
            COFFEE_Delete(_Data);
        _Data = data;
    }

    //--------------------------------------------------------------------------------------------//

    const Data& Stream::GetData() const
    {
        return *_Data;
    }

    //--------------------------------------------------------------------------------------------//

    Data& Stream::GetData()
    {
        return *_Data;
    }

    //--------------------------------------------------------------------------------------------//

    ulong Stream::GetSize() const
    {
        if (_Data==NULL)
            return 0;
        return _Data->GetSize();
    }

    //--------------------------------------------------------------------------------------------//

    ulong_ptr Stream::GetOffset() const
    {
        return _Offset;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool Stream::HasData() const
    {
        return _Data!=NULL;
    }

    //--------------------------------------------------------------------------------------------//
    
    bool Stream::IsOver() const
    {
        return _Offset>=_Data->GetSize();
    }

    //--------------------------------------------------------------------------------------------//
    
    real Stream::GetPercentage() const
    {
        if (_Data->GetSize()==0)
            return 0.0f;
        return (real)_Offset/(real)_Data->GetSize();
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Stream::Push(const Data& data)
    {
        if (_Data==NULL)
            _Data = COFFEE_New(Data);
        _Data->Push(data);
    }

    //--------------------------------------------------------------------------------------------//

    void Stream::Push(const void* buffer, ulong buffer_size)
    {
        if (_Data==NULL)
            _Data = COFFEE_New(Data);
        _Data->Push(buffer, buffer_size);
    }

    //--------------------------------------------------------------------------------------------//

    char* Stream::Pop(ulong size)
    {
        if (_Offset+size>_Data->GetSize())
            return NULL_CHAR;
        char* data = (char*)((ulong_ptr)_Data->GetBuffer()+_Offset);
        _Offset += size;
        return data;
    }

    //--------------------------------------------------------------------------------------------//

    char* Stream::Pop()
    {
        return (char*)((ulong_ptr)_Data->GetBuffer()+_Offset);
    }

    //--------------------------------------------------------------------------------------------//

    bool Stream::Pop(void* object, ulong object_size)
    {
        if (_Offset+object_size>_Data->GetSize())
        {
            COFFEE_Set(object, 0, object_size);
            _Offset += object_size;
            return false;
        }
        else
        {
            void* data = (void*)((ulong_ptr)_Data->GetBuffer()+_Offset);
            _Offset += object_size;
            COFFEE_Copy(object, data, object_size);
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    Data* Stream::PopData()
    {
        Data* data = _Data;
        _Data = NULL;
        Flush();
        return data;
    }

    //--------------------------------------------------------------------------------------------//

    void Stream::Flush()
    {
        if (_Data!=NULL)
        {
            COFFEE_Delete(_Data);
            _Data = NULL;
        }
        _Offset = 0;
    }

    //--------------------------------------------------------------------------------------------//

    void Stream::Seek(ulong_ptr offset)
    {
        _Offset = offset;
    }

    //--------------------------------------------------------------------------------------------//

    void Stream::PushString(const basic::String& string)
    {
        Push(string.GetBuffer(), string.GetLength()+1);
    }

    //--------------------------------------------------------------------------------------------//

    void Stream::PopString(basic::String& string)
    {
        char* read_char;
        string = "";
        while((read_char=Pop(1))!=NULL && *read_char!=NULL_CHAR)
            string += *read_char;
    }

    //--------------------------------------------------------------------------------------------//

    bool Stream::PopLine(basic::String& line)
    {
        char* read_char;
        line = "";
        read_char = Pop(1);
        while(read_char!=NULL && *read_char!=NULL_CHAR && *read_char!='\n')
        {
            line += *read_char;
            read_char = Pop(1);
        }
        return _Offset<_Data->GetSize();
    }

    //--------------------------------------------------------------------------------------------//

    bool Stream::PopWord(basic::String& word)
    {
        char* read_char;
        word = "";
        read_char = Pop(1);
        while (read_char!=NULL && *read_char!=NULL_CHAR && *read_char!='\n' && *read_char!=' ')
        {
            word += *read_char;
            read_char = Pop(1);
        }
        return _Offset<_Data->GetSize();
    }

}
}
