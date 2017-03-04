#include "widget/gizmo_controller/widget_gizmo_controller.h"

namespace coffee_editor
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    GizmoController::GizmoController() :
        _Document(NULL),
        _Pick(NULL),
        _Translate(NULL),
        _Rotate(NULL),
        _Scale(NULL),
        _Reference(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    GizmoController::~GizmoController()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void GizmoController::Create(ui::widget::ToolBar& tool_bar, Document& document)
    {
        _Document = &document;

        ui::Window* window = tool_bar.AddWindow(204);
        ui::Window::Create(
            window,
            basic::Vector2i(),
            basic::Vector2i(), ui::WINDOW_STYLE_None);
        GetLayout().SetStyle(ui::LAYOUT_STYLE_Expand | ui::LAYOUT_STYLE_HorizontalCanvas
            | ui::LAYOUT_STYLE_StickChildren);
        
        window = COFFEE_New(ui::Window);
        window->Create(this, basic::Vector2i(), basic::Vector2i(8, 30), 0);
        
        _Pick = COFFEE_New(ui::widget::Button);
        _Pick->Create(this, basic::Vector2i(), basic::Vector2i(30, 30),
            ui::widget::BUTTON_STYLE_HideFrame);
        _Pick->SetImage("/coffee/import/editor/icons/gizmo_pick.texture");
        _Pick->SetHelpText("Pick mode");
        
        _Translate = COFFEE_New(ui::widget::Button);
        _Translate->Create(this, basic::Vector2i(), basic::Vector2i(30, 30),
            ui::widget::BUTTON_STYLE_HideFrame);
        _Translate->SetImage("/coffee/import/editor/icons/gizmo_translate.texture");
        _Translate->SetHelpText("Translate mode");
        
        _Rotate = COFFEE_New(ui::widget::Button);
        _Rotate->Create(this, basic::Vector2i(), basic::Vector2i(30, 30),
            ui::widget::BUTTON_STYLE_HideFrame);
        _Rotate->SetImage("/coffee/import/editor/icons/gizmo_rotate.texture");
        _Rotate->SetHelpText("Rotate mode");
        
        _Scale = COFFEE_New(ui::widget::Button);
        _Scale->Create(this, basic::Vector2i(), basic::Vector2i(30, 30),
            ui::widget::BUTTON_STYLE_HideFrame);
        _Scale->SetImage("/coffee/import/editor/icons/gizmo_scale.texture");
        _Scale->SetHelpText("Scale mode");
        
        _Reference = COFFEE_New(ui::widget::Button);
        _Reference->Create(this, basic::Vector2i(), basic::Vector2i(70, 30),
            ui::widget::BUTTON_STYLE_HideFrame | ui::widget::BUTTON_STYLE_Default);
        _Reference->SetText("Local");
        _Reference->SetHelpText("Gizmo reference");        
    }

    //--------------------------------------------------------------------------------------------//

    void GizmoController::Update()
    {
        if (!resource::Manager::IsAvailable()
            || !ui::WindowManager::IsAvailable())
        {
            ui::Window::Update();
            return;
        }

        if (_Pick->IsEnabled()!=IsEnabled())
        {
            _Pick->Enable(IsEnabled());
            _Translate->Enable(IsEnabled());
            _Rotate->Enable(IsEnabled());
            _Scale->Enable(IsEnabled());
        }

        bool it_is_active = IsActive();
        edition::PluginNodeController* controller(NULL);

        if (it_is_active)
        {
            controller = static_cast<edition::PluginNodeController*>(&_Document->GetHeadActiveControl());
        
            _Reference->Enable(true);
            switch (controller->GetReference())
            {
                case scene::TRS_Local:
                    _Reference->SetText("Local");
                    break;
                case scene::TRS_Parent:
                    _Reference->SetText("Parent");
                    break;
                case scene::TRS_World:
                    _Reference->SetText("World");
                    break;
                default: break;
            }
        }
        else
        {
            _Reference->Enable(false);
        }

        if ((_Pick->GetState()==ui::widget::BUTTON_STATE_On)
            !=(it_is_active&&(controller->GetMode()==edition::GIZMO_MODE_Select)))
        {
            _Pick->SetState((it_is_active&&(controller->GetMode()==edition::GIZMO_MODE_Select))?
                ui::widget::BUTTON_STATE_On:ui::widget::BUTTON_STATE_Off);
        }

        if ((_Translate->GetState()==ui::widget::BUTTON_STATE_On)
            !=(it_is_active&&(controller->GetMode()==edition::GIZMO_MODE_Translate)))
        {
            _Translate->SetState((it_is_active&&(controller->GetMode()==edition::GIZMO_MODE_Translate))?
                ui::widget::BUTTON_STATE_On:ui::widget::BUTTON_STATE_Off);
        }

        if ((_Rotate->GetState()==ui::widget::BUTTON_STATE_On)
            !=(it_is_active&&(controller->GetMode()==edition::GIZMO_MODE_Rotate)))
        {
            _Rotate->SetState((it_is_active&&(controller->GetMode()==edition::GIZMO_MODE_Rotate))?
                ui::widget::BUTTON_STATE_On:ui::widget::BUTTON_STATE_Off);
        }

        if ((_Scale->GetState()==ui::widget::BUTTON_STATE_On)
            !=(it_is_active&&(controller->GetMode()==edition::GIZMO_MODE_Scale)))
        {
            _Scale->SetState((it_is_active&&(controller->GetMode()==edition::GIZMO_MODE_Scale))?
                ui::widget::BUTTON_STATE_On:ui::widget::BUTTON_STATE_Off);
        }

        ui::Window::Update();
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(GizmoController, ui::Window)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _Pick, OnPick)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _Translate, OnTranslate)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _Rotate, OnRotate)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _Scale, OnScale)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _Reference, OnReference)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool GizmoController::OnPick(shell::Event& event)
    {
        SetMode(edition::GIZMO_MODE_Select);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool GizmoController::OnTranslate(shell::Event& event)
    {
        SetMode(edition::GIZMO_MODE_Translate);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool GizmoController::OnRotate(shell::Event& event)
    {
        SetMode(edition::GIZMO_MODE_Rotate);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool GizmoController::OnScale(shell::Event& event)
    {
        SetMode(edition::GIZMO_MODE_Scale);
        return true;
    }
    
    //--------------------------------------------------------------------------------------------//

    bool GizmoController::OnReference(shell::Event& event)
    {
        edition::PluginNodeController* controller = static_cast<edition::PluginNodeController*>(&_Document->GetHeadActiveControl());
        
        ui::widget::Menu* menu = COFFEE_New(ui::widget::Menu);
        ui::WindowContext context;
        context.Create(_Reference);
        menu->Create(NULL, basic::Vector2i(
            context.GetDesktopWindowRect().GetMinimum().X,
            context.GetDesktopWindowRect().GetMaximum().Y), basic::Vector2i());
        
        ui::widget::Button* button;

        button = menu->AddPushButton("Local", controller->GetReference()==scene::TRS_Local);
        button->SetExtendedStyle(ui::widget::BUTTON_STYLE_HideFrame);
        button->SetSize(basic::Vector2i(70, 20));
        button->SetText("Local");
        button->SetHelpText("Local");
        COFFEE_RegisterExternEventHandler( ui::widget::EVENT_Pressed, ui::widget::Widget::GetClassMetaType(),
            *button, OnSetReferenceLocal);
        
        button = menu->AddPushButton("Parent", controller->GetReference()==scene::TRS_Parent);
        button->SetExtendedStyle(ui::widget::BUTTON_STYLE_HideFrame);
        button->SetSize(basic::Vector2i(70, 20));
        button->SetText("Parent");
        button->SetHelpText("Parent");
        COFFEE_RegisterExternEventHandler( ui::widget::EVENT_Pressed, ui::widget::Widget::GetClassMetaType(),
            *button, OnSetReferenceParent);
        
        button = menu->AddPushButton("World", controller->GetReference()==scene::TRS_World);
        button->SetExtendedStyle(ui::widget::BUTTON_STYLE_HideFrame);
        button->SetSize(basic::Vector2i(70, 20));
        button->SetText("World");
        button->SetHelpText("World");
        COFFEE_RegisterExternEventHandler( ui::widget::EVENT_Pressed, ui::widget::Widget::GetClassMetaType(),
            *button, OnSetReferenceWorld);

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool GizmoController::OnSetReferenceLocal(shell::Event& event)
    {
        edition::PluginNodeController* controller = static_cast<edition::PluginNodeController*>(&_Document->GetHeadActiveControl());
        controller->SetReference(scene::TRS_Local);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool GizmoController::OnSetReferenceParent(shell::Event& event)
    {
        edition::PluginNodeController* controller = static_cast<edition::PluginNodeController*>(&_Document->GetHeadActiveControl());
        controller->SetReference(scene::TRS_Parent);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool GizmoController::OnSetReferenceWorld(shell::Event& event)
    {
        edition::PluginNodeController* controller = static_cast<edition::PluginNodeController*>(&_Document->GetHeadActiveControl());
        controller->SetReference(scene::TRS_World);
        return true;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool GizmoController::IsActive() const
    {
        return _Document->HasActiveControl()
            && _Document->GetHeadActiveControl().IsKindOf<edition::PluginNodeController>();
    }

    //--------------------------------------------------------------------------------------------//

    bool GizmoController::IsEnabled() const
    {
        bool it_has_control(false);
        if (_Document->HasActiveControl())
        {
            // search in current control children
            {
                const ApplicationControl& control = _Document->GetActiveControl().GetHeadActiveControl();
                for (uint32 index=0 ; index<control.GetChildCount() ; ++index)
                {
                    if (control.GetChild(index).IsKindOf<edition::PluginNodeController>())
                    {
                        it_has_control = true;
                        break;
                    }
                }
            }

            // search in current control group children
            {
                const ApplicationControl& control = _Document->GetActiveControl().GetHeadActiveControlGroup();
                for (uint32 index=0 ; index<control.GetChildCount() ; ++index)
                {
                    if (control.GetChild(index).IsKindOf<edition::PluginNodeController>())
                    {
                        it_has_control = true;
                        break;
                    }
                }
            }
        }
        return IsActive() || it_has_control;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void GizmoController::SetMode(edition::GIZMO_MODE mode)
    {
        edition::PluginNodeController* controller(NULL);
        
        if (_Document->HasActiveControl() && _Document->GetHeadActiveControl().IsKindOf<edition::PluginNodeController>())
        {
            controller = static_cast<edition::PluginNodeController*>(&_Document->GetHeadActiveControl());
        }
        else
        {
            // search in current control children
            {
                const ApplicationControl& control = _Document->GetActiveControl().GetHeadActiveControl();
                for (uint32 index=0 ; index<control.GetChildCount() ; ++index)
                {
                    if (control.GetChild(index).IsKindOf<edition::PluginNodeController>())
                    {
                        controller = (edition::PluginNodeController*)&control.GetChild(index);
                        controller->Activate();
                        break;
                    }
                }
            }

            // search in current control group children
            {
                const ApplicationControl& control = _Document->GetActiveControl().GetHeadActiveControlGroup();
                for (uint32 index=0 ; index<control.GetChildCount() ; ++index)
                {
                    if (control.GetChild(index).IsKindOf<edition::PluginNodeController>())
                    {
                        controller = (edition::PluginNodeController*)&control.GetChild(index);
                        controller->Activate();
                        break;
                    }
                }
            }
        }

        if (controller==NULL)
            COFFEE_Error(core::ERROR_CODE_IncorrectUsage, "Unexpected error");

        controller->SetMode(mode);
    }

}
}
