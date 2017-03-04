#include "wide/ui/skin/ui_skin_context.h"
#include "wide/ui/skin/ui_skin.h"

namespace coffee
{
namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SkinContext::SkinContext() :
        _Renderer(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    SkinContext::~SkinContext()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void SkinContext::Create(const Window* window, const WindowContext* parent_context)
    {
        WindowContext::Create(window, parent_context);
        _Renderer = (ui::SkinRenderer*)&window->GetSkin().GetRenderer();
    }

    //--------------------------------------------------------------------------------------------//

    SkinRenderer& SkinContext::Render() const
    {
        return *(SkinRenderer*)_Renderer;
    }

}
}
