#ifndef _COFFEE_UI_WIDGET_LIST_VIEW_H_
#define _COFFEE_UI_WIDGET_LIST_VIEW_H_

#include "coffee_includes.h"
#include "wide/ui/widget/widget.h"
#include "wide/ui/widget/view_control/widget_view_control.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// ListView widget
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ListView : public ViewControl
    {
        COFFEE_Type(ListView);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ListView();
        ~ListView();

        //-ACCESSORS------------------------------------------------------------------------------//

        uint32 GetSelectedIndex() const;
        uint32 GetItemCount() const;
        const basic::Prow< basic::String*, true >& GetItemArray() const;
        const basic::String& GetItemString(uint32 item_index) const;
        const void* GetItemData(uint32 item_index) const;

        //-QUERIES--------------------------------------------------------------------------------//

        bool Sort(const Window& child1, const Window& child2) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(Window* parent, const basic::Vector2i& position,
            const basic::Vector2i& size, uint32 style=VIEW_CONTROL_STYLE_Default);

        uint32 AddItem(basic::String string, void* data=NULL, Window* item_window=NULL);
        void AddOutput(const basic::String& output);
        void RemoveItems();

        bool SelectItem(uint32 item_index);
        bool SelectItem(basic::String string);

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(ListView);
        COFFEE_Event bool OnSelectItem(shell::Event& event);
        COFFEE_Event bool OnActivateItem(shell::Event& event);
        COFFEE_Event bool OnContextMenu(shell::Event& event);

    protected:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _UpdateClientArea();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Prow< basic::String*, true > _ItemArray;
        basic::Prow< void* > _DataArray;
        uint32 _SelectedIndex;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ListView);
}
}
}
#endif
