#ifndef _EDITOR_ASSET_PLUGIN_EDITOR_H_
#define _EDITOR_ASSET_PLUGIN_EDITOR_H_

#include "coffee_editor_includes.h"
#include "asset/plugin/asset_plugin.h"

namespace coffee_editor
{
namespace asset
{
    //--------------------------------------------------------------------------------------------//
    /// Editor Plugin asset
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API PluginEditor : public Plugin
    {
        COFFEE_Type(PluginEditor);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PluginEditor() {}
        ~PluginEditor() {}

        //-QUERIES--------------------------------------------------------------------------------//

        static bool IsSupporting(const basic::String& file_extension) { return file_extension=="editor"; }

    protected:

        //-QUERIES--------------------------------------------------------------------------------//

        basic::String _GetExtension() const { return "editor"; }
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, PluginEditor);
}
}
#endif
