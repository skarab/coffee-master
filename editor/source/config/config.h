#ifndef _EDITOR_CONFIG_H_
#define _EDITOR_CONFIG_H_

#include "coffee_editor_includes.h"

#define EDITOR_ConfigFile "editor.config"

namespace coffee_editor
{
    //--------------------------------------------------------------------------------------------//
    /// Editor general configuration, shared for all projects
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API Config : public meta::Object
    {
        COFFEE_Type(Config);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Config();
        ~Config();

        //-ACCESSORS------------------------------------------------------------------------------//

        //-OPERATIONS-----------------------------------------------------------------------------//

        void SetDefaults();
        void Apply();

        //-HANDLERS-------------------------------------------------------------------------------//

        void OnPropertyModified(const void* prop);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        ui::Skin _Skin;
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, Config);
}
#endif
