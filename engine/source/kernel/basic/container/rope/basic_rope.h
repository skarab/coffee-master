#ifndef _COFFEE_BASIC_CONTAINER_ROPE_H_
#define _COFFEE_BASIC_CONTAINER_ROPE_H_

#include "coffee_includes.h"
#include "kernel/basic/container/basic_container.h"
#include "kernel/basic/container/rope/basic_rope_template.h"

namespace coffee
{
namespace basic
{
    //--------------------------------------------------------------------------------------------//
    /// Block managed, it allows to store big array of scalar/pointer/structs
    //--------------------------------------------------------------------------------------------//
    template< class type, uint32 block_size > \
    class COFFEE_TEMPLATE_API Rope : public Container< type >
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Rope();
        Rope(const Rope<type, block_size>& rope);
        virtual ~Rope();

        //-OPERATORS------------------------------------------------------------------------------//

        const type& operator [](uint32 item_index) const;
        type& operator [](uint32 item_index);
        Rope<type, block_size>& operator = (const Rope< type, block_size > & array);

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

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _GetBlockIndexFromIndex(uint32 & block_index, uint32 & element_index, uint32 item_index) const;

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        type ** _BlockArray;
        uint32 _BlockCount;
        uint32 _ReservedSize;
    };

    #include "kernel/basic/container/rope/basic_rope.hpp"
}
}
#endif
