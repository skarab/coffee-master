#include "coffee_editor.h"
#include "widget/package_importer/widget_package_importer.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(widget::PackageImporter);
        COFFEE_Ancestor(ui::widget::Dialog);
    COFFEE_EndType();

namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PackageImporter::PackageImporter() :
        _Import(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    PackageImporter::~PackageImporter()
    {
    }

    //-OPERATIONS-----------------------------------------------------------------------------//

    void PackageImporter::Launch(const storage::PhysicalPath& package_path)
    {
        _PackagePath = package_path;
        ui::widget::Dialog::Create(NULL, basic::Vector2i(), basic::Vector2i(200, 300));
        SetTitleBarText(basic::String("Package Importer: ")+package_path.GetFileNameWithoutExtension());

        GetLayout().SetStyle(ui::LAYOUT_STYLE_VerticalCanvas
            | ui::LAYOUT_STYLE_StickChildren);

        _BuildFilesList();

        _Import = COFFEE_New(ui::widget::Button);
        _Import->Create(this, basic::Vector2i(), basic::Vector2i(0, 40));
        _Import->GetLayout().SetStyle(ui::LAYOUT_STYLE_HorizontalExpand);
        _Import->SetText("Import");

        PositionToCenter();
        //DoModal();
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(PackageImporter, ui::widget::Dialog)
        COFFEE_RegisterTargetEventHandler(ui::widget::EVENT_Pressed, ui::widget::Widget, _Import, OnImport)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    ui::widget::TreeControl* _TreeControl;
    int _FilterFile(const char* filename, int it_is_folder)
    {
        storage::Path path(filename);
        path.CutLeft(strlen("package/"));
        ui::widget::TreeControlItem* item = _TreeControl->FindPath(path);
        return (item!=NULL && item->GetCheckBoxState()!=ui::widget::CHECK_BOX_STATE_UnChecked)?1:0;
    }

    storage::Path _GetTempPath(storage::Path path, const basic::String& project_name)
    {
        if (path.IsPrefixed("/coffee"))
        {
            path.CutLeft(strlen("/coffee"));
            path = basic::String("/internals/resources") + path;
        }
        else
        {
            path = basic::String("/projects/") + project_name + "/resources" + path;
        }
        return basic::String("/PACKAGE_TEMP")+path;
    }

    storage::Path _GetTempAssetPath(storage::Path path, const basic::String& project_name)
    {
        if (path.IsPrefixed("/import"))
        {
            path.CutLeft(strlen("/import"));
            path = basic::String("/projects/") + project_name + "/assets" + path;
        }
        else if (path.IsPrefixed("/coffee/import"))
        {
            path.CutLeft(strlen("/coffee/import"));
            path = basic::String("/internals/assets") + path;
        }
        return basic::String("/PACKAGE_TEMP")+path;
    }

    bool PackageImporter::OnImport(shell::Event& event)
    {
        storage::PhysicalPath root_folder(_PackagePath.GetPath());
        storage::PhysicalPath temp_folder(_PackagePath.GetPath()+"/package/");
        
        // Remove temporary folder

        if (storage::PhysicalSystem::Get().IsFolder(temp_folder)
            && !storage::PhysicalSystem::Get().RemoveFolder(temp_folder))
        {
            return false;
        }

        // Extract filtered files to temporary folder

        _TreeControl = _Files;
        const char* args[] = { root_folder.GetBuffer(), "x", _PackagePath.GetBuffer() };
        CHAR current_directory[MAX_PATH];
        GetCurrentDirectory(MAX_PATH, current_directory);
        SetCurrentDirectory(root_folder.GetBuffer());
        LZMA_FilterFile = _FilterFile;
        bool result = run7z(3, args)==0;
        LZMA_FilterFile = NULL;
        SetCurrentDirectory(current_directory);

        if (!result)
            return false;

        // Merge project file

        if (storage::System::Get().Mount("PACKAGE_TEMP", temp_folder, "/PACKAGE_TEMP/", true))
        {
            storage::Path project_path("/PACKAGE_TEMP/" COFFEE_ProjectConfigFile);
            Project project;
            
            if (project.Serialize(project_path, storage::MODE_Input))
            {
                // If skin is bundled we overwrite current one
                if (storage::System::Get().HasPath(_GetTempPath(project.GetSkin().GetFilePath(),
                    project.GetPath().GetName())))
                {
                    Application::Get().GetProject().SetSkin(
                        resource::Manager::Get().Load(project.GetSkin().GetFilePath()));
                }

                // Apply other options
                Application::Get().GetProject().SetCamera(project.GetCamera());
                if (project.GetStartScene().IsInstantiated())
                    Application::Get().GetProject().SetStartScene(project.GetStartScene());
                
                // If any plugin is bundled we added it to the current project
                for (uint32 i=0 ; i<project.GetPlugins().GetSize() ; ++i)
                {
                    if (storage::System::Get().HasPath(_GetTempAssetPath(project.GetPlugins()[i]->GetFilePath(),
                        project.GetPath().GetName())))
                    {
                        Application::Get().GetProject().LoadPlugin(project.GetPlugins()[i]->GetFilePath());
                    }
                }
            }

            storage::System::Get().UnMount(temp_folder);
        }

        // Copy Coffee files if required

        if (storage::PhysicalSystem::Get().IsFolder(temp_folder+"/internals/"))
        {
            if (!storage::PhysicalSystem::Get().MoveFolder(temp_folder+"/internals/",
                storage::System::Get().GetRootPath() + "/internals/"))
            {
                return false;
            }
        }

        // Process project files if required
        
        basic::Prow<storage::PhysicalPath*, true> pathes;
        storage::PhysicalSystem::Get().List(pathes, temp_folder+"/projects/", true, false);
        for (uint32 i=0 ; i<pathes.GetSize() ; ++i)
        {
            if (!storage::PhysicalSystem::Get().MoveFolder(*pathes[i],
                Application::Get().GetProject().GetFullPath()))
            {
                return false;
            }
        }

        // Import all

        asset::Manager::Get().Synchronize(asset::SYNC_FLAG_ForceAll | asset::SYNC_FLAG_CheckScripts);

        // Remove temporary folder

        if (storage::PhysicalSystem::Get().IsFolder(temp_folder)
            && !storage::PhysicalSystem::Get().RemoveFolder(temp_folder))
        {
            return false;
        }

        coffee_editor::Application::Get().OpenDocument(
            Application::Get().GetProject().GetStartScene().GetFilePath());
        return true;
    }

    //-OPERATIONS-----------------------------------------------------------------------------//

    void _ListFile(const char* filename, int it_is_folder)
    {
        storage::Path path(filename);
        path.CutLeft(strlen("package/"));
        ui::widget::TreeControlItem* item = _TreeControl->AddPath(path);
        if (item!=NULL)
            item->SetCheckBoxState(ui::widget::CHECK_BOX_STATE_Checked);
    }

    void PackageImporter::_BuildFilesList()
    {
        _Files = COFFEE_New(ui::widget::TreeControl);
        _Files->Create(this, basic::Vector2i(), basic::Vector2i(),
            ui::widget::VIEW_CONTROL_STYLE_SortAscending
            | ui::widget::VIEW_CONTROL_STYLE_ShowCheckBoxes);
        _Files->GetLayout().SetStyle(ui::LAYOUT_STYLE_HorizontalExpand);
        _Files->GetLayout().SetCanvas(100.0f, true);
        _TreeControl = _Files;

        const char* args[] = { "", "l", _PackagePath.GetBuffer() };
        CHAR current_directory[MAX_PATH];
        GetCurrentDirectory(MAX_PATH, current_directory);
        SetCurrentDirectory(_PackagePath.GetPath().GetBuffer());
        LZMA_ListFile = _ListFile;
        if (run7z(3, args)!=0)
        {
        }
        LZMA_ListFile = NULL;
        SetCurrentDirectory(current_directory);
    }

}
}
