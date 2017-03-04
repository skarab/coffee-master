#ifndef _COFFEE_UI_WIDGET_TREE_CONTROL_H_
#define _COFFEE_UI_WIDGET_TREE_CONTROL_H_

#include "coffee_includes.h"
#include "wide/ui/widget/widget.h"
#include "wide/ui/widget/view_control/widget_view_control.h"
#include "wide/ui/widget/tree_control/widget_tree_control_item.h"
#include "wide/ui/component/rename_box/ui_rename_box.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// TreeControl widget
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API TreeControl : public ViewControl
    {
        COFFEE_Type(TreeControl);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        TreeControl();
        ~TreeControl();

        //-QUERIES--------------------------------------------------------------------------------//

        bool Sort(const Window& child1, const Window& child2) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(Window* parent, const basic::Vector2i& position,
            const basic::Vector2i& size, uint32 style=VIEW_CONTROL_STYLE_Default);
        TreeControlItem* AddItem(basic::String string, TreeControlItem* parent=NULL,
            bool it_has_children=false, void* data=NULL, meta::Object* object=NULL, bool it_is_checked=false);
        basic::Prow<TreeControlItem*, false> GetItems(TreeControlItem* parent=NULL);
        void RemoveItems(TreeControlItem* parent=NULL);
        TreeControlItem* GetSelectedItem();
        void ClearSelection();

        TreeControlItem* AddPath(storage::Path path, bool it_is_checked=false);
        TreeControlItem* FindPath(storage::Path path);

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(TreeControl);
        COFFEE_Event bool OnItemEvent(shell::Event& event);
        COFFEE_Event bool OnMouseLeftButtonPressed(shell::Event& event);
        COFFEE_Event bool OnMouseRightButtonPressed(shell::Event& event);
        COFFEE_Event bool OnEdit(shell::Event& event);
        COFFEE_Event bool OnRename(shell::Event& event);
        
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        TreeControlItem* _SelectedItem;
        RenameBox* _RenameBox;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, TreeControl);
}
}
}
#endif
