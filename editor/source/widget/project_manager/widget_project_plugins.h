#ifndef _EDITOR_WIDGET_PROJECT_PLUGINS_H_
#define _EDITOR_WIDGET_PROJECT_PLUGINS_H_

#include "coffee_editor_includes.h"

namespace coffee_editor
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Set which plugins are loaded with the project and edit their properties
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API ProjectPlugins : public ui::Window
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ProjectPlugins();
        ~ProjectPlugins();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(ui::Window* tab_client);

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(ProjectPlugins);
        COFFEE_Event bool OnSelectPlugin(shell::Event& event);
        COFFEE_Event bool OnCheckPlugin(shell::Event& event);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _UpdatePlugins();
        void _AddPlugin(storage::Path* plugin_path);
        void _UpdateProperties();

        //-ATTRIBUTES-----------------------------------------------------------------------------//
    
        ui::widget::ListView* _Plugins;
        ui::PropertyList* _Properties;
        basic::Prow<storage::Path*, true> _PluginPathes;
    };
}
}
#endif
