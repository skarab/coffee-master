#ifndef _EDITOR_WIDGET_OUTPUT_H_
#define _EDITOR_WIDGET_OUTPUT_H_

#include "coffee_editor_includes.h"

namespace coffee_editor
{
namespace widget
{
    class OutputBar;

    //--------------------------------------------------------------------------------------------//
    /// Output
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API Output : public ui::Window
    {
        COFFEE_Type(Output);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Output();
        ~Output();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(OutputBar* output_bar);
        
        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(Output);
        COFFEE_Event bool OnDeactivate(shell::Event& event);
        
        //-HANDLERS-------------------------------------------------------------------------------//

        void OnLog(core::Log::Type type, const char* message);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        OutputBar* _OutputBar;
        ui::widget::ListView* _View;
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, Output);
}
}
#endif
