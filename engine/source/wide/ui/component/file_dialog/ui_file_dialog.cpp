#include "wide/ui/component/file_dialog/ui_file_dialog.h"
#include "wide/ui/window/ui_window_manager.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::FileDialog);
        COFFEE_Ancestor(ui::widget::Dialog);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    FileDialog::FileDialog()
    {
    }

    //--------------------------------------------------------------------------------------------//

    FileDialog::~FileDialog()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const storage::Path& FileDialog::GetFilePath() const
    {
        return _FilePath;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void FileDialog::Create(basic::String caption, uint32 flags, basic::Text extensions,
        storage::Path file_path)
    {
        widget::Dialog::Create(NULL, basic::Vector2i(100, 100), basic::Vector2i(400, 330));

        SetTitleBarText(caption);
        SetStyle(GetStyle() & ~(uint32) WINDOW_STYLE_Resizeable);

        _Flags = flags;
        _Extensions = extensions;
        _FilePath = file_path;

        if (_Extensions.GetLineCount() == 0)
        {
            _Extensions.AddLine(basic::String("All files"));
            _Extensions.AddLine(basic::String("*.*"));
        }

        PositionToCenter();

        _PathText = COFFEE_New(widget::Label);
        _PathText->Create(this, basic::Vector2i(0, 2), basic::Vector2i(80, 20));
        _PathText->SetText("Path");
        
        _PathEdit = COFFEE_New(widget::EditBox);
        _PathEdit->Create(this, basic::Vector2i(90, 2), 300);
        
        _EntryList = COFFEE_New(widget::ListView);
        _EntryList->Create(this, basic::Vector2i(0, 27), basic::Vector2i(390, 220), widget::VIEW_CONTROL_STYLE_SortAscending);
        
        _FileText = COFFEE_New(widget::Label);
        _FileText->Create(this, basic::Vector2i(0, 252), basic::Vector2i(50, 20));
        _FileText->SetText("File");
        
        _FileEdit = COFFEE_New(widget::EditBox);
        _FileEdit->Create(this, basic::Vector2i(60, 252), 275);
        
        _ExtensionText = COFFEE_New(widget::Label);
        _ExtensionText->Create(this, basic::Vector2i(0, 277), basic::Vector2i(50, 20));
        _ExtensionText->SetText("Extensions");
        
        _ExtensionCombo = COFFEE_New(widget::ComboBox);
        _ExtensionCombo->Create(this, basic::Vector2i(60, 277), 275);
        
        _OkButton = COFFEE_New(widget::Button);
        _OkButton->Create(this, basic::Vector2i(340, 252), basic::Vector2i(50, 20),
            widget::BUTTON_STYLE_Default);
        _OkButton->SetText("Ok");
        
        _CancelButton = COFFEE_New(widget::Button);
        _CancelButton->Create(this, basic::Vector2i(340, 277), basic::Vector2i(50, 20),
            widget::BUTTON_STYLE_Default);
        _CancelButton->SetText("Cancel");
        
        _InitializeContent();
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(FileDialog, widget::Dialog)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Pressed, widget::Widget, _OkButton, OnOk)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Pressed, widget::Widget, _CancelButton, OnCancel)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Select, widget::Widget, _EntryList, OnSelectEntry)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Activate, widget::Widget, _EntryList, OnActivateEntry)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Select, widget::Widget, _ExtensionCombo, OnSelectExtension)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Changed, widget::Widget, _PathEdit, OnPathChanged)
        COFFEE_RegisterTargetEventHandler(widget::EVENT_Changed, widget::Widget, _FileEdit, OnFileChanged)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool FileDialog::OnOk(shell::Event& event)
    {
        _UpdateContent();

        if (!_FilePath.IsFilePath())
            return true;

        if ((_Flags&FILE_DIALOG_FLAG_FileMustExist)==0
            || storage::System::Get().HasPath(_FilePath))
        {
            WindowManager::Get().AcceptModalWindow();
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool FileDialog::OnCancel(shell::Event& event)
    {
        Destroy();
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool FileDialog::OnSelectEntry(shell::Event& event)
    {
        uint32 selected_index = _EntryList->GetSelectedIndex();
        if (selected_index!=NONE)
        {
            storage::Path path;
            if (_EntryList->GetItemString(selected_index).IsPrefixed('/'))
            {
                path = _CurrentPath + _EntryList->GetItemString(selected_index);
            }
            else
            {
                path = _CurrentPath + '/' + _EntryList->GetItemString(selected_index);
            }
            if (storage::System::Get().HasPath(path))
            {
                if (path.IsFilePath())
                {
                    _FileEdit->SetText(path.GetName());
                }
                else
                {
                    _CurrentPath = path;
                    _UpdateContent();
                }
            }
            else
            {
                if (_EntryList->GetItemString(selected_index)=='.')
                {
                    _CurrentPath = _RootPath;
                }
                else if (_CurrentPath!=_RootPath && _CurrentPath.HasPath())
                {
                    _CurrentPath = _CurrentPath.GetPath();
                }
                _UpdateContent();
            }
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool FileDialog::OnActivateEntry(shell::Event& event)
    {
        uint32 selected_index = _EntryList->GetSelectedIndex();
        if (selected_index!=NONE)
        {
            storage::Path path;
            if (_EntryList->GetItemString(selected_index).IsPrefixed('/'))
            {
                path = _CurrentPath + _EntryList->GetItemString(selected_index);
            }
            else
            {
                path = _CurrentPath + '/' + _EntryList->GetItemString(selected_index);
            }
            if (storage::System::Get().HasPath(path))
            {
                if (path.IsFilePath())
                {
                    _FilePath = path;
                    return OnOk(event);
                }
                else
                {
                    _CurrentPath = path;
                }
            }
            else
            {
                if (_EntryList->GetItemString(selected_index)=='.')
                {
                    _CurrentPath = _RootPath;
                }
                else if(_CurrentPath!=_RootPath && _CurrentPath.HasPath())
                {
                    _CurrentPath = _CurrentPath.GetPath();
                }
            }
            _UpdateContent();
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool FileDialog::OnSelectExtension(shell::Event& event)
    {
        _ExtensionFilter = _ExtensionCombo->GetSelectedIndex();
        if ((_Flags&FILE_DIALOG_FLAG_Save)==0 &&_ExtensionFilter!=NONE)
            --_ExtensionFilter;
        _UpdateContent();
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool FileDialog::OnPathChanged(shell::Event& event)
    {
        storage::Path path = _PathEdit->GetText();
        if ((path.GetLength()==0 || path.IsPrefixed(_RootPath))
            && storage::System::Get().HasPath(path))
        {
            _CurrentPath = path;
            _UpdateContent(true);
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool FileDialog::OnFileChanged(shell::Event& event)
    {
        if (_PathEdit->GetText().GetLength()!=1)
        {
            _FilePath = storage::Path(_PathEdit->GetText() + "/" + _FileEdit->GetText());
        }
        else
        {
            _FilePath = storage::Path(_PathEdit->GetText() + _FileEdit->GetText());
        }
        return true;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool FileDialog::_IsVisibleExtension(const basic::String& file_extension) const
    {
        uint32 extension_index;

        if(_Extensions.GetLineCount() == 0)
            return true;

        if(_ExtensionFilter != NONE)
            return file_extension==_Extensions.GetLine(_ExtensionFilter*2+1);

        for(extension_index=0 ; extension_index<_Extensions.GetLineCount()/2 ; ++extension_index)
        {
            if(file_extension==_Extensions.GetLine(extension_index*2+1))
                return true;
        }

        return false;
    }

    //--------------------------------------------------------------------------------------------//

    void FileDialog::_InitializeContent()
    {
        uint32 extension_index;

        _RootPath = '/';
        _CurrentPath = _RootPath;

        if ((_Flags&FILE_DIALOG_FLAG_Save)==0)
        {
            _ExtensionFilter = NONE;
        }
        else
        {
            _ExtensionFilter = 0;
        }

        if (_Extensions.GetLineCount()==0)
        {
            _ExtensionCombo->AddItem("All files (*.*)");
        }
        else if ((_Flags&FILE_DIALOG_FLAG_Save)==0)
        {
            _ExtensionCombo->AddItem("All filtered files (*.-)");
        }

        for (extension_index=0 ; extension_index<_Extensions.GetLineCount()/2 ; ++extension_index)
        {
            _ExtensionCombo->AddItem(_Extensions.GetLine(extension_index * 2)
                + " (*." + _Extensions.GetLine(extension_index * 2 + 1) + ")");
        }

        _ExtensionCombo->SelectItem(0);
        _UpdateContent();
    }

    //--------------------------------------------------------------------------------------------//

    void FileDialog::_UpdateContent(bool it_is_edited)
    {
        basic::String path = _CurrentPath;
        if (!it_is_edited)
        {
            if (path.GetLength()==0)
                path = "/";
            _PathEdit->SetText(path);
        }

        _EntryList->RemoveItems();
        if (_CurrentPath!=_RootPath && _CurrentPath.HasPath()
            && _CurrentPath.GetPath()!=_RootPath)
        {
            _EntryList->AddItem('.');
        }

        if (_CurrentPath!=_RootPath && _CurrentPath.HasPath())
            _EntryList->AddItem("..");

        basic::Prow<storage::Path*, true> pathes;
        storage::System::Get().List(pathes, _CurrentPath);
        for (uint32 entry_index=0 ; entry_index<pathes.GetSize() ; ++entry_index)
        {
            if (pathes[entry_index]->IsFilePath())
            {
                if (_IsVisibleExtension(pathes[entry_index]->GetFileExtension()))
                    _EntryList->AddItem(pathes[entry_index]->GetName());
            }
            else
            {
                if (*pathes[entry_index]!="/root")
                    _EntryList->AddItem(basic::String("/") + pathes[entry_index]->GetName());
            }
        }

        shell::Event event;
        OnFileChanged(event);
        if (_ExtensionFilter!=NONE && _Extensions.GetLineCount() > 0)
        {
            basic::String extension = _FilePath.GetFileExtension();
            if (extension.GetLength() > 0)
            {
                _FilePath = _FilePath.GetLeft(_FilePath.GetLength()
                    - _FilePath.GetFileExtension().GetLength() - 1) + "."
                    + _Extensions.GetLine(_ExtensionFilter * 2 + 1);
            }
            else
            {
                _FilePath += basic::String('.') + _Extensions.GetLine(_ExtensionFilter * 2 + 1);
            }
            _FileEdit->SetText(_FilePath.GetFileName());
        }
    }

}
}
