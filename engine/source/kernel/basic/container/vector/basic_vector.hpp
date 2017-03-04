
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    template< typename type >
    Vector< type >::Vector() :
        _ItemArray(NULL),
        _ReservedSize(0)
    {
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    Vector< type >::Vector(const Vector<type>& vector) :
        _ItemArray(NULL),
        _ReservedSize(0)
    {
        this->operator=(vector);
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    Vector< type >::~Vector()
    {
        Erase();
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    template< typename type >
    const type& Vector< type >::operator [] (uint32 item_index) const
    {
        return _ItemArray[ item_index ];
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    type& Vector< type >::operator [] (uint32 item_index)
    {
        return _ItemArray[ item_index ];
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    Vector<type>& Vector< type >::operator = (const Vector< type > & array)
    {
        meta::Array::operator =(array);
        for(uint32 item_index = 0 ; item_index < this->GetSize() ; item_index ++)
        {
            _ItemArray[ item_index ] = array._ItemArray[ item_index ];
        }
        return *this;
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    template< typename type >
    uint32 Vector< type >::GetReservedSize() const
    {
        return _ReservedSize;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    template< typename type >
    uint32 Vector< type >::FindItem(const type& item) const
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
    uint32 Vector< type >::Add(uint32 item_index)
    {
       if (item_index==NONE)
            Reserve(this->GetSize()+this->GetSize()/4+1);
        item_index = meta::Array::Add(item_index);

        if (this->GetSize()<=GetReservedSize())
        {
            for (int32 i=(int32)this->GetSize()-1 ; i>(int32)item_index ; --i)
                _ItemArray[i] = _ItemArray[i-1];
        }
        else
        {
            type* item_array = _ItemArray;
            _ReservedSize = this->GetSize()+this->GetSize()/4+1;
            _ItemArray = COFFEE_NewArray(type, _ReservedSize);
            
            if (item_array!=NULL)
            {
                uint32 i;
                for (i=0 ; i<item_index ; ++i)
                    _ItemArray[i] = item_array[i];
                for (i=i+1 ; i<this->GetSize()-1 ; ++i)
                    _ItemArray[i] = item_array[i-1];            
                COFFEE_DeleteArray(item_array);
            }
        }
        return item_index;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    uint32 Vector< type >::AddItem(type item, uint32 item_index)
    {
        item_index = Add(item_index);
        _ItemArray[ item_index ] = item;

        return item_index;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void Vector< type >::Remove(uint32 item_index)
    {
        meta::Array::Remove(item_index);

        if (!this->IsEmpty() && item_index!=NONE)
        {
            for(uint32 index=item_index ; index<this->GetSize() ; ++index)
                _ItemArray[index] = _ItemArray[index+1];
        }
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void Vector< type >::RemoveItem(type item)
    {
        Remove(FindItem(item));
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void Vector< type >::Resize(uint32 item_count)
    {
        if (item_count>GetReservedSize())
            Reserve(item_count+item_count/4+1);

        meta::Array::Resize(item_count);
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void Vector< type >::Reserve(uint32 item_count)
    {
        if (item_count<=_ReservedSize)
            return;
        
        _ReservedSize = item_count;
        type* item_array = _ItemArray;
        _ItemArray = COFFEE_NewArray(type, _ReservedSize);

        for (uint32 i=0 ; i<this->GetSize() ; ++i)
            _ItemArray[i] = item_array[i];

        if (item_array!=NULL)
            COFFEE_DeleteArray(item_array);
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void Vector< type >::Clear()
    {
        meta::Array::Clear();
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void Vector< type >::Erase()
    {
        if (_ItemArray!=NULL)
        {
            Clear();
            COFFEE_DeleteArray(_ItemArray);
            _ItemArray = NULL;
            _ReservedSize = 0;
        }
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    const void * Vector< type >::GetLinearBuffer() const
    {
        return (const void *) _ItemArray;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void * Vector< type >::GetLinearBuffer()
    {
        return (void *) _ItemArray;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    const void * Vector< type >::GetItemPointer(uint32 item_index) const
    {
        return (const void *) &_ItemArray[ item_index ];
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void * Vector< type >::GetItemPointer(uint32 item_index)
    {
        return (void *) &_ItemArray[ item_index ];
    }

