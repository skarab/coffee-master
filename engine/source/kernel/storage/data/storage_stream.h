#ifndef _COFFEE_STORAGE_STREAM_H_
#define _COFFEE_STORAGE_STREAM_H_

#include "coffee_includes.h"
#include "kernel/storage/data/storage_data.h"
#include "kernel/storage/data/storage_mode.h"

namespace coffee
{
    //-FORWARDS-----------------------------------------------------------------------------------//

namespace basic
{
    class String;
}

namespace storage
{
    //--------------------------------------------------------------------------------------------//
    /// Stream data from/to storage::Data
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Stream
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Stream();
        ~Stream();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetData(Data* data);
        const Data& GetData() const;
        Data& GetData();
        ulong GetSize() const;
        ulong_ptr GetOffset() const;

        //-QUERIES--------------------------------------------------------------------------------//

        bool HasData() const;
        bool IsOver() const;
        real GetPercentage() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Push(const Data& data);
        void Push(const void* buffer, ulong buffer_size);
        char* Pop(ulong size);
        char* Pop();
        bool Pop(void* object, ulong object_size);
        Data* PopData();
        void Flush();
        void Seek(ulong_ptr offset);
        void PushString(const basic::String& string);
        void PopString(basic::String& string);
        bool PopLine(basic::String& line);
        bool PopWord(basic::String& word);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Data* _Data;
        ulong_ptr _Offset;
    };
}
}
#endif
