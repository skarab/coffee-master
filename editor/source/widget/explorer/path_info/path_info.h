#ifndef _EDITOR_WIDGET_PASS_INFO_H_
#define _EDITOR_WIDGET_PASS_INFO_H_

#include "coffee_editor_includes.h"

namespace coffee_editor
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Path flags
    //--------------------------------------------------------------------------------------------//
    enum PATH_FLAG
    {
        PATH_FLAG_File = 1<<0,          ///< is a file
        PATH_FLAG_Folder = 1<<1,        ///< is a folder
        PATH_FLAG_Asset = 1<<2,         ///< is in assets/ folder
        PATH_FLAG_Import = 1<<3,        ///< is in import/ folder
        PATH_FLAG_Resource = 1<<4,      ///< is in resources/ folder
        PATH_FLAG_Editor = 1<<5,        ///< is editor only
        PATH_FLAG_Document = 1<<6,      ///< belong to a document
        PATH_FLAG_HeadPath = 1<<7,      ///< is the head path
        PATH_FLAG_RootFolder = 1<<8,    ///< is one of the root folders
        PATH_FLAG_Plugin = 1<<9,        ///< is either a component or plugin or editor asset
        PATH_FLAG_Internal = 1<<10      ///< belong to coffee internal folders
    };

    //--------------------------------------------------------------------------------------------//
    /// Path info
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API PathInfo
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PathInfo(const ui::widget::TreeControlItem* item);
        ~PathInfo();

        //-ACCESSORS------------------------------------------------------------------------------//

        const storage::Path& GetPath() const { return _Path; }
        const storage::Path& GetHeadPath() const { return _HeadPath; }
        void EnableFlag(PATH_FLAG flag, bool it_has_to_enable) { COFFEE_EnableFlag(_Flags, flag, it_has_to_enable); } 
        bool IsFlagEnabled(PATH_FLAG flag) const { return COFFEE_IsFlagEnabled(flag, _Flags); }

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        storage::Path _Path;
        storage::Path _HeadPath;
        uint32 _Flags;
    };
}
}
#endif
