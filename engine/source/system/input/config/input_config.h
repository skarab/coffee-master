#ifndef _INPUT_CONFIG_H_
#define _INPUT_CONFIG_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/input/command/input_command.h"

namespace coffee
{
    //-FORWARDS-----------------------------------------------------------------------------------//
    class ApplicationControl;

namespace input
{
    //--------------------------------------------------------------------------------------------//
    /// @class Config
    /// @brief Input config
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Config : public shell::ModuleConfig
    {
        //-META-----------------------------------------------------------------------------------//

        COFFEE_Type(Config);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Config();
        ~Config();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void SetDefaults();
        void Apply();

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _RetrieveCommands(basic::Prow<Command*>& command_array);
        void _RetrieveControlCommands(basic::Prow<Command*>& command_array,
            ApplicationControl& control);
        void _RemoveUnusedCommands(const basic::Prow<Command*>& command_array);
        void _ApplyConfig(basic::Prow<Command*>& command_array);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Prow<Command*, true> _Shortcuts;
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Config);
}
}
#endif
