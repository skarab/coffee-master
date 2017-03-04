#include "widget/debugger/widget_debugger.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(widget::Debugger);
    COFFEE_Ancestor(ui::Window);
    COFFEE_EndType();

namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Debugger::Debugger() :
        _PassType(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Debugger::~Debugger()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Debugger::Create(ui::Window* parent, uint32 height)
    {
        ui::Window::Create(parent, basic::Vector2i(), basic::Vector2i(0, height),
            ui::WINDOW_STYLE_DrawFrame | ui::WINDOW_STYLE_DrawClientRaised);
        GetLayout().SetStyle(
            ui::LAYOUT_STYLE_HorizontalCanvas
            | ui::LAYOUT_STYLE_StickChildren);
        
        _PassType = COFFEE_New(ui::widget::ComboBox);
        _PassType->Create(this, basic::Vector2i(), 80);
        _PassType->GetLayout().SetCanvas(100, true);
        meta::Enum* enum_type = (meta::Enum*)meta::Types::Get().FindType("coffee_editor::widget::DEBUGGER_PASS_TYPE");
        COFFEE_Assert(enum_type!=NULL, core::ERROR_CODE_Unexpected, "Unexpected error");
        _PassType->AddItem("None");
        for (uint32 i=0 ; i<enum_type->GetValues().GetSize() ; ++i)
            _PassType->AddItem(enum_type->GetValues()[i]->GetName());
        _PassType->SelectItem(0);
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(Debugger, ui::Window)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Select, ui::widget::Widget, _PassType, OnSelectPassType)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool Debugger::OnSelectPassType(shell::Event& event)
    {
        DEBUGGER_PASS_TYPE pass_type = (DEBUGGER_PASS_TYPE)(_PassType->GetSelectedIndex()-1);
        _DebuggerPass.SetPassType(pass_type);
        return true;
    }

}
}
