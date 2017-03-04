#ifndef _COFFEE_META_ARRAY_H_
#define _COFFEE_META_ARRAY_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_object.h"
#include "kernel/meta/type/class/meta_class_serializer.h"

namespace coffee
{
namespace meta
{
    //--------------------------------------------------------------------------------------------//
    /// Serializable array base class
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Array : public Object
    {
        friend class ClassSerializer;

        COFFEE_Type(Array);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Array();
        virtual ~Array();

        //-OPERATORS------------------------------------------------------------------------------//

        Array& operator = (const Array& array);

        //-ACCESSORS------------------------------------------------------------------------------//

        uint32 GetSize() const;
        virtual const void* GetLinearBuffer() const;
        virtual void* GetLinearBuffer();
        virtual const void* GetItemPointer(uint32 item_index) const;
        virtual void* GetItemPointer(uint32 item_index);

        //-QUERIES--------------------------------------------------------------------------------//

        bool IsEmpty() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual uint32 Add(uint32 item_index = NONE);
        virtual void Remove(uint32 item_index = NONE);
        virtual void Resize(uint32 item_count);
        virtual void Clear();
        virtual void Erase();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        uint32 _Size;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Array);
}
}
#endif
