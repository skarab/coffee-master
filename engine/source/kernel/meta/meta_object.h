#ifndef _COFFEE_META_OBJECT_H_
#define _COFFEE_META_OBJECT_H_

#include "coffee_includes.h"
#include "kernel/meta/serializer/stream/meta_stream.h"
#include "kernel/meta/type/class/meta_class.h"
#include "kernel/meta/type/scalar/meta_scalar.h"
#include "kernel/meta/meta_types.h"
#include "kernel/meta/serializer/meta_serializer.h"

namespace coffee
{
    //-FORWARDS-----------------------------------------------------------------------------------//

namespace basic
{
    template< typename type > class Array;
}

namespace storage
{
    class Path;
    enum MODE;
}

namespace meta
{
    //--------------------------------------------------------------------------------------------//
    /// Base class of meta-managed objects
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Object
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Object();
        virtual ~Object();

        //-OPERATORS------------------------------------------------------------------------------//

        bool operator == (const Object& object) const;

        //-ACCESSORS------------------------------------------------------------------------------//

        /// Get the const meta::Type of the object
        virtual const Class& GetMetaType() const;
        
        /// Get the meta::Type of the object
        virtual Class& GetMetaType();

        /// Get the meta::Type of the class
        static Class& GetClassMetaType();

        //-QUERIES--------------------------------------------------------------------------------//

        /// Check if the object meta::Type is a specific type
        template<class meta_type>
        bool IsA() const { return &GetMetaType()==&meta_type::GetClassMetaType(); }
        
        /// Check if the object meta::Type is inheriting of a specific type
        template<class meta_type>
        bool IsKindOf() const { return GetMetaType().IsKindOf< meta_type >(); }

        //-OPERATIONS-----------------------------------------------------------------------------//

        /// Serialize the object in/from a file
        bool Serialize(storage::Path file_path, storage::MODE mode);

        /// Override it to make a custom serialization
        virtual void Serialize(Stream& stream);

        /// Override it to define what need to be done just before the serialization
        virtual void PreSerialize(storage::MODE mode) {}

        /// Override it to define what need to be done just after the serialization
        virtual void PostSerialize(storage::MODE mode) {}

        /// Create a clone of the object
        Object* Clone();
        
        /// Copy the object, the meta type require to be identical
        void Copy(Object& object);

        /// Cast an object to the current object type, and return a meta object
        virtual Object* CastObject(void* object) const;

        /// Serialize the object to-from an array
        void SerializeToArray(basic::Array<uint8>& array, storage::MODE mode);

        //-HANDLERS-------------------------------------------------------------------------------//

        /// Callback for when a property (attribute) has been modified from the GUI.
        virtual void OnPropertyModified(const void* property) {}
    };
}
}
#endif
