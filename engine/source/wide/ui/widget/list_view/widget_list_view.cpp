#include "wide/ui/widget/list_view/widget_list_view.h"
#include "wide/ui/widget/edit_box/widget_edit_box.h"
#include "wide/ui/window/ui_window_manager.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::widget::ListView);
        COFFEE_Ancestor(ui::widget::ViewControl);
    COFFEE_EndType();

namespace ui
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ListView::ListView() :
        _SelectedIndex(NONE)
    {
    }

    //--------------------------------------------------------------------------------------------//

    ListView::~ListView()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    uint32 ListView::GetSelectedIndex() const
    {
        return _SelectedIndex;
    }

    //--------------------------------------------------------------------------------------------//

    uint32 ListView::GetItemCount() const
    {
        return _ItemArray.GetSize();
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Prow< basic::String*, true >& ListView::GetItemArray() const
    {
        return _ItemArray;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::String& ListView::GetItemString(uint32 item_index) const
    {
        return *_ItemArray[item_index];
    }

    //--------------------------------------------------------------------------------------------//

    const void* ListView::GetItemData(uint32 item_index) const
    {
        return _DataArray[item_index];
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool ListView::Sort(const Window& child1, const Window& child2) const
    {
        if (child1.IsA<EditBox>() && child2.IsA<EditBox>())
        {
            return (strcmp(
                static_cast<const EditBox&>(child1).GetText().GetBuffer(),
                static_cast<const EditBox&>(child2).GetText().GetBuffer())<0)
                ==HasExtendedStyle(VIEW_CONTROL_STYLE_SortAscending);
        }
        return false;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ListView::Create(Window* parent, const basic::Vector2i& position,
        const basic::Vector2i& size, uint32 style)
    {
        ViewControl::Create(parent, position, size, VIEW_CONTROL_STYLE_AlwaysShowVScrollBar|style);
    }

    //--------------------------------------------------------------------------------------------//

    uint32 ListView::AddItem(basic::String string, void* data, Window* item_window)
    {
        uint32 item_index;

        item_index = _ItemArray.AddItem(COFFEE_New(basic::String, string));
        _DataArray.AddItem(data);

        if (item_window==NULL)
        {
            EditBox* edit_box = COFFEE_New(EditBox);

            edit_box->Create(
                &GetContainer(),
                basic::Vector2i(),
                20,
                EDIT_BOX_STYLE_ReadOnly | EDIT_BOX_STYLE_NoBorders
                | EDIT_BOX_STYLE_NoFrame);

            edit_box->SetText(string);
        }
        return item_index;
    }

    //--------------------------------------------------------------------------------------------//

    void ListView::AddOutput(const basic::String& output)
    {
        EditBox* last_edit_box = NULL;
        for (int32 i=(int32)GetContainer().GetChildCount()-1 ; i>=0 ; --i)
        {
            if (GetContainer().GetChild(i).IsA<EditBox>())
            {
                last_edit_box = static_cast<EditBox*>(&GetContainer().GetChild(i));
                break;
            }
        }

        for (uint32 i=0 ; i<output.GetLength() ; ++i)
        {
            if (output[i]=='\r')
                continue;
            if (_ItemArray.GetSize()==0
                || (_ItemArray.GetLast()->GetLength()>0 && _ItemArray.GetLast()->GetLast()=='\n'))
            {
                _ItemArray.AddItem(COFFEE_New(basic::String));
                _DataArray.AddItem(NULL);

                last_edit_box = COFFEE_New(EditBox);
                last_edit_box->Create(
                    &GetContainer(),
                    basic::Vector2i(),
                    20,
                    EDIT_BOX_STYLE_ReadOnly | EDIT_BOX_STYLE_NoBorders
                    | EDIT_BOX_STYLE_NoFrame);

                // Clamp to 600 items for now, else performances become mad...
                if (_ItemArray.GetSize()>600)
                {
                    _ItemArray.Remove(0);
                    _DataArray.Remove(0);
                    for (uint32 i=0 ; i<GetContainer().GetChildCount() ; ++i)
                    {
                        if (GetContainer().GetChild(i).IsA<EditBox>())
                        {
                            GetContainer().GetChild(i).Destroy();
                            break;
                        }
                    }
                }
            }
            (*_ItemArray.GetLast()) += output[i];
            last_edit_box->SetText(*_ItemArray.GetLast());
        }
    }

    //--------------------------------------------------------------------------------------------//

    void ListView::RemoveItems()
    {
        while(GetContainer().HasChildren())
            GetContainer().GetChildWindow(0).Destroy();
        
        _DataArray.Clear();
        _ItemArray.Clear();
        _SelectedIndex = NONE;
        ResetContainer();
    }

    //--------------------------------------------------------------------------------------------//

    bool ListView::SelectItem(uint32 item_index)
    {
        if(item_index>=0 && item_index<_ItemArray.GetSize())
        {
            _SelectedIndex = item_index;
            return true;
        }

        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool ListView::SelectItem(basic::String string)
    {
        uint32 item_index;

        for(item_index=0 ; item_index<_ItemArray.GetSize() ; ++item_index)
        {
            if(string==*_ItemArray[item_index])
                return SelectItem(item_index);
        }

        return false;
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(ListView, ViewControl)
        COFFEE_RegisterEventHandler(EVENT_Select, Widget, OnSelectItem)
        COFFEE_RegisterEventHandler(EVENT_Activate, Widget, OnActivateItem)
        COFFEE_RegisterEventHandler(EVENT_ContextMenu, Widget, OnContextMenu)
    COFFEE_EndEventHandler()

    //--------------------------------------------------------------------------------------------//

    bool ListView::OnSelectItem(shell::Event& event)
    {
        uint32 childIndex;
        for(childIndex=0 ; childIndex<GetContainer().GetChildCount() ; ++childIndex)
        {
            if(event.GetTarget()==&GetContainer().GetChildWindow(childIndex))
            {
                _SelectedIndex = childIndex;

                if(_SelectedIndex>=_ItemArray.GetSize())
                    _SelectedIndex = NONE;

                SendEvent(EVENT_Select);
                return true;
            }
        }

        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool ListView::OnActivateItem(shell::Event& event)
    {
        uint32 childIndex;
        for(childIndex=0 ; childIndex<GetContainer().GetChildCount() ; ++childIndex)
        {
            if(event.GetTarget()==&GetContainer().GetChildWindow(childIndex))
            {
                _SelectedIndex = childIndex;

                if(_SelectedIndex>=_ItemArray.GetSize())
                    _SelectedIndex = NONE;

                SendEvent(EVENT_Activate);
                return true;
            }
        }

        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool ListView::OnContextMenu(shell::Event& event)
    {
        uint32 childIndex;
        for(childIndex=0 ; childIndex<GetContainer().GetChildCount() ; ++childIndex)
        {
            if(event.GetTarget()==&GetContainer().GetChildWindow(childIndex))
            {
                _SelectedIndex = childIndex;

                if(_SelectedIndex>=_ItemArray.GetSize())
                    _SelectedIndex = NONE;

                SendEvent(EVENT_ContextMenu);
                return true;
            }
        }

        return false;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ListView::_UpdateClientArea()
    {
        ViewControl::_UpdateClientArea();

        if (HasContainer())
        {
            uint32 maximum_size = Maximum(GetContainer().GetSize().X,
                GetRect().Size.X-GetBorders().X*2-17);

            for (uint32 i=0 ; i<GetContainer().GetChildCount() ; ++i)
            {
                GetContainer().GetChildWindow(i).SetSize(basic::Vector2i(
                    maximum_size,
                    GetContainer().GetChildWindow(i).GetSize().Y));
            }
        }

        if (HasExtendedStyle((uint32)VIEW_CONTROL_STYLE_FollowCursorOnAdd)
            && (!WindowManager::Get().HasFocusWindow()
                || !WindowManager::Get().GetFocusWindow().IsParentedBy(_VerticalScrollBar)))
        {
            _VerticalScrollBar->SetScrollPosition(_VerticalScrollBar->GetMaximum());
        }
    }

}
}
}
