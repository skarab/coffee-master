#ifndef _EDITOR_DOCUMENT_SCENE_EDITOR_SET_ROOT_UNDO_H_
#define _EDITOR_DOCUMENT_SCENE_EDITOR_SET_ROOT_UNDO_H_

#include "coffee_editor_includes.h"

namespace coffee_editor
{
    //--------------------------------------------------------------------------------------------//
    /// Undo set root
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API SceneEditorSetRootUndo : public edition::UndoObject
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SceneEditorSetRootUndo();
        ~SceneEditorSetRootUndo();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Undo();
        void Redo();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        scene::Node* _Node;
    };
}
#endif
