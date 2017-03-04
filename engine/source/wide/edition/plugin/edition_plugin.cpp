#include "wide/edition/plugin/edition_plugin.h"
#include "wide/application/application.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(edition::Plugin);
        COFFEE_Ancestor(ApplicationControl);
    COFFEE_EndType();

namespace edition
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Plugin::Plugin(basic::String plugin_name, basic::String help_text) :
        ApplicationControl(plugin_name, help_text)
    {
        _UndoManager.SetPlugin(this);
        _SelectionManager.SetPlugin(this);
    }

    //--------------------------------------------------------------------------------------------//

    Plugin::~Plugin()
    {
        _UndoManager.Empty();
    }

    //-ACCESSORS------------------------------------------------------------------------------//

    const UndoManager& Plugin::GetUndoManager() const
    {
        return _UndoManager;
    }

    //--------------------------------------------------------------------------------------------//

    UndoManager& Plugin::GetUndoManager()
    {
        return _UndoManager;
    }

    //--------------------------------------------------------------------------------------------//

    const SelectionManager& Plugin::GetSelectionManager() const
    {
        return _SelectionManager;
    }

    //--------------------------------------------------------------------------------------------//

    SelectionManager& Plugin::GetSelectionManager()
    {
        return _SelectionManager;
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    void Plugin::OnActivate()
    {
        ApplicationControl::OnActivate();
        COFFEE_Assert(Application::Get().GetControlManager().HasEditionPlugin()
            && &Application::Get().GetControlManager().GetEditionPlugin()==this,
            core::ERROR_CODE_Unexpected, "edition::Plugin activation error");
    }

    //--------------------------------------------------------------------------------------------//

    void Plugin::OnUpdate(const basic::Time& time_step)
    {
        ApplicationControl::OnUpdate(time_step);
        _UndoManager.Update();
        _SelectionManager.Update();
    }
        
}
}
