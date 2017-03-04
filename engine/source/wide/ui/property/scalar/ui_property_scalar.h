#ifndef _COFFEE_UI_PROPERTY_SCALAR_H_
#define _COFFEE_UI_PROPERTY_SCALAR_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/property/ui_property_manager.h"
#include "wide/ui/widget/widgets.h"
#include "wide/ui/window/ui_window_manager.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Scalar property widget template
    ///
    /// @see coffee::ui::Property
    //--------------------------------------------------------------------------------------------//
    template< typename type, typename param_type > \
    class COFFEE_TEMPLATE_API PropertyScalar : public Property
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyScalar();
        virtual ~PropertyScalar();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetExtremum(type minimum_value, type maximum_value);

        //-OPERATIONS-----------------------------------------------------------------------------//

        void CreateContent();
        virtual void Update();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(PropertyScalar);
        COFFEE_Event bool OnTextChanged(shell::Event& event);
        COFFEE_Event bool OnScrollUp(shell::Event& event);
        COFFEE_Event bool OnScrollDown(shell::Event& event);
        COFFEE_Event bool OnButtonReleased(shell::Event& event);

    protected:

        //-QUERIES--------------------------------------------------------------------------------//

        virtual basic::String _GetTextFromValue(type value) const = 0;
        virtual type _GetValueFromText(const basic::String& text) const = 0;

        //-ACCESSORS------------------------------------------------------------------------------//

        void _SetValue(type value);
        type _GetValue();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        widget::Label* _Text;
        widget::EditBox* _EditBox;
        widget::Button* _Button;
        type _MinimumValue;
        type _MaximumValue;
        type _Value;
        bool _ItIsUsingExtremum;
        bool _ItIsSliding;
        real _ScrollStep;
        real _SlideFactor;
    };
}
}

//-TEMPLATES--------------------------------------------------------------------------------------//

#include "wide/ui/property/scalar/ui_property_scalar.hpp"

#endif
