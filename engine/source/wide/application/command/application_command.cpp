#include "wide/application/command/application_command.h"
#include "wide/application/application.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ApplicationCommand);
        COFFEE_Ancestor(ApplicationControl);
    COFFEE_EndType();

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ApplicationCommand::ApplicationCommand(basic::String name, basic::String help_text) :
        ApplicationControl(name, help_text)
    {
    }

	//-QUERIES------------------------------------------------------------------------------------//

	bool ApplicationCommand::IsUsable() const
	{
		return true;
	}
    
    //-OPERATIONS---------------------------------------------------------------------------------//

    void ApplicationCommand::OnExecute()
    {
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    void ApplicationCommand::OnActivate()
    {
        OnExecute();
        Deactivate();
    }

}
