#include "kernel/meta/array/meta_array.h"
#include "kernel/core/core.h"

namespace coffee
{
namespace meta
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(meta::Array);
    COFFEE_EndType();

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Array::Array() :
        _Size(0)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Array::~Array()
    {
        Erase();
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    Array& Array::operator = (const Array& array)
    {
        Erase();
        Resize(array.GetSize());
        return *this;
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    uint32 Array::GetSize() const
    {
        return _Size;
    }

    //--------------------------------------------------------------------------------------------//

    const void* Array::GetLinearBuffer() const
    {
        return NULL;
    }

    //--------------------------------------------------------------------------------------------//

    void* Array::GetLinearBuffer()
    {
        return NULL;
    }

    //--------------------------------------------------------------------------------------------//

    const void* Array::GetItemPointer(uint32 item_index) const
    {
        return NULL;
    }

    //--------------------------------------------------------------------------------------------//

    void* Array::GetItemPointer(uint32 item_index)
    {
        return NULL;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool Array::IsEmpty() const
    {
        return _Size==0;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    uint32 Array::Add(uint32 item_index)
    {
        ++_Size;
        if (item_index==NONE)
        {
            return _Size-1;
        }
        else
        {
            COFFEE_Assert(item_index<_Size, core::ERROR_CODE_IncorrectUsage, "Trying to add item at invalid index");
        }
        return item_index;
    }

    //--------------------------------------------------------------------------------------------//

    void Array::Remove(uint32 item_index)
    {
        --_Size;
    }

    //--------------------------------------------------------------------------------------------//

    void Array::Resize(uint32 item_count)
    {
        _Size = item_count;
    }

    //--------------------------------------------------------------------------------------------//

    void Array::Clear()
    {
        _Size = 0;
    }

    //--------------------------------------------------------------------------------------------//

    void Array::Erase()
    {
        Clear();
    }

}
}
