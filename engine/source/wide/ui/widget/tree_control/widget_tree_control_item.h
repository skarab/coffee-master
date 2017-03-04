#ifndef _COFFEE_UI_WIDGET_TREE_CONTROL_ITEM_H_
#define _COFFEE_UI_WIDGET_TREE_CONTROL_ITEM_H_

#include "coffee_includes.h"
#include "wide/ui/widget/widget.h"
#include "wide/ui/widget/button/widget_button.h"
#include "wide/ui/widget/check_box/widget_check_box.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// TreeControl item
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API TreeControlItem : public Widget
    {
        COFFEE_Type(TreeControlItem);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        TreeControlItem();
        ~TreeControlItem();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetText(const basic::String& text);
        const basic::String& GetText() const;
        const Button& GetTreeButton() const;
        Button& GetTreeButton();
        void SetImage(const SKIN_ICON& icon);
        void SetImage(storage::Path texture_path);
        void SetImage(graphics::Texture texture_instance);
        int32 GetItemHeight() const;
        
        //-QUERIES--------------------------------------------------------------------------------//

        bool IsOpen() const;
        CHECK_BOX_STATE GetCheckBoxState() const;
        storage::Path GetPath() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(Window* parent, const basic::Vector2i& position,
            const basic::Vector2i& size, uint32 style=0);
        void Open(bool it_is_open);
        void SetCheckBoxState(CHECK_BOX_STATE state);

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(TreeControlItem);
        COFFEE_Event bool OnTreeButton(shell::Event& event);
        COFFEE_Event bool OnSetFocus(shell::Event& event);
        COFFEE_Event bool OnMouseDoubleClick(shell::Event& event);
        COFFEE_Event bool OnMouseLeftButtonPressed(shell::Event& event);
        COFFEE_Event bool OnMouseLeftButtonReleased(shell::Event& event);
        COFFEE_Event bool OnMouseRightButtonPressed(shell::Event& event);
        COFFEE_Event bool OnCheckBox(shell::Event& event);

    protected:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _UpdateClientArea();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::String _Text;
        int32 _ItemHeight;
        Button* _TreeButton;
        CheckBox* _CheckBox;
        Image* _Thumbnail;
        bool _ItIsOpen;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, TreeControlItem);
}
}
}
#endif
