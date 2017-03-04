#ifndef _COFFEE_INPUT_SYSTEM_H_
#define _COFFEE_INPUT_SYSTEM_H_

#include "coffee_includes.h"
#include "system/input/command/input_command.h"
#include "system/input/handler/input_handler.h"
#include "system/input/input_event.h"

namespace coffee
{
namespace input
{
    //--------------------------------------------------------------------------------------------//
    /// @class System
    /// @brief Input System
    ///
    /// Entry point for input notifications & propagation. Accessible from Input module.
    ///
    /// @see coffee::input::Module
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API System : public Handler
    {
        //-META-----------------------------------------------------------------------------------//

        COFFEE_DeclareSingleton(System);
        COFFEE_Type(System);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        System();
        ~System();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void RegisterCommand(Command* command);
        void UnregisterCommand(Command* command);
        void Update(const basic::Time& time_step);
        void SendEvent(const EVENT& event, void* parameters=NULL);
        void SendEvent(const EVENT& event, void* parameters, input::Handler& target);
        
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Prow<Command*, true> _CommandArray;
        basic::Vector2i _MousePosition;
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, System);
}
}
#endif
