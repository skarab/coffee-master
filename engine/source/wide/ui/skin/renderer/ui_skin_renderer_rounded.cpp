#include "wide/ui/skin/renderer/ui_skin_renderer_rounded.h"
#include "wide/ui/skin/renderer/ui_skin_renderer_rounded_opengl.hpp"
#include "system/graphics/renderer/graphics_renderer.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::SkinRendererRounded);
        COFFEE_Ancestor(ui::SkinRenderer);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SkinRendererRounded::SkinRendererRounded()
    {
    }

    //--------------------------------------------------------------------------------------------//

    SkinRendererRounded::~SkinRendererRounded()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void SkinRendererRounded::Line(const basic::Vector2i& point_a, const basic::Vector2i& point_b)
    {
        float ix = 5.0f;
        if (Absolute(point_a.X-point_b.X)<10)
            ix = 0.0f;
        float iy = 5.0f;
        if (Absolute(point_a.Y-point_b.Y)<10)
            iy = 0.0f;

        graphics::Renderer::Get().SetShadeModel(graphics::RENDER_STATE_SHADE_MODEL_Flat);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        
        glBegin(GL_LINES);
            glVertex3f((point_a.X+ix) / (graphics::Viewport::GetCurrent().GetFrameBufferSize().X / 2.0f) - 1.0f, - (point_a.Y+iy)
                / (graphics::Viewport::GetCurrent().GetFrameBufferSize().Y / 2.0f) + 1.0f, - 1.0f);
            glVertex3f((point_b.X-ix) / (graphics::Viewport::GetCurrent().GetFrameBufferSize().X / 2.0f) - 1.0f, - (point_b.Y-iy)
                / (graphics::Viewport::GetCurrent().GetFrameBufferSize().Y / 2.0f) + 1.0f, - 1.0f);
        glEnd();

        glMatrixMode(GL_MODELVIEW);
    }
    
    //--------------------------------------------------------------------------------------------//

    void SkinRendererRounded::Rectangle(const basic::Vector2i& point_a, const basic::Vector2i& point_b)
    {
        float ix = 5.0f;
        if (Absolute(point_a.X-point_b.X)<10)
            ix = 0.0f;
        float iy = 5.0f;
        if (Absolute(point_a.Y-point_b.Y)<10)
            iy = 0.0f;

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glTranslatef(0.0, 0.0, -1.0f);

        glBegin(GL_TRIANGLE_FAN);
        
        glVertex2f(
            (point_a.X+ix)/(graphics::Viewport::GetCurrent().GetFrameBufferSize().X/2.0f)-1.0f,
            -(point_a.Y)/(graphics::Viewport::GetCurrent().GetFrameBufferSize().Y/2.0f)+1.0f);
        glVertex2f(
            (point_b.X-ix)/(graphics::Viewport::GetCurrent().GetFrameBufferSize().X/2.0f)-1.0f,
            -(point_a.Y)/(graphics::Viewport::GetCurrent().GetFrameBufferSize().Y/2.0f)+1.0f);
        glVertex2f(
            (point_b.X)/(graphics::Viewport::GetCurrent().GetFrameBufferSize().X/2.0f)-1.0f,
            -(point_a.Y+iy)/(graphics::Viewport::GetCurrent().GetFrameBufferSize().Y/2.0f)+1.0f);
        glVertex2f(
            (point_b.X)/(graphics::Viewport::GetCurrent().GetFrameBufferSize().X/2.0f)-1.0f,
            -(point_b.Y-iy)/(graphics::Viewport::GetCurrent().GetFrameBufferSize().Y/2.0f)+1.0f);
        glVertex2f(
            (point_b.X-ix)/(graphics::Viewport::GetCurrent().GetFrameBufferSize().X/2.0f)-1.0f,
            -(point_b.Y)/(graphics::Viewport::GetCurrent().GetFrameBufferSize().Y/2.0f)+1.0f);
        glVertex2f(
            (point_a.X+ix)/(graphics::Viewport::GetCurrent().GetFrameBufferSize().X/2.0f)-1.0f,
            -(point_b.Y)/(graphics::Viewport::GetCurrent().GetFrameBufferSize().Y/2.0f)+1.0f);
        glVertex2f(
            (point_a.X)/(graphics::Viewport::GetCurrent().GetFrameBufferSize().X/2.0f)-1.0f,
            -(point_b.Y-iy)/(graphics::Viewport::GetCurrent().GetFrameBufferSize().Y/2.0f)+1.0f);
        glVertex2f(
            (point_a.X)/(graphics::Viewport::GetCurrent().GetFrameBufferSize().X/2.0f)-1.0f,
            -(point_a.Y+iy)/(graphics::Viewport::GetCurrent().GetFrameBufferSize().Y/2.0f)+1.0f);

        glEnd();

        glMatrixMode(GL_MODELVIEW);
    }

}
}
