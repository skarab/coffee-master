#include "wide/application/control/application_control_manager.h"
#include "wide/application/application.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ApplicationControlManager);
        COFFEE_Ancestor(ApplicationControl);
    COFFEE_EndType();

    //--------------------------------------------------------------------------------------------//

    COFFEE_ImplementSingleton(ApplicationControlManager);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ApplicationControlManager::ApplicationControlManager() :
        ApplicationControl("ControlManager"),
        _EditionPlugin(NULL)
    {
        COFFEE_CreateSingleton(ApplicationControlManager);
    }

    //--------------------------------------------------------------------------------------------//

    ApplicationControlManager::~ApplicationControlManager()
    {
        COFFEE_DestroySingleton(ApplicationControlManager);
    }

    //-ACCESSORS------------------------------------------------------------------------------//

    const edition::Plugin& ApplicationControlManager::GetEditionPlugin() const
    {
        return *_EditionPlugin;
    }

    //--------------------------------------------------------------------------------------------//

    edition::Plugin& ApplicationControlManager::GetEditionPlugin()
    {
        return *_EditionPlugin;
    }

    //-QUERIES--------------------------------------------------------------------------------//

    bool ApplicationControlManager::HasEditionPlugin() const
    {
        return _EditionPlugin!=NULL;
    }
    
    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(ApplicationControlManager, ApplicationControl)
        COFFEE_RegisterEventHandler(input::EVENT_KeyPressed, input::Handler, OnKeyPressed)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool ApplicationControlManager::OnKeyPressed(shell::Event& event)
    {
        input::EventKey* parameter = (input::EventKey*)
            event.GetParameters().GetCustomParameter();        
        if (parameter->Key==input::KEY_Escape)
        {
            if (HasActiveControl())
            {
                GetHeadActiveControl().Deactivate();
                GetHeadActiveControl()._ChildActivate(GetHeadActiveControl());
            }
            return true;
        }
        return false;
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    void ApplicationControlManager::OnInitialize()
    {
    }

    //--------------------------------------------------------------------------------------------//

    void ApplicationControlManager::OnFinalize()
    {
    }

    //--------------------------------------------------------------------------------------------//

    void ApplicationControlManager::OnChildActivate(ApplicationControl& control)
    {
        if (control.IsKindOf<edition::Plugin>())
            _EditionPlugin = static_cast<edition::Plugin*>(&control);
        
        Application::Get().OnActivateControl(control);
    }

    //--------------------------------------------------------------------------------------------//

    void ApplicationControlManager::OnChildDeactivate(ApplicationControl& control)
    {
        if (control.IsKindOf<edition::Plugin>())
            _EditionPlugin = NULL;
    }

}
