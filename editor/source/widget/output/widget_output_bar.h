#ifndef _EDITOR_WIDGET_OUTPUT_BAR_H_
#define _EDITOR_WIDGET_OUTPUT_BAR_H_

#include "coffee_editor_includes.h"
#include "widget/output/widget_output.h"

namespace coffee_editor
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Output bar
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API OutputBar : public ui::Window
    {
        COFFEE_Type(OutputBar);
        
    public:

        enum Filter
        {
            FilterAll,
            FilterErrors,
            FilterWarnings
        };

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        OutputBar();
        ~OutputBar();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(ui::Window* parent, uint32 height);
        void Update();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(OutputBar);
        COFFEE_Event bool OnFilterAll(shell::Event& event);
        COFFEE_Event bool OnFilterErrors(shell::Event& event);
        COFFEE_Event bool OnFilterWarnings(shell::Event& event);
        COFFEE_Event bool OnClear(shell::Event& event);
        COFFEE_Event bool OnOutput(shell::Event& event);
        COFFEE_DeclareExternEventHandler(OutputBar, OnDestroyOutput);
        
        //-HANDLERS-------------------------------------------------------------------------------//

        void OnLog(core::Log::Type type, const char* message, bool it_has_to_add=true);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _UpdateFilters();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        ui::widget::Button* _FilterAll;
        ui::widget::Button* _FilterErrors;
        ui::widget::Button* _FilterWarnings;
        ui::widget::Button* _Clear;
        Filter _Filter;
        ui::widget::Label* _Label;
        Output* _Output;
        basic::Text _Log;
        basic::Array<core::Log::Type> _LogType;
        shell::Mutex _Mutex;
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, OutputBar);
}
}
#endif
