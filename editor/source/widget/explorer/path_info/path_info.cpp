#include "widget/explorer/path_info/path_info.h"
#include "coffee_editor.h"

namespace coffee_editor
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PathInfo::PathInfo(const ui::widget::TreeControlItem* item) :
        _Flags(0)
    {
        if (item!=NULL)
        {
            _Path = item->GetPath();
            _HeadPath = _Path.GetHeadFilePath("*");
        }

        EnableFlag(PATH_FLAG_File, _Path.IsFilePath());
        EnableFlag(PATH_FLAG_Folder, !_Path.IsFilePath());

        EnableFlag(PATH_FLAG_Asset, _Path.IsPrefixed("/coffee/assets") || _Path.IsPrefixed("/assets"));
        EnableFlag(PATH_FLAG_Import, _Path.IsPrefixed("/coffee/import") || _Path.IsPrefixed("/import"));
        EnableFlag(PATH_FLAG_Resource, !IsFlagEnabled(PATH_FLAG_Asset) && !IsFlagEnabled(PATH_FLAG_Import));
        EnableFlag(PATH_FLAG_Editor, _Path.IsPrefixed("/coffee/editor") || _Path.IsPrefixed("/editor")
            || _Path.IsPrefixed("/coffee/assets/editor") || _Path.IsPrefixed("/assets/editor")
            || _Path.IsPrefixed("/coffee/import/editor") || _Path.IsPrefixed("/import/editor"));
        
        EnableFlag(PATH_FLAG_Document, coffee_editor::Application::Get().IsDocument(_Path));

        EnableFlag(PATH_FLAG_HeadPath, (_Path==_HeadPath)||_HeadPath.IsEmpty());
        EnableFlag(PATH_FLAG_RootFolder, _Path=="/coffee/assets" || _Path=="/assets"
            || _Path=="/coffee/assets/editor" || _Path=="/assets/editor"
            || _Path=="/coffee/import" || _Path=="/import"
            || _Path=="/coffee/import/editor" || _Path=="/import/editor"
            || _Path=="/coffee/editor" || _Path=="/editor"
            || _Path=="/coffee" || _Path=="");

        EnableFlag(PATH_FLAG_Plugin, _Path.IsContaining(".component")
            || _Path.IsContaining(".plugin") || _Path.IsContaining(".editor"));

        EnableFlag(PATH_FLAG_Internal, _Path.IsPrefixed("/coffee"));
    }

    //--------------------------------------------------------------------------------------------//

    PathInfo::~PathInfo()
    {
    }

}
}
