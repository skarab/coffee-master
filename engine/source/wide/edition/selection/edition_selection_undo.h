#ifndef _COFFEE_EDITION_SELECTION_UNDO_H_
#define _COFFEE_EDITION_SELECTION_UNDO_H_

#include "coffee_includes.h"
#include "wide/edition/undo/edition_undo_object.h"

namespace coffee
{
namespace edition
{
    //--------------------------------------------------------------------------------------------//
    /// Selection undo object
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API SelectionUndo : public UndoObject
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SelectionUndo();
        ~SelectionUndo();

        //-QUERIES--------------------------------------------------------------------------------//

        bool HasObject() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Undo();
        void Redo();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Prow< meta::Object* > _UndoObjectArray;
        basic::Prow< meta::Object* > _RedoObjectArray;
    };
}
}
#endif
