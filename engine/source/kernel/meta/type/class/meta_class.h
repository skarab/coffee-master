#ifndef _COFFEE_META_CLASS_H_
#define _COFFEE_META_CLASS_H_

#include "coffee_includes.h"
#include "kernel/meta/type/meta_type.h"
#include "kernel/meta/type/class/meta_attribute.h"
#include "kernel/basic/container/prow/basic_prow_template.h"

namespace coffee
{
namespace meta
{
    class Param;

    //--------------------------------------------------------------------------------------------//
    /// Store the hierarchy of a class type
    /// @see coffee::meta::Object, coffee::meta::ClassSerializer
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Class : public Type
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Class();
        virtual ~Class();

        //-ACCESSORS------------------------------------------------------------------------------//

        const Class* GetAncestor() const;
        Class* GetAncestor();
        const basic::Prow<Attribute*, true>& GetAttributes() const;
        basic::Prow<Attribute*, true>& GetAttributes();

        //-QUERIES--------------------------------------------------------------------------------//

        bool IsKindOf(const Class& meta_type) const;

        //----------------------------------------------------------------------------------------//

        template< class meta_class >
        bool IsA() const
        {
            return this==&meta_class::GetClassMetaType();
        }

        //----------------------------------------------------------------------------------------//

        template< class meta_class >
        bool IsKindOf() const
        {
            return IsKindOf(meta_class::GetClassMetaType());
        }

        //----------------------------------------------------------------------------------------//

        const Attribute* FindAttribute(const basic::String& name, bool it_has_to_check_ancestors=true) const;

        //----------------------------------------------------------------------------------------//

        bool FindNextAttribute(uint32& ancestor_index, uint32& attribute_index,
            Attribute** attribute, ulong_ptr& attribute_offset);

        //-OPERATIONS-----------------------------------------------------------------------------//

        void SetAncestor(const char* type_name);
        void SetAncestor(Class& meta_type);
        void AddAttribute(const char* name, const char* type_name, ulong_ptr offset, uint32 mode,
            Param* param = NULL);
        void AddAttributeArray(const char* name, const char* type_name, ulong_ptr offset,
            Param* param);
        void Serialize(Stream& stream);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool _ParseTypeName(basic::String& type_name);
        void _ParsePointerName(basic::String& pointer_name);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Class* _Ancestor;
        basic::Prow<Attribute*, true> * _Attributes;
    };
}
}
#endif
