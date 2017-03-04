#ifndef _COFFEE_EDITION_PLUGIN_ATTACH_NODE_UNDO_H_
#define _COFFEE_EDITION_PLUGIN_ATTACH_NODE_UNDO_H_

#include "coffee_includes.h"
#include "wide/edition/undo/edition_undo_object.h"
#include "system/scene/scene.h"

namespace coffee
{
namespace edition
{
    //--------------------------------------------------------------------------------------------//
    /// Undo add node
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PluginAttachNodeUndo : public UndoObject
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PluginAttachNodeUndo(scene::Node* node);
        ~PluginAttachNodeUndo();

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
