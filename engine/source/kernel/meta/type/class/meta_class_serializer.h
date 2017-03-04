#ifndef _COFFEE_META_CLASS_SERIALIZER_H_
#define _COFFEE_META_CLASS_SERIALIZER_H_

#include "coffee_includes.h"
#include "kernel/meta/type/class/meta_class.h"

namespace coffee
{
namespace meta
{
    //--------------------------------------------------------------------------------------------//
    /// Internal class serializer
    ///
    /// It manages the serialization of meta object types, using a dictionary for managing
    /// type changes.
    //--------------------------------------------------------------------------------------------//
    class ClassSerializer
    {
    private:

        //-FORWARDS-------------------------------------------------------------------------------//

        struct Class;
        struct Attribute;
        struct Dictionnary;

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ClassSerializer();
        ~ClassSerializer();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Serialize(meta::Class& meta_type, Stream& stream);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _PreSerializeDictionnary(meta::Class& meta_type, Stream& stream);
        void _PostSerializeDictionnary(meta::Class& meta_type, Stream& stream);
        void _BuildDictionnary(meta::Class& meta_type, Stream& stream);
        void _SerializeAncestors(Stream& stream);
        void _SerializeAttributes(Stream& stream);
        void _SerializeAttribute(meta::Attribute& attribute, Stream& stream);
        
        void _SearchAncestor(meta::Class& meta_type, Class* ancestor, ulong_ptr offset);
        void _SearchAttribute(meta::Class& meta_type, Attribute* attribute);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Dictionnary* _Dictionnary;
        ulong _ClassSize;
        ulong _ObjectSize;
    };
}
}
#endif
