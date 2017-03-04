#include "asset/asset_widget.h"
#include "asset/asset_manager.h"
#include "coffee_editor.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(asset::Widget);
        COFFEE_Ancestor(ui::Window);
    COFFEE_EndType();

namespace asset
{
    //-CONSTUCTORS--------------------------------------------------------------------------------//

    Widget::Widget() :
        _Importer(NULL),
        _PropertyList(NULL),
        _ItIsModified(false),
        _ToolBar(NULL),
        _SaveButton(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Widget::~Widget()
    {
        if (_Importer!=NULL)
            COFFEE_Delete(_Importer);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Widget::Create(const storage::Path& import_path, ui::Window* parent)
    {
        ui::Window::Create(
            parent, basic::Vector2i(), basic::Vector2i(200, 200),
            ui::WINDOW_STYLE_None);
        GetLayout().SetStyle(
            ui::LAYOUT_STYLE_HorizontalExpand
            | ui::LAYOUT_STYLE_VerticalShrink
            | ui::LAYOUT_STYLE_VerticalCanvas
            | ui::LAYOUT_STYLE_StickChildren);

        _ImportPath = import_path;
        _Importer = Manager::Get().LoadImporter(_ImportPath);
        if (_Importer==NULL)
        {
            Destroy();
            return;
        }
        _UpdateContent();
    }

    //--------------------------------------------------------------------------------------------//

    void Widget::CheckForModifications()
    {
        if (_ItIsModified
            && !ui::WindowManager::Get().HasModalWindow())
        {
            if(ui::DoMessageBox(
                "Settings modified",
                basic::String("Settings has been modified. Would you like to save it ?"),
                ui::MESSAGE_BOX_FLAG_YesNo))
            {
                _ItIsModified = false;
                Manager::Get().Import(*_Importer);
            }
            else
            {
                _ItIsModified = false;
            }
        }
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(Widget, ui::Window)
        COFFEE_RegisterEventHandler(ui::PROPERTY_MESSAGE_Modified, ui::Property, OnModified)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _SaveButton, OnSave)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool Widget::OnModified(shell::Event& event)
    {
        _ItIsModified = true;
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Widget::OnSave(shell::Event& event)
    {
        _ItIsModified = false;
        Manager::Get().Import(*_Importer);
        return true;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Widget::_CreateToolBar()
    {
        _ToolBar = COFFEE_New(ui::widget::ToolBar);
        _ToolBar->Create(this, 16);

        _SaveButton = _ToolBar->AddButton("Apply", ui::SKIN_ICON_Save);
    }

    //--------------------------------------------------------------------------------------------//

    void Widget::_UpdateContent()
    {
        _CreateToolBar();
        _PropertyList = COFFEE_New(ui::PropertyList);
        _PropertyList->Create(*_Importer, basic::Vector2i(0, 60),
            basic::Vector2i(GetParentWindow().GetClientRect().Size.X, 0), this, true);
    }

}
}
