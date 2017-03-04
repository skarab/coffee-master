#ifndef _BUILDER_WIDGET_H_
#define _BUILDER_WIDGET_H_

#include "builder_includes.h"
#include "builder_config.h"

namespace builder
{
    //--------------------------------------------------------------------------------------------//
    /// Builder main window
    //--------------------------------------------------------------------------------------------//
    class Widget : public ui::Window
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Widget();
        ~Widget();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Update();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(Widget);
        COFFEE_Event bool OnRun(shell::Event& event);
        COFFEE_Event bool OnGenerateWorkspace(shell::Event& event);
        COFFEE_Event bool OnClear(shell::Event& event);
        COFFEE_Event bool OnStop(shell::Event& event);
        
    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _EnableControls(bool it_is_building);
        
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Config _Config;
        ui::PropertyList* _Properties;
        ui::widget::Button* _Run;
        ui::widget::Button* _GenerateWorkspace;
        ui::widget::ListView* _Output;        
        ui::widget::Button* _Clear;
        ui::widget::Button* _Stop;
    };

}
#endif
