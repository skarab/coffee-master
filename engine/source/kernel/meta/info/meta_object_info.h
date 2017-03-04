#ifndef _COFFEE_META_OBJECT_INFO_H_
#define _COFFEE_META_OBJECT_INFO_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_mode.h"
#include "kernel/meta/type/meta_type.h"
#include "kernel/basic/hierarchy/tree/basic_tree_node.h"
#include "kernel/basic/alpha/string/basic_string.h"

namespace coffee
{
namespace resource
{
    class PropertyBase;
}

namespace meta
{
    //--------------------------------------------------------------------------------------------//
    /// Meta object info
    ///
    /// This is used to retrieve the whole class/type hierarchy of an object.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ObjectInfo : public basic::TreeNode<ObjectInfo>
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ObjectInfo(Object* object);
        ObjectInfo(void* object_data, Type* object_type,
            Attribute* attribute=NULL, Class* ancestor=NULL);
        ~ObjectInfo();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetName(const basic::String& name);
        const basic::String& GetName() const;
        const void* GetData() const;
        void* GetData();
        const Type& GetType() const;
        Type& GetType();
        void SetAttribute(Attribute& attribute);
        const Attribute& GetAttribute() const;
        void SetAncestor(Class& ancestor);
        const Class& GetAncestor() const;
        void SetResourceProperty(resource::PropertyBase* resource_property);
        resource::PropertyBase* GetResourceProperty();
        const resource::PropertyBase* GetResourceProperty() const;

        //-QUERIES--------------------------------------------------------------------------------//

        bool IsScalar() const;
        bool IsClass() const;
        bool IsAttribute() const;
        bool IsAncestor() const;
        bool IsArray() const;
        bool IsResourceProperty() const;

        ObjectInfo* FindByNameAndType(const basic::String& name, const Type& type);

        //-OPERATIONS-----------------------------------------------------------------------------//

        void BuildTree(bool it_is_rebuilding=false);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _BuildTreeClass();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::String _Name;
        void* _Data;
        Type* _Type;
        Attribute* _Attribute;
        Class* _Ancestor;
        bool _ItIsArray;
        resource::PropertyBase* _ResourceProperty;
    };
}
}
#endif
