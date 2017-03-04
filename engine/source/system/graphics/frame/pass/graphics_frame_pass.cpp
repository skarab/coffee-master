#include "system/graphics/frame/pass/graphics_frame_pass.h"
#include "system/graphics/renderer/graphics_renderer.h"
#include "system/graphics/component/graphics_components.h"
#include "system/graphics/viewport/graphics_viewport.h"
#include "system/graphics/device/graphics_device.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::FramePass);
        COFFEE_Attribute(basic::String, _Name, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(bool, _ItIsEnabled, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(graphics::FrameBuffer*, _FrameBuffer, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    FramePass::FramePass() :
        _ItIsEnabled(false),
        _FrameBuffer(NULL)
    {
    }

    //--------------------------------------------------------------------------------------------//

    FramePass::FramePass(basic::String name) :
        _Name(name),
        _ItIsEnabled(true),
        _FrameBuffer(NULL)
    {
        if (Device::IsInstantiated())
        {
            _FrameBuffer = COFFEE_New(FrameBuffer,
                Device::Get().GetFrameBufferWidth(),
                Device::Get().GetFrameBufferHeight());
        }
    }

    //--------------------------------------------------------------------------------------------//

    FramePass::~FramePass()
    {
        if (_FrameBuffer!=NULL)
            COFFEE_Delete(_FrameBuffer);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void FramePass::RenderQuad(Viewport& viewport, FrameBuffer* input_frame_buffer)
    {
        basic::Vector3 corner;
        real position_parameter(0.0f);

        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();

        const basic::Frustum3& frustum = static_cast<graphics::ComponentCameraPerspective&>(
            viewport.GetCamera().GetComponent()).GetFrustum();

        basic::Vector3 frustum_vectors[] = {
            frustum.GetCorner(basic::FRUSTUM3_CORNER_FarBottomLeft),
            frustum.GetCorner(basic::FRUSTUM3_CORNER_FarBottomRight),
            frustum.GetCorner(basic::FRUSTUM3_CORNER_FarTopRight),
            frustum.GetCorner(basic::FRUSTUM3_CORNER_FarTopLeft) };

        int32 width = (int32)(input_frame_buffer==NULL?viewport.GetFrameBufferSize().X:input_frame_buffer->GetWidth())-1;
        int32 height = (int32)(input_frame_buffer==NULL?viewport.GetFrameBufferSize().Y:input_frame_buffer->GetHeight())-1;

        glBegin(GL_QUADS);
            glColor3fv(&frustum_vectors[3].X);
            glMultiTexCoord2f(GL_TEXTURE0, 0.0f, (real)height);
            glVertex3i(-1,  1, -1);
            glColor3fv(&frustum_vectors[2].X);
            glMultiTexCoord2f(GL_TEXTURE0, (real)width, (real)height);
            glVertex3i( 1,  1, -1);
            glColor3fv(&frustum_vectors[1].X);
            glMultiTexCoord2f(GL_TEXTURE0, (real)width, 0.0f);
            glVertex3i( 1, -1, -1);
            glColor3fv(&frustum_vectors[0].X);
            glMultiTexCoord2f(GL_TEXTURE0, 0.0f, 0.0f);
            glVertex3i(-1, -1, -1);
        glEnd();

        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
        glPopMatrix();
    }

}
}
