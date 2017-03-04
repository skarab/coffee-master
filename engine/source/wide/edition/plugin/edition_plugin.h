#ifndef _COFFEE_EDITION_PLUGIN_H_
#define _COFFEE_EDITION_PLUGIN_H_

#include "coffee_includes.h"
#include "wide/application/control/application_control.h"
#include "wide/edition/undo/edition_undo_manager.h"
#include "wide/edition/selection/edition_selection_manager.h"
#include "wide/edition/plugin/edition_plugin_node_controller.h"

namespace coffee
{
namespace edition
{
    //--------------------------------------------------------------------------------------------//
    /// Plugin
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Plugin : public ApplicationControl
    {
        COFFEE_Type(Plugin);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Plugin(basic::String plugin_name="", basic::String help_text="");
        virtual ~Plugin();

        //-ACCESSORS------------------------------------------------------------------------------//

        const UndoManager& GetUndoManager() const;
        UndoManager& GetUndoManager();
        const SelectionManager& GetSelectionManager() const;
        SelectionManager& GetSelectionManager();

        //-HANDLERS-------------------------------------------------------------------------------//

        virtual void OnActivate();
        virtual void OnUpdate(const basic::Time& time_step);
        
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        UndoManager _UndoManager;
        SelectionManager _SelectionManager;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Plugin);
}
}
#endif
