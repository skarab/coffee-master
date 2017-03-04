#ifndef _COFFEE_EDITION_UNDO_OBJECT_H_
#define _COFFEE_EDITION_UNDO_OBJECT_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"

namespace coffee
{
namespace edition
{
    //--------------------------------------------------------------------------------------------//
    /// Undo object
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API UndoObject
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        UndoObject() {}
        virtual ~UndoObject() {}

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void Undo() = 0;
        virtual void Redo() = 0;
    };
}
}
#endif
