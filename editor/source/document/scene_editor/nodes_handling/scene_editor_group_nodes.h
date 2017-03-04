#ifndef _EDITOR_DOCUMENT_SCENE_EDITOR_GROUP_NODES_H_
#define _EDITOR_DOCUMENT_SCENE_EDITOR_GROUP_NODES_H_

#include "coffee_editor_includes.h"

namespace coffee_editor
{
    //--------------------------------------------------------------------------------------------//
    /// Group scene nodes
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API SceneEditorGroupNodes : public ApplicationCommand
    {
        //-META-----------------------------------------------------------------------------------//

        COFFEE_Type(SceneEditorGroupNodes);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SceneEditorGroupNodes();

        //-QUERIES--------------------------------------------------------------------------------//

		bool IsUsable() const;
        
        //-HANDLERS-------------------------------------------------------------------------------//

        void OnExecute();
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, SceneEditorGroupNodes);
}
#endif
