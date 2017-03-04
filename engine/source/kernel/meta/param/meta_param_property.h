#ifndef _COFFEE_META_PARAM_PROPERTY_H_
#define _COFFEE_META_PARAM_PROPERTY_H_

#include "coffee_includes.h"
#include "kernel/meta/param/meta_param.h"

namespace coffee
{
namespace meta
{
    //--------------------------------------------------------------------------------------------//
    /// Resource property custom parameter
    ///
    /// Internal used only !
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ParamProperty : public Param
    {
        COFFEE_Type(ParamProperty);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ParamProperty();
        ParamProperty(uint32 mode, uint32 flags);
        ~ParamProperty();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetFlags(uint32 flags);
        uint32 GetFlags() const;

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        uint32 _Flags;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ParamProperty);
}
}
#endif
