#ifndef _COFFEE_META_TYPE_H_
#define _COFFEE_META_TYPE_H_

#include "coffee_includes.h"
#include "kernel/meta/serializer/stream/meta_stream.h"
#include "kernel/meta/type/meta_type_info.h"

namespace coffee
{
namespace basic
{
    class String;
}

namespace meta
{
    class Object;

    //--------------------------------------------------------------------------------------------//
    /// Meta type base class
    ///
    /// The meta type keeps memory information about types, acts like a RTTI (RunTime Type
    /// Identification) system.
    /// Supported types are basic scalars and class inherited from from meta::Object.
    /// It manages the serialization of given type.
    ///
    /// @see coffee::meta::Object
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Type
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Type(TYPE_INFO info);
        virtual ~Type();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetName(const basic::String& name);
        void SetName(const char* name);
        const basic::String& GetName() const;
        void SetSize(ulong size);
        ulong GetSize() const;
        const TYPE_INFO& GetInfo() const;
        void SetCreationMethod(Object* (* creation_method) ());

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual Object* CreateObject() const;
        virtual void Serialize(Stream& stream);

    protected:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::String* _Name;
        ulong _Size;
        TYPE_INFO _Info;
        Object* (* _CreationMethod)();
    };
}
}
#endif
