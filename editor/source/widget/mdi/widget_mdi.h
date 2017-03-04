#ifndef _EDITOR_WIDGET_MDI_H_
#define _EDITOR_WIDGET_MDI_H_

#include "coffee_editor_includes.h"
#include "document/document.h"

namespace coffee_editor
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Multi document interface widget
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API MDI : public ui::Window
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        MDI();
        ~MDI();

        //-OPERATIONS-----------------------------------------------------------------------------//

        const ui::widget::ToolBar& GetDocuments() const { return *_Documents; }
        ui::widget::ToolBar& GetDocuments() { return *_Documents; }
        const ui::Window& GetClient() const { return *_Client; }
        ui::Window& GetClient() { return *_Client; }

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(ui::Window& panel, uint32 style=ui::WINDOW_STYLE_None);
        bool OpenDocument(storage::Path document_path, Document* document_interface);
        bool CloseDocument(Document* document);
        void UpdateDocuments();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(MDI);
        COFFEE_Event bool OnActivate(shell::Event& event);
        COFFEE_DeclareExternEventHandler(MDI, OnActivateDocument);
        COFFEE_DeclareExternEventHandler(MDI, OnCloseDocument);
        COFFEE_DeclareExternEventHandler(MDI, OnSave);
        
        void OnDestroyDocument(Document* document);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _FillToolbar();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        ui::widget::ToolBar* _Documents;
        ui::widget::ToolBar* _ToolBar;
        ui::Window* _Client;
        Document* _Document;
    };
}
}
#endif
