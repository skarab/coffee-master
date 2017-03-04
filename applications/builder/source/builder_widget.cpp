#include "builder_widget.h"

namespace builder
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Widget::Widget()
    {
        ui::Window::Create(NULL, basic::Vector2i(), basic::Vector2i(),
            ui::WINDOW_STYLE_DrawFrame);
        GetLayout().SetStyle(ui::LAYOUT_STYLE_Expand
            | ui::LAYOUT_STYLE_VerticalCanvas
            | ui::LAYOUT_STYLE_StickChildren);

        ui::Window* frame = COFFEE_New(ui::Window);
        frame->Create(this, basic::Vector2i(), basic::Vector2i(), ui::WINDOW_STYLE_DrawFrame);
        frame->GetLayout().SetStyle(ui::LAYOUT_STYLE_HorizontalExpand
            | ui::LAYOUT_STYLE_VerticalShrink
            | ui::LAYOUT_STYLE_HorizontalCanvas | ui::LAYOUT_STYLE_StickChildren);

        {
            ui::widget::Image* logo = COFFEE_New(ui::widget::Image);
            logo->Create(frame, basic::Vector2i(), basic::Vector2i(), ui::widget::IMAGE_STYLE_AutoSize);
            logo->SetImage("/coffee/import/editor/logo.texture");
            logo->GetLayout().SetCanvas(320, false);

            ui::Window* spacing = COFFEE_New(ui::Window);
            spacing->Create(frame, basic::Vector2i(), basic::Vector2i(), ui::WINDOW_STYLE_None);
            spacing->GetLayout().SetCanvas(10, false);
            
            ui::Window* layout = COFFEE_New(ui::Window);
            layout->Create(frame, basic::Vector2i(), basic::Vector2i(), ui::WINDOW_STYLE_None);
            layout->GetLayout().SetStyle(
                ui::LAYOUT_STYLE_VerticalShrink
                | ui::LAYOUT_STYLE_VerticalCanvas
                | ui::LAYOUT_STYLE_StickChildren);
            layout->GetLayout().SetCanvas(100, true);
            
            {
                spacing = COFFEE_New(ui::Window);
                spacing->Create(layout, basic::Vector2i(), basic::Vector2i(), ui::WINDOW_STYLE_None);
                spacing->GetLayout().SetCanvas(15, false);
                        
                _Properties = COFFEE_New(ui::PropertyList);
                _Properties->Create(_Config, basic::Vector2i(), basic::Vector2i(), layout, false);

                spacing = COFFEE_New(ui::Window);
                spacing->Create(layout, basic::Vector2i(), basic::Vector2i(), ui::WINDOW_STYLE_None);
                spacing->GetLayout().SetCanvas(15, false);

                ui::Window* controls = COFFEE_New(ui::Window);
                controls->Create(layout, basic::Vector2i(), basic::Vector2i(), ui::WINDOW_STYLE_DrawFrame | ui::WINDOW_STYLE_DrawClientSunken);
                controls->GetLayout().SetStyle(ui::LAYOUT_STYLE_HorizontalExpand
                    | ui::LAYOUT_STYLE_HorizontalCanvas | ui::LAYOUT_STYLE_StickChildren);
                controls->GetLayout().SetCanvas(24, false);

                {
                    _Run = COFFEE_New(ui::widget::Button);
                    _Run->Create(controls, basic::Vector2i(), basic::Vector2i());
                    _Run->GetLayout().SetStyle(ui::LAYOUT_STYLE_VerticalExpand);
                    _Run->GetLayout().SetCanvas(100, true);
                    _Run->SetText("Run");

                    _GenerateWorkspace = COFFEE_New(ui::widget::Button);
                    _GenerateWorkspace->Create(controls, basic::Vector2i(), basic::Vector2i());
                    _GenerateWorkspace->GetLayout().SetStyle(ui::LAYOUT_STYLE_VerticalExpand);
                    _GenerateWorkspace->GetLayout().SetCanvas(100, true);
                    _GenerateWorkspace->SetText("Generate Workspace");
                }

                spacing = COFFEE_New(ui::Window);
                spacing->Create(layout, basic::Vector2i(), basic::Vector2i(), ui::WINDOW_STYLE_None);
                spacing->GetLayout().SetCanvas(15, false);
            }

            spacing = COFFEE_New(ui::Window);
            spacing->Create(frame, basic::Vector2i(), basic::Vector2i(), ui::WINDOW_STYLE_None);
            spacing->GetLayout().SetCanvas(10, false);
        }

        _Output = COFFEE_New(ui::widget::ListView);
        _Output->Create(this, basic::Vector2i(), basic::Vector2i(), ui::widget::VIEW_CONTROL_STYLE_FollowCursorOnAdd);
        _Output->GetLayout().SetStyle(ui::LAYOUT_STYLE_HorizontalExpand);
        _Output->GetLayout().SetCanvas(100, true);

         ui::Window* controls = COFFEE_New(ui::Window);
        controls->Create(this, basic::Vector2i(), basic::Vector2i(),
            ui::WINDOW_STYLE_DrawFrame | ui::WINDOW_STYLE_DrawClientRaised);
        controls->GetLayout().SetStyle(
            ui::LAYOUT_STYLE_HorizontalExpand
            | ui::LAYOUT_STYLE_HorizontalCanvas
            | ui::LAYOUT_STYLE_StickChildren);
        controls->GetLayout().SetCanvas(30, false);
            
        {
            _Clear = COFFEE_New(ui::widget::Button);
            _Clear->Create(controls, basic::Vector2i(), basic::Vector2i());
            _Clear->GetLayout().SetStyle(ui::LAYOUT_STYLE_VerticalExpand);
            _Clear->GetLayout().SetCanvas(100, false);
            _Clear->SetText("Clear");

            ui::Window* spacing = COFFEE_New(ui::Window);
            spacing->Create(controls, basic::Vector2i(), basic::Vector2i(), ui::WINDOW_STYLE_None);
            spacing->GetLayout().SetCanvas(100, true);

            _Stop = COFFEE_New(ui::widget::Button);
            _Stop->Create(controls, basic::Vector2i(), basic::Vector2i());
            _Stop->GetLayout().SetStyle(ui::LAYOUT_STYLE_VerticalExpand);
            _Stop->GetLayout().SetCanvas(100, false);
            _Stop->SetText("Stop!");
        }

        _EnableControls(false);
    }

    //--------------------------------------------------------------------------------------------//

    Widget::~Widget()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Widget::Update()
    {
        if (!_Run->IsEnabled())
        {
            if (!core::Platform::Get().IsPipeRunning())
            {
                _Output->AddOutput(core::Platform::Get().GetPipeOutput());

                if (core::Platform::Get().GetPipeReturnCode()==0)
                {
                    _Output->AddOutput("\nSucceeded!");
                }
                else
                {
                    _Output->AddOutput("\nFailed!");
                }

                _EnableControls(false);
            }
            else
            {
                _Output->AddOutput(core::Platform::Get().GetPipeOutput());
            }
        }
        
        Window::Update();
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(Widget, ui::Window)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _Run, OnRun)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _GenerateWorkspace, OnGenerateWorkspace)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _Clear, OnClear)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _Stop, OnStop)
    COFFEE_EndEventHandler()
    
    //--------------------------------------------------------------------------------------------//

    bool Widget::OnRun(shell::Event& event)
    {
        _Output->RemoveItems();

        basic::String cmd = storage::System::Get().GetRootPath()+"/tools/python/python.exe "
            + storage::System::Get().GetRootPath()+"/tools/scripts/build.py ";

        switch (_Config.GetOperation())
        {
            case OPERATION_rebuild: cmd += "full ";  break;
            case OPERATION_clean: cmd += "clean ";  break;
            default: break;
        }

        cmd += _Config.GetTarget() + " ";
        cmd += _Config.GetPlatform() + " ";
        cmd += _Config.GetCompiler() + " ";
        cmd += _Config.GetMode() + " ";

        if (core::Platform::Get().RunPipe(cmd, storage::System::Get().GetRootPath(), false))
            _EnableControls(true);
        return true;
    }
    
    //--------------------------------------------------------------------------------------------//

    bool Widget::OnGenerateWorkspace(shell::Event& event)
    {
        _Output->RemoveItems();
        
        basic::String cmd = storage::System::Get().GetRootPath()+"/tools/python/python.exe "
            + storage::System::Get().GetRootPath()+ "/tools/scripts/generate_workspace.py ";
        cmd += _Config.GetCompiler() + " ";
        if (core::Platform::Get().RunPipe(cmd, storage::System::Get().GetRootPath(), false))
            _EnableControls(true);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Widget::OnClear(shell::Event& event)
    {
        _Output->RemoveItems();
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Widget::OnStop(shell::Event& event)
    {
        core::Platform::Get().StopPipe();
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    void Widget::_EnableControls(bool it_is_building)
    {
        _Run->Enable(!it_is_building);
        _GenerateWorkspace->Enable(!it_is_building);
        _Stop->Enable(it_is_building);
    }

}
