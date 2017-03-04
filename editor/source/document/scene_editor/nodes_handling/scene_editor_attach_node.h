#ifndef _EDITOR_DOCUMENT_SCENE_EDITOR_ATTACH_NODE_H_
#define _EDITOR_DOCUMENT_SCENE_EDITOR_ATTACH_NODE_H_

#include "coffee_editor_includes.h"

namespace coffee_editor
{
    //--------------------------------------------------------------------------------------------//
    /// Attach scene node
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API SceneEditorAttachNode : public ApplicationCommand
    {
        //-META-----------------------------------------------------------------------------------//

        COFFEE_Type(SceneEditorAttachNode);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SceneEditorAttachNode();

        //-QUERIES--------------------------------------------------------------------------------//

		bool IsUsable() const;
        
        //-HANDLERS-------------------------------------------------------------------------------//

        void OnExecute();
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, SceneEditorAttachNode);
}
#endif
