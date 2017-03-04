#include "asset/asset_resource_widget.h"
#include "coffee_editor.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(asset::ResourceWidget);
        COFFEE_Ancestor(ui::Window);
    COFFEE_EndType();

namespace asset
{
    //-CONSTUCTORS--------------------------------------------------------------------------------//

    ResourceWidget::ResourceWidget() :
        _PropertyList(NULL),
        _ItIsModified(false),
        _ToolBar(NULL),
        _SaveButton(NULL),
        _ReloadButton(NULL),
        _LODGroup(NULL),
        _LODCombo(NULL),
        _AddLODButton(NULL),
        _RemoveLODButton(NULL),
        _LODPropertyList(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    ResourceWidget::~ResourceWidget()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ResourceWidget::Create(const storage::Path& resource_path, ui::Window* parent)
    {
        ui::Window::Create(
            parent, basic::Vector2i(), basic::Vector2i(200, 200),
            ui::WINDOW_STYLE_None);
        GetLayout().SetStyle(
            ui::LAYOUT_STYLE_HorizontalExpand
            | ui::LAYOUT_STYLE_VerticalShrink
            | ui::LAYOUT_STYLE_VerticalCanvas
            | ui::LAYOUT_STYLE_StickChildren);

        _ResourcePath = resource_path;
        _ResourceInstance = resource::Manager::Get().Load(resource_path);
        _ResourceChunk = &_ResourceInstance.GetChunk();
    }

    //--------------------------------------------------------------------------------------------//

    void ResourceWidget::Destroy()
    {
        _DestroyContent();
        ui::Window::Destroy();
    }

    //--------------------------------------------------------------------------------------------//

    void ResourceWidget::Update()
    {
        _UpdateContent();
        ui::Window::Update();
    }

    //--------------------------------------------------------------------------------------------//

    void ResourceWidget::CheckForModifications()
    {
        if(_ResourceInstance.IsAvailable() && _ItIsModified
            && !ui::WindowManager::Get().HasModalWindow())
        {
            if(ui::DoMessageBox(
                "Resource modified",
                basic::String("%s has been modified. Would you like to save it ?",
                _ResourceChunk->GetFilePath().GetBuffer()),
                ui::MESSAGE_BOX_FLAG_YesNo))
            {
                resource::Manager::Get().Save(
                    _ResourceInstance, _ResourceInstance.GetLODIndex());
                _ItIsModified = false;
            }
            else
            {
                _ItIsModified = false;
                resource::Manager::Get().Reload(
                    _ResourceInstance, _ResourceInstance.GetLODIndex());
            }
        }
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(ResourceWidget, ui::Window)
        COFFEE_RegisterEventHandler(ui::PROPERTY_MESSAGE_Modified, ui::Property, OnModified)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _SaveButton, OnSave)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _ReloadButton, OnReload)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Select, ui::widget::Widget, _LODCombo, OnSelectLOD)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _AddLODButton, OnAddLOD)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _RemoveLODButton, OnRemoveLOD)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool ResourceWidget::OnModified(shell::Event& event)
    {
        if(_ResourceChunk->IsLoaded() && _ResourceInstance.GetResource().IsAvailable())
            _ItIsModified = true;
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool ResourceWidget::OnSave(shell::Event& event)
    {
        resource::Manager::Get().Save(
            _ResourceInstance, _ResourceInstance.GetLODIndex());
        _ItIsModified = false;
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool ResourceWidget::OnReload(shell::Event& event)
    {
        if (_ItIsModified)
        {
            if (ui::DoMessageBox(
                "Reloading modified resource",
                basic::String("%s has been modified. Save it before reloading ?",
                    _ResourceChunk->GetFilePath().GetBuffer()),
                    ui::MESSAGE_BOX_FLAG_YesNo))
            {
                resource::Manager::Get().Save(
                    _ResourceInstance, _ResourceInstance.GetLODIndex());
                _ItIsModified = false;
            }
        }

        _DestroyContent();
        _ItIsModified = false;
        resource::Manager::Get().Reload(
            _ResourceInstance, _ResourceInstance.GetLODIndex());
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool ResourceWidget::OnSelectLOD(shell::Event& event)
    {
        uint32 lod_index;

        lod_index = _LODCombo->GetSelectedIndex();

        if(lod_index!=_ResourceInstance.GetLODIndex())
        {
            if(_ItIsModified)
            {
                if(DoMessageBox(
                    "Reloading modified resource",
                    basic::String("%s has been modified. Save it before reloading ?",
                    _ResourceChunk->GetFilePath().GetBuffer()),
                    ui::MESSAGE_BOX_FLAG_YesNo))
                {
                    resource::Manager::Get().Save(
                        _ResourceInstance, _ResourceInstance.GetLODIndex());
                    _ItIsModified = false;
                }
            }

            _ResourceInstance.QueryLOD(lod_index);
            _PropertyList->Destroy();
            _PropertyList = NULL;
            _LODPropertyList->Destroy();
            _LODPropertyList = NULL;
            _ItIsModified = false;
            _UpdateContent();
        }

        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool ResourceWidget::OnAddLOD(shell::Event& event)
    {
        resource::Object* lod_resource;
        uint32 lod_index;

        lod_index = _ResourceChunk->GetLODCount();
        lod_resource = (resource::Object *)
            _ResourceInstance.GetResource().GetMetaType().CreateObject();
        lod_resource->PreCreateLOD(lod_index);
        _ResourceChunk->AddLOD(*lod_resource);
        resource::Manager::Get().Save(_ResourceInstance, lod_index);
        _ResourceInstance.QueryLOD(lod_index);
        _DestroyContent();
        _ItIsModified = false;
        _UpdateContent();
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool ResourceWidget::OnRemoveLOD(shell::Event& event)
    {
        return true;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ResourceWidget::_CreateToolBar()
    {
        _ToolBar = COFFEE_New(ui::widget::ToolBar);
        _ToolBar->Create(this, 16);
        
        _SaveButton = _ToolBar->AddButton("Save", ui::SKIN_ICON_Save);
        _ReloadButton = _ToolBar->AddButton("Reload", "/coffee/import/editor/icons/reload.texture");
    }

    //--------------------------------------------------------------------------------------------//

    void ResourceWidget::_CreateLODBar()
    {
        Window* lod_window;
        uint32 lod_index;

        _LODGroup = COFFEE_New(ui::widget::Group);
        _LODGroup->Create(this, basic::Vector2i(0, 22), basic::Vector2i(0, 30));
        _LODGroup->SetTitleBarText(basic::String("LOD properties"));
        
        lod_window = COFFEE_New(Window);
        lod_window->Create(_LODGroup, basic::Vector2i(0, 0), basic::Vector2i(0, 20),
            ui::WINDOW_STYLE_None);
        lod_window->GetLayout().SetStyle(
            ui::LAYOUT_STYLE_HorizontalCanvas
            | ui::LAYOUT_STYLE_StickChildren
            | ui::LAYOUT_STYLE_HorizontalExpand);
        
        _LODCombo = COFFEE_New(ui::widget::ComboBox);
        _LODCombo->Create(lod_window, basic::Vector2i(0, 0), 30);
        _LODCombo->GetLayout().SetCanvas(100, true);

        for(lod_index=0 ; lod_index<_ResourceChunk->GetLODCount() ; ++lod_index)
        {
            _LODCombo->AddItem(_ResourceChunk->GetLOD(lod_index).GetParameters().GetLODName(lod_index));
        }

        _LODCombo->SelectItem(_ResourceInstance.GetLODIndex());
        
        _AddLODButton = COFFEE_New(ui::widget::Button);
        _AddLODButton->Create(lod_window, basic::Vector2i(10, 0), basic::Vector2i(18, 18));
        _AddLODButton->GetLayout().SetCanvas(18, false);
        _AddLODButton->SetImage("/coffee/import/editor/icons/add.texture");
        _AddLODButton->SetHelpText(basic::String("Add LOD"));

        _RemoveLODButton = COFFEE_New(ui::widget::Button);
        _RemoveLODButton->Create(lod_window, basic::Vector2i(30, 0), basic::Vector2i(18, 18));
        _RemoveLODButton->GetLayout().SetCanvas(18, false);
        _RemoveLODButton->SetImage("/coffee/import/editor/icons/remove.texture");
        _RemoveLODButton->SetHelpText(basic::String("Remove LOD"));
    }

    //--------------------------------------------------------------------------------------------//

    void ResourceWidget::_CreateLODProperties()
    {
        _LODPropertyList = COFFEE_New(ui::PropertyList);

        _LODPropertyList->Create(
            _ResourceChunk->GetLOD(_ResourceInstance.GetLODIndex()).GetParameters(),
            basic::Vector2i(0, 44),
            basic::Vector2i(GetParentWindow().GetClientRect().Size.X, 0),
            _LODGroup, true);
    }

    //--------------------------------------------------------------------------------------------//

    void ResourceWidget::_UpdateContent()
    {
        if(_PropertyList == NULL
            && _ResourceChunk->IsLoaded()
            && _ResourceInstance.IsAvailable())
        {
            if(_ToolBar==NULL)
            {
                _CreateToolBar();

                if(_ResourceInstance.HasResourceMode(resource::MODE_LevelOfDetail))
                    _CreateLODBar();
            }

            if(_ResourceInstance.HasResourceMode(resource::MODE_LevelOfDetail))
                _CreateLODProperties();

            _PropertyList = COFFEE_New(ui::PropertyList);
            _PropertyList->Create(_ResourceInstance.GetResource(), basic::Vector2i(0, 60),
                basic::Vector2i(GetParentWindow().GetClientRect().Size.X, 0), this, true);
        }
        else if(_ResourceChunk->IsInvalid())
        {
            resource::Manager::Get().Reload(_ResourceInstance);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void ResourceWidget::_DestroyContent()
    {
        _ToolBar = NULL;
        _SaveButton = NULL;
        _ReloadButton = NULL;
        _PropertyList = NULL;
        _LODPropertyList = NULL;
        _LODGroup = NULL;
        DestroyChildren();
    }

}
}
