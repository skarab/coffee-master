#ifndef _COFFEE_EDITION_SELECTION_MANAGER_H_
#define _COFFEE_EDITION_SELECTION_MANAGER_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/input/input_module.h"

namespace coffee
{
namespace edition
{
    class Plugin;
    class SelectionUndo;

    //--------------------------------------------------------------------------------------------//
    /// Selection manager
    ///
    /// Generic selection manager based on an array of selected meta::Object.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API SelectionManager
    {
        friend class SelectionUndo;

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SelectionManager();
        ~SelectionManager();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetPlugin(Plugin* plugin);
        uint32 GetObjectCount() const;
        const meta::Object& GetObject(uint32 index) const;
        meta::Object& GetObject(uint32 index);
        const basic::Prow< meta::Object* >& GetObjectArray() const;

        //-QUERIES--------------------------------------------------------------------------------//

        bool IsObjectSelected(meta::Object& object) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Select(meta::Object& object, bool it_is_selected, bool it_has_to_handle_undo,
			bool it_has_to_accept_undo=true);
        void Clear(bool it_has_to_handle_undo, bool it_has_to_accept_undo=true);
        void Update();

        //-VARIABLES------------------------------------------------------------------------------//

        static COFFEE_STATIC_API input::Command* CopyCommand;
        static COFFEE_STATIC_API input::Command* CutCommand;
        static COFFEE_STATIC_API input::Command* PasteCommand;
        static COFFEE_STATIC_API input::Command* DeleteCommand;
        
    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _Select(basic::Prow< meta::Object* >& object_array);
        
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Prow< meta::Object* > _ObjectArray;
        bool _ItHasBeenModified;
        Plugin* _Plugin;
    };
}
}
#endif
