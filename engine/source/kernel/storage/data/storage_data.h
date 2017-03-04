#ifndef _COFFEE_STORAGE_DATA_H_
#define _COFFEE_STORAGE_DATA_H_

#include "coffee_includes.h"

namespace coffee
{
namespace storage
{
    //--------------------------------------------------------------------------------------------//
    /// Data buffering class used to hold file data
    ///
    /// It is mainly used internally by the data stream class.
    ///
    /// @see coffee::storage::Stream
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Data
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Data();
        ~Data();

        //-OPERATORS------------------------------------------------------------------------------//

        char operator [](ulong index) const;
        Data& operator = (const Data& data);

        //-ACCESSORS------------------------------------------------------------------------------//

        ulong GetSize() const;
        const char* GetBuffer() const;
        char* GetBuffer();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Reserve(ulong size);
        void Resize(ulong size);
        void Erase();
        void Push(const Data& data);
        void Push(const void* buffer, ulong buffer_size);
        bool Pop(void* buffer, ulong buffer_size);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        ulong _ReservedSize;
        ulong _Size;
        char* _Buffer;
    };
}
}
#endif
