
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    template< typename type, bool it_is_owner >
    Prow< type, it_is_owner >::Prow() :
        _ItemArray(NULL),
        _ReservedSize(0)
    {
    }

	//--------------------------------------------------------------------------------------------//

	template< typename type, bool it_is_owner >
    Prow< type, it_is_owner >::Prow(const Prow<type, it_is_owner>& prow) :
        _ItemArray(NULL),
        _ReservedSize(0)
    {
        this->operator=(prow);
    }
        
    //--------------------------------------------------------------------------------------------//

    template< typename type, bool it_is_owner >
    Prow< type, it_is_owner >::~Prow()
    {
        Erase();
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    template< typename type, bool it_is_owner >
    const type& Prow< type, it_is_owner >::operator [] (uint32 item_index) const
    {
        return _ItemArray[ item_index ];
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type, bool it_is_owner >
    type& Prow< type, it_is_owner >::operator [] (uint32 item_index)
    {
        return _ItemArray[ item_index ];
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type, bool it_is_owner >
    Prow<type, it_is_owner>& Prow< type, it_is_owner >::operator = (const Prow< type, it_is_owner > & array)
    {
        meta::Array::operator =(array);
        COFFEE_Copy(_ItemArray, array._ItemArray, this->GetSize() * sizeof(type));
        return *this;
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    template< typename type, bool it_is_owner >
    uint32 Prow< type, it_is_owner >::GetReservedSize() const
    {
        return _ReservedSize;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    template< typename type, bool it_is_owner >
    uint32 Prow< type, it_is_owner >::FindItem(const type& item) const
    {
        for (uint32 item_index=0 ; item_index<this->GetSize() ; ++item_index)
        {
            if (_ItemArray[item_index]==item)
                return item_index;
        }
        return NONE;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    template< typename type, bool it_is_owner >
    uint32 Prow< type, it_is_owner >::Add(uint32 item_index)
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

        _ItemArray[ item_index ] = NULL;

        return item_index;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type, bool it_is_owner >
    uint32 Prow< type, it_is_owner >::AddItem(type item, uint32 item_index)
    {
        item_index = Add(item_index);
        _ItemArray[ item_index ] = item;

        return item_index;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type, bool it_is_owner >
    void Prow< type, it_is_owner >::Remove(uint32 item_index)
    {
        uint32 index;

        if(item_index == NONE)
            item_index = this->GetSize() - 1;

        if(it_is_owner && _ItemArray[ item_index ] != NULL)
            _HardDeleteItem(item_index);

        meta::Array::Remove(item_index);

        for(index = item_index ; index < this->GetSize() ; index ++)
            _ItemArray[ index ] = _ItemArray[ index + 1 ];

        _ItemArray[ this->GetSize() ] = NULL;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type, bool it_is_owner >
    void Prow< type, it_is_owner >::RemoveItem(type item)
    {
        uint32 i = FindItem(item);
        if (i!=NONE) Remove(i);
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type, bool it_is_owner >
    void Prow< type, it_is_owner >::Resize(uint32 item_count)
    {
        if(it_is_owner)
        {
            if(item_count > GetReservedSize())
            {
                Reserve(item_count);
            }
            else if(item_count < this->GetSize())
            {
                uint32 item_index;

                for(item_index = item_count ; item_index < this->GetSize() ; item_index ++)
                {
                    if(_ItemArray[ item_index ] != NULL)
                    {
                        _HardDeleteItem(item_index);
                        _ItemArray[ item_index ] = NULL;
                    }
                }
            }

            meta::Array::Resize(item_count);
        }
        else
        {
            if(item_count > GetReservedSize())
            {
                Reserve(item_count);
            }
            else if(item_count < this->GetSize())
            {
                uint32 item_index;

                for(item_index = item_count ; item_index < this->GetSize() ; item_index ++)
                {
                    if(_ItemArray[ item_index ] != NULL)
                        _ItemArray[ item_index ] = NULL;
                }
            }

            meta::Array::Resize(item_count);
        }
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type, bool it_is_owner >
    void Prow< type, it_is_owner >::Reserve(uint32 item_count)
    {
        if(item_count <= _ReservedSize)
            return;

        _ReservedSize = item_count;
        _ItemArray = (type *) COFFEE_Reallocate(_ItemArray, _ReservedSize * sizeof(type));
        COFFEE_Set(&_ItemArray[ this->GetSize() ], NULL, (_ReservedSize - this->GetSize()) * sizeof(type));
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type, bool it_is_owner >
    void Prow< type, it_is_owner >::Clear()
    {
        if(it_is_owner)
        {
            uint32 item_index;

            for(item_index = 0 ; item_index < this->GetSize() ; item_index ++)
            {
                if(_ItemArray[ item_index ] != NULL)
                {
                    _HardDeleteItem(item_index);
                    _ItemArray[ item_index ] = NULL;
                }
            }

            meta::Array::Clear();
        }
        else
        {
            COFFEE_Set(_ItemArray, NULL, this->GetSize() * sizeof(type));
            meta::Array::Clear();
        }
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type, bool it_is_owner >
    void Prow< type, it_is_owner >::Erase()
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

    template< typename type, bool it_is_owner >
    const void * Prow< type, it_is_owner >::GetLinearBuffer() const
    {
        return (const void *) _ItemArray;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type, bool it_is_owner >
    void * Prow< type, it_is_owner >::GetLinearBuffer()
    {
        return (void *) _ItemArray;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type, bool it_is_owner >
    const void * Prow< type, it_is_owner >::GetItemPointer(uint32 item_index) const
    {
        return (const void *) &_ItemArray[ item_index ];
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type, bool it_is_owner >
    void * Prow< type, it_is_owner >::GetItemPointer(uint32 item_index)
    {
        return (void *) &_ItemArray[ item_index ];
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    template< typename type, bool it_is_owner >
    void Prow< type, it_is_owner >::_HardDeleteItem(uint32 item_index)
    {
        COFFEE_Delete(_ItemArray[ item_index ]);
    }

    //--------------------------------------------------------------------------------------------//

    template<>
    COFFEE_TEMPLATE_API void Prow< void*, false >::_HardDeleteItem(uint32 item_index);

