#ifndef _COFFEE_EDITION_PLUGIN_DETACH_NODE_UNDO_H_
#define _COFFEE_EDITION_PLUGIN_DETACH_NODE_UNDO_H_

#include "coffee_includes.h"
#include "wide/edition/undo/edition_undo_object.h"
#include "system/scene/scene.h"

namespace coffee
{
namespace edition
{
    //--------------------------------------------------------------------------------------------//
    /// Undo remove node
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PluginDetachNodeUndo : public UndoObject
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PluginDetachNodeUndo(scene::Node* node);
        ~PluginDetachNodeUndo();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Undo();
        void Redo();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        scene::Node* _Node;
		scene::Node* _Parent;
        basic::Matrix _Transform;
    };
}
}
#endif
