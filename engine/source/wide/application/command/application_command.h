#ifndef _COFFEE_WIDE_APPLICATION_COMMAND_H_
#define _COFFEE_WIDE_APPLICATION_COMMAND_H_

#include "coffee_includes.h"
#include "wide/application/control/application_control.h"

namespace coffee
{
    //--------------------------------------------------------------------------------------------//
    /// Simple command execution
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ApplicationCommand : public ApplicationControl
    {
        COFFEE_Type(ApplicationCommand);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ApplicationCommand(basic::String name="", basic::String help_text="");
        
		//-QUERIES--------------------------------------------------------------------------------//

		virtual bool IsUsable() const;
        
        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void OnExecute();

        //-HANDLERS-------------------------------------------------------------------------------//

        void OnActivate();
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ApplicationCommand);
}
#endif
