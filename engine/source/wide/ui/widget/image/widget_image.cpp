#include "wide/ui/widget/image/widget_image.h"
#include "wide/ui/skin/ui_skin_context.h"
#include "system/graphics/texture/2d/graphics_texture_2d.h"
#include "system/graphics/renderer/graphics_renderer.h"
#include "system/graphics/geometric/graphics_geometric_renderer.h"
#include "wide/ui/skin/ui_skin.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::widget::Image);
        COFFEE_Ancestor(ui::widget::Widget);
    COFFEE_EndType();

namespace ui
{
namespace widget
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Image::Image() :
        _Texture(NULL),
        _Icon(SKIN_ICON_None)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Image::~Image()
    {
        _DestroyTexture();
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Image::SetImage(const basic::Image& image)
    {
        _Icon = SKIN_ICON_None;
        _GenerateTexture(image);
    }

    //--------------------------------------------------------------------------------------------//

    void Image::SetImage(const SKIN_ICON& icon)
    {
        _Icon = icon;
    }

    //--------------------------------------------------------------------------------------------//

    void Image::SetImage(graphics::Texture texture_instance)
    {
        _Icon = SKIN_ICON_None;
        _TextureInstance = texture_instance;
    }

    //--------------------------------------------------------------------------------------------//

    void Image::SetImage(storage::Path texture_path)
    {
        _Icon = SKIN_ICON_None;
        if (_TextureInstance.GetFilePath()!=texture_path)
        {
            graphics::Texture texture;
            texture = coffee::resource::Manager::Get().Load(texture_path);
            SetImage(texture);
        }
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Image::Create(Window* parent, const basic::Vector2i& position,
        const basic::Vector2i& size, uint32 style)
    {
        Window::Create(parent, position, size, 0);
        SetExtendedStyle(style);
    }

    //--------------------------------------------------------------------------------------------//

    void Image::RenderImage(const SkinContext& paint_context)
    {
        if (_TextureInstance.IsAvailable())
        {
            graphics::Renderer::Get().EnableDepthTest(false);
            graphics::Renderer::Get().SetColor(
                IsEnabled()?basic::Color(1.0f, 1.0f, 1.0f, 1.0f):
                basic::Color(1.0f, 1.0f, 1.0f, 0.5f));
            graphics::Renderer::Get().EnableBlending(true);
            graphics::Renderer::Get().SetBlendingFactors(
                graphics::RENDER_STATE_BLENDING_FACTOR_SourceAlpha,
                graphics::RENDER_STATE_BLENDING_FACTOR_SourceAlphaInversed);

            _TextureInstance.Bind(0);

            if (HasExtendedStyle(IMAGE_STYLE_NoBorders))
            {
                graphics::GeometricRenderer::RenderViewportTexturedRectangle(
                    paint_context.GetDesktopWindowRect().GetMinimum(),
                    paint_context.GetDesktopWindowRect().GetMaximum());
            }
            else
            {
                graphics::GeometricRenderer::RenderViewportTexturedRectangle(
                    paint_context.GetDesktopWindowRect().GetMinimum() + GetBorders(),
                    paint_context.GetDesktopWindowRect().GetMaximum() - GetBorders());
            }

            _TextureInstance.UnBind(0);
        }
        else if (_Texture!=NULL)
        {
            graphics::Renderer::Get().EnableDepthTest(false);
            graphics::Renderer::Get().SetColor(
                IsEnabled()?basic::Color(1.0f, 1.0f, 1.0f, 1.0f):
                basic::Color(1.0f, 1.0f, 1.0f, 0.5f));
            graphics::Renderer::Get().EnableBlending(true);
            graphics::Renderer::Get().SetBlendingFactors(
                graphics::RENDER_STATE_BLENDING_FACTOR_SourceAlpha,
                graphics::RENDER_STATE_BLENDING_FACTOR_SourceAlphaInversed);

            _Texture->Bind(0);

            if (HasExtendedStyle(IMAGE_STYLE_NoBorders))
            {
                graphics::GeometricRenderer::RenderViewportTexturedRectangle(
                    paint_context.GetDesktopWindowRect().GetMinimum(),
                    paint_context.GetDesktopWindowRect().GetMaximum());
            }
            else
            {
                graphics::GeometricRenderer::RenderViewportTexturedRectangle(
                    paint_context.GetDesktopWindowRect().GetMinimum() + GetBorders(),
                    paint_context.GetDesktopWindowRect().GetMaximum() - GetBorders());
            }

            _Texture->UnBind(0);
        }
    }

    //-EVENTS-------------------------------------------------------------------------------------//

    COFFEE_BeginEventHandler(Image, Widget)
    COFFEE_EndEventHandler()

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Image::_UpdateClientArea()
    {
        Window::_UpdateClientArea();

        if (_Icon!=SKIN_ICON_None && GetSkin().IsAvailable())
            SetImage(GetSkin().GetIcon(_Icon));

        if (HasExtendedStyle(IMAGE_STYLE_AutoSize))
        {
            int32 height;
            graphics::Texture2D* texture = _Texture;
            if (texture==NULL && _TextureInstance.IsAvailable()
                && _TextureInstance.GetChunk().GetLOD(0).GetData().IsA<graphics::Texture2D>())
            {
                texture = static_cast<graphics::Texture2D*>(&_TextureInstance.GetChunk().GetLOD(0).GetData());
            }

            if (texture==NULL || !texture->IsAvailable()
                || texture->GetImage().GetWidth()==0
                || texture->GetImage().GetHeight()==0)
            {
                height = GetRect().Size.X;
            }
            else
            {
                height = GetRect().Size.X*texture->GetImage().GetHeight()
                    / texture->GetImage().GetWidth();
            }
        
            SetSize(basic::Vector2i(GetRect().Size.X, height));
        }
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Image::_GenerateTexture(const basic::Image& image)
    {
        basic::Image *thumbnail;

        _DestroyTexture();

        thumbnail = COFFEE_New(basic::Image);
        thumbnail->SetFrom(image, true);

        _Texture = COFFEE_New(graphics::Texture2D);
        _Texture->SetImage(*thumbnail);
        _Texture->EnableParameter(graphics::TEXTURE_PARAMETER_BilinearFiltering, true);
        _Texture->Initialize();
    }

    //--------------------------------------------------------------------------------------------//

    void Image::_DestroyTexture()
    {
        if(_Texture!=NULL)
        {
            _Texture->Finalize();
            COFFEE_Delete(_Texture);
            _Texture = NULL;
        }
    }

}
}
}
