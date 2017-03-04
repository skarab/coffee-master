#ifndef _COFFEE_EDITION_UNDO_GROUP_H_
#define _COFFEE_EDITION_UNDO_GROUP_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "wide/edition/undo/edition_undo_object.h"

namespace coffee
{
namespace edition
{
    //--------------------------------------------------------------------------------------------//
    /// Undo group
    ///
    /// @see coffee::edition::UndoObject
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API UndoGroup
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        UndoGroup();
        ~UndoGroup();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetName(const basic::String& name) { _Name = name; }
        const basic::String& GetName() const { return _Name; }
        const basic::Prow< UndoObject*, true >& GetObjects() const { return _Objects; }

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Add(UndoObject* object);
        
        void Undo();
        void Redo();
        void Cancel();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::String _Name;
        basic::Prow< UndoObject*, true > _Objects;
    };
}
}
#endif
