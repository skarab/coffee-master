#include "coffee_editor.h"
#include "document/scene_editor/scene_editor.h"
#include "component/components.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(SceneEditor);
        COFFEE_Ancestor(Document);
    COFFEE_EndType();

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SceneEditor::SceneEditor() :
        Document("Scene Editor"),
        _CurrentNode(NULL),
        _NodeController(NULL),
        _Camera(NULL)
    {
        _SetSupportedExtension("Scene", "scene");
    }

    //--------------------------------------------------------------------------------------------//

    SceneEditor::~SceneEditor()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void SceneEditor::SetCurrentNode(scene::Node* node)
    {
        _CurrentNode = node;
        _NodeController->SetNode(node);
    }

    //--------------------------------------------------------------------------------------------//

    const scene::Node& SceneEditor::GetCurrentNode() const
    {
        return *_CurrentNode;
    }

    //--------------------------------------------------------------------------------------------//

    scene::Node& SceneEditor::GetCurrentNode()
    {
        return *_CurrentNode;
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    void SceneEditor::OnInitialize()
    {
        Document::OnInitialize();

        SetViewport(COFFEE_New(graphics::Viewport));
        GetViewport().Create(_ClientFrame,
            basic::Vector2i(), basic::Vector2i(), ui::WINDOW_STYLE_Focusable | ui::WINDOW_STYLE_ForwardsInput);
        GetViewport().GetLayout().SetStyle(ui::LAYOUT_STYLE_Expand);

        _NodeController = COFFEE_New(SceneEditorNodeController);
        Register(*_NodeController);
    }

    //--------------------------------------------------------------------------------------------//

    void SceneEditor::OnFinalize()
    {
        widget::Properties::Get().Clear();
        SetViewport(NULL);
        scene::World::Get().Unload(_Scene);
        Document::OnFinalize();
    }

    //--------------------------------------------------------------------------------------------//

    void SceneEditor::OnActivate()
    {
        Document::OnActivate();        
        if (_Scene.GetState()==resource::HANDLER_STATE_Ready)
        {
            _Camera = _Scene.Get().GetRoot().FindChild("_EditorCamera");
            if (_Camera!=NULL)
            {
                _Camera->Start();
                graphics::ComponentCameraPerspective* camera = _Camera->FindComponent<graphics::ComponentCameraPerspective>();
                if (camera!=NULL)
                    GetViewport().AttachCamera(_Scene, camera);
            }
        }
    }

    //--------------------------------------------------------------------------------------------//

    void SceneEditor::OnDeactivate()
    {
        _NodeController->KillPreview();
        Document::OnDeactivate();
    }

    //--------------------------------------------------------------------------------------------//

    void SceneEditor::OnUpdate(const basic::Time& time_step)
    {
        static bool update_explorer = false;

        Document::OnUpdate(time_step);

        switch (_Scene.Update())
        {
            case resource::HANDLER_STATE_BeginLoading:
            {
                _Reset();
            } break;

            case resource::HANDLER_STATE_EndLoading:
            {
                scene::Node& root = _Scene.Get().GetRoot();
                SetCurrentNode(&root);
                
                _Camera = root.FindChild("_EditorCamera");
                if (_Camera!=NULL)
                {
                    graphics::ComponentCameraPerspective* camera = _Camera->FindComponent<graphics::ComponentCameraPerspective>();
                    if (camera!=NULL)
                    {
                        camera->EnableFlag(graphics::COMPONENT_FLAG_CastShadows, true);
                        GetViewport().AttachCamera(_Scene, camera);
                    }
                }

                update_explorer = true;
            } break;
            
            case resource::HANDLER_STATE_Ready:
            {
                if (update_explorer)
                {
                    UpdateExplorer();
                    update_explorer = false;
                }
                if (!HasActiveControl())
                    _NodeController->Activate();
            } break;

            default:
                break;
        }

        if (_Camera!=NULL && GetViewport().HasCamera())
        {
            coffee::component::Controller* controller = GetViewport().GetCamera().GetComponent().GetNode().FindComponent<coffee::component::Controller>();
            if (controller!=NULL && !controller->IsRunning())
            {
                graphics::ComponentCameraPerspective* camera = _Camera->FindComponent<graphics::ComponentCameraPerspective>();
                if (camera==NULL)
                {
                    GetViewport().DetachCamera();
                }
                else if (camera!=&GetViewport().GetCamera().GetComponent())
                {
                    GetViewport().AttachCamera(_Scene, camera);
                }
            }
        }
    }

    //--------------------------------------------------------------------------------------------//

    void SceneEditor::OnRender(graphics::Viewport& viewport, bool it_is_transparent, bool it_is_hdr)
    {
        if (it_is_transparent && !it_is_hdr)
        {
            _RenderGrid(viewport);
            if (_Scene.GetState()==resource::HANDLER_STATE_Ready)
                _RenderHelpers(_Scene.Get().GetRoot());
        }
    }

    //--------------------------------------------------------------------------------------------//

    void SceneEditor::OnNew(const storage::Path& file_path)
    {
        Document::OnNew(file_path);
        SetCurrentNode(NULL);

        scene::Resource* scene;
        resource::Chunk* resource_chunk;

        scene = COFFEE_New(scene::Resource);
        scene->PreCreateLOD(0);
        scene->Initialize();
        
        scene::Node& root = scene->GetRoot();
        root.AddComponent(COFFEE_New(scene::Transform));
        root.AddComponent(COFFEE_New(scene::Bounding));

        physics::Scene* physics = COFFEE_New(physics::Scene);
        physics->SetIsInstantiable(false);
        root.AddComponent(physics);
        
        root.AddComponent(COFFEE_New(graphics::ComponentSky));

        _Camera = COFFEE_New(scene::Node, "_EditorCamera");
        _Camera->AddComponent(COFFEE_New(scene::Transform));
        _Camera->AddComponent(COFFEE_New(scene::Bounding));
        _Camera->AddComponent(COFFEE_New(graphics::ComponentCameraPerspective));
        _Camera->AddComponent(COFFEE_New(coffee::component::FreeController));

        basic::Matrix transform;
        transform.SetFromLookAt(
            basic::Vector3(10.0f, 10.0f, -10.0f),
            basic::Vector3(0.0f, 0.0f, 0.0f),
            basic::Vector3(0.0f, 1.0f, 0.0f));

        _Camera->GetTransform().SetPosition(transform.GetTranslation(), transform.GetRotation(),
            basic::Vector3::One);

        root.Attach(*_Camera);

        scene::Node* light = COFFEE_New(scene::Node, "Light");
        light->AddComponent(COFFEE_New(scene::Transform));
        light->AddComponent(COFFEE_New(scene::Bounding));
        graphics::ComponentLight* light_component = COFFEE_New(graphics::ComponentLightDirectional); 
        light->AddComponent(light_component);
        light->SetIsInstantiable(false);
        root.Attach(*light);  

        light->GetTransform().SetTranslation(basic::Vector3(-5.0f, 5.0f, -5.0f));
        
        basic::Vector3 axis(1.0f, -1.0f, 1.0f);
        axis.Normalize();
        basic::Quaternion rotation;
        rotation.SetFromZAxis(axis);
        light->GetTransform().SetRotation(rotation);
        
        resource_chunk = resource::Manager::Get().Create(file_path);
        resource_chunk->AddLOD(*scene);
        resource::Manager::Get().Save(*resource_chunk);
        scene->Finalize();
        COFFEE_Delete(resource_chunk);

        OnOpen(file_path);
    }

    //--------------------------------------------------------------------------------------------//

    void SceneEditor::OnOpen(const storage::Path& file_path)
    {
        SetCurrentNode(NULL);
        Document::OnOpen(file_path);
        _Scene = scene::World::Get().Load(file_path);
    }

    //--------------------------------------------------------------------------------------------//

    void SceneEditor::OnSave()
    {
        Document::OnSave();
        resource::Manager::Get().Save(_Scene.Get(), _Scene.Get().GetLODIndex());
    }

    //--------------------------------------------------------------------------------------------//

    bool SceneEditor::OnUpdateCopy()
    {
        return GetSelectionManager().GetObjectCount()>0;
    }

    //--------------------------------------------------------------------------------------------//

    bool SceneEditor::OnUpdateCut()
    {
        return GetSelectionManager().GetObjectCount()>0;
    }

    //--------------------------------------------------------------------------------------------//

    bool SceneEditor::OnUpdatePaste()
    {
        return _ClipBoard.GetSize()>0;
    }

    //--------------------------------------------------------------------------------------------//

    bool SceneEditor::OnUpdateDelete()
    {
        return GetSelectionManager().GetObjectCount()>0;
    }

    //--------------------------------------------------------------------------------------------//

    void SceneEditor::OnSelectItem(const storage::Path& path)
    {
        scene::Node* node = _Scene.Get().FindNode(path);
        if (node!=NULL && Application::Get().GetControlManager().HasEditionPlugin())
        {
            edition::Plugin& plugin = Application::Get().GetControlManager().GetEditionPlugin();
            edition::SelectionManager& selection_manager = plugin.GetSelectionManager();
            selection_manager.Clear(false);
            selection_manager.Select(*node, true, true);
        }
    }

    //--------------------------------------------------------------------------------------------//

    bool SceneEditor::OnRenameItem(const storage::Path& path, const storage::Path& new_path)
    {
        scene::Node* node = _Scene.Get().FindNode(path);
        if (node!=NULL && _Scene.Get().FindNode(new_path)==NULL)
        {
            node->SetName(new_path.GetName());
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    void SceneEditor::OnActivateItem(const storage::Path& path)
    {
        scene::Node* node = _Scene.Get().FindNode(path);
        if (node!=NULL)
        {
            graphics::ComponentCameraPerspective* camera = node->FindComponent<graphics::ComponentCameraPerspective>();
            if (camera!=NULL && Application::Get().GetControlManager().HasEditionPlugin())
            {
                edition::Plugin& plugin = Application::Get().GetControlManager().GetEditionPlugin();
                edition::SelectionManager& selection_manager = plugin.GetSelectionManager();
                selection_manager.Clear(false);
                selection_manager.Update();

                coffee::component::Controller* controller = node->FindComponent<coffee::component::Controller>();
                if (controller!=NULL)
                    controller->Start();

                GetViewport().SetFocus();
                GetViewport().AttachCamera(_Scene, camera);
            }
        }
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(SceneEditor, Document)
        COFFEE_RegisterEventHandler(input::EVENT_MouseLeftButtonPressed, input::Handler, OnMouseLeftButtonPressed)
        COFFEE_RegisterEventHandler(input::EVENT_KeyPressed, input::Handler, OnKeyPressed)
        COFFEE_RegisterEventHandler(input::EVENT_KeyReleased, input::Handler, OnKeyReleased)
        COFFEE_RegisterEventHandler(input::EVENT_Command, input::Handler, OnCommand)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//
    
    bool SceneEditor::OnMouseLeftButtonPressed(shell::Event& event)
    {
        input::EventMouse* parameter = (input::EventMouse*)
            event.GetParameters().GetCustomParameter();
        if (_ToolBar->HitTest(parameter->Position))
            return true;
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool SceneEditor::OnKeyPressed(shell::Event& event)
    {
        if (GetViewport().HasFocus() && _Scene.GetState()==resource::HANDLER_STATE_Ready)
        {
            input::EventKey* parameter = (input::EventKey*)
                event.GetParameters().GetCustomParameter();
            if (parameter->Key==input::KEY_Control)
            {
                if (_Camera!=NULL)
                {
                    graphics::ComponentCameraPerspective* camera = _Camera->FindComponent<graphics::ComponentCameraPerspective>();
                    if (camera!=NULL && camera->HasViewport())
                    {
                        coffee::component::Controller* controller = _Camera->FindComponent<coffee::component::Controller>();
                        if (controller!=NULL)
                            controller->Start();
                        return true;
                    }
                }                
            }
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool SceneEditor::OnKeyReleased(shell::Event& event)
    {
        if (GetViewport().HasFocus() && _Scene.GetState()==resource::HANDLER_STATE_Ready)
        {
            input::EventKey* parameter = (input::EventKey*)
                event.GetParameters().GetCustomParameter();
            if (parameter->Key==input::KEY_Control)
            {
                if (_Camera!=NULL)
                {
                    graphics::ComponentCameraPerspective* camera = _Camera->FindComponent<graphics::ComponentCameraPerspective>();
                    if (camera!=NULL && camera->HasViewport())
                    {
                        coffee::component::Controller* controller = _Camera->FindComponent<coffee::component::Controller>();
                        if (controller!=NULL && controller->IsRunning())
                            controller->Stop();
                    }
                }
                return true;
            }
        }
        return false;
    }
    
    //--------------------------------------------------------------------------------------------//

    bool SceneEditor::OnCommand(shell::Event& event)
    {
        input::Command* command = (input::Command*)event.GetParameters().GetCustomParameter();
        if (!_Scene.Get().IsAvailable())
            return false;

        if (command==edition::SelectionManager::CopyCommand)
        {
            if (GetSelectionManager().GetObjectCount()>0)
            {
                _ClipBoard = GetSelectionManager().GetObjectArray();
                return true;
            }
        }
        else if (command==edition::SelectionManager::CutCommand)
        {
            if (GetSelectionManager().GetObjectCount()>0)
            {
                _ClipBoard = GetSelectionManager().GetObjectArray();
                edition::SelectionManager& selection_manager = GetSelectionManager();
		        edition::UndoManager& undo_manager = GetUndoManager();
		        undo_manager.Begin();    
                selection_manager.Clear(false);
		        for (uint32 index=0 ; index<_ClipBoard.GetSize() ; ++index)
                {
                    scene::Node* node = static_cast<scene::Node*>(_ClipBoard[index]);
                    undo_manager.Add(COFFEE_New(edition::PluginDetachNodeUndo, node));
		            node->Detach();
		        }
                undo_manager.Accept("Cut");
                UpdateExplorer();
                return true;
            }
        }
        else if (command==edition::SelectionManager::PasteCommand)
        {
            if (_ClipBoard.GetSize()>0)
            {
                edition::SelectionManager& selection_manager = GetSelectionManager();
			    edition::UndoManager& undo_manager = GetUndoManager();
			    undo_manager.Begin();    
                selection_manager.Clear(false);
			    for (uint32 index=0 ; index<_ClipBoard.GetSize() ; ++index)
                {
                    scene::Node* node = static_cast<scene::Node*>(_ClipBoard[index]->Clone());
                    selection_manager.Select(*node, true, index==0, false);
			        undo_manager.Add(COFFEE_New(edition::PluginAttachNodeUndo, node));
			        GetCurrentNode().Attach(*node);
			    }
                undo_manager.Accept("Paste");
                UpdateExplorer();
                return true;
            }
        }
        else if (command==edition::SelectionManager::DeleteCommand)
        {
            edition::SelectionManager& selection_manager = GetSelectionManager();
			edition::UndoManager& undo_manager = GetUndoManager();
			if (selection_manager.GetObjectCount()>0)
            {
                basic::Prow<meta::Object*> nodes = selection_manager.GetObjectArray();
			    undo_manager.Begin();
			    selection_manager.Clear(true, false);
			    for (uint32 index=0 ; index<nodes.GetSize() ; ++index)
			    {
				    scene::Node* node = static_cast<scene::Node*>(nodes[index]);
				    undo_manager.Add(COFFEE_New(edition::PluginDetachNodeUndo, node));
				    node->Detach();
			    }
			    undo_manager.Accept(nodes.GetSize()>1?"Remove Nodes":"Remove Node");
                UpdateExplorer();
            }
            return true;
        }
        else if (command==edition::UndoManager::UndoCommand)
        {
            edition::UndoManager& undo_manager = Application::Get().GetControlManager().GetEditionPlugin().GetUndoManager();
            if (!undo_manager.IsActive() && undo_manager.HasUndoGroup())
            {
                undo_manager.Undo();
                UpdateExplorer();                
                return true;
            }
        }
        else if (command==edition::UndoManager::RedoCommand)
        {
            edition::UndoManager& undo_manager = Application::Get().GetControlManager().GetEditionPlugin().GetUndoManager();
            if (!undo_manager.IsActive() && undo_manager.HasRedoGroup())
            {
                undo_manager.Redo();   
                UpdateExplorer();                
                return true;
            }
        }
        return false;
    }
    
    //--------------------------------------------------------------------------------------------//

    bool SceneEditor::OnRun(shell::Event& event)
    {
        OnSave();
        scene::Resource start_scene = Application::Get().GetProject().GetStartScene();
        Application::Get().GetProject().SetStartScene(_Scene.Get());    
        coffee_editor::Application::Get().SaveConfiguration(true);

        basic::String game_path = basic::String(Engine::Get().GetApplicationPath())+"/player.exe";
        basic::String root_path = Engine::Get().GetApplicationPath();
        core::Platform::Get().Run(game_path, root_path);

        Application::Get().GetProject().SetStartScene(start_scene);    
        coffee_editor::Application::Get().SaveConfiguration(true);
        return true;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void SceneEditor::FillToolbar(ui::widget::ToolBar& toolbar)
    {
        COFFEE_RegisterExternEventHandler(
            ui::widget::EVENT_Pressed,
            ui::widget::Widget::GetClassMetaType(),
            *toolbar.AddButton("Run", "/coffee/import/editor/icons/run.texture"),
            OnRun);

        toolbar.AddSeparator();

        widget::SelectionController* selection_controller = COFFEE_New(widget::SelectionController);
        selection_controller->Create(toolbar, *this);

        widget::UndoController* undo_controller = COFFEE_New(widget::UndoController);
        undo_controller->Create(toolbar, *this);

        widget::GizmoController* gizmo_controller = COFFEE_New(widget::GizmoController);
        gizmo_controller->Create(toolbar, *this);
    }

    //--------------------------------------------------------------------------------------------//

    bool SceneEditor::IsFolderEmpty(const storage::Path& path)
    {
        scene::Path node_path(path);
        if (node_path.IsValid() && node_path.GetScenePath()==GetPath()
            && IsAvailable())
        {
            scene::Node* node = _Scene.Get().FindNode(node_path);
            if (node!=NULL)
                return !node->HasChildren();
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool SceneEditor::ListFolder(basic::Prow<storage::Path*, true>& pathes, const storage::Path& path)
    {
        scene::Path node_path(path);
        if (node_path.IsValid() && node_path.GetScenePath()==GetPath()
            && IsAvailable())
        {
            scene::Node* node = _Scene.Get().FindNode(node_path);
            if (node!=NULL)
            {
                //if (node->GetName()=="_EditorCamera")
                //    return false;

                for (uint32 i=0 ; i<node->GetChildCount() ; ++i)
                {
                    //if (node->GetChild(i).GetName()!="_EditorCamera")
                        pathes.AddItem(COFFEE_New(storage::Path, path+"/"+node->GetChild(i).GetName()));
                }
            }
            return true;
        }
        return false;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void SceneEditor::_RenderGrid(graphics::Viewport& viewport)
    {
        basic::Vector3 center;
        float distance;

        basic::Matrix grid_matrix;
        grid_matrix.Set(basic::Vector3(), basic::Euler(-Pi/2.0f, 0.0f, 0.0f));

        graphics::ComponentCamera& camera = viewport.GetCamera().GetComponent();
        basic::Matrix camera_matrix = camera.GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World);
        basic::Segment3 camera_segment;
        basic::Plane grid_plane(grid_matrix.GetTranslation(), grid_matrix.GetZAxis());
        basic::Vector3 direction;

        basic::Vector3 target = camera_matrix.GetTranslation() + camera_matrix.GetZAxis()*20.0f;
        direction = 0.0f; //camera_matrix.GetZAxis();
        direction.Y = grid_matrix.GetTranslation().Y - target.Y;

        if (direction.IsZero())
            return;

        direction.Normalize();
        
        camera_segment.SetFromDirection(
            target,
            direction,
            1000.0f);

        if (!grid_plane.FindSegmentIntersection(center, camera_segment, false))
            return;

        distance = (center-camera_segment.A).GetNorm();
        basic::Matrix world_to_local;
        world_to_local.SetInversed(grid_matrix);
        center *= world_to_local;
        
        graphics::Renderer::Get().EnableDepthTest(true);
        graphics::Renderer::Get().EnableDepthWriting(false);
        graphics::Renderer::Get().SetLocalToWorldMatrix(grid_matrix);
        graphics::Renderer::Get().SetColor(basic::Color(1.0f, 1.0f, 1.0f, 0.99f));
        graphics::Renderer::Get().SetFaceCullingMode(graphics::RENDER_STATE_FACE_CULLING_None);
                
        Clamp(distance, 20.0f, 114.0f);
        int32 step = (int)(distance/20.0f);
        int32 step_count = 20;

        center.X = (float)(((int)center.X/step)*step);
        center.Y = (float)(((int)center.Y/step)*step);
        center.Z = (float)(((int)center.Z/step)*step);

        for (int32 y=-step*step_count ; y<step*step_count ; y+=step)
        for (int32 x=-step*step_count ; x<step*step_count ; x+=step)
        {
            basic::Vector3 v1((real)x,(real)y,0.0f);
            basic::Vector3 v2((real)x+step,(real)y,0.0f);
            basic::Vector3 v3((real)x,(real)y+step,0.0f);
            real a1 = (1.0f-Pow(v1.GetNorm()/(step*step_count-2), 2.0f))/4.0f;
            real a2 = (1.0f-Pow(v2.GetNorm()/(step*step_count-2), 2.0f))/4.0f;
            real a3 = (1.0f-Pow(v3.GetNorm()/(step*step_count-2), 2.0f))/4.0f;
            
            v1 += center;
            v2 += center;
            v3 += center;

            graphics::GeometricRenderer::RenderLine(v1, v2,
                basic::Color(0.5f,0.5f,0.5f,a1),
                basic::Color(0.5f,0.5f,0.5f,a2));
            graphics::GeometricRenderer::RenderLine(v1, v3,
                basic::Color(0.5f,0.5f,0.5f,a1),
                basic::Color(0.5f,0.5f,0.5f,a3));
        }
        graphics::Renderer::Get().EnableDepthTest(false);
    }

    //--------------------------------------------------------------------------------------------//

    void SceneEditor::_RenderHelpers(scene::Node& node)
    {
        graphics::Renderer& renderer = graphics::Renderer::Get();
        
        if (node.HasBounding()) // && !node.GetBounding().GetBox().IsEmpty()
        {
            const basic::Box& box = node.GetBounding().GetBox();
            basic::Vector3 minimum, maximum;
            box.GetExtent(minimum, maximum);
            minimum *= 1.01f;
            maximum *= 1.01f;

            if ((&node==_CurrentNode && node.HasParent()) || GetSelectionManager().IsObjectSelected(node))
            {
                renderer.SetLocalToWorldMatrix(node.GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World));
                renderer.SetColor(&node==_CurrentNode?basic::Color(1.0f, 0.3f, 0.0f, 0.04f)
                    :basic::Color(1.0f, 1.0f, 1.0f, 0.08f));
                renderer.SetPolygonModes(graphics::RENDER_STATE_POLYGON_MODE_Fill,
                    graphics::RENDER_STATE_POLYGON_MODE_Fill);
                renderer.SetFaceCullingMode(graphics::RENDER_STATE_FACE_CULLING_None);
                renderer.EnableDepthTest(true);
                renderer.EnableDepthWriting(false);
                
                basic::Vector3 a(minimum.X, maximum.Y, minimum.Z);
                basic::Vector3 b(maximum.X, maximum.Y, minimum.Z);
                basic::Vector3 c(maximum.X, maximum.Y, maximum.Z);
                basic::Vector3 d(minimum.X, maximum.Y, maximum.Z);
                basic::Vector3 e(minimum.X, minimum.Y, minimum.Z);
                basic::Vector3 f(maximum.X, minimum.Y, minimum.Z);
                basic::Vector3 g(maximum.X, minimum.Y, maximum.Z);
                basic::Vector3 h(minimum.X, minimum.Y, maximum.Z);

                graphics::GeometricRenderer::RenderQuad(a, b, c, d);
                graphics::GeometricRenderer::RenderQuad(e, f, g, h);
                graphics::GeometricRenderer::RenderQuad(a, b, f, e);
                graphics::GeometricRenderer::RenderQuad(b, c, g, f);
                graphics::GeometricRenderer::RenderQuad(c, d, h, g);
                graphics::GeometricRenderer::RenderQuad(a, d, h, e);
            }
            else if (node.HasParent() && &node.GetParent()==_CurrentNode)
            {
                renderer.SetLocalToWorldMatrix(node.GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World));
                renderer.SetColor(&node==_CurrentNode?basic::Color(1.0f, 0.3f, 0.0f, 0.2f)
                    :basic::Color(1.0f, 1.0f, 1.0f, 0.2f));
                renderer.SetPolygonModes(graphics::RENDER_STATE_POLYGON_MODE_Line,
                    graphics::RENDER_STATE_POLYGON_MODE_Line);
                renderer.SetFaceCullingMode(graphics::RENDER_STATE_FACE_CULLING_None);
                renderer.EnableDepthTest(true);
                renderer.EnableDepthWriting(false);

                basic::Vector3 a(minimum.X, maximum.Y, minimum.Z);
                basic::Vector3 b(maximum.X, maximum.Y, minimum.Z);
                basic::Vector3 c(maximum.X, maximum.Y, maximum.Z);
                basic::Vector3 d(minimum.X, maximum.Y, maximum.Z);
                basic::Vector3 e(minimum.X, minimum.Y, minimum.Z);
                basic::Vector3 f(maximum.X, minimum.Y, minimum.Z);
                basic::Vector3 g(maximum.X, minimum.Y, maximum.Z);
                basic::Vector3 h(minimum.X, minimum.Y, maximum.Z);

                graphics::GeometricRenderer::RenderQuad(a, b, c, d);
                graphics::GeometricRenderer::RenderQuad(e, f, g, h);
                graphics::GeometricRenderer::RenderQuad(a, b, f, e);
                graphics::GeometricRenderer::RenderQuad(b, c, g, f);
                graphics::GeometricRenderer::RenderQuad(c, d, h, g);
                graphics::GeometricRenderer::RenderQuad(a, d, h, e);

                renderer.SetPolygonModes(graphics::RENDER_STATE_POLYGON_MODE_Fill,
                    graphics::RENDER_STATE_POLYGON_MODE_Fill);
            }
        }

        for (uint32 index=0 ; index<node.GetChildCount() ; ++index)
        {
            _RenderHelpers(*(scene::Node*)&node.GetChild(index));
        }
    }

}
