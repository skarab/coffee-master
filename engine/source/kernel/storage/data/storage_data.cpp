#include "kernel/storage/data/storage_data.h"
#include "kernel/core/core.h"
#include "kernel/basic/alpha/string/basic_string.h"

namespace coffee
{
namespace storage
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Data::Data() :
        _ReservedSize(0),
        _Size(0),
        _Buffer(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Data::~Data()
    {
        Erase();
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    char Data::operator [] (ulong index) const
    {
        return _Buffer[index];
    }

    //--------------------------------------------------------------------------------------------//

    Data& Data::operator = (const Data& data)
    {
        Resize(data.GetSize());
        COFFEE_Copy(_Buffer, data.GetBuffer(), _Size);
        return *this;
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    ulong Data::GetSize() const
    {
        return _Size;
    }

    //--------------------------------------------------------------------------------------------//

    const char* Data::GetBuffer() const
    {
        return _Buffer;
    }

    //--------------------------------------------------------------------------------------------//

    char* Data::GetBuffer()
    {
        return _Buffer;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Data::Reserve(ulong size)
    {
        if (size<=_ReservedSize)
            return;

        COFFEE_Assert(size>=_Size, core::ERROR_CODE_IncorrectUsage,
            "Forbidden to reserve less than actual allocated size");

        size = size+size/2;
        _Buffer = (char*) COFFEE_Reallocate(_Buffer, (ulong)size);
        _ReservedSize = size;
    }

    //--------------------------------------------------------------------------------------------//

    void Data::Resize(ulong size)
    {
        if (size>_ReservedSize)
            Reserve(size);
        _Size = size;
    }

    //--------------------------------------------------------------------------------------------//

    void Data::Erase()
    {
        _Size = 0;
        _ReservedSize = 0;

        if (_Buffer!=NULL)
        {
            COFFEE_Free(_Buffer);
            _Buffer = NULL;
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Data::Push(const Data& data)
    {
        Reserve(_Size+data.GetSize());
        COFFEE_Copy((void*)((ulong_ptr)_Buffer+_Size), data.GetBuffer(), data.GetSize());
        _Size += data.GetSize();
    }

    //--------------------------------------------------------------------------------------------//

    void Data::Push(const void* buffer, ulong buffer_size)
    {
        Reserve(_Size+buffer_size);
        COFFEE_Copy((void*)((ulong_ptr)_Buffer+_Size), buffer, buffer_size);
        _Size += buffer_size;
    }

    //--------------------------------------------------------------------------------------------//

    bool Data::Pop(void* buffer, ulong buffer_size)
    {
        if (buffer_size>GetSize())
            return false;

        COFFEE_Copy(buffer, (void*)((ulong_ptr)_Buffer+GetSize()-buffer_size), buffer_size);
        Resize(GetSize()-buffer_size);
        return true;
    }

}
}
