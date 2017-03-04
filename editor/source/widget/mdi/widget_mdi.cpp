#include "widget/mdi/widget_mdi.h"
#include "coffee_editor.h"

namespace coffee_editor
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    MDI::MDI() :
        _Documents(NULL),
        _ToolBar(NULL),
        _Client(NULL),
        _Document(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    MDI::~MDI()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void MDI::Create(ui::Window& panel, uint32 style)
    {
        ui::Window::Create(
            &panel,
            basic::Vector2i(),
            basic::Vector2i(0, 160),
            ui::WINDOW_STYLE_None);
        SetStyle(ui::WINDOW_STYLE_Activable
            | ui::WINDOW_STYLE_ForwardsInput
            | style);
        GetLayout().SetStyle(ui::LAYOUT_STYLE_HorizontalExpand
            | ui::LAYOUT_STYLE_VerticalCanvas
            | ui::LAYOUT_STYLE_StickChildren);
        if (style==0)
            GetLayout().SetCanvas(100, true);

        ui::Window* border = COFFEE_New(ui::Window);
        border->Create(this, basic::Vector2i(), basic::Vector2i(),
            ui::WINDOW_STYLE_DrawFrame|ui::WINDOW_STYLE_DrawClientSunken);
        border->GetLayout().SetCanvas(4, false);
        border->GetLayout().SetStyle(ui::LAYOUT_STYLE_HorizontalExpand);

        _Documents = COFFEE_New(ui::widget::ToolBar);
        _Documents->Create(this, 16);
        _Documents->GetLayout().SetCanvas(16, false);
        
        _ToolBar = COFFEE_New(ui::widget::ToolBar);
        _ToolBar->Create(this, 30);
        _ToolBar->GetLayout().SetCanvas(30, false);
        
        _Client = COFFEE_New(ui::Window);
        _Client->Create(this, basic::Vector2i(), basic::Vector2i(),
            ui::WINDOW_STYLE_Focusable | ui::WINDOW_STYLE_ForwardsInput
            | ui::WINDOW_STYLE_DrawFrame | ui::WINDOW_STYLE_DrawClientSunken);
        _Client->GetLayout().SetCanvas(100, true);
        _Client->GetLayout().SetStyle(ui::LAYOUT_STYLE_HorizontalExpand);
    }

    //--------------------------------------------------------------------------------------------//
    
    bool MDI::OpenDocument(storage::Path document_path, Document* document_interface)
    {
        Document* instance = static_cast<Document*>(document_interface->GetMetaType().CreateObject());
        instance->_MDI = this;
        coffee_editor::Application::Get().GetControlManager().Register(*instance);
        instance->Activate();

        if (storage::System::Get().HasPath(document_path))
        {
            instance->OnOpen(document_path);
        }
        else
        {
            instance->OnNew(document_path);
        }
        
        ui::Window* frame = _Documents->AddWindow(128);
        ui::widget::Button* button = COFFEE_New(ui::widget::Button);
        button->Create(frame, basic::Vector2i(), basic::Vector2i(108, 16), ui::widget::BUTTON_STYLE_PushLike);
        button->SetText(document_path.GetFileName());
        button = COFFEE_New(ui::widget::Button);
        button->Create(frame, basic::Vector2i(109,0), basic::Vector2i(16, 16));
        button->SetImage(ui::SKIN_ICON_Close);
        
        static_cast<ui::widget::Button&>(frame->GetChildWindow(0)).SetData(instance);
        static_cast<ui::widget::Button&>(frame->GetChildWindow(1)).SetData(instance);
        COFFEE_RegisterExternEventHandler(
            ui::widget::EVENT_Pressed,
            ui::widget::Widget::GetClassMetaType(),
            frame->GetChildWindow(0),
            OnActivateDocument);
        COFFEE_RegisterExternEventHandler(
            ui::widget::EVENT_Pressed,
            ui::widget::Widget::GetClassMetaType(),
            frame->GetChildWindow(1),
            OnCloseDocument);
        UpdateDocuments();
        return true;
    }

    //--------------------------------------------------------------------------------------------//
    
    bool MDI::CloseDocument(Document* document)
    {
        for (uint32 index=0 ; index<_Documents->GetChildCount() ; ++index)
        {
            ui::Window* frame = (ui::Window*)&_Documents->GetChild(index);
            if (!frame->IsDestroyed())
            {
                ui::widget::Button& button = static_cast<ui::widget::Button&>(frame->GetChildWindow(0));
                Document* doc = (Document*)button.GetData();
                if (doc==document)
                {
                    frame->Destroy();
                    doc->Destroy();
                    if (coffee_editor::Application::Get().GetControlManager().GetChildCount()>0)
                        static_cast<Document&>(coffee_editor::Application::Get().GetControlManager().GetChild(0)).Activate();
                    UpdateDocuments();
                    return true;
                }
            }
        }
        return false;
    }
        
    //--------------------------------------------------------------------------------------------//
    
    void MDI::UpdateDocuments()
    {
        _Document = NULL;
        if (_Documents!=NULL)
        {
            for (uint32 index=0 ; index<_Documents->GetChildCount() ; ++index)
            {
                ui::Window* frame = (ui::Window*)&_Documents->GetChild(index);
                if (!frame->IsDestroyed())
                {
                    ui::widget::Button& button = static_cast<ui::widget::Button&>(frame->GetChildWindow(0));
                    Document* document = (Document*)button.GetData();
                    button.SetState(document->IsActive()?
                        ui::widget::BUTTON_STATE_On:ui::widget::BUTTON_STATE_Off);
                    button.SetText(document->GetPath().GetFileName());

                    if (document->IsActive())
                        _Document = document;
                }
            }
        }

        _ToolBar->DestroyChildren();
        if (_Document!=NULL)
            _FillToolbar();

        Explorer::Get().UpdateContent();
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(MDI, ui::Window)
        COFFEE_RegisterEventHandler(ui::WINDOW_EVENT_Activate, ui::Window, OnActivate)
    COFFEE_EndEventHandler()
    
    //--------------------------------------------------------------------------------------------//

    bool MDI::OnActivate(shell::Event& event)
    {
        if (_Document!=NULL && !_Document->IsActive())
        {
            // HACK: doesn't recreate toolbar else it breaks the button events
            _Document->_ItHasToUpdateToolbar = false;
            _Document->Activate();
            _Document->_ItHasToUpdateToolbar = true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool MDI::OnActivateDocument(shell::Event& event)
    {
        ui::widget::Button* button = (ui::widget::Button*)event.GetTarget();
        Document* plugin = (Document*)button->GetData();
        if (!plugin->IsActive())
            plugin->Activate();
        UpdateDocuments();
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool MDI::OnCloseDocument(shell::Event& event)
    {
        ui::widget::Button* button = (ui::widget::Button*)event.GetTarget();
        Document* plugin = (Document*)button->GetData();
        button->GetParentWindow().Destroy();
        plugin->Destroy();
        if (coffee_editor::Application::Get().GetControlManager().GetChildCount()>0)
            static_cast<Document&>(coffee_editor::Application::Get().GetControlManager().GetChild(0)).Activate();
        UpdateDocuments();
        return true;
    }
    
    //--------------------------------------------------------------------------------------------//

    void MDI::OnDestroyDocument(Document* document)
    {
        if (_Document!=NULL && _Document==document)
        {
            _ToolBar->DestroyChildren();
            _Document = NULL;
        }
    }

    //--------------------------------------------------------------------------------------------//

    bool MDI::OnSave(shell::Event& event)
    {
        _Document->OnSave();
        return true;
    }

    //-OPERATIONS-----------------------------------------------------------------------------//

    void MDI::_FillToolbar()
    {
        COFFEE_RegisterExternEventHandler(
            ui::widget::EVENT_Pressed,
            ui::widget::Widget::GetClassMetaType(),
            *_ToolBar->AddButton("Save", ui::SKIN_ICON_Save),
            OnSave);

        _ToolBar->AddSeparator();

        _Document->FillToolbar(*_ToolBar);
    }

}
}
