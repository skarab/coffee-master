#ifndef _EDITOR_DOCUMENT_SCENE_EDITOR_OPEN_NODE_H_
#define _EDITOR_DOCUMENT_SCENE_EDITOR_OPEN_NODE_H_

#include "coffee_editor_includes.h"

namespace coffee_editor
{
    //--------------------------------------------------------------------------------------------//
    /// Open node
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API SceneEditorOpenNode : public ApplicationCommand
    {
        COFFEE_Type(SceneEditorOpenNode);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SceneEditorOpenNode();

		//-QUERIES--------------------------------------------------------------------------------//

		bool IsUsable() const;
        
        //-HANDLERS-------------------------------------------------------------------------------//

        void OnExecute();
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, SceneEditorOpenNode);
}
#endif
