#ifndef _COFFEE_UI_WIDGET_COMBO_BOX_PROPERTY_H_
#define _COFFEE_UI_WIDGET_COMBO_BOX_PROPERTY_H_

#include "coffee_includes.h"
#include "wide/ui/widget/combo_box/widget_combo_box.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// ComboBoxProperty widget
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ComboBoxProperty : public Widget
    {
        COFFEE_Type(ComboBoxProperty);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ComboBoxProperty();

        //-ACCESSORS------------------------------------------------------------------------------//

        const ComboBox& GetComboBox() const;
        ComboBox& GetComboBox();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(basic::String text, Window* parent, const basic::Vector2i& position,
            uint32 width);
    
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        ComboBox* _ComboBox;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ComboBoxProperty);
}
}
}
#endif
