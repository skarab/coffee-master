
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    template< typename type >
    List< type >::List() :
        _FirstItem(NULL),
        _LastItem(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

	template< typename type >
    List< type >::List(const List<type>& list) :
        _FirstItem(NULL),
        _LastItem(NULL)
    {
		this->operator=(list);
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    List< type >::~List()
    {
        Erase();
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    template< typename type >
    const type& List< type >::operator [] (uint32 item_index) const
    {
        uint32 current_index = 0;
        ListItem< type > * item = _FirstItem;

        while(current_index != item_index)
        {
            item = item->GetNext();
            current_index ++;
        }

        return item->Get();
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    type& List< type >::operator [] (uint32 item_index)
    {
        uint32 current_index = 0;
        ListItem< type > * item = _FirstItem;

        while(current_index != item_index)
        {
            item = item->GetNext();
            current_index ++;
        }

        return item->Get();
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    List<type>& List< type >::operator = (const List< type > & array)
    {
        Erase();
        for(uint32 item_index = 0 ; item_index < array.GetSize() ; item_index ++)
            AddItem(array[ item_index ]);
        return *this;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    template< typename type >
    uint32 List< type >::FindItem(const type& item) const
    {
        uint32 item_index = 0;
        ListItem< type > * list_item = _FirstItem;

        while (list_item!=NULL)
        {
            if (list_item->Get()==item)
                return item_index;
            list_item = list_item->GetNext();
            ++item_index;
        }
        return NONE;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    template< typename type >
    void List< type >::AddFirst(type item)
    {
        ListItem< type > * list_item;

        meta::Array::Add();

        list_item = COFFEE_New(ListItem<type>);
        list_item->Set(item);

        if(_FirstItem != NULL)
        {
            list_item->SetNext(_FirstItem);
            _FirstItem->SetPrevious(list_item);

            if(_LastItem == NULL)
                _LastItem = _FirstItem;
        }

        _FirstItem = list_item;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void List< type >::AddLast(type item)
    {
        ListItem< type > * list_item;

        meta::Array::Add();

        list_item = COFFEE_New(ListItem<type>);
        list_item->Set(item);

        if(_FirstItem == NULL)
        {
            _FirstItem = list_item;
        }
        else
        {
            ListItem< type > * previous_item = _LastItem;

            if(previous_item == NULL)
                previous_item = _FirstItem;

            list_item->SetPrevious(previous_item);
            previous_item->SetNext(list_item);
            _LastItem = list_item;
        }
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void List< type >::InsertBefore(type item, const type target_item)
    {
        AddItem(item, FindItem(target_item));
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void List< type >::InsertAfter(type item, const type target_item)
    {
        AddItem(item, FindItem(target_item) + 1);
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void List< type >::RemoveFirst()
    {
        ListItem< type > * item = _FirstItem;

        meta::Array::Remove();

        _FirstItem = item->GetNext();

        if(_FirstItem != NULL)
        {
            _FirstItem->SetPrevious(NULL);

            if(_FirstItem->GetNext() == NULL)
                _LastItem = NULL;
        }

        COFFEE_Delete(item);
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void List< type >::RemoveLast()
    {
        ListItem< type > * item = _LastItem;

        meta::Array::Remove();

        if(item == NULL)
        {
            item = _FirstItem;
            _FirstItem = NULL;
        }

        _LastItem = item->GetPrevious();

        if(_LastItem != NULL)
        {
            _LastItem->SetNext(NULL);

            if(_LastItem->GetPrevious() == NULL)
            {
                _FirstItem = _LastItem;
                _LastItem = NULL;
            }
        }

        COFFEE_Delete(item);
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    uint32 List< type >::Add(uint32 item_index)
    {
        COFFEE_Error(core::ERROR_CODE_IncorrectUsage, "Unsupported");
        return NONE;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    uint32 List< type >::AddItem(type item, uint32 item_index)
    {
        if(item_index == 0)
        {
            AddFirst(item);

            return 0;
        }
        else if(item_index == NONE || item_index >= this->GetSize())
        {
            AddLast(item);

            return this->GetSize() - 1;
        }

        uint32 current_index = 0;
        ListItem< type > * list_item;
        ListItem< type > * next_item(_FirstItem);

        meta::Array::Add(item_index);
        list_item = COFFEE_New(ListItem<type>);
        list_item->Set(item);

        while(current_index != item_index)
        {
            next_item = next_item->GetNext();
            current_index ++;
        }

        list_item->SetPrevious(next_item->GetPrevious());
        list_item->SetNext(next_item);
        next_item->SetPrevious(list_item);

        if(list_item->GetPrevious() == NULL)
        {
            _FirstItem = list_item;

            if(_LastItem == NULL)
                _LastItem = next_item;
        }
        else
        {
            list_item->GetPrevious()->SetNext(list_item);
        }

        return item_index;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void List< type >::Remove(uint32 item_index)
    {
        if(item_index == 0)
        {
            RemoveFirst();
        }
        else if(item_index == NONE || item_index >= this->GetSize() - 1)
        {
            RemoveLast();
        }
        else
        {
            uint32 current_index = 0;
            ListItem< type > * item = _FirstItem;

            meta::Array::Remove();

            while(current_index != item_index)
            {
                item = item->GetNext();
                current_index ++;
            }

            item->GetPrevious()->SetNext(item->GetNext());
            item->GetNext()->SetPrevious(item->GetPrevious());

            COFFEE_Delete(item);
        }
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void List< type >::RemoveItem(type item)
    {
        Remove(FindItem(item));
    }

    template< typename type >
    void List< type >::Resize(uint32 item_count)
    {
        if(item_count > this->GetSize())
        {
            while(this->GetSize() < item_count)
                AddLast(type());
        }
        else
        {
            while(this->GetSize() > item_count)
                RemoveLast();
        }
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void List< type >::Clear()
    {
        while(this->GetSize() > 0)
            RemoveLast();
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void List< type >::Erase()
    {
        Clear();
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    const void * List< type >::GetLinearBuffer() const
    {
        return NULL;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void * List< type >::GetLinearBuffer()
    {
        return NULL;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    const void * List< type >::GetItemPointer(uint32 item_index) const
    {
        return (const void *) &(*this)[ item_index ];
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void * List< type >::GetItemPointer(uint32 item_index)
    {
        return (void *) &(*this)[ item_index ];
    }

