
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    template< typename type >
    TreeNode< type >::TreeNode() :
        _Parent(NULL),
        _Children()
    {
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    TreeNode< type >::~TreeNode()
    {
        COFFEE_Assert(!HasParent() && !HasChildren(), core::ERROR_CODE_IncorrectUsage,
            "Call Destroy() instead of delete when using TreeNode.");
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    template< typename type >
    const type& TreeNode< type >::GetParent() const
    {
        return *_Parent;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    type& TreeNode< type >::GetParent()
    {
        return *_Parent;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    const type& TreeNode< type >::GetChild(uint32 index) const
    {
        return *_Children[index];
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    type& TreeNode< type >::GetChild(uint32 index)
    {
        return *_Children[index];
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    uint32 TreeNode< type >::GetChildCount() const
    {
        return _Children.GetSize();
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    const type& TreeNode< type >::GetRoot() const
    {
        const type* root = this;
        while (root->_Parent!=NULL) root = root->_Parent;
        return *root;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    type& TreeNode< type >::GetRoot()
    {
        type* root = static_cast<type*>(this);
        while (root->_Parent!=NULL) root = root->_Parent;
        return *root;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    template< typename type >
    bool TreeNode< type >::HasParent() const
    {
        return _Parent!=NULL;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    bool TreeNode< type >::HasChildren() const
    {
        return GetChildCount()>0;
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    uint32 TreeNode< type >::GetIndex()
    {
        if (!HasParent())
            return NONE;
        return _Parent->_Children.FindItem(static_cast<type*>(this));
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    bool TreeNode< type >::IsChild(type& object) const
    {
        for (uint32 i=0 ; i<GetChildCount() ; ++i)
        {
            if (&object==_Children[i] || _Children[i]->IsChild(object))
                return true;
        }
        return false;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    template< typename type >
    void TreeNode< type >::Attach(type& child, uint32 child_index)
    {
        if (child.HasParent())
            child.Detach();
        child._Parent = static_cast<type*>(this);
        _Children.AddItem(&child, child_index);
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void TreeNode< type >::Detach()
    {
        if (HasParent())
        {
            _Parent->_Children.Remove(GetIndex());
            _Parent = NULL;
        }
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void TreeNode< type >::Destroy()
    {
        Detach();
        while (HasChildren())
            GetChild(GetChildCount()-1).Destroy();
        COFFEE_Delete(this);
    }

    //--------------------------------------------------------------------------------------------//

    template< typename type >
    void TreeNode< type >::PostSerialize(storage::MODE mode)
    {
        if (mode==storage::MODE_Input)
        {
            for (uint32 i=0 ; i<GetChildCount() ; ++i)
                _Children[i]->_Parent = static_cast<type*>(this);
        }
    }

