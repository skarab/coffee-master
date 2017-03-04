#include "widget/output/widget_output_bar.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(widget::OutputBar);
    COFFEE_Ancestor(ui::Window);
    COFFEE_EndType();

namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    OutputBar::OutputBar() :
        _FilterAll(NULL),
        _FilterErrors(NULL),
        _FilterWarnings(NULL),
        _Clear(NULL),
        _Label(NULL),
        _Output(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    OutputBar::~OutputBar()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void OutputBar::Create(ui::Window* parent, uint32 height)
    {
        ui::Window::Create(parent, basic::Vector2i(), basic::Vector2i(0, height), ui::WINDOW_STYLE_None);
        GetLayout().SetStyle(
            ui::LAYOUT_STYLE_HorizontalCanvas
            | ui::LAYOUT_STYLE_StickChildren);
            
        _FilterAll = COFFEE_New(ui::widget::Button);
        _FilterAll->Create(this, basic::Vector2i(), basic::Vector2i(0, height), ui::widget::BUTTON_STYLE_PushLike);
        _FilterAll->SetText("All");
        _FilterAll->GetLayout().SetCanvas(60, false);

        _FilterErrors = COFFEE_New(ui::widget::Button);
        _FilterErrors->Create(this, basic::Vector2i(), basic::Vector2i(0, height), ui::widget::BUTTON_STYLE_PushLike);
        _FilterErrors->SetText("Errors");
        _FilterErrors->GetLayout().SetCanvas(60, false);

        _FilterWarnings = COFFEE_New(ui::widget::Button);
        _FilterWarnings->Create(this, basic::Vector2i(), basic::Vector2i(0, height), ui::widget::BUTTON_STYLE_PushLike);
        _FilterWarnings->SetText("Warnings");
        _FilterWarnings->GetLayout().SetCanvas(60, false);

        _Clear = COFFEE_New(ui::widget::Button);
        _Clear->Create(this, basic::Vector2i(), basic::Vector2i(0, height));
        _Clear->SetText("Clear");
        _Clear->GetLayout().SetCanvas(60, false);
        
        _Label = COFFEE_New(ui::widget::Label);
        _Label->Create(this, basic::Vector2i(), basic::Vector2i(0, height));
        _Label->SetStyle(ui::WINDOW_STYLE_Activable | ui::WINDOW_STYLE_DrawFrame
            | ui::WINDOW_STYLE_DrawClientSunken);
        _Label->GetLayout().SetCanvas(80, true);

        _Filter = FilterAll;
        _UpdateFilters();
    }

    //--------------------------------------------------------------------------------------------//

    void OutputBar::Update()
    {
        shell::Locker lock(_Mutex);
        ui::Window::Update();
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(OutputBar, ui::Window)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _FilterAll, OnFilterAll)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _FilterErrors, OnFilterErrors)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _FilterWarnings, OnFilterWarnings)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _Clear, OnClear)
        COFFEE_RegisterTargetEventHandler(ui::WINDOW_EVENT_Activate, ui::Window, _Label, OnOutput)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool OutputBar::OnFilterAll(shell::Event& event)
    {
        _Filter = FilterAll;
        return OnOutput(event);
    }
    
    //--------------------------------------------------------------------------------------------//

    bool OutputBar::OnFilterErrors(shell::Event& event)
    {
        _Filter = FilterErrors;
        return OnOutput(event);
    }
    
    //--------------------------------------------------------------------------------------------//

    bool OutputBar::OnFilterWarnings(shell::Event& event)
    {
        _Filter = FilterWarnings;
        return OnOutput(event);
    }

    //--------------------------------------------------------------------------------------------//

    bool OutputBar::OnClear(shell::Event& event)
    {
        _Log.SetEmpty();
        _LogType.Erase();
        _Label->SetText("");
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool OutputBar::OnOutput(shell::Event& event)
    {
        _UpdateFilters();
        if (_Output==NULL)
        {
            _Output = COFFEE_New(Output);
            _Output->Create(this);
            COFFEE_RegisterExternEventHandler(shell::EVENT_MESSAGE_Destroyed,
                shell::EventHandler::GetClassMetaType(), *_Output, OnDestroyOutput);

            for (uint32 i=0 ; i<_LogType.GetSize() ; ++i)
                OnLog(_LogType[i], _Log[i].GetBuffer(), false);
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool OutputBar::OnDestroyOutput(shell::Event& event)
    {
        _Output = NULL;
        return true;
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    void OutputBar::OnLog(core::Log::Type type, const char* message, bool it_has_to_add)
    {
        shell::Locker lock(_Mutex);
        if (it_has_to_add)
        {
            if (_LogType.GetSize()>=600)
            {
                _LogType.Remove(0);
                _Log.RemoveLine(0);
            }

            _LogType.AddItem(type);
            _Log.AddLine(message);

            if (_Label!=NULL)
                _Label->SetText(message);
        }

        if (_Output!=NULL)
        {
            if (_Filter==FilterAll
                || (_Filter==FilterWarnings && type==core::Log::Warning)
                || (_Filter==FilterErrors && type==core::Log::Error))
            {
                _Output->OnLog(type, message);
            }
        }
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void OutputBar::_UpdateFilters()
    {
        _FilterAll->SetState(_Filter==FilterAll?ui::widget::BUTTON_STATE_On:ui::widget::BUTTON_STATE_Off);
        _FilterErrors->SetState(_Filter==FilterErrors?ui::widget::BUTTON_STATE_On:ui::widget::BUTTON_STATE_Off);
        _FilterWarnings->SetState(_Filter==FilterWarnings?ui::widget::BUTTON_STATE_On:ui::widget::BUTTON_STATE_Off);
    }

}
}
