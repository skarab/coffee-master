#ifndef _COFFEE_UI_WIDGET_IMAGE_H_
#define _COFFEE_UI_WIDGET_IMAGE_H_

#include "coffee_includes.h"
#include "wide/ui/widget/widget.h"
#include "wide/ui/widget/image/widget_image_style.h"
#include "system/graphics/texture/graphics_texture.h"
#include "wide/ui/skin/ui_skin_icon.h"

namespace coffee
{
namespace graphics
{
    //-FORWARDS-----------------------------------------------------------------------------------//
    class Texture2D;
}
namespace ui
{
namespace widget
{
    //--------------------------------------------------------------------------------------------//
    /// Image widget
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Image : public Widget
    {
        COFFEE_Type(Image);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Image();
        virtual ~Image();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetImage(const basic::Image& image);
        void SetImage(const SKIN_ICON& icon);
        void SetImage(graphics::Texture texture_instance);
        void SetImage(storage::Path texture_path);

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void Create(Window* parent, const basic::Vector2i& position,
            const basic::Vector2i& size, uint32 style=IMAGE_STYLE_Default);
        void RenderImage(const SkinContext& paint_context);

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(Image);

    protected:

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void _UpdateClientArea();

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _GenerateTexture(const basic::Image& image);
        void _DestroyTexture();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        graphics::Texture2D* _Texture;
        graphics::Texture _TextureInstance;
        SKIN_ICON _Icon;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Image);
}
}
}
#endif
