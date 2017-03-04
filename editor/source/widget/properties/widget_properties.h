#ifndef _EDITOR_WIDGET_PROPERTIES_H_
#define _EDITOR_WIDGET_PROPERTIES_H_

#include "coffee_editor_includes.h"
#include "asset/asset_manager.h"

namespace coffee_editor
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Properties
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API Properties : public ui::widget::Dialog
    {
        COFFEE_DeclareSingleton(Properties);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Properties();
        ~Properties();

        //-ACCESSORS------------------------------------------------------------------------------//

        const storage::Path& GetObjectPath() const { return _ObjectPath; }
        const asset::Widget& GetAssetWidget() const { return *_AssetWidget; }

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(ui::Window& panel);
        void Edit(storage::Path object_path);
        void Edit(basic::String object_name, meta::Object& object);
        void Clear();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(Properties);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        bool ItIsCheckingAsset;
        storage::Path _ObjectPath;
        asset::Widget* _AssetWidget;
        meta::Object* _Object;
    };
}
}
#endif
