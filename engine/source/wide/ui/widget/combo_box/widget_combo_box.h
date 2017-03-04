#ifndef _COFFEE_UI_WIDGET_COMBO_BOX_H_
#define _COFFEE_UI_WIDGET_COMBO_BOX_H_

#include "coffee_includes.h"
#include "wide/ui/widget/widget.h"
#include "wide/ui/widget/edit_box/widget_edit_box.h"
#include "wide/ui/widget/button/widget_button.h"
#include "wide/ui/widget/list_view/widget_list_view.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// ComboBox widget
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ComboBox : public Widget
    {
        COFFEE_Type(ComboBox);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ComboBox();
        virtual ~ComboBox();

        //-ACCESSORS------------------------------------------------------------------------------//

        uint32 GetSelectedIndex() const;
        basic::String GetSelectedString() const; 
        const basic::Prow< basic::String*, true >& GetItemArray() const;
        const basic::String& GetItemString(uint32 item_index) const;
        const void* GetItemData(uint32 item_index) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void Create(Window* parent, const basic::Vector2i& position,
            int32 width, uint32 style=0);

        int32 AddItem(basic::String string, void* data=NULL);
        void RemoveItems();
        bool SelectItem(uint32 item_index);
        bool SelectItem(basic::String string);

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(ComboBox);
        COFFEE_Event bool OnComboButton(shell::Event& event);
        COFFEE_Event bool OnSelectText(shell::Event& event);
        COFFEE_Event bool OnComboListKillFocus(shell::Event& event);
        COFFEE_Event bool OnComboListSelectItem(shell::Event& event);

    protected:

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void _UpdateClientArea();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        EditBox* _EditBox;
        Button* _ComboButton;
        ListView* _ComboList;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ComboBox);
}
}
}
#endif
