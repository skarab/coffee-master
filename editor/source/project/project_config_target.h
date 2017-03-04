#ifndef _EDITOR_PROJECT_CONFIG_TARGET_H_
#define _EDITOR_PROJECT_CONFIG_TARGET_H_

#include "coffee_editor_includes.h"
#include "project/project_target.h"

namespace coffee_editor
{
    //--------------------------------------------------------------------------------------------//
    /// Configuration of deployment for a specific target
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API ProjectConfigTarget : public meta::Object
    {
        COFFEE_Type(ProjectConfigTarget);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ProjectConfigTarget();
        ProjectConfigTarget(PROJECT_TARGET target);
        ~ProjectConfigTarget();

        //-ACCESSORS------------------------------------------------------------------------------//

        
        //-OPERATIONS-----------------------------------------------------------------------------//

        void SetDefaults();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        PROJECT_TARGET _Target;
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, ProjectConfigTarget);
}
#endif
