#ifndef _COFFEE_UI_WIDGET_PROGRESS_BAR_H_
#define _COFFEE_UI_WIDGET_PROGRESS_BAR_H_

#include "coffee_includes.h"
#include "wide/ui/widget/widget.h"
#include "wide/ui/widget/progress_bar/widget_progress_bar_style.h"

namespace coffee
{
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// ProgressBar widget
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ProgressBar : public Widget
    {
        //-META-----------------------------------------------------------------------------------//

        COFFEE_Type(ProgressBar);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ProgressBar();
        virtual ~ProgressBar();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetPercentage(real percentage);
        real GetPercentage() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void Create(Window* parent, const basic::Vector2i& position,
            const basic::Vector2i& size, uint32 style=PROGRESS_BAR_STYLE_Horizontal);

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(ProgressBar);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        real _Percentage;
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ProgressBar);
}
}
}
#endif
