#ifndef _EDITOR_ASSET_COMPONENT_H_
#define _EDITOR_ASSET_COMPONENT_H_

#include "coffee_editor_includes.h"
#include "asset/plugin/asset_plugin.h"

namespace coffee_editor
{
namespace asset
{
    //--------------------------------------------------------------------------------------------//
    /// Component asset
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API Component : public Plugin
    {
        COFFEE_Type(Component);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Component() {}
        virtual ~Component() {}

        //-QUERIES--------------------------------------------------------------------------------//

        static bool IsSupporting(const basic::String& file_extension) { return file_extension=="component"; }

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool Import();
        bool Create(const storage::PhysicalPath& asset_path, const storage::Path& logical_path);
        
    protected:

        //-QUERIES--------------------------------------------------------------------------------//

        virtual basic::String _GetExtension() const { return "component"; }  
        virtual plugins::Object* _CreateComponent() { return COFFEE_New(plugins::ComponentObject); }
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, Component);
}
}
#endif
