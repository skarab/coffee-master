#include "coffee_editor.h"
#include "document/document.h"
#include "widget/widgets.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(Document);
        COFFEE_Ancestor(edition::Plugin);
    COFFEE_EndType();

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Document::Document(basic::String plugin_name, basic::String help_text) :
        edition::Plugin(plugin_name, help_text),
        _MDI(NULL),
        _ToolBar(NULL),
        _ClientFrame(NULL),
        _ItHasToUpdateToolbar(true)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Document::~Document()
    {
        if (_MDI!=NULL)
            _MDI->OnDestroyDocument(this);
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool Document::IsSupportedExtension(const basic::String& extension) const
    {
        if (_SupportedExtension.GetLineCount()==2)
            return extension==_SupportedExtension[1];
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Document::GetRootPath(storage::Path& root, const storage::Path& path) const
    {
        root = "";
        basic::Text items = path.GetHierarchy();
        for (uint32 i=1 ; i<items.GetLineCount() ; ++i)
        {
            if (GetSupportedExtension().GetLineCount()==2
                && items[i].IsSuffixed(GetSupportedExtension().GetLine(1)))
            {
                for (uint32 k=1 ; k<i+1 ; ++k)
                {
                    root += "/";
                    root += items[k];
                }
                return true;
            }
        }
        return false;
    }
    
    //-HANDLERS-----------------------------------------------------------------------------------//

    void Document::OnInitialize()
    {
        ui::Window& client = _MDI->GetClient();
        client.GetLayout().SetStyle(ui::LAYOUT_STYLE_HorizontalExpand
            | ui::LAYOUT_STYLE_HorizontalCanvas
            | ui::LAYOUT_STYLE_StickChildren);

        if (!HasTransparentToolBar())
        {
            _ToolBar = COFFEE_New(ui::widget::ToolBar);
            _ToolBar->Create(&client, 100, ui::widget::TOOL_BAR_STYLE_Vertical
                | ui::widget::TOOL_BAR_STYLE_DrawFrame);
            _ToolBar->GetLayout().SetCanvas(100, false);
        }

        _ClientFrame = COFFEE_New(ui::Window);
        _ClientFrame->Create(&client, basic::Vector2i(), basic::Vector2i(),
            ui::WINDOW_STYLE_Focusable | ui::WINDOW_STYLE_ForwardsInput);
        _ClientFrame->GetLayout().SetCanvas(100, true);
        _ClientFrame->GetLayout().SetStyle(ui::LAYOUT_STYLE_VerticalExpand);
        
        if (HasTransparentToolBar())
        {
            _ToolBar = COFFEE_New(ui::widget::ToolBar);
            _ToolBar->Create(_ClientFrame, 100, ui::widget::TOOL_BAR_STYLE_Vertical
                | ui::widget::TOOL_BAR_STYLE_DrawFrame);
            _ToolBar->SetStyle(_ToolBar->GetStyle() | ui::WINDOW_STYLE_TopMost);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Document::OnFinalize()
    {
        COFFEE_Log(core::Log::None, "Close %s", _Path.GetBuffer());
        
        _ClientFrame->Destroy();
        if (!HasTransparentToolBar())
            _ToolBar->Destroy();
        _ToolBar = NULL;
        _ClientFrame = NULL;
    }
 
    //--------------------------------------------------------------------------------------------//

    void Document::OnActivate()
    {
        edition::Plugin::OnActivate();
        
        ui::Window& client = _MDI->GetClient();
        for (uint32 i=0 ; i<client.GetChildCount() ; ++i)
            client.GetChildWindow(i).Show(false);

        _ToolBar->Show(true);
        _ClientFrame->Show(true);

        if (_ItHasToUpdateToolbar)
            GetHeadActiveControlGroup().PopulateToolBar(*_ToolBar);
    }

    //--------------------------------------------------------------------------------------------//

    void Document::OnDeactivate()
    {        
        edition::Plugin::OnDeactivate();
    }

    //--------------------------------------------------------------------------------------------//

    void Document::OnActivateControl()
    {
        if (_ToolBar!=NULL && _ItHasToUpdateToolbar)
            GetHeadActiveControlGroup().PopulateToolBar(*_ToolBar);
    }

    //--------------------------------------------------------------------------------------------//

    void Document::OnUpdate(const basic::Time& time_step)
    {
        edition::Plugin::OnUpdate(time_step);

        if (_ToolBar!=NULL)
            GetHeadActiveControlGroup().UpdateToolBar(*_ToolBar);
    }

    //--------------------------------------------------------------------------------------------//

    void Document::OnNew(const storage::Path& file_path)
    {
        _Path = file_path;
        COFFEE_Log(core::Log::None, "Create %s", _Path.GetBuffer());
        _Reset();
    }

    //--------------------------------------------------------------------------------------------//

    void Document::OnOpen(const storage::Path& file_path)
    {
        _Path = file_path;
        COFFEE_Log(core::Log::None, "Open %s", _Path.GetBuffer());
        _Reset();
    }

    //--------------------------------------------------------------------------------------------//

    void Document::OnSave()
    {
        COFFEE_Log(core::Log::None, "Save %s", _Path.GetBuffer());
        _Reset();
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Document::UpdateExplorer()
    {
        widget::Explorer::Get().UpdateContent();
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Document::_SetSupportedExtension(basic::String description, basic::String extension)
    {
        _SupportedExtension.SetEmpty();
        _SupportedExtension.AddLine(description);
        _SupportedExtension.AddLine(extension);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Document::_Reset()
    {
        GetUndoManager().Empty();
        GetSelectionManager().Clear(false);
        DeactivateChildren();
        widget::Properties::Get().Clear();
    
        if (_ToolBar!=NULL)
            PopulateToolBar(*_ToolBar);
    }

}
