#ifndef _COFFEE_SHELL_MODULE_CONFIG_H_
#define _COFFEE_SHELL_MODULE_CONFIG_H_

#include "coffee_includes.h"
#include "kernel/meta/meta.h"

namespace coffee
{
namespace shell
{
    //--------------------------------------------------------------------------------------------//
    /// Module configuration
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ModuleConfig : public meta::Object
    {
        COFFEE_Type(ModuleConfig);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ModuleConfig();
        virtual ~ModuleConfig();

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void SetDefaults();
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ModuleConfig);
}
}
#endif
