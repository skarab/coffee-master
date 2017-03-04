#ifndef _COFFEE_UI_FILE_DIALOG_H_
#define _COFFEE_UI_FILE_DIALOG_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/widget/widgets.h"
#include "wide/ui/component/file_dialog/ui_file_dialog_flag.h"
#include "kernel/storage/storage.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// File dialog
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API FileDialog : public widget::Dialog
    {
        COFFEE_Type(FileDialog);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        FileDialog();
        virtual ~FileDialog();

        //-ACCESSORS------------------------------------------------------------------------------//

        const storage::Path& GetFilePath() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(basic::String caption, uint32 flags = FILE_DIALOG_FLAG_Open
            | FILE_DIALOG_FLAG_FileMustExist, basic::Text extensions = basic::Text(),
            storage::Path file_path = storage::Path());

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(FileDialog);
        COFFEE_Event bool OnOk(shell::Event& event);
        COFFEE_Event bool OnCancel(shell::Event& event);
        COFFEE_Event bool OnSelectEntry(shell::Event& event);
        COFFEE_Event bool OnActivateEntry(shell::Event& event);
        COFFEE_Event bool OnSelectExtension(shell::Event& event);
        COFFEE_Event bool OnPathChanged(shell::Event& event);
        COFFEE_Event bool OnFileChanged(shell::Event& event);

    private:

        //-QUERIES--------------------------------------------------------------------------------//

        bool _IsVisibleExtension(const basic::String& file_extension) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _InitializeContent();
        void _UpdateContent(bool it_is_edited=false);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Text _Extensions;
        storage::Path _FilePath;
        storage::Path _CurrentPath;
        storage::Path _RootPath;
        uint32 _ExtensionFilter;
        uint32 _Flags;
        widget::Label* _PathText;
        widget::EditBox* _PathEdit;
        widget::ListView* _EntryList;
        widget::Label* _FileText;
        widget::EditBox* _FileEdit;
        widget::Label* _ExtensionText;
        widget::ComboBox* _ExtensionCombo;
        widget::Button* _OkButton;
        widget::Button* _CancelButton;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, FileDialog);
}
}
#endif
