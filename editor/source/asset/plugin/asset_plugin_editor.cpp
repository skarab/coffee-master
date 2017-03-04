#include "asset/plugin/asset_plugin_editor.h"
#include "coffee_editor.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(asset::PluginEditor);
        COFFEE_Ancestor(asset::Plugin);
    COFFEE_EndType();
}
