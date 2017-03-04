#ifndef _COFFEE_META_PARAM_H_
#define _COFFEE_META_PARAM_H_

#include "coffee_includes.h"
#include "kernel/meta/meta_object.h"
#include "kernel/meta/meta_mode.h"

namespace coffee
{
namespace meta
{
    //--------------------------------------------------------------------------------------------//
    /// Meta custom parameter base class
    ///
    /// Passing it to COFFEE_AttributeCustom, it allows to set custom parameters to meta type,
    /// edition parameters for instance.
    /// This class is set by default using COFFEE_Attribute, and coffee::meta::ParamArray is used for
    /// array type.
    ///
    /// @see COFFEE_AttributeCustom, coffee::meta::ParamArray
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Param : public Object
    {
        COFFEE_Type(Param);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Param();
        Param(uint32 mode);
        virtual ~Param();

        //-ACCESSORS------------------------------------------------------------------------------//

        uint32 GetMode() const;
        void SetMode(uint32 mode);

        //-QUERIES--------------------------------------------------------------------------------//

        bool IsSerializeable() const;
        bool IsEditable() const;

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        uint32 _Mode;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Param);
}
}
#endif
