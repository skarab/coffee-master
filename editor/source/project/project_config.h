#ifndef _EDITOR_PROJECT_CONFIG_H_
#define _EDITOR_PROJECT_CONFIG_H_

#include "coffee_editor_includes.h"
#include "project/project_target.h"
#include "project/project_config_target.h"

#define EDITOR_ProjectConfigFile "project.config"

namespace coffee_editor
{
    //--------------------------------------------------------------------------------------------//
    /// Project configuration (editor only)
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API ProjectConfig : public meta::Object
    {
        COFFEE_Type(ProjectConfig);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ProjectConfig();
        ~ProjectConfig();

        //-ACCESSORS------------------------------------------------------------------------------//

        const ProjectConfigTarget& GetTarget(PROJECT_TARGET target) const { return *_Targets[(uint32)target]; }
        ProjectConfigTarget& GetTarget(PROJECT_TARGET target) { return *_Targets[(uint32)target]; }

        //-OPERATIONS-----------------------------------------------------------------------------//

        void SetDefaults();
        void PostSerialize(storage::MODE mode);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Prow<ProjectConfigTarget*, true> _Targets;
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, ProjectConfig);
}
#endif
