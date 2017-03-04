#include "coffee_editor.h"
#include "document/scene_editor/scene_editor.h"
#include "asset/shader/asset_shader_property.h"

namespace coffee_editor
{
    //-META-----------------------------------------------------------------------------------//

    COFFEE_ImplementSingleton(Application);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Application::Application() :
        _ComponentTypes(NULL)
    {
        COFFEE_CreateSingleton(Application);
        ilInit();
    }

    //--------------------------------------------------------------------------------------------//

    Application::~Application()
    {
        COFFEE_DestroySingleton(Application);
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const widget::EditorFrame& Application::GetEditorFrame() const
    {
        return _EditorFrame;
    }

    //--------------------------------------------------------------------------------------------//

    widget::EditorFrame& Application::GetEditorFrame()
    {
        return _EditorFrame;
    }

    //--------------------------------------------------------------------------------------------//

    ui::Window* Application::GetWindow()
    {
        Document* document = GetActiveDocument();
        if (document!=NULL)
            return &document->GetClientFrame();
        return coffee::Application::GetWindow();
    }

    //-QUERIES------------------------------------------------------------------------------------//

    storage::Path Application::GetDocumentRootPath(const storage::Path& path) const
    {
        storage::Path document_path;
        for (uint32 i=0 ; i<_DocumentInterfaces.GetSize() ; ++i)
        {
            if (_DocumentInterfaces[i]->GetRootPath(document_path, path))
                break;
        }
        return document_path;
    }

    //--------------------------------------------------------------------------------------------//

    bool Application::IsDocument(const storage::Path& path) const
    {
        storage::Path document_path = GetDocumentRootPath(path);
        basic::String extension = document_path.GetFileExtension();
        if (document_path.GetLength()==0 || extension.GetLength()==0)
            return false;

        for (uint32 i=0 ; i<_DocumentInterfaces.GetSize() ; ++i)
        {
            if (_DocumentInterfaces[i]->IsSupportedExtension(extension))
                return true;
        }
        COFFEE_Error(core::ERROR_CODE_Unexpected, "Unexpected!");
        return false;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Application::RegisterDocumentInterface(Document* document)
    {
        _DocumentInterfaces.AddItem(document);
    }

    //--------------------------------------------------------------------------------------------//

    Document* Application::FindDocument(const storage::Path& path)
    {
        storage::Path document_path = GetDocumentRootPath(path);
        for (uint32 control=0 ; control<GetControlManager().GetChildCount() ; ++control)
        {
            Document* document = (Document*)&GetControlManager().GetChild(control);
            if (document_path==document->GetPath())
                return document;
        }
        return NULL;
    }

    //--------------------------------------------------------------------------------------------//

    Document* Application::GetActiveDocument()
    {
        for (uint32 control=0 ; control<GetControlManager().GetChildCount() ; ++control)
        {
            Document* document = (Document*)&GetControlManager().GetChild(control);
            if (document->IsActive())
                return document;
        }
        return NULL;
    }

    //--------------------------------------------------------------------------------------------//

    bool Application::IsDocumentAvailable(const storage::Path& path)
    {
        Document* document = FindDocument(path);
        if (document!=NULL)
            return document->IsAvailable();
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Application::IsDocumentFolderEmpty(const storage::Path& path)
    {
        Document* document = FindDocument(path);
        if (document!=NULL && document->IsAvailable())
            return document->IsFolderEmpty(path);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    void Application::ListFolder(basic::Prow<storage::Path*, true>& pathes, const storage::Path& path)
    {
        Document* document = FindDocument(path);
        if (document!=NULL && document->IsAvailable()
            && document->ListFolder(pathes, path))
        {
            return;
        }
        storage::System::Get().List(pathes, path);
    }

    //--------------------------------------------------------------------------------------------//

    void Application::OnSelectDocumentItem(const storage::Path& path)
    {
        Document* document = FindDocument(path);
        if (document!=NULL && document->IsAvailable())
            document->OnSelectItem(path);
    }

    //--------------------------------------------------------------------------------------------//

    bool Application::OnRenameDocumentItem(const storage::Path& path, const storage::Path& new_path)
    {
        Document* document = FindDocument(path);
        if (document!=NULL && document->IsAvailable())
            return document->OnRenameItem(path, new_path);
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    void Application::OnActivateDocumentItem(const storage::Path& path)
    {
        Document* document = FindDocument(path);
        if (document!=NULL && document->IsAvailable())
            document->OnActivateItem(path);
    }

    //--------------------------------------------------------------------------------------------//

    bool Application::OpenDocument(const storage::Path& document_path)
    {
        Document* document = FindDocument(document_path);
        if (document!=NULL)
        {
            if (!document->IsActive())
            {
                document->Activate();
                _UpdateDocumentToolBar();
            }
            return true;
        }

        for (uint32 index=0 ; index<_DocumentInterfaces.GetSize() ; ++index)
        {
            const basic::Text& extension = _DocumentInterfaces[index]->GetSupportedExtension();
            if (extension.GetLineCount()==2 && document_path.GetFileExtension()==extension[1])
            {
                document = _DocumentInterfaces[index];
                break;
            }
        }

        if (document!=NULL)
        {
            if (document_path.GetFileExtension()=="scene")
                _EditorFrame.GetSceneMDI().OpenDocument(document_path, document);
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Application::CloseDocument(const storage::Path& document_path)
    {
        Document* document = FindDocument(document_path);
        if (document==NULL)
            return false;

        if (document_path.GetFileExtension()=="scene")
            return _EditorFrame.GetSceneMDI().CloseDocument(document);
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Application::CreateDocument(const storage::Path& document_path)
    {
        for (uint32 control=0 ; control<GetControlManager().GetChildCount() ; ++control)
        {
            Document& plugin = *(Document*)&GetControlManager().GetChild(control);
            if (plugin.GetPath()==document_path)
            {
                plugin.Activate();
                _UpdateDocumentToolBar();
                return false;
            }
        }

        Document* document(NULL);
        for (uint32 index=0 ; index<_DocumentInterfaces.GetSize() ; ++index)
        {
            const basic::Text& extension = _DocumentInterfaces[index]->GetSupportedExtension();
            if (extension.GetLineCount()==2 && document_path.GetFileExtension()==extension[1])
            {
                document = _DocumentInterfaces[index];
                break;
            }
        }

        if (document!=NULL)
        {
            if (document_path.GetFileExtension()=="scene")
            {
                _EditorFrame.GetSceneMDI().OpenDocument(document_path, document);
                return true;
            }
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    void Application::SaveConfiguration(bool it_saves_runtime)
    {
        GetProject().Serialize("/" COFFEE_ProjectConfigFile, storage::MODE_Output);
        GetProjectConfig().Serialize("/editor/" EDITOR_ProjectConfigFile, storage::MODE_Output);
        GetConfig().Serialize("/coffee/editor/" EDITOR_ConfigFile, storage::MODE_Output);

        if (it_saves_runtime)
        {
            GetProject().PushEditorPlugins();
            GetProject().Serialize("/root/" COFFEE_ProjectConfigFile, storage::MODE_Output);
            GetProject().PopEditorPlugins();
        }
    }

    //--------------------------------------------------------------------------------------------//

    bool Application::SetProgress(basic::String text, float percentage)
    {
        _EditorFrame.SetProgress(text, percentage);
        _Clock.Update();
        _LastUpdate += _Clock.GetTimeStep();

        if (_LastUpdate.GetSecondCount()>1.0f/30.0f)
        {
            _LastUpdate.SetSecondCount(0.0f);
            return coffee::Engine::Get().Update();
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    void Application::OnInitialize()
    {
        _ComponentTypes = COFFEE_New(component::Types);

        coffee::Application::OnInitialize();
        graphics::Device::Get().PositionWindowToCenter(640, 440);

        storage::MODE mode = storage::MODE_Input;
        if (!storage::System::Get().HasPath("/coffee/editor/" EDITOR_ConfigFile))
        {
            mode = storage::MODE_Output;
            GetConfig().SetDefaults();
        }
        GetConfig().Serialize("/coffee/editor/" EDITOR_ConfigFile, mode);

        ui::PropertyManager::Get().Register<asset::ShaderProperty>();
        ui::PropertyManager::Get().Register<widget::NodeEditor>();

        GetProject().SetIsInEditorMode(true);
        _AssetManager.Synchronize(asset::SYNC_FLAG_Immediate);

        widget::ProjectBrowser* project_browser = COFFEE_New(widget::ProjectBrowser);
        project_browser->Create();
        if (project_browser->DoModal())
            project_browser->Destroy();
        if (GetProject().GetPath().IsEmpty())
            return;

        storage::Path project_path = GetProject().GetPath();

        GetConfig().Apply();

        if (!GetProject().MountFolders())
        {
            ui::DoMessageBox("Error", basic::String("Failed to open project %s because folders are invalid",
                GetProject().GetFullPath().GetBuffer()));
            GetProject().SetPath("");
            return;
        }

        bool it_is_new_project = false;
        mode = storage::MODE_Input;
        if (!storage::System::Get().HasPath("/" COFFEE_ProjectConfigFile))
        {
            it_is_new_project = true;
            mode = storage::MODE_Output;
            GetProject().SetStartScene(
                resource::Manager::Get().Load("/default.scene"));
        }
        GetProject().Serialize("/" COFFEE_ProjectConfigFile, mode);

        // Project has been renamed
        if (GetProject().GetPath()!=project_path)
        {
            GetProject().SetPath(project_path);
            GetProject().Serialize("/" COFFEE_ProjectConfigFile, storage::MODE_Output);
        }

        mode = storage::MODE_Input;
        if (!storage::System::Get().HasPath("/editor/" EDITOR_ProjectConfigFile))
        {
            mode = storage::MODE_Output;
            GetProjectConfig().SetDefaults();
        }
        GetProjectConfig().Serialize("/editor/" EDITOR_ProjectConfigFile, mode);

        _AssetManager.Synchronize(asset::SYNC_FLAG_CheckScripts);

        graphics::Device::Get().Maximize();

        _EditorFrame.Initialize();

        RegisterDocumentInterface(COFFEE_New(SceneEditor));
        
        storage::Path start_scene = GetProject().GetStartScene().GetFilePath();
        if (it_is_new_project || storage::System::Get().HasPath(start_scene))
            OpenDocument(start_scene);
    }

    //--------------------------------------------------------------------------------------------//

    void Application::OnFinalize()
    {
        if (!GetProject().GetPath().IsEmpty())
            SaveConfiguration();

        COFFEE_Delete(_ComponentTypes);

        coffee::Application::OnFinalize();
    }

    //--------------------------------------------------------------------------------------------//

    void Application::OnUpdate(const basic::Time& time_step)
    {
        coffee::Application::OnUpdate(time_step);

        if (GetActiveDocument()!=NULL)
            GetActiveDocument()->OnUpdate(time_step);

        _AssetManager.Update(time_step);
    }

    //--------------------------------------------------------------------------------------------//

    void Application::OnActivateControl(ApplicationControl& control)
    {
        if (GetActiveDocument()!=NULL)
            GetActiveDocument()->OnActivateControl();
    }

    //--------------------------------------------------------------------------------------------//

    void Application::OnBeginCursorOverControl(ApplicationControl& control, ui::Window& widget)
    {
        ui::widget::ToolTip* tooltip = COFFEE_New(ui::widget::ToolTip);
        tooltip->Create(control.GetHelpText(), basic::Vector2i(
            (int32) input::Mouse::Get().GetPosition().X,
            (int32) input::Mouse::Get().GetPosition().Y + 25), &widget);
        ui::WindowManager::Get().SetToolTipWindow(tooltip);
    }

    //--------------------------------------------------------------------------------------------//

    void Application::OnLog(core::Log::Type type, const char* message)
    {
        _EditorFrame.GetOutputBar().OnLog(type, message);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Application::_UpdateDocumentToolBar()
    {
        _EditorFrame.GetSceneMDI().UpdateDocuments();
    }

}
