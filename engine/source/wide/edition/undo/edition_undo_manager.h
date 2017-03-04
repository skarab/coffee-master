#ifndef _COFFEE_EDITION_UNDO_MANAGER_H_
#define _COFFEE_EDITION_UNDO_MANAGER_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "wide/ui/property/ui_property_undo.h"
#include "wide/edition/undo/edition_undo_object.h"
#include "wide/edition/undo/edition_undo_group.h"
#include "system/input/input_module.h"

namespace coffee
{
namespace edition
{
    class Plugin;

    //--------------------------------------------------------------------------------------------//
    /// Undo manager
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API UndoManager
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        UndoManager();
        ~UndoManager();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetPlugin(Plugin* plugin);
        const basic::Prow< UndoGroup*, true >& GetUndoGroupArray() const;
        const basic::Prow< UndoGroup*, true >& GetRedoGroupArray() const;
        const UndoGroup& GetLastUndoGroup() const;

        //-QUERIES--------------------------------------------------------------------------------//

        bool IsActive() const;
        bool HasUndoGroup() const;
        bool HasRedoGroup() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Begin();
        void Accept(basic::String name);
        void Cancel();
        void Add(UndoObject* object);
        void CancelObjects();
        void Undo();
        void Redo();
        void Empty();
        void Update();

        //-VARIABLES------------------------------------------------------------------------------//

        static COFFEE_STATIC_API input::Command* UndoCommand;
        static COFFEE_STATIC_API input::Command* RedoCommand;

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        UndoGroup* _CurrentGroup;
        basic::Prow< UndoGroup*, true > _UndoGroupArray;
        basic::Prow< UndoGroup*, true > _RedoGroupArray;
        bool _ItHasBeenModified;
        Plugin* _Plugin;
    };
}
}
#endif
