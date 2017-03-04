#ifndef _COFFEE_META_TYPES_H_
#define _COFFEE_META_TYPES_H_

#include "coffee_includes.h"
#include "kernel/basic/container/prow/basic_prow_template.h"
#include "kernel/core/core.h"
#include "kernel/meta/type/meta_type.h"
#include "kernel/shell/thread/shell_mutex.h"

namespace coffee
{
namespace meta
{
    //-FORWARDS-----------------------------------------------------------------------------------//
    class Class;

    //--------------------------------------------------------------------------------------------//
    /// Manage types registration
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Types
    {
        COFFEE_DeclareSingleton(Types);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Types();
        ~Types();

        //-ACCESSORS------------------------------------------------------------------------------//

        const Class& GetNullClassType() const;
        Class& GetNullClassType();

        //-QUERIES--------------------------------------------------------------------------------//

        const Type* FindType(const basic::String type_name) const;
        Type* FindType(const basic::String type_name);
        bool HasType(const basic::String type_name) const;
        
    //private:

        //-TYPES----------------------------------------------------------------------------------//

        struct _TypeRegistration
        {
            void (* Register) (_TypeRegistration &);
            Object * (* Create) ();
        };

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _RegisterTypes(basic::Prow<Type*>& registered_types);
        void _UnregisterTypes(basic::Prow<Type*>& registered_types);
        void _RegisterType(Type& type);
        void _RequireType(const basic::String& type_name);
        
        //-FUNCTIONS------------------------------------------------------------------------------//

        static void _AddTypeRegistration(
            void (*registeration_method)(_TypeRegistration&),
            meta::Object* (*creation_method) ());

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _RegisterTypes();
        void _UnregisterTypes();
        void _RemoveRequiredType(uint32 type_index);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Prow<Type *>* _Types;
        basic::Prow<Type *>* _RequiredTypes;
        shell::Mutex _Mutex;
        Class* _NullClassType;

        //-VARIABLES------------------------------------------------------------------------------//

        static _TypeRegistration* _TypeRegistrationArray;
        static uint32 _TypeRegistrationCount;
    };
}
}
#endif
