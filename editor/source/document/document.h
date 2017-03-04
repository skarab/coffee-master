#ifndef _EDITOR_DOCUMENT_H_
#define _EDITOR_DOCUMENT_H_

#include "coffee_editor_includes.h"

namespace coffee_editor
{
namespace widget
{
    class MDI;
}

    //--------------------------------------------------------------------------------------------//
    /// Document
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API Document : public edition::Plugin
    {
        friend class widget::MDI;

        COFFEE_Type(Document);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Document(basic::String plugin_name="", basic::String help_text="");
        virtual ~Document();

        //-ACCESSORS------------------------------------------------------------------------------//

        const basic::Text& GetSupportedExtension() const { return _SupportedExtension; }
        const storage::Path& GetPath() const { return _Path; }
        const ui::Window& GetClientFrame() const { return *_ClientFrame; }
        ui::Window& GetClientFrame() { return *_ClientFrame; }

        //-QUERIES--------------------------------------------------------------------------------//

        bool IsSupportedExtension(const basic::String& extension) const;
        virtual bool IsAvailable() const { return false; }
        virtual bool GetRootPath(storage::Path& root, const storage::Path& path) const;
        virtual bool HasTransparentToolBar() const { return false; }

        //-HANDLERS-------------------------------------------------------------------------------//

        virtual void OnInitialize();
        virtual void OnFinalize();
        virtual void OnActivate();
        virtual void OnDeactivate();
        virtual void OnActivateControl();
        virtual void OnUpdate(const basic::Time& time_step);

        virtual void OnNew(const storage::Path& file_path);
        virtual void OnOpen(const storage::Path& file_path);
        virtual void OnSave();
        virtual bool OnUpdateCopy() { return false; }
        virtual bool OnUpdateCut() { return false; }
        virtual bool OnUpdatePaste() { return false; }
        virtual bool OnUpdateDelete() { return false; }
        virtual void OnSelectItem(const storage::Path& path) {};
        virtual bool OnRenameItem(const storage::Path& path, const storage::Path& new_path) { return false; };
        virtual void OnActivateItem(const storage::Path& path) {};

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void UpdateExplorer();
        virtual void FillToolbar(ui::widget::ToolBar& toolbar) {};
        virtual bool IsFolderEmpty(const storage::Path& path) { return true; }
        virtual bool ListFolder(basic::Prow<storage::Path*, true>& pathes, const storage::Path& path) { return false; }
        
    protected:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _SetSupportedExtension(basic::String description, basic::String extension);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        storage::Path _Path;
        basic::Text _SupportedExtension;
        basic::Prow<meta::Object*> _ClipBoard;

    protected:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _Reset();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        widget::MDI* _MDI;
        ui::widget::ToolBar* _ToolBar;
        ui::Window* _ClientFrame;
        bool _ItHasToUpdateToolbar;
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, Document);
}
#endif
