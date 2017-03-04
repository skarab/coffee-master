#ifndef _EDITOR_DOCUMENT_SCENE_EDITOR_CLOSE_NODE_H_
#define _EDITOR_DOCUMENT_SCENE_EDITOR_CLOSE_NODE_H_

#include "coffee_editor_includes.h"

namespace coffee_editor
{
    //--------------------------------------------------------------------------------------------//
    /// Close scene node
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API SceneEditorCloseNode : public ApplicationCommand
    {
        //-META-----------------------------------------------------------------------------------//

        COFFEE_Type(SceneEditorCloseNode);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SceneEditorCloseNode();

        //-QUERIES--------------------------------------------------------------------------------//

		bool IsUsable() const;
        
        //-HANDLERS-------------------------------------------------------------------------------//

        void OnExecute();
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, SceneEditorCloseNode);
}
#endif
