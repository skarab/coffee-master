#ifndef _COFFEE_BASIC_CONTAINER_VECTOR_H_
#define _COFFEE_BASIC_CONTAINER_VECTOR_H_

#include "coffee_includes.h"
#include "kernel/basic/container/basic_container.h"
#include "kernel/basic/container/vector/basic_vector_template.h"

namespace coffee
{
namespace basic
{
    //--------------------------------------------------------------------------------------------//
    /// Array supporting objects, takes care of calling constructors/destructors
    //--------------------------------------------------------------------------------------------//
    template< typename type > \
    class COFFEE_TEMPLATE_API Vector : public Container< type >
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Vector();
        Vector(const Vector<type>& vector);
        virtual ~Vector();

        //-OPERATORS------------------------------------------------------------------------------//

        const type& operator [](uint32 item_index) const;
        type& operator [](uint32 item_index);
        Vector<type>& operator = (const Vector< type > & array);

        //-ACCESSORS------------------------------------------------------------------------------//

        uint32 GetReservedSize() const;

        //-QUERIES--------------------------------------------------------------------------------//

        virtual uint32 FindItem(const type& item) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual uint32 Add(uint32 item_index = NONE);
        virtual uint32 AddItem(type item, uint32 item_index = NONE);
        virtual void Remove(uint32 item_index = NONE);
        virtual void RemoveItem(type item);
        virtual void Resize(uint32 item_count);
        void Reserve(uint32 item_count);
        virtual void Clear();
        virtual void Erase();

        virtual const void * GetLinearBuffer() const;
        virtual void * GetLinearBuffer();
        virtual const void * GetItemPointer(uint32 item_index) const;
        virtual void * GetItemPointer(uint32 item_index);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        type * _ItemArray;
        uint32 _ReservedSize;
    };

    #include "kernel/basic/container/vector/basic_vector.hpp"
}
}
#endif
