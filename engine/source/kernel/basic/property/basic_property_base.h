#ifndef _COFFEE_BASIC_PROPERTY_BASE_H_
#define _COFFEE_BASIC_PROPERTY_BASE_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_object.h"
#include "kernel/meta/type/meta_type_templates.h"
#include "kernel/basic/alpha/string/basic_string.h"
#include "kernel/basic/property/basic_property_flag.h"
#include "kernel/basic/property/basic_property_scalar.h"

namespace coffee
{
namespace basic
{
    //--------------------------------------------------------------------------------------------//
    /// Property base class
    ///
    /// This is the base class for all properties, it manages property access & serialization.
    ///
    /// @see coffee::basic::Property
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PropertyBase : public meta::Object
    {
        COFFEE_Type(PropertyBase);
        
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyBase();
        PropertyBase(String name, const meta::Type* type);
        virtual ~PropertyBase();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetName(const String& name);
        const String& GetName() const;
        const meta::Type* GetType() const;
        const meta::Object* GetObject() const;
        meta::Object* GetObject();
        const char* GetScalarObject() const;
        char* GetScalarObject();

        //-QUERIES--------------------------------------------------------------------------------//

        bool IsScalar() const;
        bool IsMetaObject() const;
        bool IsNull() const;
        bool HasFlag(const PROPERTY_FLAG& flag) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void SetScalarValue(char* scalar_object);
        void SetMetaObjectValue(const meta::Object& meta_object);
        void SetNull();
        virtual void Serialize(coffee::meta::Stream& stream);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _Create();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        String _Name;
        const meta::Type* _Type;
        meta::Object* _Object;
        uint32 _Flags;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, PropertyBase);
}
}
#endif
