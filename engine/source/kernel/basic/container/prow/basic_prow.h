#ifndef _COFFEE_BASIC_CONTAINER_PROW_H_
#define _COFFEE_BASIC_CONTAINER_PROW_H_

#include "coffee_includes.h"
#include "kernel/basic/container/basic_container.h"
#include "kernel/basic/container/prow/basic_prow_template.h"

namespace coffee
{
namespace basic
{
    //--------------------------------------------------------------------------------------------//
    /// Specialized for pointers array, it mays own the ptr (automatic deletion)
    //--------------------------------------------------------------------------------------------//
    template< typename type, bool it_is_owner > \
    class COFFEE_TEMPLATE_API Prow : public Container< type >
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Prow();
        Prow(const Prow<type, it_is_owner>& prow);
        ~Prow();

        //-OPERATORS------------------------------------------------------------------------------//

        const type& operator [](uint32 item_index) const;
        type& operator [](uint32 item_index);
        Prow<type, it_is_owner>& operator = (const Prow< type, it_is_owner > & array);

        //-ACCESSORS------------------------------------------------------------------------------//

        uint32 GetReservedSize() const;

        //-QUERIES--------------------------------------------------------------------------------//

        uint32 FindItem(const type& item) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        uint32 Add(uint32 item_index = NONE);
        uint32 AddItem(type item, uint32 item_index = NONE);
        void Remove(uint32 item_index = NONE);
        void RemoveItem(type item);
        void Resize(uint32 item_count);
        void Reserve(uint32 item_count);
        void Clear();
        void Erase();

        const void * GetLinearBuffer() const;
        void * GetLinearBuffer();
        const void * GetItemPointer(uint32 item_index) const;
        void * GetItemPointer(uint32 item_index);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _HardDeleteItem(uint32 item_index);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        type * _ItemArray;
        uint32 _ReservedSize;
    };

    #include "kernel/basic/container/prow/basic_prow.hpp"
}
}
#endif
