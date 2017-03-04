#ifndef _EDITOR_DOCUMENT_SCENE_EDITOR_DETACH_NODE_H_
#define _EDITOR_DOCUMENT_SCENE_EDITOR_DETACH_NODE_H_

#include "coffee_editor_includes.h"

namespace coffee_editor
{
    //--------------------------------------------------------------------------------------------//
    /// Detach scene nodes
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API SceneEditorDetachNode : public ApplicationCommand
    {
        //-META-----------------------------------------------------------------------------------//

        COFFEE_Type(SceneEditorDetachNode);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SceneEditorDetachNode();

        //-QUERIES--------------------------------------------------------------------------------//

		bool IsUsable() const;
        
        //-HANDLERS-------------------------------------------------------------------------------//

        void OnExecute();
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, SceneEditorDetachNode);
}
#endif
