#ifndef _COFFEE_UI_SKIN_CONTEXT_H_
#define _COFFEE_UI_SKIN_CONTEXT_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/window/ui_window_context.h"
#include "wide/ui/skin/renderer/ui_skin_renderer.h"

namespace coffee
{ 
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Skin context
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API SkinContext : public WindowContext
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        SkinContext();
        ~SkinContext();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create(const Window* window=NULL, const WindowContext* parent_context=NULL);
        SkinRenderer& Render() const;

    private:
        
        //-ATTRIBUTES-----------------------------------------------------------------------------//

        SkinRenderer* _Renderer;
    };
}
}
#endif
