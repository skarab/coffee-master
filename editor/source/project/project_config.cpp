#include "project/project_config.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ProjectConfig);
        COFFEE_Attribute(<ProjectConfigTarget*>, _Targets, meta::MODE_Serializeable);
    COFFEE_EndType();

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ProjectConfig::ProjectConfig()
    {
    }

    //--------------------------------------------------------------------------------------------//

    ProjectConfig::~ProjectConfig()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ProjectConfig::SetDefaults()
    {
        _Targets.Erase();
        for (uint32 i=0 ; i<PROJECT_TARGET_Count ; ++i)
        {
            _Targets.AddItem(COFFEE_New(ProjectConfigTarget, (PROJECT_TARGET)i));
            _Targets[i]->SetDefaults();
        }
    }

    //--------------------------------------------------------------------------------------------//

    void ProjectConfig::PostSerialize(storage::MODE mode)
    {
        if (mode==storage::MODE_Input)
        {
            if (_Targets.GetSize()!=PROJECT_TARGET_Count)
                SetDefaults();
        }
    }

}
