#ifndef _COFFEE_BASIC_TREE_NODE_H_
#define _COFFEE_BASIC_TREE_NODE_H_

#include "coffee_includes.h"
#include "kernel/basic/container/prow/basic_prow.h"

namespace coffee
{
namespace basic
{
    //--------------------------------------------------------------------------------------------//
    /// Hierarchical tree template
    //--------------------------------------------------------------------------------------------//
    template< typename type > \
    class COFFEE_TEMPLATE_API TreeNode : public meta::Object
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        TreeNode();
        virtual ~TreeNode();

        //-ACCESSORS------------------------------------------------------------------------------//

        const type& GetParent() const;
        type& GetParent();
        const type& GetChild(uint32 index) const;
        type& GetChild(uint32 index);
        uint32 GetChildCount() const;
        const type& GetRoot() const;
        type& GetRoot();
        
        //-QUERIES--------------------------------------------------------------------------------//

        bool HasParent() const;
        bool HasChildren() const;
        uint32 GetIndex();

        template<class T>
        const T* FindParent() const
        {
            if (HasParent())
            {
                if (GetParent().IsKindOf<T>())
                    return static_cast<const T*>(&GetParent());
                return GetParent().FindParent<T>();
            }
            return NULL;
        }

        template<class T>
        T* FindParent()
        {
            if (HasParent())
            {
                if (GetParent().IsKindOf<T>())
                    return static_cast<T*>(&GetParent());
                return GetParent().FindParent<T>();
            }
            return NULL;
        }

        bool IsChild(type& object) const;
        
        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void Attach(type& child, uint32 index=NONE);
        virtual void Detach();
        virtual void Destroy();
        virtual void PostSerialize(storage::MODE mode);

    protected:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        type* _Parent;
        Prow<type*> _Children;
    };

    #include "kernel/basic/hierarchy/tree/basic_tree_node.hpp"
}
}
#endif
