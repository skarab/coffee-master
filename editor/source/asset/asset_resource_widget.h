#ifndef _EDITOR_ASSET_RESOURCE_WIDGET_H_
#define _EDITOR_ASSET_RESOURCE_WIDGET_H_

#include "coffee_editor_includes.h"
#include "asset/asset_importer.h"

namespace coffee_editor
{
namespace asset
{
    //--------------------------------------------------------------------------------------------//
    /// Widget dedicated to resource edition
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API ResourceWidget : public ui::Window
    {
        COFFEE_Type(ResourceWidget);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ResourceWidget();
        ~ResourceWidget();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(const storage::Path& resource_path, ui::Window* parent);
        virtual void Destroy();
        virtual void Update();
        void CheckForModifications();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(Widget);
        COFFEE_Event bool OnModified(shell::Event& event);
        COFFEE_Event bool OnSave(shell::Event& event);
        COFFEE_Event bool OnReload(shell::Event& event);
        COFFEE_Event bool OnSelectLOD(shell::Event& event);
        COFFEE_Event bool OnAddLOD(shell::Event& event);
        COFFEE_Event bool OnRemoveLOD(shell::Event& event);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _CreateToolBar();
        void _CreateLODBar();
        void _CreateLODProperties();
        void _UpdateContent();
        void _DestroyContent();
        
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        storage::Path _ResourcePath;
        resource::Chunk* _ResourceChunk;
        resource::Object _ResourceInstance;
        ui::PropertyList* _PropertyList;
        bool _ItIsModified;
        ui::widget::ToolBar* _ToolBar;
        ui::widget::Button* _SaveButton;
        ui::widget::Button* _ReloadButton;
        ui::widget::Group* _LODGroup;
        ui::widget::ComboBox* _LODCombo;
        ui::widget::Button* _AddLODButton;
        ui::widget::Button* _RemoveLODButton;
        ui::PropertyList* _LODPropertyList;
    };

    COFFEE_RegisterType(COFFEE_EDITOR_EXPORT_STATICS, ResourceWidget);
}
}
#endif
