#ifndef _COFFEE_GRAPHICS_GEOMETRIC_RENDERER_H_
#define _COFFEE_GRAPHICS_GEOMETRIC_RENDERER_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/renderer/graphics_renderer.h"

#define COFFEE_GraphicGeometricRendererDefaultCircleStep    20

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Geometric Renderer
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API GeometricRenderer
    {
    public:

        //--------------------------------------------------------------------------------------------//
        // 3D rendering utilities
        //--------------------------------------------------------------------------------------------//
      
        static inline void RenderPoint(const basic::Vector3& point)
        {
            glBegin(GL_POINTS);
                glVertex3fv(&point.X);
            glEnd();
        }

        //--------------------------------------------------------------------------------------------//

        static inline void RenderLine(const basic::Vector3& point_a, const basic::Vector3& point_b)
        {
            Renderer::Get().SetShadeModel(RENDER_STATE_SHADE_MODEL_Flat);

            glBegin(GL_LINES);
                glVertex3fv(&point_a.X);
                glVertex3fv(&point_b.X);
            glEnd();
        }

        //--------------------------------------------------------------------------------------------//

        static inline void RenderLine(const basic::Vector3& point_a, const basic::Vector3& point_b,
            const basic::Color& color_a, const basic::Color& color_b)
        {
            Renderer::Get().SetShadeModel(RENDER_STATE_SHADE_MODEL_Flat);

            glBegin(GL_LINES);
                glColor4fv(color_a.GetBuffer());
                glVertex3fv(&point_a.X);
                glColor4fv(color_b.GetBuffer());
                glVertex3fv(&point_b.X);
            glEnd();
        }

        //--------------------------------------------------------------------------------------------//

        static inline void RenderCircle(const basic::Vector3& center, real radius, uint32 smoothing)
        {
            uint32 vertex_index;
            real angle;

            Renderer::Get().SetShadeModel(RENDER_STATE_SHADE_MODEL_Flat);

            glBegin(GL_LINE_STRIP);
                for(vertex_index=0; vertex_index<smoothing ; ++vertex_index)
                {
                    angle = vertex_index*2.0f*Pi/smoothing;
                    basic::Vector3 vector(center+basic::Vector3(cos(angle), sin(angle), 0.0f)*radius);
                    glVertex3fv(&vector.X);
                }
                basic::Vector3 vector(center+basic::Vector3(radius, 0.0f, 0.0f));
                glVertex3fv(&vector.X);
            glEnd();
        }

        //--------------------------------------------------------------------------------------------//

        static inline void RenderTriangle(const basic::Vector3& point_a, const basic::Vector3& point_b,
            const basic::Vector3& point_c)
        {
            Renderer::Get().SetShadeModel(RENDER_STATE_SHADE_MODEL_Flat);

            glBegin(GL_TRIANGLES);
                glVertex3fv(&point_a.X);
                glVertex3fv(&point_b.X);
                glVertex3fv(&point_c.X);
            glEnd();
        }

        //--------------------------------------------------------------------------------------------//

        static inline void RenderQuad(const basic::Vector3& point_a, const basic::Vector3& point_b,
            const basic::Vector3& point_c, const basic::Vector3& point_d)
        {
            Renderer::Get().SetShadeModel(RENDER_STATE_SHADE_MODEL_Flat);

            glBegin(GL_QUADS);
                glVertex3fv(&point_a.X);
                glVertex3fv(&point_b.X);
                glVertex3fv(&point_c.X);
                glVertex3fv(&point_d.X);
            glEnd();
        }

        //--------------------------------------------------------------------------------------------//

        static inline void RenderArrow(const basic::Vector3& size, uint32 smoothing)
        {
            uint32 face_index;
            real angle = 0.0f;
            real angle_step;
            basic::Vector3 start_point(0.0f, 0.0f, 0.0f);
            basic::Vector3 end_point(0.0f, 0.0f, size.Z);
            basic::Vector3 first_point;
            basic::Vector3 second_point;

            Renderer::Get().SetShadeModel(RENDER_STATE_SHADE_MODEL_Flat);
            angle_step = 2.0f * Pi / smoothing;

            glBegin(GL_TRIANGLES);

            for(face_index = 0; face_index < smoothing ; face_index ++)
            {
                first_point.Set(cos(angle) * size.X, sin(angle) * size.Y, 0.0f);

                if(face_index == smoothing - 1)
                {
                    second_point.Set(1.0f * size.X, 0.0f, 0.0f);
                }
                else
                {
                    second_point.Set(cos(angle + angle_step) * size.X, sin(angle + angle_step) * size.Y, 0.0f);
                }

                glVertex3fv(&first_point.X);
                glVertex3fv(&second_point.X);
                glVertex3fv(&start_point.X);

                glVertex3fv(&first_point.X);
                glVertex3fv(&second_point.X);
                glVertex3fv(&end_point.X);

                angle += angle_step;
            }

            glEnd();
        }

        //--------------------------------------------------------------------------------------------//

        static inline void RenderSphere(const basic::Vector3& size, uint32 smoothing)
        {
            real da = (Pi / (real) smoothing);
            real db = (2.0f * Pi / (real) smoothing);
            uint32 i, j;
            real r0, r1;
            real x0, y0, z0;
            real x1, y1, z1;
            real x2, z2;
            real x3, z3;

            Renderer::Get().SetShadeModel(RENDER_STATE_SHADE_MODEL_Flat);

            glBegin(GL_QUADS);

            for(i = 0; i < smoothing ; i++)
            {
                r0 = sin (i * da);
                y0 = cos (i * da) * size.Y;
                r1 = sin ((i + 1) * da);
                y1 = cos ((i + 1) * da) * size.Y;

                for(j = 0; j < smoothing ; j++)
                {
                    x0 = r0 * sin(j * db) * size.X;
                    z0 = r0 * cos(j * db) * size.Z;
                    x1 = r0 * sin((j + 1) * db) * size.X;
                    z1 = r0 * cos((j + 1) * db) * size.Z;

                    x2 = r1 * sin(j * db) * size.X;
                    z2 = r1 * cos(j * db) * size.Z;
                    x3 = r1 * sin((j + 1) * db) * size.X;
                    z3 = r1 * cos((j + 1) * db) * size.Z;

                    glVertex3f(x2, y1, z2);
                    glVertex3f(x3, y1, z3);
                    glVertex3f(x1, y0, z1);
                    glVertex3f(x0, y0, z0);
                }
            }
            glEnd();
        }

        //--------------------------------------------------------------------------------------------//
        // Viewport utilities
        //--------------------------------------------------------------------------------------------//
      
        static inline void RenderViewportLine(const basic::Vector2i& point_a, const basic::Vector2i& point_b)
        {
            if (!graphics::Viewport::HasCurrent())
                return;
            
            basic::Vector2 a = graphics::Viewport::GetCurrent().ComputeViewportToGLViewportPoint(point_a);
            basic::Vector2 b = graphics::Viewport::GetCurrent().ComputeViewportToGLViewportPoint(point_b);
            
            Renderer::Get().SetShadeModel(RENDER_STATE_SHADE_MODEL_Flat);

            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadIdentity();
            
            glBegin(GL_LINES);
                glVertex2fv(&a.X);
                glVertex2fv(&b.X);
            glEnd();

            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
            glPopMatrix();
        }

        //--------------------------------------------------------------------------------------------//

        static inline void RenderViewportLine(const basic::Vector2i& point_a, const basic::Vector2i& point_b,
            const basic::Color& color_a, const basic::Color& color_b)
        {
            if (!graphics::Viewport::HasCurrent())
                return;
            
            basic::Vector2 a = graphics::Viewport::GetCurrent().ComputeViewportToGLViewportPoint(point_a);
            basic::Vector2 b = graphics::Viewport::GetCurrent().ComputeViewportToGLViewportPoint(point_b);
            
            Renderer::Get().SetShadeModel(RENDER_STATE_SHADE_MODEL_Smooth);

            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadIdentity();
            
            glBegin(GL_LINES);
            Renderer::Get().SetColor(color_a);
            glVertex2fv(&a.X);
            Renderer::Get().SetColor(color_b);
            glVertex2fv(&b.X);
            glEnd();

            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
            glPopMatrix();
        }

        //--------------------------------------------------------------------------------------------//

        static inline void RenderViewportRectangle(const basic::Vector2i& point_a, const basic::Vector2i& point_b)
        {
            if (!graphics::Viewport::HasCurrent())
                return;
            
            basic::Vector2 a = graphics::Viewport::GetCurrent().ComputeViewportToGLViewportPoint(point_a);
            basic::Vector2 b = graphics::Viewport::GetCurrent().ComputeViewportToGLViewportPoint(point_b);
            
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadIdentity();
            glTranslatef(0.0, 0.0, -1.0f);

            glRectfv(&a.X, &b.X);

            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
            glPopMatrix();
        }

        //--------------------------------------------------------------------------------------------//

        static inline void RenderViewportTexturedRectangle(const basic::Vector2i& point_a,
            const basic::Vector2i& point_b)
        {
            if (!graphics::Viewport::HasCurrent())
                return;

            basic::Vector2 a = graphics::Viewport::GetCurrent().ComputeViewportToGLViewportPoint(point_a);
            basic::Vector2 b = graphics::Viewport::GetCurrent().ComputeViewportToGLViewportPoint(point_b);
            
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadIdentity();
            glTranslatef(0.0, 0.0, -1.0f);

            glBegin(GL_QUADS);
                glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f); glVertex2f(a.X, a.Y);
                glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 0.0f); glVertex2f(b.X, a.Y);
                glMultiTexCoord2f(GL_TEXTURE0, 1.0f, 1.0f); glVertex2f(b.X, b.Y);
                glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 1.0f); glVertex2f(a.X, b.Y);
            glEnd();

            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
            glPopMatrix();
        }

        //--------------------------------------------------------------------------------------------//

        static inline void RenderViewportColoredRectangle(const basic::Vector2i& point_a,
            const basic::Vector2i& point_b,
            const basic::Color& color0, const basic::Color& color1,
            const basic::Color& color2, const basic::Color& color3)
        {
            if (!graphics::Viewport::HasCurrent())
                return;

            basic::Vector2 a = graphics::Viewport::GetCurrent().ComputeViewportToGLViewportPoint(point_a);
            basic::Vector2 b = graphics::Viewport::GetCurrent().ComputeViewportToGLViewportPoint(point_b);
            
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadIdentity();
            glTranslatef(0.0, 0.0, -1.0f);

            Renderer::Get().SetColor(basic::Color(0.12f, 0.12f, 0.12f, 0.12f));

            glBegin(GL_QUADS);
                glColor4fv(color0.GetBuffer()); glVertex2f(a.X, a.Y);
                glColor4fv(color1.GetBuffer()); glVertex2f(b.X, a.Y);
                glColor4fv(color2.GetBuffer()); glVertex2f(b.X, b.Y);
                glColor4fv(color3.GetBuffer()); glVertex2f(a.X, b.Y);
            glEnd();

            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
            glPopMatrix();
        }

        //--------------------------------------------------------------------------------------------//
        // Fullscreen utilities
        //--------------------------------------------------------------------------------------------//
      
        static inline void RenderFullScreenQuad()
        {
            glMatrixMode(GL_MODELVIEW);
            glPushMatrix();
            glLoadIdentity();
            glMatrixMode(GL_PROJECTION);
            glPushMatrix();
            glLoadIdentity();

            glBegin(GL_QUADS);
                glVertex3i(-1, -1, -1);
                glVertex3i( 1, -1, -1);
                glVertex3i( 1,  1, -1);
                glVertex3i(-1,  1, -1);
            glEnd();

            glPopMatrix();
            glMatrixMode(GL_MODELVIEW);
            glPopMatrix();
        }
    };

}
}
#endif
