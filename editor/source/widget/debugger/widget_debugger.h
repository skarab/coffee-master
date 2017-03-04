#ifndef _EDITOR_WIDGET_DEBUGGER_H_
#define _EDITOR_WIDGET_DEBUGGER_H_

#include "coffee_editor_includes.h"
#include "widget/output/widget_output.h"
#include "widget/debugger/pass/debugger_pass.h"

namespace coffee_editor
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Graphics debugger
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API Debugger : public ui::Window
    {
        COFFEE_Type(Debugger);
        
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Debugger();
        ~Debugger();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(ui::Window* parent, uint32 height);
        
        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(Debugger);
        COFFEE_Event bool OnSelectPassType(shell::Event& event);
       
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        DebuggerPass _DebuggerPass;
        ui::widget::ComboBox* _PassType; 
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, Debugger);
}
}
#endif
