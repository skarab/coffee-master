#ifndef _COFFEE_INPUT_HANDLER_H_
#define _COFFEE_INPUT_HANDLER_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "kernel/shell/event/shell_event_handler.h"
#include "system/input/keyboard/input_key_code.h"
#include "system/input/command/input_command.h"
#include "system/input/input_event.h"

namespace coffee
{
namespace input
{
    //--------------------------------------------------------------------------------------------//
    /// Hierarchical input events handler interface
    ///
    /// Base class giving access to input notifications.
    /// The handlers are organized in a tree, the children get the priority on the notifications.
    /// The child handlers are owned by the parent.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Handler : public shell::EventHandler
    {
        COFFEE_Type(Handler);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Handler();
        virtual ~Handler();

        //-EVENTS---------------------------------------------------------------------------------//

        void OnDestroyEvent(shell::Event& event);
        static void ForwardDestroyEvent(shell::Event& event);
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Handler);
}
}
#endif
