#ifndef _COFFEE_UI_SKIN_DEFAULT_IMAGE_H_
#define _COFFEE_UI_SKIN_DEFAULT_IMAGE_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/widget/widgets.h"
#include "wide/ui/skin/ui_skin_widget.h"

namespace coffee
{ 
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Image skin
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API SkinImage : public SkinWidget
    {
        //-META-----------------------------------------------------------------------------------//

        COFFEE_Type(SkinImage);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SkinImage();
        ~SkinImage();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void ApplyTheme(SkinTheme& theme);
        void Render(Window& window, const SkinContext& paint_context);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//
        
        SkinWidgetState _Frame;
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, SkinImage);
}
}
#endif
