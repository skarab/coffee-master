#ifndef _COFFEE_PLUGINS_MODULE_H_
#define _COFFEE_PLUGINS_MODULE_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "wide/plugins/plugins_object.h"
#include "wide/plugins/component/plugins_component.h"

namespace coffee
{
namespace plugins
{
    //--------------------------------------------------------------------------------------------//
    /// Plugins module
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Module : public shell::Module
    {
        COFFEE_Type(Module);
        COFFEE_DeclareModuleSingleton(Module);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Module();
        ~Module();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void OnInitialize();
        void OnFinalize();
        void OnStart();
        void OnStop();
        void OnUpdate(const basic::Time& time_step);
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Module);
}
}
#endif
