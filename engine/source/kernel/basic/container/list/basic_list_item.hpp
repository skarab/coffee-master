
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    template< typename type >
    ListItem< type >::ListItem() :
        _Next(NULL),
        _Previous(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    ListItem< type >::~ListItem()
    {
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    template< typename type >
    ListItem< type >& ListItem< type >::operator = (const ListItem< type > & item)
    {
        _Item = item.Get();
        _Next = item._Next;
        _Previous = item._Previous;
        return *this;
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    template< typename type >
    void ListItem< type >::Set(type item)
    {
        _Item = item;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    const type& ListItem< type >::Get() const
    {
        return _Item;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    type& ListItem< type >::Get()
    {
        return _Item;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    template< typename type >
    void ListItem< type >::SetNext(ListItem< type > * next)
    {
        _Next = next;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    const ListItem< type > * ListItem< type >::GetNext() const
    {
        return _Next;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    ListItem< type > * ListItem< type >::GetNext()
    {
        return _Next;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void ListItem< type >::SetPrevious(ListItem< type > * previous)
    {
        _Previous = previous;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    const ListItem< type > * ListItem< type >::GetPrevious() const
    {
        return _Previous;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    ListItem< type > * ListItem< type >::GetPrevious()
    {
        return _Previous;
    }

