#ifndef _COFFEE_META_SCALAR_H_
#define _COFFEE_META_SCALAR_H_

#include "coffee_includes.h"
#include "kernel/meta/type/meta_type.h"
#include "kernel/meta/type/scalar/meta_scalar_format.h"

namespace coffee
{
namespace meta
{
    //--------------------------------------------------------------------------------------------//
    /// Scalar meta type class
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Scalar : public Type
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Scalar(basic::String name);
        virtual ~Scalar();

        //-ACCESSORS------------------------------------------------------------------------------//

        const SCALAR_FORMAT& GetFormat() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        Object* CreateObject() const;
        void Serialize(Stream& stream);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        SCALAR_FORMAT _Format;
    };
}
}
#endif
