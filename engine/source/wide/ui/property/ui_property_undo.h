#ifndef _COFFEE_UI_PROPERTY_UNDO_H_
#define _COFFEE_UI_PROPERTY_UNDO_H_

#include "coffee_includes.h"
#include "wide/edition/undo/edition_undo_object.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Property undo object
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PropertyUndo : public edition::UndoObject
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyUndo(meta::Object* object, void* property, const meta::Type& type);
        ~PropertyUndo();

        //-OPERATORS------------------------------------------------------------------------------//

        bool operator==(const PropertyUndo& undo) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Undo();
        void Redo();

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _UpdateValue();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        meta::Object* _Object;
        void* _Property;
        const meta::Type& _Type;
        meta::Object* _Value;
    };
}
}
#endif
