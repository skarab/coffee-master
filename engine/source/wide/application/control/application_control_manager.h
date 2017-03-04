#ifndef _COFFEE_WIDE_APPLICATION_CONTROL_MANAGER_H_
#define _COFFEE_WIDE_APPLICATION_CONTROL_MANAGER_H_

#include "coffee_includes.h"
#include "wide/application/control/application_control.h"
#include "wide/edition/plugin/edition_plugin.h"

namespace coffee
{
    //--------------------------------------------------------------------------------------------//
    /// Manager of the application controls
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ApplicationControlManager : public ApplicationControl
    {
        COFFEE_Type(ApplicationControlManager);
        COFFEE_DeclareSingleton(ApplicationControlManager);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ApplicationControlManager();
        ~ApplicationControlManager();

        //-ACCESSORS------------------------------------------------------------------------------//

        const edition::Plugin& GetEditionPlugin() const;
        edition::Plugin& GetEditionPlugin();

        //-QUERIES--------------------------------------------------------------------------------//

        bool HasEditionPlugin() const;

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(ApplicationControlManager);
        COFFEE_Event bool OnKeyPressed(shell::Event& event);
        
        //-HANDLERS-------------------------------------------------------------------------------//

        void OnInitialize();
        void OnFinalize();
        void OnChildActivate(ApplicationControl& control);
        void OnChildDeactivate(ApplicationControl& control);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        edition::Plugin* _EditionPlugin;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ApplicationControlManager);
}
#endif
