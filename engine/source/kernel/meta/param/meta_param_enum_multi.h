#ifndef _COFFEE_META_PARAM_ENUM_MULTI_H_
#define _COFFEE_META_PARAM_ENUM_MULTI_H_

#include "coffee_includes.h"
#include "kernel/meta/param/meta_param.h"

namespace coffee
{
namespace basic
{
    class String;
}

namespace meta
{
    //--------------------------------------------------------------------------------------------//
    /// Custom edition of uint32 binded on enum
    ///
    /// Tell the GUI system the specified uint32 is binded to an enum MULTI, read boolean array.
    /// Used to overpass the enum system, since an enum can be SINGLE or MULTI, this is to allow
    /// uint32 to use a MULTI approach on an enum in SINGLE mode.
    ///
    /// @see coffee::CInterfacePropertyEnumMulti
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ParamEnumMulti : public Param
    {
        COFFEE_Type(ParamEnumMulti);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ParamEnumMulti();
        ParamEnumMulti(uint32 mode, basic::String enum_name);
        virtual ~ParamEnumMulti();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetEnumName(const basic::String& enum_name);
        const basic::String& GetEnumName() const;

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::String* _EnumName;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ParamEnumMulti);
}
}
#endif
