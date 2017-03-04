#ifndef _COFFEE_META_SERIALIZER_H_
#define _COFFEE_META_SERIALIZER_H_

#include "coffee_includes.h"
#include "kernel/meta/type/meta_type.h"
#include "kernel/meta/serializer/stream/meta_stream.h"
#include "kernel/basic/container/rope/basic_rope_template.h"

namespace coffee
{
namespace meta
{
    //-FORWARDS-----------------------------------------------------------------------------------//
    struct Attribute;
    class Array;

    //--------------------------------------------------------------------------------------------//
    /// Serialize meta::Object
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Serializer
    {
    private:

        //-TYPES----------------------------------------------------------------------------------//

        struct SObject;
        struct SPointer;
        struct SWeakPointer;

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Serializer();
        ~Serializer();

        //-OPERATIONS-----------------------------------------------------------------------------//
        
        void Serialize(meta::Object& object, Stream& stream);
        void SerializeObject(Stream& stream, Object& object);
        void SerializeObjectFromType(Stream& stream, Type& type);
        void SerializePointer(Stream& stream, Attribute& attribute);
        void SerializeArray(Stream& stream, meta::Attribute& attribute);
        
    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _RegisterObject(Stream& stream, void* object, Type& type);
        uint32 _RegisterPointer(Stream& stream, void* object, Type& type, uint32 identifier=NONE,
            void** address=NULL, bool it_is_weak=false);
        bool _Process(Stream& stream);
        void _ProcessPointers(Stream& stream);
        
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        bool _ItIsProcessing;
        basic::Rope<Object*>* _Objects;
        basic::Rope<SObject*>* _ProcessingObjects;
        basic::Rope<SObject*>* _ProcessedObjects;
        basic::Rope<SPointer*>* _Pointers;
        basic::Rope<SWeakPointer*>* _WeakPointers;
        Object* _RootObject;
    };

}
}
#endif
