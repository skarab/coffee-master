#ifndef _EDITOR_DOCUMENT_SCENE_EDITOR_ADD_NODE_H_
#define _EDITOR_DOCUMENT_SCENE_EDITOR_ADD_NODE_H_

#include "coffee_editor_includes.h"

namespace coffee_editor
{
    //--------------------------------------------------------------------------------------------//
    /// Add node
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API SceneEditorAddNode : public ApplicationCommand
    {
        COFFEE_Type(SceneEditorAddNode);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SceneEditorAddNode();

        //-HANDLERS-------------------------------------------------------------------------------//

        void OnExecute();
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, SceneEditorAddNode);
}
#endif
