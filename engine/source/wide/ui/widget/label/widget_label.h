#ifndef _COFFEE_UI_WIDGET_LABEL_H_
#define _COFFEE_UI_WIDGET_LABEL_H_

#include "coffee_includes.h"
#include "wide/ui/widget/widget.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Label widget
    ///
    /// Simple widget displaying a static text.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Label : public Widget
    {
        COFFEE_Type(Label);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Label();
        virtual ~Label();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetText(const basic::String& text);
        const basic::String& GetText() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void Create(Window* parent, const basic::Vector2i& position,
            const basic::Vector2i& size, uint32 style=0);

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(Label);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::String _Text;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Label);
}
}
}
#endif
