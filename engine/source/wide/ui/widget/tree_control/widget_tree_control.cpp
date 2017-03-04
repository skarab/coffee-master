#include "wide/ui/widget/tree_control/widget_tree_control.h"
#include "wide/ui/window/ui_window_manager.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::widget::TreeControl);
        COFFEE_Ancestor(ui::widget::ViewControl);
    COFFEE_EndType();

namespace ui
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    TreeControl::TreeControl() :
        _SelectedItem(NULL),
        _RenameBox(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    TreeControl::~TreeControl()
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool TreeControl::Sort(const Window& child1, const Window& child2) const
    {
        if (child1.IsA<TreeControlItem>() && child2.IsA<TreeControlItem>())
        {
            const TreeControlItem& item1 = static_cast<const TreeControlItem&>(child1);
            const TreeControlItem& item2 = static_cast<const TreeControlItem&>(child2);

            if (item1.GetTreeButton().IsVisible()!=item2.GetTreeButton().IsVisible())
                return item1.GetTreeButton().IsVisible();
            
            return (strcmp(item1.GetText().GetBuffer(), item2.GetText().GetBuffer())<0)
                ==HasExtendedStyle(VIEW_CONTROL_STYLE_SortAscending);
        }
        return false;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void TreeControl::Create(Window* parent, const basic::Vector2i& position,
        const basic::Vector2i& size, uint32 style)
    {
        ViewControl::Create(parent, position, size, VIEW_CONTROL_STYLE_AlwaysShowVScrollBar|style);
    }

    //--------------------------------------------------------------------------------------------//

    TreeControlItem* TreeControl::AddItem(basic::String string, TreeControlItem* parent,
        bool it_has_children, void* data, meta::Object* object, bool it_is_checked)
    {
        TreeControlItem* item;
        Window* parent_window = &GetContainer();

        if (parent!=NULL)
        {
            parent_window = parent;
            parent->GetTreeButton().Show(true);
        }

        item = COFFEE_New(TreeControlItem);
        item->Create(parent_window, basic::Vector2i(0,0), basic::Vector2i(100,50), GetExtendedStyle());
        
        if (HasExtendedStyle(VIEW_CONTROL_STYLE_SortAscending)
            || HasExtendedStyle(VIEW_CONTROL_STYLE_SortDescending))
        {
            item->GetLayout().SetStyle(item->GetLayout().GetStyle()|LAYOUT_STYLE_Sort);
        }

        if (parent!=NULL && !parent->IsOpen())
            item->Show(false);
        
        item->SetText(string);
        item->SetData(data);
        item->SetObjectData(object); 
        item->GetTreeButton().Show(it_has_children);

        if (it_is_checked)
            item->SetCheckBoxState(CHECK_BOX_STATE_Checked);

        return item;
    }

    //--------------------------------------------------------------------------------------------//

    basic::Prow<TreeControlItem*, false> TreeControl::GetItems(TreeControlItem* parent)
    {
        basic::Prow<TreeControlItem*, false> children;
        Window* container = &GetContainer();
        if (parent!=NULL) container = parent;
        for (uint32 i=0 ; i<container->GetChildCount() ; ++i)
        {
            if (container->GetChild(i).IsA<TreeControlItem>())
            {
                TreeControlItem& item = static_cast<TreeControlItem&>(container->GetChild(i));
                children.AddItem(&item);
            }
        }
        return children;                
    }

    //--------------------------------------------------------------------------------------------//

    void TreeControl::RemoveItems(TreeControlItem* parent)
    {
        basic::Prow<TreeControlItem*, false> children;
        children = GetItems(parent);
        for (uint32 i=0 ; i<children.GetSize() ; ++i)
        {
            if (_SelectedItem!=NULL && _SelectedItem->IsParentedBy(children[i]))
                _SelectedItem = NULL;

            children[i]->Destroy();
        }
    
        if (parent==NULL)
            ResetContainer();
    }

    //--------------------------------------------------------------------------------------------//

    TreeControlItem* TreeControl::GetSelectedItem()
    {
        return _SelectedItem;
    }

    //--------------------------------------------------------------------------------------------//

    void TreeControl::ClearSelection()
    {
        if (_SelectedItem!=NULL)
        {
            _SelectedItem->KillFocus();
            _SelectedItem = NULL;
        }
    }

    //--------------------------------------------------------------------------------------------//

    TreeControlItem* TreeControl::AddPath(storage::Path path, bool it_is_checked)
    {
        Window* parent = &GetContainer();
        basic::Text hierarchy = path.GetHierarchy();
        TreeControlItem* parent_item = NULL;
        for (uint32 i=1 ; i<hierarchy.GetLineCount() ; ++i)
        {
            bool it_has_found = false;
            for (uint32 j=0 ; j<parent->GetChildCount() ; ++j)
            {
                if (parent->GetChild(j).IsA<TreeControlItem>())
                {
                    TreeControlItem& item = static_cast<TreeControlItem&>(parent->GetChild(j));
                    if (item.GetText()==hierarchy[i])
                    {
                        parent = parent_item = &item;
                        it_has_found = true;
                        break;
                    }
                }
            }
            if (!it_has_found)
                parent = parent_item = AddItem(hierarchy[i], parent_item, false, NULL, NULL, it_is_checked);
        }
        return parent_item;
    }

    //--------------------------------------------------------------------------------------------//

    TreeControlItem* TreeControl::FindPath(storage::Path path)
    {
        Window* parent = &GetContainer();
        basic::Text hierarchy = path.GetHierarchy();
        TreeControlItem* parent_item = NULL;
        for (uint32 i=1 ; i<hierarchy.GetLineCount() ; ++i)
        {
            bool it_has_found = false;
            for (uint32 j=0 ; j<parent->GetChildCount() ; ++j)
            {
                if (parent->GetChild(j).IsA<TreeControlItem>())
                {
                    TreeControlItem& item = static_cast<TreeControlItem&>(parent->GetChild(j));
                    if (item.GetText()==hierarchy[i])
                    {
                        parent = parent_item = &item;
                        it_has_found = true;
                        break;
                    }
                }
            }
            if (!it_has_found)
                return NULL;
        }
        return parent_item;
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(TreeControl, ViewControl)
        COFFEE_RegisterEventHandler(EVENT_Changed, Widget, OnItemEvent)
        COFFEE_RegisterEventHandler(EVENT_Select, Widget, OnItemEvent)
        COFFEE_RegisterEventHandler(EVENT_Activate, Widget, OnItemEvent)
        COFFEE_RegisterEventHandler(input::EVENT_MouseLeftButtonReleased, input::Handler, OnMouseLeftButtonPressed)
        COFFEE_RegisterEventHandler(input::EVENT_MouseRightButtonPressed, input::Handler, OnMouseRightButtonPressed)
        COFFEE_RegisterEventHandler(EVENT_Edit, Widget, OnEdit)
        COFFEE_RegisterTargetEventHandler(EVENT_Changed, Widget, _RenameBox, OnRename)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool TreeControl::OnItemEvent(shell::Event& event)
    {
        if (event.GetTarget()!=NULL && event.GetTarget()->IsA<TreeControlItem>())
        {
            _SelectedItem = static_cast<TreeControlItem*>(event.GetTarget());
            SendEvent((EVENT)event.GetCode().GetIdentifier());
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool TreeControl::OnMouseLeftButtonPressed(shell::Event& event)
    {
        if (_SelectedItem!=NULL)
        {
            _SelectedItem->KillFocus();
            _SelectedItem = NULL;
            SendEvent(EVENT_Select);
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool TreeControl::OnMouseRightButtonPressed(shell::Event& event)
    {
        if (_SelectedItem!=NULL)
        {
            _SelectedItem->KillFocus();
            _SelectedItem = NULL;
            SendEvent(EVENT_Select);
        }
        SendEvent(EVENT_ContextMenu);
        return true;
    }
       
    //--------------------------------------------------------------------------------------------//

    bool TreeControl::OnEdit(shell::Event& event)
    {
        if (event.GetTarget()!=NULL && event.GetTarget()->IsA<TreeControlItem>())
        {
            if (SendImmediateEvent(EVENT_MayEdit))
            {
                _RenameBox = COFFEE_New(RenameBox);
                _RenameBox->Create(GetSelectedItem(), GetSelectedItem()->GetText());
            }
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool TreeControl::OnRename(shell::Event& event)
    {        
        SendImmediateEvent(EVENT_Edit, (void*)&_RenameBox->GetText());
        return true;
    }

}
}
}
