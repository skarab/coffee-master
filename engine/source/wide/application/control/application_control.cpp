#include "wide/application/control/application_control.h"
#include "wide/application/application.h"
#include "wide/edition/plugin/edition_plugin.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ApplicationControl);
        COFFEE_Ancestor(input::Handler);
    COFFEE_EndType();

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ApplicationControl::ApplicationControl(basic::String name, basic::String help_text) :
        _Name(name),
        _HelpText(help_text),
        _CommandButton(NULL),
        _ActiveControl(NULL),
        _Command(NULL),
        _Viewport(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    ApplicationControl::~ApplicationControl()
    {
        if (_Command!=NULL)
            COFFEE_Delete(_Command);
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const basic::String& ApplicationControl::GetName() const
    {
        return _Name;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::String& ApplicationControl::GetHelpText() const
    {
        return _HelpText;
    }

    //--------------------------------------------------------------------------------------------//
    
    const ApplicationControl& ApplicationControl::GetActiveControl() const
    {
        return *_ActiveControl;
    }

    //--------------------------------------------------------------------------------------------//

    ApplicationControl& ApplicationControl::GetActiveControl()
    {
        return *_ActiveControl;
    }

    //--------------------------------------------------------------------------------------------//

    const ApplicationControl& ApplicationControl::GetHeadActiveControl() const
    {
        if (HasActiveControl())
            return GetActiveControl().GetHeadActiveControl();

        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    ApplicationControl& ApplicationControl::GetHeadActiveControl()
    {
        if (HasActiveControl())
            return GetActiveControl().GetHeadActiveControl();

        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    const ApplicationControl& ApplicationControl::GetHeadActiveControlGroup() const
    {
        if (HasActiveControl() && GetActiveControl().HasChildren())
            return GetActiveControl().GetHeadActiveControlGroup();

        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    ApplicationControl& ApplicationControl::GetHeadActiveControlGroup()
    {
        if (HasActiveControl() && GetActiveControl().HasChildren())
            return GetActiveControl().GetHeadActiveControlGroup();

        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    edition::Plugin* ApplicationControl::GetPlugin()
    {
        edition::Plugin* plugin(NULL);
        shell::EventHandler* node = this;
        while(node->HasParent())
        {
            if (node->IsKindOf<edition::Plugin>())
            {
                return static_cast<edition::Plugin*>(node);
            }

            node = &node->GetParent();
        }
        return NULL;
    }

	//--------------------------------------------------------------------------------------------//

    const edition::Plugin* ApplicationControl::GetPlugin() const
    {
        const shell::EventHandler* node = this;
        while(node->HasParent())
        {
            if (node->IsKindOf<edition::Plugin>())
            {
                return static_cast<const edition::Plugin*>(node);
            }

            node = &node->GetParent();
        }
        return NULL;
    }

    //--------------------------------------------------------------------------------------------//

    edition::UndoManager* ApplicationControl::GetUndoManager()
    {
        edition::Plugin* plugin = GetPlugin();
        if (plugin!=NULL)
            return &plugin->GetUndoManager();
        return NULL;
    }
        
    //--------------------------------------------------------------------------------------------//

    edition::SelectionManager* ApplicationControl::GetSelectionManager()
    {
        edition::Plugin* plugin = GetPlugin();
        if (plugin!=NULL)
            return &plugin->GetSelectionManager();
        return NULL;
    }

	//--------------------------------------------------------------------------------------------//

    const edition::SelectionManager* ApplicationControl::GetSelectionManager() const
    {
        const edition::Plugin* plugin = GetPlugin();
        if (plugin!=NULL)
            return &plugin->GetSelectionManager();
        return NULL;
    }

	//--------------------------------------------------------------------------------------------//

    const input::Command& ApplicationControl::GetCommand() const
    {
        return *_Command;
    }
    
    //--------------------------------------------------------------------------------------------//

    input::Command& ApplicationControl::GetCommand()
    {
        return *_Command;
    }
    
    //--------------------------------------------------------------------------------------------//

    const basic::Prow<input::Command*, true>& ApplicationControl::GetCommandArray() const
    {
        return _CommandArray;
    }
    
    //--------------------------------------------------------------------------------------------//

    basic::Prow<input::Command*, true>& ApplicationControl::GetCommandArray()
    {
        return _CommandArray;
    }

    //--------------------------------------------------------------------------------------------//

    void ApplicationControl::SetViewport(graphics::Viewport* viewport)
    {
        _Viewport = viewport;
    }
    
    //--------------------------------------------------------------------------------------------//

    const graphics::Viewport& ApplicationControl::GetViewport() const
    {
        return *_Viewport;
    }
    
    //--------------------------------------------------------------------------------------------//

    graphics::Viewport& ApplicationControl::GetViewport()
    {
        return *_Viewport;
    }

    //--------------------------------------------------------------------------------------------//

    graphics::Viewport& ApplicationControl::GetParentViewport()
    {
        if (HasViewport())
            return GetViewport();

        if (HasParent() && GetParent().IsKindOf<ApplicationControl>())
        {
            ApplicationControl* parent(static_cast<ApplicationControl*>(&GetParent()));
            return parent->GetParentViewport();
        }

        COFFEE_Error(core::ERROR_CODE_IncorrectUsage, "Parent controls have not viewport.");
        return *_Viewport;
    }
        
    //-QUERIES------------------------------------------------------------------------------------//

    bool ApplicationControl::IsUsable() const
    {
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool ApplicationControl::IsValid() const
    {
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool ApplicationControl::IsActive() const
    {
        if (HasParent() && GetParent().IsKindOf<ApplicationControl>())
        {
            const ApplicationControl* parent(static_cast<const ApplicationControl*>(&GetParent()));
            return (parent->_ActiveControl==this);
        }

        return IsEnabled();
    }

    //--------------------------------------------------------------------------------------------//

    bool ApplicationControl::HasActiveControl() const
    {
        return (_ActiveControl != NULL);
    }

    //--------------------------------------------------------------------------------------------//

    bool ApplicationControl::HasCommand() const
    {
        return _Command!=NULL;
    }

    //--------------------------------------------------------------------------------------------//

    bool ApplicationControl::HasViewport() const
    {
        return _Viewport!=NULL;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ApplicationControl::Register(ApplicationControl& control, input::Command* command)
    {
        if (command!=NULL)
        {
            control._Command = command;
            control._Command->SetName(control._Name);
            control._Command->SetDescription(control._HelpText);
        }
        
        input::Handler::Register(control);
        control.Initialize();
    }

    //--------------------------------------------------------------------------------------------//

    void ApplicationControl::Unregister()
    {
        Finalize();
        input::Handler::Unregister();
    }

    //--------------------------------------------------------------------------------------------//

    void ApplicationControl::Initialize()
    {
        OnInitialize();
    }

    //--------------------------------------------------------------------------------------------//

    void ApplicationControl::Finalize()
    {
        OnFinalize();
    }

    //--------------------------------------------------------------------------------------------//

    void ApplicationControl::Activate()
    {
        if (HasParent() && GetParent().IsKindOf<ApplicationControl>())
        {
            ApplicationControl* parent(static_cast<ApplicationControl*>(&GetParent()));

            if (parent->HasActiveControl())
                parent->GetActiveControl().Deactivate();

            parent->_ActiveControl = this;
        }

        OnActivate();
    }

    //--------------------------------------------------------------------------------------------//

    void ApplicationControl::Deactivate()
    {
        if (HasParent() && GetParent().IsKindOf<ApplicationControl>())
        {
            ApplicationControl * parent(static_cast<ApplicationControl*>(&GetParent()));
            parent->_ActiveControl = NULL;
        }

        OnDeactivate();
    }

    //--------------------------------------------------------------------------------------------//

    void ApplicationControl::DeactivateChildren()
    {
        while(HasActiveControl())
        {
            GetHeadActiveControl().Deactivate();
        }
    }
        
    //--------------------------------------------------------------------------------------------//

    void ApplicationControl::Update(const basic::Time& time_step)
    {
        if (!_CheckValidity())
            return;

        input::Handler::Update();
        for (uint32 index=0 ; index<GetChildCount() ; ++index)
            ((ApplicationControl*)&GetChild(index))->Update(time_step);

        if (_CheckValidity() && IsEnabled())
            OnUpdate(time_step);
    }

    //--------------------------------------------------------------------------------------------//

    void ApplicationControl::Render(graphics::Viewport& viewport, bool it_is_transparent, bool it_is_hdr)
    {
        if (HasViewport() && &GetViewport()!=&viewport)
            return;

        if (_CheckValidity() && IsEnabled())
            OnRender(viewport, it_is_transparent, it_is_hdr);
    
        for (uint32 index=0 ; index<GetChildCount() ; ++index)
            ((ApplicationControl*)&GetChild(index))->Render(viewport, it_is_transparent, it_is_hdr);
    }

    //--------------------------------------------------------------------------------------------//

    void ApplicationControl::Destroy()
    {
        if (IsActive())
            Deactivate();

        Unregister();
        input::Handler::Destroy();
    }

    //--------------------------------------------------------------------------------------------//

    void ApplicationControl::PopulateToolBar(ui::widget::ToolBar& tool_bar)
    {
        tool_bar.DestroyChildren();
        for (uint32 index=0 ; index<GetChildCount() ; ++index)
            ((ApplicationControl*)&GetChild(index))->OnPopulateToolBar(tool_bar);
    }

    //--------------------------------------------------------------------------------------------//

    void ApplicationControl::UpdateToolBar(ui::widget::ToolBar& tool_bar)
    {
        for (uint32 index=0 ; index<GetChildCount() ; ++index)
             ((ApplicationControl*)&GetChild(index))->OnUpdateToolBar(tool_bar);
    }

    //--------------------------------------------------------------------------------------------//

    void ApplicationControl::RegisterCommand(input::Command* command)
    {
        _CommandArray.AddItem(command);
    }
        
    //-HANDLERS-----------------------------------------------------------------------------------//

    void ApplicationControl::OnInitialize()
    {
        Enable(false);
    }

    //--------------------------------------------------------------------------------------------//

    void ApplicationControl::OnFinalize()
    {
        for (uint32 index=0 ; index<GetChildCount() ; ++index)
        {
            if (((ApplicationControl*)&GetChild(index))->_Command!=NULL)
            {
                input::System::Get().UnregisterCommand(
                    ((ApplicationControl*)&GetChild(index))->_Command);
            }
        }
        
        for (uint32 index=0 ; index<_CommandArray.GetSize() ; ++index)
            input::System::Get().UnregisterCommand(_CommandArray[index]);
    }

    //--------------------------------------------------------------------------------------------//

    void ApplicationControl::OnActivate()
    {
        Enable(true, false);
        _ChildActivate(*this);
        
        for (uint32 index=0 ; index<GetChildCount() ; ++index)
        {
            if (((ApplicationControl*)&GetChild(index))->_Command!=NULL)
            {
                input::System::Get().RegisterCommand(
                    ((ApplicationControl*)&GetChild(index))->_Command);
            }
        }

        for (uint32 index=0 ; index<_CommandArray.GetSize() ; ++index)
            input::System::Get().RegisterCommand(_CommandArray[index]);
    }

    //--------------------------------------------------------------------------------------------//

    void ApplicationControl::OnDeactivate()
    {
        if (HasParent())
            DeactivateChildren();

        Enable(false, false);
        _ChildDeactivate(*this);

        for (uint32 index=0 ; index<GetChildCount() ; ++index)
        {
            if (((ApplicationControl*)&GetChild(index))->_Command!=NULL)
            {
                input::System::Get().UnregisterCommand(
                    ((ApplicationControl*)&GetChild(index))->_Command);
            }
        }
        
        for (uint32 index=0 ; index<_CommandArray.GetSize() ; ++index)
            input::System::Get().UnregisterCommand(_CommandArray[index]);
    }

    //--------------------------------------------------------------------------------------------//

    void ApplicationControl::OnChildActivate(ApplicationControl& control)
    {
        _ChildActivate(control);
    }

    //--------------------------------------------------------------------------------------------//

    void ApplicationControl::OnChildDeactivate(ApplicationControl& control)
    {
        _ChildDeactivate(control);
    }

    //--------------------------------------------------------------------------------------------//

    void ApplicationControl::OnPopupMenu(ui::widget::Menu& menu)
    {
    }

    //--------------------------------------------------------------------------------------------//

    void ApplicationControl::OnPopulateToolBar(ui::widget::ToolBar& tool_bar)
    {
        if (GetName().GetLength()>0)
        {
            _CommandButton = tool_bar.AddButton(GetName(),
                ui::widget::BUTTON_STYLE_HideFrame | ui::widget::BUTTON_STYLE_PushLike);
            _CommandButton->SetSize(basic::Vector2i(100, 30));

            if (_Command!=NULL)
            {
                _CommandButton->SetHelpText(_Command->GetDescription()+" ["+_Command->GetControlString()+"]");
            }

            COFFEE_RegisterExternEventHandler(
                ui::widget::EVENT_Pressed,
                ui::widget::Widget::GetClassMetaType(),
                *_CommandButton, OnCommandButton);

            COFFEE_RegisterExternEventHandler(
                ui::WINDOW_EVENT_BeginCursorOver,
                ui::Window::GetClassMetaType(),
                *_CommandButton, OnBeginCursorOver);

            COFFEE_RegisterExternEventHandler(
                ui::WINDOW_EVENT_EndCursorOver,
                ui::Window::GetClassMetaType(),
                *_CommandButton, OnEndCursorOver);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void ApplicationControl::OnUpdateToolBar(ui::widget::ToolBar& tool_bar)
    {
        if (_CommandButton!=NULL)
        {
            if (_CommandButton->IsEnabled()!=IsUsable())
                _CommandButton->Enable(IsUsable());
            _CommandButton->SetState(IsActive() ? ui::widget::BUTTON_STATE_On
                : ui::widget::BUTTON_STATE_Off);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void ApplicationControl::OnBeginCursorOverToolBar(ui::Window& widget)
    {
        Application::Get().OnBeginCursorOverControl(*this, widget);
    }

    //--------------------------------------------------------------------------------------------//

    void ApplicationControl::OnEndCursorOverToolBar()
    {
        Application::Get().OnEndCursorOverControl(*this);
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(ApplicationControl, input::Handler)
        COFFEE_RegisterEventHandler(input::EVENT_Command, input::Handler, OnCommand)
    COFFEE_EndEventHandler()
    
    //--------------------------------------------------------------------------------------------//

    bool ApplicationControl::OnCommand(shell::Event& event)
    {
        for (uint32 index=0 ; index<GetChildCount() ; ++index)
        {
            if (event.GetParameters().GetCustomParameter()
                ==((ApplicationControl*)&GetChild(index))->_Command)
            {
                ((ApplicationControl*)&GetChild(index))->Activate();
                return true;
            }
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool ApplicationControl::OnCommandButton(shell::Event& event)
    {
        if (!IsActive())
            Activate();
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool ApplicationControl::OnBeginCursorOver(shell::Event& event)
    {
        OnBeginCursorOverToolBar(*static_cast<ui::Window*>(event.GetTarget()));
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool ApplicationControl::OnEndCursorOver(shell::Event& event)
    {
        OnEndCursorOverToolBar();
        return false;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool ApplicationControl::_CheckValidity()
    {
        if (!IsValid())
        {
            Deactivate();
            return false;
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    void ApplicationControl::_ChildActivate(ApplicationControl& control)
    {
        if (HasParent() && GetParent().IsKindOf<ApplicationControl>())
        {
            ApplicationControl* parent(static_cast<ApplicationControl*>(&GetParent()));
            parent->OnChildActivate(control);
        }
        else
        {
            // ApplicationControlManager -> needs to forward activation as well
            OnChildActivate(control);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void ApplicationControl::_ChildDeactivate(ApplicationControl& control)
    {
        if (HasParent() && GetParent().IsKindOf<ApplicationControl>())
        {
            ApplicationControl* parent(static_cast<ApplicationControl*>(&GetParent()));
            parent->OnChildDeactivate(control);
        }
    }    

}
