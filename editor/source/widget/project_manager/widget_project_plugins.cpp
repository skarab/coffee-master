#include "widget/project_manager/widget_project_plugins.h"
#include "coffee_editor.h"

namespace coffee_editor
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ProjectPlugins::ProjectPlugins() :
        _Plugins(NULL),
        _Properties(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    ProjectPlugins::~ProjectPlugins()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ProjectPlugins::Create(ui::Window* tab_client)
    {
        ui::Window::Create(
            tab_client,
            basic::Vector2i(),
            basic::Vector2i(), 0);
        GetLayout().SetStyle(ui::LAYOUT_STYLE_Expand
            | ui::LAYOUT_STYLE_StickChildren
            | ui::LAYOUT_STYLE_VerticalCanvas);
        _UpdatePlugins();
        _UpdateProperties();
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(ProjectPlugins, ui::Window)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Select, ui::widget::Widget, _Plugins, OnSelectPlugin)
        COFFEE_RegisterEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, OnCheckPlugin)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool ProjectPlugins::OnSelectPlugin(shell::Event& event)
    {
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool ProjectPlugins::OnCheckPlugin(shell::Event& event)
    {
        if (event.GetTarget()!=NULL && event.GetTarget()->IsA<ui::widget::CheckBox>())
        {
            ui::widget::CheckBox* checkbox = static_cast<ui::widget::CheckBox*>(event.GetTarget());
            storage::Path* plugin_path = (storage::Path*)checkbox->GetData();
            if (checkbox->GetState()==ui::widget::CHECK_BOX_STATE_Checked)
            {
                Application::Get().GetProject().LoadPlugin(*plugin_path);
            }
            else
            {
                Application::Get().GetProject().UnloadPlugin(*plugin_path);
            }
        }
        return true;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ProjectPlugins::_UpdatePlugins()
    {
        if (_Plugins!=NULL)
            _Plugins->Destroy();

        _Plugins = COFFEE_New(ui::widget::ListView);
        _Plugins->Create(this, basic::Vector2i(), basic::Vector2i());
        _Plugins->GetLayout().SetStyle(ui::LAYOUT_STYLE_VerticalCanvas
            | ui::LAYOUT_STYLE_HorizontalExpand);
        _Plugins->GetLayout().SetCanvas(60, true);
        _Plugins->GetContainer().GetLayout().SetStyle(
            ui::LAYOUT_STYLE_VerticalCanvas | ui::LAYOUT_STYLE_StickChildren
            | ui::LAYOUT_STYLE_HorizontalExpand | ui::LAYOUT_STYLE_VerticalShrink);

        storage::System::Get().List(_PluginPathes, "/", false, true, "editor", true);
        storage::System::Get().List(_PluginPathes, "/", false, true, "plugin", true, true);
        for (uint32 index=0 ; index<_PluginPathes.GetSize() ; ++index)
        {
            if (!_PluginPathes[index]->IsContaining("/assets/"))
                _AddPlugin(_PluginPathes[index]);
        }
    }
      
    //--------------------------------------------------------------------------------------------//

    void ProjectPlugins::_AddPlugin(storage::Path* plugin_path)
    {
        ui::Window* client = COFFEE_New(ui::Window);
        client->Create(&_Plugins->GetContainer(), basic::Vector2i(), basic::Vector2i(),
            ui::WINDOW_STYLE_DrawFrame | ui::WINDOW_STYLE_DrawClientSunken
            | ui::WINDOW_STYLE_Focusable);
        client->GetLayout().SetStyle(ui::LAYOUT_STYLE_HorizontalCanvas
            | ui::LAYOUT_STYLE_HorizontalExpand | ui::LAYOUT_STYLE_StickChildren
            | ui::LAYOUT_STYLE_VerticalShrink);
        client->GetLayout().SetCanvas(20, false);
        
        ui::widget::CheckBox* is_loaded = COFFEE_New(ui::widget::CheckBox);
        is_loaded->Create(client, basic::Vector2i(), basic::Vector2i(20, 20));
        is_loaded->GetLayout().SetCanvas(20, false);
        is_loaded->SetData((void*)plugin_path);

        if (Application::Get().GetProject().IsPluginLoaded(*plugin_path))
            is_loaded->SetState(ui::widget::CHECK_BOX_STATE_Checked);

        ui::widget::Label* name = COFFEE_New(ui::widget::Label);
        name->Create(client, basic::Vector2i(), basic::Vector2i(0, 20));
        name->GetLayout().SetCanvas(100, true);
        name->SetText(plugin_path->GetFileNameWithoutExtension());
        name->SetData((void*)plugin_path);

        _Plugins->AddItem(plugin_path->GetFileNameWithoutExtension(), NULL, client);
    }

    //--------------------------------------------------------------------------------------------//

    void ProjectPlugins::_UpdateProperties()
    {
        if (_Properties!=NULL)
            _Properties->Destroy();

        _Properties = COFFEE_New(ui::PropertyList);
        _Properties->Create(*this,
            basic::Vector2i(), GetSize(), this, false);
        _Properties->GetLayout().SetCanvas(40, true);
    }

}
}
