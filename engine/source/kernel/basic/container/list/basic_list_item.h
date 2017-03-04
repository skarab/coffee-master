#ifndef _COFFEE_BASIC_CONTAINER_LIST_ITEM_H_
#define _COFFEE_BASIC_CONTAINER_LIST_ITEM_H_

#include "coffee_includes.h"
#include "kernel/basic/container/list/basic_list_item_template.h"

namespace coffee
{
namespace basic
{
    //--------------------------------------------------------------------------------------------//
    /// List item
    //--------------------------------------------------------------------------------------------//
    template< typename type > \
    class COFFEE_TEMPLATE_API ListItem
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ListItem();
        virtual ~ListItem();

        //-OPERATORS------------------------------------------------------------------------------//

        ListItem< type >& operator = (const ListItem< type > & item);

        //-ACCESSORS------------------------------------------------------------------------------//

        void Set(type item);
        const type& Get() const;
        type& Get();
        void SetNext(ListItem< type > * next);
        const ListItem< type > * GetNext() const;
        ListItem< type > * GetNext();
        void SetPrevious(ListItem< type > * previous);
        const ListItem< type > * GetPrevious() const;
        ListItem< type > * GetPrevious();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        type _Item;
        ListItem< type > * _Next;
        ListItem< type > * _Previous;
    };

    #include "kernel/basic/container/list/basic_list_item.hpp"
}
}
#endif
