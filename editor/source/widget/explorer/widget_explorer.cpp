#include "widget/explorer/widget_explorer.h"
#include "coffee_editor.h"
#include "document/scene_editor/scene_editor.h"
#include "widget/package_importer/widget_package_importer.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_ImplementSingleton(widget::Explorer);

namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Explorer::Explorer() :
        _MainMenu(NULL),
        _TreeControl(NULL),
        _ItNeedsUpdate(false)
    {
        COFFEE_CreateSingleton(Explorer);
    }

    //--------------------------------------------------------------------------------------------//

    Explorer::~Explorer()
    {
        COFFEE_DestroySingleton(Explorer);
    }

     //-OPERATIONS---------------------------------------------------------------------------------//

    void Explorer::Create(ui::Window& panel)
    {
        ui::Window::Create(&panel,
            basic::Vector2i(), basic::Vector2i(280, 0),
            ui::WINDOW_STYLE_Activable | ui::WINDOW_STYLE_DrawFrame
            | ui::WINDOW_STYLE_DrawClientSunken | ui::WINDOW_STYLE_ResizeableRight);
        GetLayout().SetStyle(ui::LAYOUT_STYLE_VerticalExpand
            | ui::LAYOUT_STYLE_VerticalCanvas
            | ui::LAYOUT_STYLE_StickChildren);
        
        _CreateToolBar();

        _TreeControl = COFFEE_New(ui::widget::TreeControl);
        _TreeControl->Create(this, basic::Vector2i(), basic::Vector2i(), ui::widget::VIEW_CONTROL_STYLE_SortAscending);
        _TreeControl->GetLayout().SetStyle(ui::LAYOUT_STYLE_HorizontalExpand);
        _TreeControl->GetLayout().SetCanvas(100, true);
        
        _ItNeedsUpdate = true;
    }
    
	//--------------------------------------------------------------------------------------------//

    void Explorer::Update()
    {
        if (_ItNeedsUpdate)
        {
            UpdateContent();        
            _ItNeedsUpdate = false;
        }

        ui::Window::Update();
    }

    //--------------------------------------------------------------------------------------------//

    void Explorer::UpdateContent()
    {
        _SyncFolder("/", NULL);        
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(Explorer, ui::Window)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Select, ui::widget::Widget, _TreeControl, OnSelectItem)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Activate, ui::widget::Widget, _TreeControl, OnActivateItem)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Changed, ui::widget::Widget, _TreeControl, OnOpenItem)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_MayEdit, ui::widget::Widget, _TreeControl, OnCheckRenameItem)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Edit, ui::widget::Widget, _TreeControl, OnRenameItem)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _MainMenu, OnMenu)
        COFFEE_RegisterEventHandler(ui::widget::EVENT_ContextMenu, ui::widget::Widget, OnContextMenu)
        COFFEE_RegisterEventHandler(input::EVENT_Command, input::Handler, OnCommand)
        COFFEE_RegisterEventHandler(ui::WINDOW_EVENT_QueryDrag, ui::Window, OnQueryDrag)
        COFFEE_RegisterEventHandler(ui::WINDOW_EVENT_QueryDrop, ui::Window, OnQueryDrop)
        COFFEE_RegisterEventHandler(ui::WINDOW_EVENT_Drop, ui::Window, OnDrop)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool Explorer::OnOpenItem(shell::Event& event)
    {
        ui::widget::TreeControlItem* item = _TreeControl->GetSelectedItem();
        if (item!=NULL)
        {
            if (item->IsOpen())
            {
                _SyncFolder(item->GetPath(), item);
            }
            else
            {
                _TreeControl->RemoveItems(item);
            }
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Explorer::OnSelectItem(shell::Event& event)
    {
        ui::widget::TreeControlItem* item = _TreeControl->GetSelectedItem();
        if (item!=NULL)
        {
            storage::Path path = item->GetPath();
            if (coffee_editor::Application::Get().IsDocument(path))
            {
                coffee_editor::Application::Get().OnSelectDocumentItem(path);
            }
            else
            {
                storage::Path import_path = path.GetHeadFilePath("*");
                ui::widget::TreeControlItem* root = _TreeControl->FindPath(import_path);
                if (import_path.GetLength()>0 && root!=NULL && root->GetData()!=NULL)
                {
                    if (import_path.GetLength()==path.GetLength())
                    {
                        Properties::Get().Edit(path+".import");
                    }
                    else
                    {
                        storage::Path resource_path = asset::Manager::Get().GetResourcePath(import_path);
                        resource_path += path.GetRight(path.GetLength()-import_path.GetLength());
                        Properties::Get().Edit(resource_path);
                    }
                }
                else if (path.IsFilePath())
                {
                    Properties::Get().Edit(path);
                }
            }
        }
        else
        {
            Properties::Get().Clear();
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Explorer::OnActivateItem(shell::Event& event)
    {
        ui::widget::TreeControlItem* item = _TreeControl->GetSelectedItem();
        if (item!=NULL)
        {
            PathInfo info(item);
            if (info.IsFlagEnabled(PATH_FLAG_Document))
            {
                coffee_editor::Application::Get().OpenDocument(info.GetHeadPath());
                coffee_editor::Application::Get().OnActivateDocumentItem(info.GetHeadPath());
            }
            else if (info.IsFlagEnabled(PATH_FLAG_Plugin))
            {
                asset::Manager::Get().ActivateAsset(info.GetPath()+".import");
            }
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Explorer::OnCheckRenameItem(shell::Event& event)
    {
        PathInfo info(_TreeControl->GetSelectedItem());
        if (!info.IsFlagEnabled(PATH_FLAG_RootFolder)
            && !info.IsFlagEnabled(PATH_FLAG_Import)
            && !info.IsFlagEnabled(PATH_FLAG_Plugin))
        {
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Explorer::OnRenameItem(shell::Event& event)
    {
        PathInfo info(_TreeControl->GetSelectedItem());
        const basic::String& new_name = *static_cast<const basic::String*>(
            event.GetParameters().GetCustomParameter());
        bool result = false;
        storage::Path path;
        if (_TreeControl->GetSelectedItem()->GetParent().IsA<ui::widget::TreeControlItem>())
            path = static_cast<ui::widget::TreeControlItem&>(_TreeControl->GetSelectedItem()->GetParent()).GetPath();
        
        if (info.IsFlagEnabled(PATH_FLAG_Document) && !info.IsFlagEnabled(PATH_FLAG_HeadPath))
        {
            result = coffee_editor::Application::Get().OnRenameDocumentItem(info.GetPath(), path+"/"+new_name);
        }
        else
        {
            if (info.IsFlagEnabled(PATH_FLAG_Folder))
            {
                if (!new_name.IsContaining("."))
                    result = _MoveFolder(info.GetPath(), path+"/"+new_name);
            }
            else
            {
                result = _MoveFile(info.GetPath(), path+"/"+new_name);
            }
            asset::Manager::Get().Synchronize();
        }
        _ItNeedsUpdate = true;
        return result;
    }

    //--------------------------------------------------------------------------------------------//

    bool Explorer::OnMenu(shell::Event& event)
    {
        ui::widget::Menu* menu = COFFEE_New(ui::widget::Menu);
        ui::WindowContext context;
        context.Create(_MainMenu);
        menu->Create(NULL, basic::Vector2i(
            context.GetDesktopWindowRect().GetMinimum().X,
            context.GetDesktopWindowRect().GetMaximum().Y), basic::Vector2i());

        COFFEE_RegisterExternEventHandler(ui::widget::EVENT_Pressed,
            ui::widget::Widget::GetClassMetaType(), *menu->AddButton("Run"), OnRun);
        COFFEE_RegisterExternEventHandler(ui::widget::EVENT_Pressed,
            ui::widget::Widget::GetClassMetaType(), *menu->AddButton("Project Manager"), OnProjectManager);
        COFFEE_RegisterExternEventHandler(ui::widget::EVENT_Pressed,
            ui::widget::Widget::GetClassMetaType(), *menu->AddButton("Settings"), OnSettings);
         
        menu->AddSeparator();

        COFFEE_RegisterExternEventHandler(ui::widget::EVENT_Pressed,
            ui::widget::Widget::GetClassMetaType(), *menu->AddButton("Import package..."), OnImportPackage);
        COFFEE_RegisterExternEventHandler(ui::widget::EVENT_Pressed,
            ui::widget::Widget::GetClassMetaType(), *menu->AddButton("Browse packages..."), OnBrowsePackages);
        COFFEE_RegisterExternEventHandler(ui::widget::EVENT_Pressed,
            ui::widget::Widget::GetClassMetaType(), *menu->AddButton("Reimport all"), OnReimportAll);

        menu->AddSeparator();
        _FillMenu(*menu);
        menu->AddSeparator();
        
        COFFEE_RegisterExternEventHandler(ui::widget::EVENT_Pressed,
            ui::widget::Widget::GetClassMetaType(), *menu->AddButton("Exit"), OnExit);
       
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Explorer::OnContextMenu(shell::Event& event)
    {
        ui::widget::Menu* menu = COFFEE_New(ui::widget::Menu);
        menu->Create(NULL, input::Mouse::Get().GetPosition(), basic::Vector2i());
        _FillMenu(*menu);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Explorer::OnCommand(shell::Event& event)
    {
        ui::widget::TreeControlItem* item = NULL;
        if (_TreeControl!=NULL)
            item = _TreeControl->GetSelectedItem();
        input::Command* command = (input::Command*)event.GetParameters().GetCustomParameter();
        if (command==edition::SelectionManager::DeleteCommand)
        {
            if (item!=NULL)
            {
                PathInfo info(item);
                if (!info.IsFlagEnabled(PATH_FLAG_RootFolder)
                    && info.IsFlagEnabled(PATH_FLAG_HeadPath)
                    && (info.IsFlagEnabled(PATH_FLAG_Asset) || info.IsFlagEnabled(PATH_FLAG_Resource)))
                {
                    shell::Event event;
                    OnDelete(event);
                }
                else if (!info.IsFlagEnabled(PATH_FLAG_HeadPath)
                    && info.IsFlagEnabled(PATH_FLAG_Document))
                {
                    Document* document = coffee_editor::Application::Get().FindDocument(info.GetHeadPath());
                    if (document!=NULL)
                    {
                        input::System::Get().SendEvent(
                            input::EVENT_Command,
                            (void*)edition::SelectionManager::DeleteCommand,
                            *document);
                    }
                }
            }
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Explorer::OnQueryDrag(shell::Event& event)
    {
        if (event.GetTarget()->IsKindOf<ui::widget::TreeControlItem>())
        {
            ui::widget::TreeControlItem* item = static_cast<ui::widget::TreeControlItem*>(event.GetTarget());
            PathInfo info(item);
            return !info.IsFlagEnabled(PATH_FLAG_RootFolder) && !info.IsFlagEnabled(PATH_FLAG_Plugin);
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Explorer::OnQueryDrop(shell::Event& event)
    {
        if (event.GetParameters().GetParameter()!=NULL)
        {
            if (event.GetParameters().GetParameter()->IsKindOf<storage::PhysicalPath>())
            {
                const storage::PhysicalPath& path = static_cast<const storage::PhysicalPath&>(
                    *event.GetParameters().GetParameter());
                if (path.GetFileExtension()=="coffee_package")
                    return true;

                if (asset::Manager::Get().IsAssetSupported(path))
                {
                    if (event.GetTarget()->IsKindOf<ui::widget::TreeControl>())
                        return true;

                    if (event.GetTarget()->IsKindOf<ui::widget::TreeControlItem>())
                    {
                        ui::widget::TreeControlItem* item = static_cast<ui::widget::TreeControlItem*>(event.GetTarget());
                        PathInfo info(item);
                        return info.IsFlagEnabled(PATH_FLAG_Folder) && info.IsFlagEnabled(PATH_FLAG_Asset);
                    }
                }
            }
            else if (event.GetParameters().GetParameter()->IsKindOf<ui::widget::TreeControlItem>())
            {
                const ui::widget::TreeControlItem* drag_item = static_cast<const ui::widget::TreeControlItem*>(event.GetParameters().GetParameter());
                ui::widget::TreeControlItem* drop_item(NULL);
                if (event.GetTarget()->IsKindOf<ui::widget::TreeControlItem>())
                    drop_item = static_cast<ui::widget::TreeControlItem*>(event.GetTarget());
                PathInfo drag(drag_item);
                PathInfo drop(drop_item);

                if (drag.IsFlagEnabled(PATH_FLAG_Import) || !drag.IsFlagEnabled(PATH_FLAG_HeadPath))
                    return false;

                return drop.IsFlagEnabled(PATH_FLAG_Folder)
                    && ((drag.IsFlagEnabled(PATH_FLAG_Asset) && drop_item!=NULL && drop.IsFlagEnabled(PATH_FLAG_Asset))
                    || (drag.IsFlagEnabled(PATH_FLAG_Resource) && (drop_item==NULL || drop.IsFlagEnabled(PATH_FLAG_Resource))));
            }
        }
        return false;
    }
    
    //--------------------------------------------------------------------------------------------//

    bool Explorer::OnDrop(shell::Event& event)
    {
        if (event.GetParameters().GetParameter()!=NULL)
        {
            if (event.GetParameters().GetParameter()->IsKindOf<storage::PhysicalPath>())
            {
                const storage::PhysicalPath& path = static_cast<const storage::PhysicalPath&>(
                    *event.GetParameters().GetParameter());
                if (path.GetFileExtension()=="coffee_package")
                {
                    _ImportPackage(path);
                }
                else
                {
                    if (event.GetTarget()->IsKindOf<ui::widget::TreeControlItem>())
                    {
                        ui::widget::TreeControlItem* item = static_cast<ui::widget::TreeControlItem*>(event.GetTarget());
                        asset::Manager::Get().OnImport(path, item->GetPath());
                    }
                    else
                    {
                        asset::Manager::Get().OnImport(path, "/assets");
                    }
                }
            }
            else if (event.GetParameters().GetParameter()->IsKindOf<ui::widget::TreeControlItem>())
            {
                const ui::widget::TreeControlItem* drag_item = static_cast<const ui::widget::TreeControlItem*>(event.GetParameters().GetParameter());
                ui::widget::TreeControlItem* drop_item(NULL);
                if (event.GetTarget()->IsKindOf<ui::widget::TreeControlItem>())
                    drop_item = static_cast<ui::widget::TreeControlItem*>(event.GetTarget());
                PathInfo drag(drag_item);
                PathInfo drop(drop_item);

                if (drag.IsFlagEnabled(PATH_FLAG_File))
                {
                    if (!_MoveFile(drag.GetPath(), drop.GetPath()+"/"+drag.GetPath().GetFileName()))
                        return false;
                }
                else
                {
                    if (!_MoveFolder(drag.GetPath(), drop.GetPath()+"/"+drag.GetPath().GetName()))
                        return false;
                }
                asset::Manager::Get().Synchronize();
            }
            _ItNeedsUpdate = true;
        }
        return true;
    }
    
    //--------------------------------------------------------------------------------------------//

    bool Explorer::OnCreate(shell::Event& event)
    {
        ui::widget::TreeControlItem* item = _TreeControl->GetSelectedItem();
        storage::Path path;
        if (item!=NULL)
            path = item->GetPath();
        
        ui::widget::Button* button = static_cast<ui::widget::Button*>(event.GetTarget());
        if (button->GetText()=="Folder")
        {
            storage::Path folder_path = path+"/new";
            storage::System::Get().CreateFolder(folder_path);
        }
        else if (button->GetText()=="Scene" || button->GetText()=="Graph")
        {
            ui::widget::Button* button = static_cast<ui::widget::Button*>(event.GetTarget());
            const basic::Prow< Document*, true >& documents = coffee_editor::Application::Get().GetDocumentInterfaces();
            for (uint32 i=0 ; i<documents.GetSize() ; ++i)
            {
                if (documents[i]->GetSupportedExtension().GetLineCount()==2
                    && button->GetText()==documents[i]->GetSupportedExtension()[0])
                {
                    coffee_editor::Application::Get().OpenDocument(path+"/new."+documents[i]->GetSupportedExtension()[1]);
                    return true;
                }
            }
        }
        else if (button->GetText()=="Component" || button->GetText()=="Plugin"
            || button->GetText()=="Editor")
        {
            basic::String extension(button->GetText().ToLowerCase());
            basic::String asset_name = ui::DoStringBox("Choose asset name",
                basic::String("Enter name of the new ") + button->GetText() + " :",
                "", "Create!");
            if (asset_name.GetLength()>0)
            {
                if (!storage::PhysicalSystem::Get().IsValidName(asset_name))
                {
                    ui::DoMessageBox("Invalid asset name !", "Remember: asset name is used as filename.");
                    return true;
                }
                asset::Manager::Get().CreateAsset(path+"/"+asset_name.ToLowerCase()+'.'+extension );
            }
        }
        else if (button->GetText()=="Material")
        {
            storage::Path file_path = path+"/new.material";
            graphics::Material* material = COFFEE_New(graphics::Material);
            material->PreCreateLOD(0);
            material->GrabShader() = resource::Manager::Get().Load("/coffee/import/shaders/default.shader");
            resource::Chunk* resource_chunk = resource::Manager::Get().Create(file_path);
            resource_chunk->AddLOD(*material);
            resource::Manager::Get().Save(*resource_chunk);
            COFFEE_Delete(resource_chunk);
        }
        else if (button->GetText()=="GUI Skin")
        {
            basic::String asset_name = ui::DoStringBox("Set skin name",
               "Enter name :", "", "Create!");
            if (asset_name.GetLength()>0)
            {
                if (!storage::PhysicalSystem::Get().IsValidName(asset_name))
                {
                    ui::DoMessageBox("Invalid asset name !", "Remember: asset name is used as filename.");
                    return true;
                }

                storage::Path file_path = path+"/"+asset_name+".skin";
                ui::Skin* skin = COFFEE_New(ui::Skin);
                skin->Create();
                skin->PreCreateLOD(0);
                resource::Chunk* resource_chunk;
                resource_chunk = resource::Manager::Get().Create(file_path);
                resource_chunk->AddLOD(*skin);
                resource::Manager::Get().Save(*resource_chunk);
                COFFEE_Delete(resource_chunk);
            }
        }
        else if (button->GetText()=="Physics Material")
        {
            basic::String asset_name = ui::DoStringBox("Set physics material name",
               "Enter name :", "", "Create!");
            if (asset_name.GetLength()>0)
            {
                if (!storage::PhysicalSystem::Get().IsValidName(asset_name))
                {
                    ui::DoMessageBox("Invalid asset name !", "Remember: asset name is used as filename.");
                    return true;
                }

                storage::Path file_path = path+"/"+asset_name+".physics_material";
                physics::Material* material = COFFEE_New(physics::Material);
                material->PreCreateLOD(0);
                resource::Chunk* resource_chunk;
                resource_chunk = resource::Manager::Get().Create(file_path);
                resource_chunk->AddLOD(*material);
                resource::Manager::Get().Save(*resource_chunk);
                COFFEE_Delete(resource_chunk);
            }
        }
        _ItNeedsUpdate = true;
        return true;
    }
    
    //--------------------------------------------------------------------------------------------//

    bool Explorer::OnImport(shell::Event& event)
    {
        PathInfo info(_TreeControl->GetSelectedItem());
        asset::Manager::Get().OnImport(
            _TreeControl->GetSelectedItem()==NULL? "/assets" : info.GetPath());
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Explorer::OnReimport(shell::Event& event)
    {
        PathInfo info(_TreeControl->GetSelectedItem());
        basic::Prow<storage::Path*, true> files;
        if (!storage::System::Get().List(files, info.GetPath(), false, true, "*", true))
            files.AddItem(COFFEE_New(storage::Path, info.GetPath()));
        for (uint32 i=0 ; i<files.GetSize() ; ++i)
        {
            storage::Path path = *files[i] + ".import";
            if (storage::System::Get().HasPath(path))
                asset::Manager::Get().ReImport(path);
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Explorer::OnDelete(shell::Event& event)
    {
        PathInfo info(_TreeControl->GetSelectedItem());

        // Check for pre-delete operations...
        bool result = true;
        basic::Prow<storage::Path*, true> files;
        if (!storage::System::Get().List(files, info.GetPath(), false, true, "*", true))
            files.AddItem(COFFEE_New(storage::Path, info.GetPath()));
        for (int32 i=0 ; i<(int32)files.GetSize() ; ++i)
        {
            storage::Path path = *files[i] + ".import";
            if (storage::System::Get().HasPath(path))
            {
                if (!asset::Manager::Get().Delete(path))
                    result = false;
                files.Remove(i--);
            }
        }

        // Delete all
        if (info.IsFlagEnabled(PATH_FLAG_File))
        {
            if (storage::System::Get().HasPath(info.GetPath()))
            {
                if (!storage::System::Get().RemoveFile(info.GetPath()))
                    result = false;
            }
        }
        else
        {
            if (!storage::System::Get().RemoveFolder(info.GetPath()))
                result = false;
        }
        Properties::Get().Clear();
        _ItNeedsUpdate = true;
        return result;
    }

    //--------------------------------------------------------------------------------------------//

    bool Explorer::OnBreakAssets(shell::Event& event)
    {
        PathInfo info(_TreeControl->GetSelectedItem());
        bool result = true;
        basic::Prow<storage::Path*, true> files;
        if (!storage::System::Get().List(files, info.GetPath(), false, true, "*", true))
            files.AddItem(COFFEE_New(storage::Path, info.GetPath()));
        for (uint32 i=0 ; i<files.GetSize() ; ++i)
        {
            storage::Path path = *files[i] + ".import";
            if (storage::System::Get().HasPath(path)
                && !asset::Manager::Get().BreakDependencies(path))
            {
                result = false;
            }
        }
        _ItNeedsUpdate = true;
        return result;
    }

    //--------------------------------------------------------------------------------------------//
    
    bool Explorer::OnRun(shell::Event& event)
    {
        coffee_editor::Application::Get().SaveConfiguration(true);
        basic::String game_path = basic::String(Engine::Get().GetApplicationPath())+"/player.exe";
        basic::String root_path = Engine::Get().GetApplicationPath();
        core::Platform::Get().Run(game_path, root_path);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Explorer::OnProjectManager(shell::Event& event)
    {
        widget::ProjectManager* project_manager;
        project_manager = COFFEE_New(widget::ProjectManager);
        project_manager->Create();
        return true;
    }
    
    //--------------------------------------------------------------------------------------------//
    
    bool Explorer::OnSettings(shell::Event& event)
    {
        widget::ConfigDialog* config_dialog;
        config_dialog = COFFEE_New(widget::ConfigDialog);
        config_dialog->Create();
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Explorer::OnImportPackage(shell::Event& event)
    {
        basic::String path;
        basic::Text extensions;
        extensions.AddLine("Packages"); extensions.AddLine("*.coffee_package");
        
        if (core::Platform::Get().AskForFile(path, extensions))
            _ImportPackage(path);
        return true;
    }
    
    //--------------------------------------------------------------------------------------------//

    bool Explorer::OnBrowsePackages(shell::Event& event)
    {
        ui::FileDialog* file_dialog;
        basic::Text extensions;
        extensions.AddLine("Packages");
        extensions.AddLine("coffee_package");

        storage::System::Get().Mount("packages", Application::Get().GetProject().GetFullPath()+"/packages", "/packages/", true);
        
        file_dialog = COFFEE_New(ui::FileDialog);
        file_dialog->Create(basic::String("Open..."),
            ui::FILE_DIALOG_FLAG_Open | ui::FILE_DIALOG_FLAG_FileMustExist,
            extensions);
        bool it_has_open = file_dialog->DoModal();
        
        storage::System::Get().UnMount(Application::Get().GetProject().GetFullPath()+"/packages");
        _ItNeedsUpdate = true;

        if (it_has_open)
        {
            storage::Path file_path = file_dialog->GetFilePath();
            file_dialog->Destroy();

            basic::String package_path = file_path;
            widget::PackageImporter* importer = COFFEE_New(widget::PackageImporter);
            importer->Launch(Application::Get().GetProject().GetFullPath()+package_path);
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//
 
    bool Explorer::OnReimportAll(shell::Event& event)
    {
        asset::Manager::Get().Synchronize(asset::SYNC_FLAG_ForceAll);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Explorer::OnExit(shell::Event& event)
    {
        Engine::Get().Quit();
        return true;
    }
    
    //-QUERIES------------------------------------------------------------------------------------//

    bool Explorer::_Filter(const storage::Path& path) const
    {
        if (!path.IsFilePath())
        {
            if (path!="/coffee/import"
                && path!="/import"
                && path!="/root"
                && path!="/coffee/editor/thumbnails"
                && path !="/editor/thumbnails")
            {
                return true;
            }
            return false;
        }

        if (coffee_editor::Application::Get().IsDocument(path))
            return true;

        if (path.IsSuffixed(".import"))
            return true;
        
        if (path.IsContaining(".component")
            || path.IsContaining(".editor")
            || path.IsContaining(".plugin"))
        {
            return false;
        }

        if (resource::Manager::IsAvailable())
        {
            uint32 library_index;
            const basic::Prow< resource::Library * > & library_array = resource::Manager::Get().GetLibraryArray();
            basic::String file_extension(path.GetFileExtension());
            for (library_index=0 ; library_index<library_array.GetSize() ; ++library_index)
            {
                if (file_extension==resource::Manager::Get().GetLibraryArray()[
                    library_index]->GetResourceName())
                {
                    return true;
                }
            }
        }
        return false;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Explorer::_FillMenu(ui::widget::Menu& menu)
    {
        PathInfo info(_TreeControl->GetSelectedItem());

        // Create
        if (info.IsFlagEnabled(PATH_FLAG_Folder)
            && (info.IsFlagEnabled(PATH_FLAG_Resource) || info.IsFlagEnabled(PATH_FLAG_Asset)))
        {
            ui::widget::Menu* menu_create = menu.AddMenu("Create...");
        
            COFFEE_RegisterExternEventHandler(ui::widget::EVENT_Pressed,
                ui::widget::Widget::GetClassMetaType(), *menu_create->AddButton("Folder"), OnCreate);
            
            if (info.IsFlagEnabled(PATH_FLAG_Resource))
            {
                menu_create->AddSeparator();
            
                const basic::Prow< Document*, true >& documents = coffee_editor::Application::Get().GetDocumentInterfaces();
                for (uint32 i=0 ; i<documents.GetSize() ; ++i)
                {
                    if (documents[i]->GetSupportedExtension().GetLineCount()==2)
                    {
                        COFFEE_RegisterExternEventHandler(ui::widget::EVENT_Pressed,
                            ui::widget::Widget::GetClassMetaType(),
                            *menu_create->AddButton(documents[i]->GetSupportedExtension()[0]),
                            OnCreate);
                    }
                }
            
                menu_create->AddSeparator();

                COFFEE_RegisterExternEventHandler(ui::widget::EVENT_Pressed,
                    ui::widget::Widget::GetClassMetaType(), *menu_create->AddButton("Material"), OnCreate);
                COFFEE_RegisterExternEventHandler(ui::widget::EVENT_Pressed,
                    ui::widget::Widget::GetClassMetaType(), *menu_create->AddButton("GUI Skin"), OnCreate);
                COFFEE_RegisterExternEventHandler(ui::widget::EVENT_Pressed,
                    ui::widget::Widget::GetClassMetaType(), *menu_create->AddButton("Physics Material"), OnCreate);
            }
            else if (info.IsFlagEnabled(PATH_FLAG_Asset))
            {
                menu_create->AddSeparator();

                COFFEE_RegisterExternEventHandler(ui::widget::EVENT_Pressed,
                    ui::widget::Widget::GetClassMetaType(), *menu_create->AddButton("Component"), OnCreate);
                COFFEE_RegisterExternEventHandler(ui::widget::EVENT_Pressed,
                    ui::widget::Widget::GetClassMetaType(), *menu_create->AddButton("Plugin"), OnCreate);

                if (info.IsFlagEnabled(PATH_FLAG_Editor))
                {
                    COFFEE_RegisterExternEventHandler(ui::widget::EVENT_Pressed,
                        ui::widget::Widget::GetClassMetaType(), *menu_create->AddButton("Editor"), OnCreate);
                }
                else
                {
                    menu_create->AddButton("Editor")->Enable(false);
                }
            }
        }
        else
        {
            menu.AddButton("Create...")->Enable(false);
        }    
        
        ui::widget::Button* button;

        button = menu.AddButton("Import...");
        button->Enable(_TreeControl->GetSelectedItem()==NULL
            || (info.IsFlagEnabled(PATH_FLAG_Folder) && info.IsFlagEnabled(PATH_FLAG_Asset)));
        COFFEE_RegisterExternEventHandler(ui::widget::EVENT_Pressed,
            ui::widget::Widget::GetClassMetaType(), *button, OnImport);
        
        button = menu.AddButton("Reimport");
        button->Enable(info.IsFlagEnabled(PATH_FLAG_Asset) || info.IsFlagEnabled(PATH_FLAG_Import));
        COFFEE_RegisterExternEventHandler(ui::widget::EVENT_Pressed,
            ui::widget::Widget::GetClassMetaType(), *button, OnReimport);

        button = menu.AddButton("Delete");
        button->Enable(!info.IsFlagEnabled(PATH_FLAG_RootFolder)
            && info.IsFlagEnabled(PATH_FLAG_HeadPath)
            && (info.IsFlagEnabled(PATH_FLAG_Asset) || info.IsFlagEnabled(PATH_FLAG_Resource))
            && !info.IsFlagEnabled(PATH_FLAG_Plugin));
        COFFEE_RegisterExternEventHandler(ui::widget::EVENT_Pressed,
            ui::widget::Widget::GetClassMetaType(), *button, OnDelete);

        button = menu.AddButton("Break Assets");
        button->Enable(info.IsFlagEnabled(PATH_FLAG_HeadPath) && info.IsFlagEnabled(PATH_FLAG_Asset)
            && !info.IsFlagEnabled(PATH_FLAG_Plugin));
        COFFEE_RegisterExternEventHandler(ui::widget::EVENT_Pressed,
            ui::widget::Widget::GetClassMetaType(), *button, OnBreakAssets);
    }

    //--------------------------------------------------------------------------------------------//

    void Explorer::_CreateToolBar()
    {
        ui::widget::ToolBar* tool_bar;
        tool_bar = COFFEE_New(ui::widget::ToolBar);
        tool_bar->Create(this, 30);
        tool_bar->GetLayout().SetCanvas(30, false);

        _MainMenu = tool_bar->AddButton("Project",
            "/coffee/import/editor/icons/explorer.texture");

        COFFEE_RegisterExternEventHandler(
            ui::widget::EVENT_Pressed,
            ui::widget::Widget::GetClassMetaType(),
            *tool_bar->AddButton("Run", "/coffee/import/editor/icons/run.texture"),
            OnRun);
    }

    //--------------------------------------------------------------------------------------------//

    void Explorer::_SyncFolder(const storage::Path& path, ui::widget::TreeControlItem* item)
    {
        basic::Prow<storage::Path*, true> pathes;

        if (item!=NULL && item->GetData()!=NULL)
        {
            storage::Path import_path = path+".import";
            if (Properties::Get().GetObjectPath()==import_path)
            {
                const basic::Vector<storage::Path>& resources = Properties::Get().GetAssetWidget().GetImporter().GetResourcePathes();
                for (uint32 i=0 ; i<resources.GetSize() ; ++i)
                    pathes.AddItem(COFFEE_New(storage::Path, resources[i]));
            }
        }
        else
        {
            coffee_editor::Application::Get().ListFolder(pathes, path);
        }

        for (int32 i=pathes.GetSize()-1 ; i>=0 ; --i)
        {
            if (!_Filter(*pathes[i]))
                pathes.Remove(i);
        }

        // Remove unexisting items
        basic::Prow<ui::widget::TreeControlItem*, false> items = _TreeControl->GetItems(item);
        for (int32 i=0 ; i<(int32)items.GetSize() ; ++i)
        {
            bool exist = false;
            for (uint32 j=0 ; j<pathes.GetSize() ; ++j)
            {
                if (pathes[j]->GetName()==items[i]->GetText())
                {
                    exist = true;
                    break;
                }
            }
            if (!exist)
            {
                if (_TreeControl->GetSelectedItem()!=NULL
                    && _TreeControl->GetSelectedItem()->IsParentedBy(items[i]))
                {
                    _TreeControl->ClearSelection();
                    Properties::Get().Clear();
                }

                items[i]->Destroy();
                items.Remove(i--);
            }
        }

        // Add missing items
        for (uint32 i=0 ; i<pathes.GetSize() ; ++i)
        {
            ui::widget::TreeControlItem* child = NULL;
            for (uint32 j=0 ; j<items.GetSize() ; ++j)
            {
                if (items[j]->GetData()!=NULL && pathes[i]->IsSuffixed(".import"))
                {
                    storage::Path asset_path = pathes[i]->GetLeft(pathes[i]->GetLength()
                        -basic::String(".import").GetLength());
                    if (items[j]->GetText()==asset_path.GetName())
                    {
                        child = items[j];
                        break;
                    }
                }
                else if (items[j]->GetText()==pathes[i]->GetName())
                {
                    child = items[j];
                    break;
                }
            }
            
            if (child==NULL)
            {
                child = _TreeControl->AddItem(pathes[i]->GetName(), item);
                child->SetImage(asset::Manager::Get().GetThumbnail(*pathes[i]));
            }

            bool show_control = !pathes[i]->IsFilePath();
            if (coffee_editor::Application::Get().IsDocumentAvailable(*pathes[i]))
                show_control = !coffee_editor::Application::Get().IsDocumentFolderEmpty(*pathes[i]);
            if (pathes[i]->IsSuffixed(".import"))
            {
                storage::Path asset_path = pathes[i]->GetLeft(pathes[i]->GetLength()
                    -basic::String(".import").GetLength());
                child->SetText(asset_path.GetName());
                child->SetData((void*)1);
                PathInfo info(child);
                show_control = !info.IsFlagEnabled(PATH_FLAG_Plugin);
            }
            
            child->GetTreeButton().Show(show_control);

            if (show_control)
            {
                if (child->IsOpen())
                    _SyncFolder(*pathes[i], child);
            }
            else
            {
                _TreeControl->RemoveItems(child);
            }
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Explorer::_ImportPackage(const storage::PhysicalPath& filepath)
    {
        storage::PhysicalPath package_path = Application::Get().GetProject().GetFullPath()+"/packages/"+filepath.GetFileName();
        if (storage::PhysicalSystem::Get().IsFile(package_path)
            && !ui::DoMessageBox("Package already exists", "Do you want to replace it ?", ui::MESSAGE_BOX_FLAG_YesNo))
        {
            return;
        }
        
        if (!storage::PhysicalSystem::Get().CopyFile(filepath, package_path, true))
        {
            ui::DoMessageBox("Failed to copy package", "Check if project_path/packages/ is not opened or read-only.");
            return;
        }

        widget::PackageImporter* importer = COFFEE_New(widget::PackageImporter);
        importer->Launch(package_path);
    }

    //--------------------------------------------------------------------------------------------//

    bool Explorer::_MoveFolder(const storage::Path& path, const storage::Path& new_path)
    {
        basic::Prow<storage::Path*, true> files;
        storage::System::Get().List(files, path, false, true, "*", true);
        for (int32 i=0 ; i<(int32)files.GetSize() ; ++i)
        {
            storage::Path filepath = *files[i];
            filepath.Replace(path, new_path);
            if (storage::System::Get().HasPath(*files[i]) && !_MoveFile(*files[i], filepath))
                return false;
        }
        storage::System::Get().CreateFolder(new_path);
        return storage::System::Get().RemoveFolder(path);
    }

    //--------------------------------------------------------------------------------------------//

    bool Explorer::_MoveFile(const storage::Path& path, const storage::Path& new_path)
    {
        bool it_has_to_open(false);

        if (coffee_editor::Application::Get().IsDocument(path))
        {
            if (coffee_editor::Application::Get().CloseDocument(path))
                it_has_to_open = true;
        }
        else
        {
            storage::Path import_path = path + ".import";
            if (storage::System::Get().HasPath(import_path))
            {
                if (!asset::Manager::Get().Move(import_path))
                    return false;
            
                // Makes sure the import is moved before asset, to have reimported at the end
                if (!storage::System::Get().MoveFile(import_path, new_path+".import"))
                    return false;
            }
        }
        
        if (!storage::System::Get().MoveFile(path, new_path))
            return false;

        if (coffee_editor::Application::Get().IsDocument(path))
        {
            if (it_has_to_open)
                coffee_editor::Application::Get().OpenDocument(new_path);
        }
        return true;
    }

}
}
