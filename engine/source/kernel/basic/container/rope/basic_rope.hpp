
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    template< class type, uint32 block_size >
    Rope< type, block_size >::Rope() :
        _BlockArray(NULL),
        _BlockCount(0),
        _ReservedSize(0)
    {
    }

    //--------------------------------------------------------------------------------------------//

    template< class type, uint32 block_size >
    Rope< type, block_size >::Rope(const Rope<type, block_size>& rope) :
        _BlockArray(NULL),
        _BlockCount(0),
        _ReservedSize(0)
    {
        this->operator=(rope);
    }

    //--------------------------------------------------------------------------------------------//

    template< class type, uint32 block_size >
    Rope< type, block_size >::~Rope()
    {
        Erase();
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    template< class type, uint32 block_size >
    const type& Rope< type, block_size >::operator [](uint32 item_index) const
    {
        uint32 block_index, element_index;

        _GetBlockIndexFromIndex(block_index, element_index, item_index);

        return _BlockArray[ block_index ][ element_index ];
    }

    //--------------------------------------------------------------------------------------------//

    template< class type, uint32 block_size >
    type& Rope< type, block_size >::operator [](uint32 item_index)
    {
        uint32 block_index, element_index;

        _GetBlockIndexFromIndex(block_index, element_index, item_index);

        return _BlockArray[ block_index ][ element_index ];
    }

    //--------------------------------------------------------------------------------------------//

    template< class type, uint32 block_size >
    Rope<type, block_size>& Rope< type, block_size >::operator = (const Rope< type, block_size > & array)
    {
        Resize(array.GetSize());
        for(uint32 block_index = 0 ; block_index < array._BlockCount ; block_index ++)
            COFFEE_Copy(_BlockArray[ block_index ], array._BlockArray[ block_index ], block_size * sizeof(type));
        return *this;
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    template< class type, uint32 block_size >
    uint32 Rope< type, block_size >::GetReservedSize() const
    {
        return _ReservedSize;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    template< class type, uint32 block_size >
    uint32 Rope< type, block_size >::FindItem(const type& item) const
    {
        for (uint32 item_index=0 ; item_index<this->GetSize() ; ++item_index)
        {
            if (this->operator[](item_index)==item)
                return item_index;
        }
        return NONE;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    template< class type, uint32 block_size >
    uint32 Rope< type, block_size >::Add(uint32 item_index)
    {
        Resize(this->GetSize()+1);
        if (item_index!=NONE)
        {
            for (uint32 i=this->GetSize()-1 ; i>item_index ; --i)
                (*this)[i] = (*this)[i-1];
            return item_index;
        }
        return this->GetSize()-1;
    }

    //--------------------------------------------------------------------------------------------//

    template< class type, uint32 block_size >
    uint32 Rope< type, block_size >::AddItem(type item, uint32 item_index)
    {
        uint32 block_index, element_index;
        item_index = Add(item_index);
        _GetBlockIndexFromIndex(block_index, element_index, item_index);
        _BlockArray[block_index][element_index] = item;
        return item_index;
    }

    //--------------------------------------------------------------------------------------------//

    template< class type, uint32 block_size >
    void Rope< type, block_size >::Remove(uint32 item_index)
    {
        Resize(this->GetSize() - 1);

        if (item_index!=NONE)
        {
            uint32 item_position;

            for(item_position = item_index ; item_position < this->GetSize() ; ++item_position)
                (*this)[item_position] = (*this)[item_position+1];
        }
    }

    //--------------------------------------------------------------------------------------------//

    template< class type, uint32 block_size >
    void Rope< type, block_size >::RemoveItem(type item)
    {
        Remove(FindItem(item));
    }

    //--------------------------------------------------------------------------------------------//

    template< class type, uint32 block_size >
    void Rope< type, block_size >::Resize(uint32 item_count)
    {
        if(item_count > _ReservedSize)
            Reserve(item_count);

        meta::Array::Resize(item_count);
    }

    //--------------------------------------------------------------------------------------------//

    template< class type, uint32 block_size >
    void Rope< type, block_size >::Reserve(uint32 item_count)
    {
        uint32 block_count, old_block_count;
        uint32 block_index;

        block_count = (item_count / block_size) + 1;

        if(block_count > _BlockCount)
        {
            old_block_count = _BlockCount;
            _BlockArray = (type **) COFFEE_Reallocate(_BlockArray, sizeof(type *) * block_count);
            _BlockCount = block_count;

            for(block_index = old_block_count ; block_index < block_count ; block_index ++)
                _BlockArray[ block_index ] = (type *) COFFEE_Allocate(sizeof(type) * block_size);

            _ReservedSize = _BlockCount * block_size;
        }
    }

    //--------------------------------------------------------------------------------------------//

    template< class type, uint32 block_size >
    void Rope< type, block_size >::Clear()
    {
        meta::Array::Clear();
    }

    //--------------------------------------------------------------------------------------------//

    template< class type, uint32 block_size >
    void Rope< type, block_size >::Erase()
    {
        uint32 block_index;

        Clear();

        for(block_index = 0 ; block_index < _BlockCount ; block_index ++)
            COFFEE_Free(_BlockArray[ block_index ]);

        COFFEE_Free(_BlockArray);
        _BlockArray = NULL;
        _BlockCount = 0;
        _ReservedSize = 0;
    }

    //--------------------------------------------------------------------------------------------//

    template< class type, uint32 block_size >
    const void * Rope< type, block_size >::GetLinearBuffer() const
    {
        return NULL;
    }

    //--------------------------------------------------------------------------------------------//

    template< class type, uint32 block_size >
    void * Rope< type, block_size >::GetLinearBuffer()
    {
        return NULL;
    }

    //--------------------------------------------------------------------------------------------//

    template< class type, uint32 block_size >
    const void * Rope< type, block_size >::GetItemPointer(uint32 item_index) const
    {
        return &(*this)[ item_index ];
    }

    //--------------------------------------------------------------------------------------------//

    template< class type, uint32 block_size >
    void * Rope< type, block_size >::GetItemPointer(uint32 item_index)
    {
        return &(*this)[ item_index ];
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    template< class type, uint32 block_size >
    void Rope< type, block_size >::_GetBlockIndexFromIndex(uint32 & block_index, uint32 & element_index, uint32 item_index) const
    {
        block_index = item_index / block_size;
        element_index = item_index - (block_index * block_size);
    }

