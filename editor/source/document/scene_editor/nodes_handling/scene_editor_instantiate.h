#ifndef _EDITOR_DOCUMENT_SCENE_EDITOR_INSTANTIATE_H_
#define _EDITOR_DOCUMENT_SCENE_EDITOR_INSTANTIATE_H_

#include "coffee_editor_includes.h"

namespace coffee_editor
{
    //--------------------------------------------------------------------------------------------//
    /// Instantiate scene
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API SceneEditorInstantiate : public ApplicationCommand
    {
        COFFEE_Type(SceneEditorInstantiate);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SceneEditorInstantiate();

        //-HANDLERS-------------------------------------------------------------------------------//

        void OnExecute();
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, SceneEditorInstantiate);
}
#endif
