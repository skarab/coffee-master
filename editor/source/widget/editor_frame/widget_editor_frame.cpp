#include "widget/editor_frame/widget_editor_frame.h"

namespace coffee_editor
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    EditorFrame::EditorFrame() :
        _MainFrame(NULL),
        _StatusFrame(NULL),
        _StatusProgressLabel(NULL),
        _StatusProgress(NULL),
        _StatusSubProgress(NULL),
        _OutputBar(NULL),
        _Debugger(NULL),
        _BodyFrame(NULL),
        _SceneMDI(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    EditorFrame::~EditorFrame()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void EditorFrame::Initialize()
    {
        // Main frame

        _MainFrame = COFFEE_New(ui::Window);
        _MainFrame->Create(NULL, basic::Vector2i(), basic::Vector2i(),
            ui::WINDOW_STYLE_BottomMost);
        _MainFrame->GetLayout().SetStyle(
            ui::LAYOUT_STYLE_Expand
            | ui::LAYOUT_STYLE_VerticalCanvas
            | ui::LAYOUT_STYLE_StickChildren);

        // Body frame

        _BodyFrame = COFFEE_New(ui::Window);
        _BodyFrame->Create(_MainFrame, basic::Vector2i(), basic::Vector2i(), 0);
        _BodyFrame->GetLayout().SetStyle(ui::LAYOUT_STYLE_HorizontalExpand
            | ui::LAYOUT_STYLE_HorizontalCanvas | ui::LAYOUT_STYLE_StickChildren);
        _BodyFrame->GetLayout().SetCanvas(100, true);
        
        {
            // Create Explorer

            Explorer* explorer = COFFEE_New(Explorer);
            explorer->Create(*_BodyFrame);
    
            // Client frame

            ui::Window* full_client = COFFEE_New(ui::Window);
            full_client->Create(_BodyFrame, basic::Vector2i(), basic::Vector2i(),
                ui::WINDOW_STYLE_Focusable | ui::WINDOW_STYLE_ForwardsInput);
            full_client->GetLayout().SetCanvas(100, true);
            full_client->GetLayout().SetStyle(ui::LAYOUT_STYLE_VerticalExpand
                | ui::LAYOUT_STYLE_VerticalCanvas
                | ui::LAYOUT_STYLE_StickChildren);

            {
                _SceneMDI = COFFEE_New(MDI);
                _SceneMDI->Create(*full_client);
            }

            // Create Properties

            Properties* properties = COFFEE_New(Properties);
            properties->Create(*_BodyFrame);
        }

        // Status bars

        _StatusFrame = COFFEE_New(ui::Window);
        _StatusFrame->Create(_MainFrame, basic::Vector2i(), basic::Vector2i(0, 30),
            ui::WINDOW_STYLE_DrawFrame | ui::WINDOW_STYLE_DrawClientRaised);
        _StatusFrame->GetLayout().SetCanvas(30, false);
        _StatusFrame->GetLayout().SetStyle(
            ui::LAYOUT_STYLE_HorizontalExpand
            | ui::LAYOUT_STYLE_HorizontalCanvas
            | ui::LAYOUT_STYLE_StickChildren);

        {
            _OutputBar = COFFEE_New(OutputBar);
            _OutputBar->Create(_StatusFrame, 28);
            _OutputBar->GetLayout().SetCanvas(60, true);

            _Debugger = COFFEE_New(Debugger);
            _Debugger->Create(_StatusFrame, 28);
            _Debugger->GetLayout().SetCanvas(20, true);
        
            ui::Window* status = COFFEE_New(ui::Window);
            status->Create(_StatusFrame, basic::Vector2i(), basic::Vector2i(280, 30),
                ui::WINDOW_STYLE_DrawFrame | ui::WINDOW_STYLE_DrawClientSunken);
            status->GetLayout().SetCanvas(280, false);
            
            _StatusProgressLabel = COFFEE_New(ui::widget::Label);
            _StatusProgressLabel->Create(status, basic::Vector2i(2,0), basic::Vector2i(276, 15));
            
            _StatusProgress = COFFEE_New(ui::widget::ProgressBar);
            _StatusProgress->Create(status, basic::Vector2i(2,15), basic::Vector2i(276, 8));
        
            _StatusSubProgress = COFFEE_New(ui::widget::ProgressBar);
            _StatusSubProgress->Create(status, basic::Vector2i(2,23), basic::Vector2i(276, 5));
        }
    }

    //--------------------------------------------------------------------------------------------//

    void EditorFrame::Finalize()
    {
    }

    //--------------------------------------------------------------------------------------------//

    void EditorFrame::SetProgress(basic::String text, real percentage)
    {
        if (_StatusProgressLabel!=NULL)
            _StatusProgressLabel->SetText(text);
        if (_StatusProgress!=NULL)
            _StatusProgress->SetPercentage(percentage);
    }

    //--------------------------------------------------------------------------------------------//

    void EditorFrame::SetSubProgress(real percentage)
    {
        if (_StatusSubProgress!=NULL)
            _StatusSubProgress->SetPercentage(percentage);
    }
       
}
}
