#include "wide/ui/skin/renderer/ui_skin_renderer_basic.h"
#include "system/graphics/renderer/graphics_renderer.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(ui::SkinRendererBasic);
        COFFEE_Ancestor(ui::SkinRenderer);
    COFFEE_EndType();

namespace ui
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    SkinRendererBasic::SkinRendererBasic()
    {
    }

    //--------------------------------------------------------------------------------------------//

    SkinRendererBasic::~SkinRendererBasic()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void SkinRendererBasic::Line(const basic::Vector2i& point_a, const basic::Vector2i& point_b)
    {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        
        glBegin(GL_LINES);
            glVertex3f(point_a.X / (graphics::Viewport::GetCurrent().GetFrameBufferSize().X / 2.0f) - 1.0f, - point_a.Y
                / (graphics::Viewport::GetCurrent().GetFrameBufferSize().Y / 2.0f) + 1.0f, - 1.0f);
            glVertex3f(point_b.X / (graphics::Viewport::GetCurrent().GetFrameBufferSize().X / 2.0f) - 1.0f, - point_b.Y
                / (graphics::Viewport::GetCurrent().GetFrameBufferSize().Y / 2.0f) + 1.0f, - 1.0f);
        glEnd();

        glMatrixMode(GL_MODELVIEW);
    }
    
    //--------------------------------------------------------------------------------------------//

    void SkinRendererBasic::Rectangle(const basic::Vector2i& point_a, const basic::Vector2i& point_b)
    {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glTranslatef(0.0, 0.0, -1.0f);

        glRectf(point_a.X / (graphics::Viewport::GetCurrent().GetFrameBufferSize().X / 2.0f) - 1.0f,
            - point_a.Y / (graphics::Viewport::GetCurrent().GetFrameBufferSize().Y / 2.0f) + 1.0f,
            point_b.X / (graphics::Viewport::GetCurrent().GetFrameBufferSize().X / 2.0f) - 1.0f,
            - point_b.Y / (graphics::Viewport::GetCurrent().GetFrameBufferSize().Y / 2.0f) + 1.0f);

        glMatrixMode(GL_MODELVIEW);
    }

}
}
