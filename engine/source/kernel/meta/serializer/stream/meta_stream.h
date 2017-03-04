#ifndef _COFFEE_META_STREAM_H_
#define _COFFEE_META_STREAM_H_

#include "coffee_includes.h"
#include "kernel/storage/data/storage_stream.h"

namespace coffee
{
    //-FORWARDS-----------------------------------------------------------------------------------//

namespace basic
{
    class String;
}
namespace storage
{
    class File;
    class Path;
}

namespace meta
{
    class Serializer;

    //--------------------------------------------------------------------------------------------//
    /// Stream objects into memory or file, during the serialization
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Stream
    {
        friend class Serializer;

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Stream();
        ~Stream();

        //-ACCESSORS------------------------------------------------------------------------------//

        Serializer& GetSerializer();
        storage::Stream& GetStream();
        storage::MODE GetMode() const;
        void SetObject(void* object);
        void* GetObject();
        void* GetRootObject();
        void SetObjectOffset(ulong_ptr offset);
        ulong_ptr GetObjectOffset() const;
        
        //-OPERATIONS-----------------------------------------------------------------------------//

        bool Open(const storage::Path& file_path, const storage::MODE& mode);
        bool Open(const storage::MODE& mode);
        bool Close();
        storage::Stream& RetrieveStream();
        void DisableEncoder();

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _Encode();
        void _Decode();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        bool _ItIsUsingEncoder;
        Serializer* _Serializer;
        storage::Stream* _Stream;
        storage::MODE _Mode;
        storage::File* _File;
        void* _Object;
        ulong_ptr _ObjectOffset;
    };
}
}
#endif
