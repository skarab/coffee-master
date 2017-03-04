#ifndef _COFFEE_BASIC_PROPERTY_SCALAR_H_
#define _COFFEE_BASIC_PROPERTY_SCALAR_H_

#include "coffee_includes.h"
#include "kernel/meta/meta.h"

namespace coffee
{
namespace basic
{
    //--------------------------------------------------------------------------------------------//
    /// Scalar property class
    ///
    /// Used internally to deferred scalar from basic::PropertyBase, this to makes a single pointer
    /// in base class.
    ///
    /// @see coffee::basic::PropertyBase
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PropertyScalar : public meta::Object
    {
        COFFEE_Type(PropertyScalar);
        
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyScalar();
        PropertyScalar(const meta::SCALAR_FORMAT & format);
        ~PropertyScalar();

        //-ACCESSORS------------------------------------------------------------------------------//

        const meta::SCALAR_FORMAT & GetFormat() const;
        const char * GetObject() const;
        char * GetObject();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void SetValue(char * scalar_object);
        void Create();
        void Destroy();
        void Serialize(coffee::meta::Stream& stream);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        meta::SCALAR_FORMAT _Format;
        char * _Object;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, PropertyScalar);
}
}
#endif
