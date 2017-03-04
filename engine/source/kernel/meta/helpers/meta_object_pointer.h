#ifndef _COFFEE_META_OBJECT_REFERENCE_H_
#define _COFFEE_META_OBJECT_REFERENCE_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_object.h"

namespace coffee
{
namespace meta
{
    //--------------------------------------------------------------------------------------------//
    /// Unknown-type meta object serialization helper
    ///
    /// This is the way to serialize directly a pointer with unknown meta::Object pointed type.
    /// Just set your object and serialize it.
    /// Note that it doesn't own it, you'll need to destroy the object yourself.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ObjectPointer : public Object
    {
        COFFEE_Type(ObjectPointer);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ObjectPointer();
        ~ObjectPointer();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetObject(Object* object);
        Object* GetObject();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Object* _Object;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ObjectPointer);
}
}
#endif
