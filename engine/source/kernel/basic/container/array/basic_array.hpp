
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    template< typename type >
    Array< type >::Array() :
        _ItemArray(NULL),
        _ReservedSize(0)
    {
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    Array< type >::Array(const Array<type>& array) :
        _ItemArray(NULL),
        _ReservedSize(0)
    {
        this->operator=(array);
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    Array< type >::~Array()
    {
        Erase();
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    template< typename type >
    const type& Array< type >::operator [] (uint32 item_index) const
    {
        return _ItemArray[ item_index ];
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    type& Array< type >::operator [] (uint32 item_index)
    {
        return _ItemArray[ item_index ];
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    Array<type>& Array< type >::operator = (const Array< type > & array)
    {
        meta::Array::operator =(array);
        COFFEE_Copy(_ItemArray, array._ItemArray, this->GetSize() * sizeof(type));
        return *this;
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    template< typename type >
    uint32 Array< type >::GetReservedSize() const
    {
        return _ReservedSize;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    template< typename type >
    uint32 Array< type >::FindItem(const type& item) const
    {
        for (uint32 item_index=0 ; item_index<this->GetSize() ; ++item_index)
        {
            if (_ItemArray[item_index]==item)
                return item_index;
        }
        return NONE;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    template< typename type >
    uint32 Array< type >::Add(uint32 item_index)
    {
        uint32 index;

        if(item_index == NONE)
            Reserve(this->GetSize() + this->GetSize() / 4 + 1);

        item_index = meta::Array::Add(item_index);

        if(this->GetSize() <= GetReservedSize())
        {
            for(index = this->GetSize() - 1 ; index > item_index ; index --)
                _ItemArray[ index ] = _ItemArray[ index - 1 ];
        }
        else
        {
            type * item_array = _ItemArray;

            _ReservedSize = this->GetSize() + this->GetSize() / 4 + 1;
            _ItemArray = (type *) COFFEE_Allocate(_ReservedSize * sizeof(type));

            if(item_array != NULL)
            {
                COFFEE_Copy(_ItemArray, item_array, item_index * sizeof(type));
                COFFEE_Copy(_ItemArray + item_index + 1, item_array + item_index, (this->GetSize() - item_index - 1) * sizeof(type));
                COFFEE_Free(item_array);
            }
        }

        return item_index;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    uint32 Array< type >::AddItem(type item, uint32 item_index)
    {
        item_index = Add(item_index);
        _ItemArray[ item_index ] = item;

        return item_index;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void Array< type >::Remove(uint32 item_index)
    {
        meta::Array::Remove(item_index);

        if (!this->IsEmpty() && item_index!=NONE)
        {
            for (uint32 index=item_index ; index<this->GetSize() ; ++index)
                _ItemArray[index] = _ItemArray[index+1];
        }
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void Array< type >::RemoveItem(type item)
    {
        Remove(FindItem(item));
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void Array< type >::Resize(uint32 item_count)
    {
        if(item_count > GetReservedSize())
            Reserve(item_count+item_count/4+1);

        meta::Array::Resize(item_count);
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void Array< type >::Reserve(uint32 item_count)
    {
        if(item_count <= _ReservedSize)
            return;

        _ReservedSize = item_count;
        _ItemArray = (type *) COFFEE_Reallocate(_ItemArray, _ReservedSize * sizeof(type));
        COFFEE_Set(&_ItemArray[ this->GetSize() ], NULL, (_ReservedSize - this->GetSize()) * sizeof(type) );
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void Array< type >::Clear()
    {
        meta::Array::Clear();
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void Array< type >::Erase()
    {
        if(_ItemArray != NULL)
        {
            Clear();
            COFFEE_Free(_ItemArray);
            _ItemArray = NULL;
            _ReservedSize = 0;
        }
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    const void * Array< type >::GetLinearBuffer() const
    {
        return (const void *) _ItemArray;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void * Array< type >::GetLinearBuffer()
    {
        return (void *) _ItemArray;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    const void * Array< type >::GetItemPointer(uint32 item_index) const
    {
        return (const void *) &_ItemArray[ item_index ];
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void * Array< type >::GetItemPointer(uint32 item_index)
    {
        return (void *) &_ItemArray[ item_index ];
    }

