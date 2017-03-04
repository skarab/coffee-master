#ifndef _EDITOR_ASSET_WIDGET_H_
#define _EDITOR_ASSET_WIDGET_H_

#include "coffee_editor_includes.h"
#include "asset/asset_importer.h"
#include "asset/asset_resource_widget.h"

namespace coffee_editor
{
namespace asset
{
    //--------------------------------------------------------------------------------------------//
    /// GUI of asset importer
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API Widget : public ui::Window
    {
        COFFEE_Type(Widget);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Widget();
        ~Widget();

        //-ACCESSORS------------------------------------------------------------------------------//

        const Importer& GetImporter() const { return *_Importer; }

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(const storage::Path& import_path, ui::Window* parent);
        void CheckForModifications();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(Widget);
        COFFEE_Event bool OnModified(shell::Event& event);
        COFFEE_Event bool OnSave(shell::Event& event);
        
    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _CreateToolBar();
        void _UpdateContent();
        
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        storage::Path _ImportPath;
        Importer* _Importer;
        ui::PropertyList* _PropertyList;
        bool _ItIsModified;
        ui::widget::ToolBar* _ToolBar;
        ui::widget::Button* _SaveButton;
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, Widget);
}
}
#endif
