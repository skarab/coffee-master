#include "project/project_config_target.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ProjectConfigTarget);
        COFFEE_Attribute(coffee_editor::PROJECT_TARGET, _Target, meta::MODE_Serializeable);
    COFFEE_EndType();

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ProjectConfigTarget::ProjectConfigTarget()
    {
    }

    //--------------------------------------------------------------------------------------------//

    ProjectConfigTarget::ProjectConfigTarget(PROJECT_TARGET target) :
        _Target(target)
    {
    }

    //--------------------------------------------------------------------------------------------//

    ProjectConfigTarget::~ProjectConfigTarget()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ProjectConfigTarget::SetDefaults()
    {
    }

}
