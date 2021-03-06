#ifndef _COFFEE_BASIC_CONTAINER_LIST_H_
#define _COFFEE_BASIC_CONTAINER_LIST_H_

#include "coffee_includes.h"
#include "kernel/basic/container/basic_container.h"
#include "kernel/basic/container/list/basic_list_template.h"
#include "kernel/basic/container/list/basic_list_item_template.h"
#include "kernel/basic/container/list/basic_list_item.h"

namespace coffee
{
namespace basic
{
    //--------------------------------------------------------------------------------------------//
    /// Double linked list
    //--------------------------------------------------------------------------------------------//
    template< typename type > \
    class COFFEE_TEMPLATE_API List : public Container< type >
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        List();
        List(const List<type>& list);
        virtual ~List();

        //-OPERATORS------------------------------------------------------------------------------//

        const type& operator [](uint32 item_index) const;
        type& operator [](uint32 item_index);
        List<type>& operator = (const List< type >& array);
		
        //-QUERIES--------------------------------------------------------------------------------//

        virtual uint32 FindItem(const type& item) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void AddFirst(type item);
        void AddLast(type item);
        void InsertBefore(type item, const type target_item);
        void InsertAfter(type item, const type target_item);
        void RemoveFirst();
        void RemoveLast();

        virtual uint32 Add(uint32 item_index = NONE);
        virtual uint32 AddItem(type item, uint32 item_index = NONE);
        virtual void Remove(uint32 item_index = NONE);
        virtual void RemoveItem(type item);
        virtual void Resize(uint32 item_count);
        virtual void Clear();
        virtual void Erase();

        virtual const void * GetLinearBuffer() const;
        virtual void * GetLinearBuffer();
        virtual const void * GetItemPointer(uint32 item_index) const;
        virtual void * GetItemPointer(uint32 item_index);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        ListItem< type > * _FirstItem;
        ListItem< type > * _LastItem;
    };

    #include "kernel/basic/container/list/basic_list.hpp"
}
}
#endif
