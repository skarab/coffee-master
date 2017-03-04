#include "wide/edition/gizmo/edition_gizmo_mesh.h"

namespace coffee
{
namespace edition
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    GizmoMesh::GizmoMesh()
    {
    }

    //--------------------------------------------------------------------------------------------//

    GizmoMesh::~GizmoMesh()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void GizmoMesh::Render(graphics::Viewport& viewport, const basic::Matrix& local_to_world_matrix,
        basic::Vector3 size, basic::Vector3 arrow_size, const GIZMO_MODE& mode, const GIZMO_AXIS& selected_axis)
    {
        _LocalToWorldMatrix = local_to_world_matrix;
        _Size = size;
        _ArrowSize = arrow_size;
        _Mode = mode;
        _SelectedAxis = selected_axis;
        _ItIsPicking = false;

        graphics::Renderer::Get().EnableDepthTest(true);
        graphics::Renderer::Get().EnableDepthWriting(true);
        graphics::Renderer::Get().ClearDepth();
        graphics::Renderer::Get().SetFaceCullingMode(graphics::RENDER_STATE_FACE_CULLING_None);
        
        for (int32 i=(int32)GIZMO_AXIS_Count-1 ; i>=0 ; --i)
            _RenderAxis(viewport, (GIZMO_AXIS)i);
    }

    //--------------------------------------------------------------------------------------------//

    GIZMO_AXIS GizmoMesh::Pick(graphics::Viewport& viewport, const basic::Vector2i& point,
            const basic::Matrix& local_to_world_matrix,
            basic::Vector3 size, basic::Vector3 arrow_size, const GIZMO_MODE& mode)
    {
        _LocalToWorldMatrix = local_to_world_matrix;
        _Size = size;
        _ArrowSize = arrow_size;
        _Mode = mode;
        _SelectedAxis = GIZMO_AXIS_None;
        _ItIsPicking = true;

        graphics::FramePickerContext pick_context(point);
        pick_context.Begin(viewport);
        graphics::Renderer::Get().EnableDepthTest(false);
        graphics::Renderer::Get().SetFaceCullingMode(graphics::RENDER_STATE_FACE_CULLING_None);
        
        for (uint32 index=0 ; index<GIZMO_AXIS_Count ; ++index)
        {
            pick_context.Register(index);
            _RenderAxis(viewport, (GIZMO_AXIS)index);
        }

        pick_context.End(viewport);

        if (pick_context.GetHitCount()>0)
            return (GIZMO_AXIS)pick_context.GetHitIndex(0);

        return GIZMO_AXIS_None;
    }
    
    //-QUERIES--------------------------------------------------------------------------------//

    basic::Color GizmoMesh::GetAxisColor(const GIZMO_AXIS& axis, bool it_is_selected)
    {
        if (it_is_selected)
            return basic::Color(1.0f, 1.0f, 0.0f, 1.0f);

        switch (axis)
        {
            case GIZMO_AXIS_X:      return basic::Color(1.0f, 0.0f, 0.0f, 1.0f);
            case GIZMO_AXIS_Y:      return basic::Color(0.0f, 1.0f, 0.0f, 1.0f);
            case GIZMO_AXIS_Z:      return basic::Color(0.0f, 0.0f, 1.0f, 1.0f);
            case GIZMO_AXIS_Camera: return basic::Color(0.8f, 0.8f, 0.8f, 1.0f);
            case GIZMO_AXIS_Free:   return basic::Color(0.5f, 0.5f, 0.5f, 1.0f);
        }

        return basic::Color(1.0, 1.0, 1.0, 1.0);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void GizmoMesh::_RenderAxis(graphics::Viewport& viewport, const GIZMO_AXIS& axis)
    {
        _Axis = axis;

        glLineWidth(_ItIsPicking?6.0f:3.0f);

        switch (_Mode)
        {
            case GIZMO_MODE_Translate:  _RenderTranslation(viewport);   break;
            case GIZMO_MODE_Rotate:     _RenderRotation(viewport);      break;
            case GIZMO_MODE_Scale:      _RenderScale(viewport);         break;            
            default: break;
        };

        glLineWidth(1.0f);
    }

    //--------------------------------------------------------------------------------------------//

    void GizmoMesh::_RenderTranslation(graphics::Viewport& viewport)
    {
        basic::Matrix matrix;
        graphics::Renderer& renderer = graphics::Renderer::Get();
        
        switch(_Axis)
        {
            case GIZMO_AXIS_X:
            {
                renderer.SetLocalToWorldMatrix(_LocalToWorldMatrix);
                renderer.SetColor(GetAxisColor(GIZMO_AXIS_X, _SelectedAxis==_Axis));
                
                graphics::GeometricRenderer::RenderLine(
                    basic::Vector3(0.0f, 0.0f, 0.0f),
                    basic::Vector3(_Size.X, 0.0f, 0.0f));

                matrix.SetFromYRotation(basic::Angle(Pi/2.0f));
                matrix.Translate(basic::Vector3(_Size.X, 0.0f, 0.0f));
                matrix *= _LocalToWorldMatrix;

                renderer.SetLocalToWorldMatrix(matrix);
                graphics::GeometricRenderer::RenderArrow(_ArrowSize, 12);
            } break;

            case GIZMO_AXIS_Y:
            {
                renderer.SetLocalToWorldMatrix(_LocalToWorldMatrix);
                renderer.SetColor(GetAxisColor(_Axis,_SelectedAxis==_Axis));
                
                graphics::GeometricRenderer::RenderLine(basic::Vector3(0.0f, 0.0f, 0.0f),
                    basic::Vector3(0.0f, _Size.X, 0.0f));

                matrix.SetFromXRotation(basic::Angle(-Pi/2.0f));
                matrix.Translate(basic::Vector3(0.0f, _Size.X, 0.0f));
                matrix *= _LocalToWorldMatrix;

                renderer.SetLocalToWorldMatrix(matrix);
                graphics::GeometricRenderer::RenderArrow(_ArrowSize, 12);
            } break;

            case GIZMO_AXIS_Z:
            {
                renderer.SetLocalToWorldMatrix(_LocalToWorldMatrix);
                renderer.SetColor(GetAxisColor(_Axis,_SelectedAxis==_Axis));
                
                graphics::GeometricRenderer::RenderLine(basic::Vector3(0.0f, 0.0f, 0.0f),
                    basic::Vector3(0.0f, 0.0f, _Size.X));

                matrix.SetIdentity();
                matrix.Translate(basic::Vector3(0.0f, 0.0f, _Size.X));
                matrix *= _LocalToWorldMatrix;

                renderer.SetLocalToWorldMatrix(matrix);
                graphics::GeometricRenderer::RenderArrow(_ArrowSize, 12);
            } break;

            case GIZMO_AXIS_XY:
            {
                renderer.SetLocalToWorldMatrix(_LocalToWorldMatrix);
                renderer.SetColor(GetAxisColor(GIZMO_AXIS_X,_SelectedAxis==_Axis));
                
                graphics::GeometricRenderer::RenderLine(basic::Vector3(_Size.X * 0.5f, 0.0f, 0.0f),
                    basic::Vector3(_Size.X * 0.5f, _Size.X * 0.5f, 0.0f));
                graphics::GeometricRenderer::RenderLine(basic::Vector3(0.0f, _Size.X * 0.5f, 0.0f),
                    basic::Vector3(_Size.X * 0.5f, _Size.X * 0.5f, 0.0f));
            
                if (_ItIsPicking || _SelectedAxis==_Axis)
                {
                    renderer.SetColor(GetAxisColor(_Axis, true));
                    
                    graphics::GeometricRenderer::RenderQuad(
                        basic::Vector3(_Size.X * 0.5f, 0.0f, 0.0f),
                        basic::Vector3(_Size.X * 0.5f, _Size.X * 0.5f, 0.0f),
                        basic::Vector3(0.0f, _Size.X * 0.5f, 0.0f),
                        basic::Vector3(0.0f, 0.0f, 0.0f));
                }
            } break;

            case GIZMO_AXIS_XZ:
            {
                renderer.SetLocalToWorldMatrix(_LocalToWorldMatrix);
                renderer.SetColor(GetAxisColor(GIZMO_AXIS_X,_SelectedAxis==_Axis));
                
                graphics::GeometricRenderer::RenderLine(basic::Vector3(_Size.X * 0.5f, 0.0f, 0.0f),
                    basic::Vector3(_Size.X * 0.5f, 0.0f, _Size.X * 0.5f));
                graphics::GeometricRenderer::RenderLine(basic::Vector3(0.0f, 0.0f, _Size.X * 0.5f),
                    basic::Vector3(_Size.X * 0.5f, 0.0f, _Size.X * 0.5f));
            
                if (_ItIsPicking ||_SelectedAxis==_Axis)
                {
                    renderer.SetColor(GetAxisColor(GIZMO_AXIS_XZ, true));

                    graphics::GeometricRenderer::RenderQuad(
                        basic::Vector3(_Size.X * 0.5f, 0.0f, 0.0f),
                        basic::Vector3(_Size.X * 0.5f, 0.0f, _Size.X * 0.5f),
                        basic::Vector3(0.0f, 0.0f, _Size.X * 0.5f),
                        basic::Vector3(0.0f, 0.0f, 0.0f));
                }
            } break;

            case GIZMO_AXIS_YZ:
            {
                renderer.SetLocalToWorldMatrix(_LocalToWorldMatrix);
                renderer.SetColor(GetAxisColor(GIZMO_AXIS_Y,_SelectedAxis==_Axis));
                
                graphics::GeometricRenderer::RenderLine(basic::Vector3(0.0f, _Size.X * 0.5f, 0.0f),
                    basic::Vector3(0.0f, _Size.X * 0.5f, _Size.X * 0.5f));
                graphics::GeometricRenderer::RenderLine(basic::Vector3(0.0f, 0.0f, _Size.X * 0.5f),
                    basic::Vector3(0.0f, _Size.X * 0.5f, _Size.X * 0.5f));
            
                if (_ItIsPicking ||_SelectedAxis==_Axis)
                {
                    renderer.SetColor(GetAxisColor(_Axis, true));

                    graphics::GeometricRenderer::RenderQuad(
                        basic::Vector3(0.0f, _Size.X * 0.5f, 0.0f),
                        basic::Vector3(0.0f, _Size.X * 0.5f, _Size.X * 0.5f),
                        basic::Vector3(0.0f, 0.0f, _Size.X * 0.5f),
                        basic::Vector3(0.0f, 0.0f, 0.0f));
                }
            } break;
        }
    }

    //--------------------------------------------------------------------------------------------//

    void GizmoMesh::_RenderRotation(graphics::Viewport& viewport)
    {
        basic::Matrix matrix, transform_matrix;
        graphics::Renderer& renderer = graphics::Renderer::Get();
        
        switch (_Axis)
        {
            case GIZMO_AXIS_X:
            {
                matrix.SetFromYRotation(basic::Angle(Pi/2.0f));
                matrix *= _LocalToWorldMatrix;
                renderer.SetLocalToWorldMatrix(matrix);
                renderer.SetColor(GetAxisColor(_Axis,_SelectedAxis==_Axis));
                graphics::GeometricRenderer::RenderCircle(basic::Vector3(0.0f, 0.0f, 0.0f), _Size.X, 30);
            } break;

            case GIZMO_AXIS_Y:
            {
                matrix.SetFromXRotation(basic::Angle(Pi/2.0f));
                matrix *= _LocalToWorldMatrix;
                renderer.SetLocalToWorldMatrix(matrix);
                renderer.SetColor(GetAxisColor(_Axis,_SelectedAxis==_Axis));
                graphics::GeometricRenderer::RenderCircle(basic::Vector3(0.0f, 0.0f, 0.0f), _Size.X, 30);
            } break;

            case GIZMO_AXIS_Z:
            {
                renderer.SetLocalToWorldMatrix(_LocalToWorldMatrix);
                renderer.SetColor(GetAxisColor(_Axis,_SelectedAxis==_Axis));
                graphics::GeometricRenderer::RenderCircle(basic::Vector3(0.0f, 0.0f, 0.0f), _Size.X, 30);
            } break;

            case GIZMO_AXIS_Camera:
            {
                basic::Vector3 camera_vector;
                basic::Quaternion rotation;
                
                camera_vector = viewport.GetCamera().GetComponent().GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World).GetTranslation() - _LocalToWorldMatrix.GetTranslation();
                if (camera_vector.IsZero())
                    return;

                camera_vector.Normalize();
                rotation.SetFromZAxis(camera_vector);
                matrix = rotation;
                matrix.Translate(_LocalToWorldMatrix.GetTranslation());

                glLineWidth(24.0f);
                renderer.SetLocalToWorldMatrix(matrix);
                renderer.SetColor(GetAxisColor(_Axis,_SelectedAxis==_Axis));
                graphics::GeometricRenderer::RenderCircle(basic::Vector3(0.0f, 0.0f, 0.0f), _Size.X*1.02f, 30);
            } break;

            case GIZMO_AXIS_Free:
            {
                renderer.SetColor(GetAxisColor(_Axis, _SelectedAxis==_Axis));
                renderer.SetFaceCullingMode(graphics::RENDER_STATE_FACE_CULLING_Back);
                renderer.SetLocalToWorldMatrix(_LocalToWorldMatrix);
                graphics::GeometricRenderer::RenderSphere(_Size * 0.1f, 8);
                
                if (!_ItIsPicking)
                {
                    basic::Color color = GetAxisColor(_Axis, _SelectedAxis==_Axis);
                    color.A = 0.7f;
                    renderer.SetColor(color);
                    graphics::GeometricRenderer::RenderSphere(_Size * 0.99f, 12);
                }

                renderer.SetFaceCullingMode(graphics::RENDER_STATE_FACE_CULLING_None);
            }
        }
    }

    //--------------------------------------------------------------------------------------------//

    void GizmoMesh::_RenderScale(graphics::Viewport& viewport)
    {
        basic::Matrix matrix, transform_matrix;
        graphics::Renderer& renderer = graphics::Renderer::Get();
        real center = 0.7f / sqrtf(2.0f);
 
        switch (_Axis)
        {
            case GIZMO_AXIS_X:
            {
                renderer.SetLocalToWorldMatrix(_LocalToWorldMatrix);
                renderer.SetColor(GetAxisColor(_Axis,_SelectedAxis==_Axis));
                
                graphics::GeometricRenderer::RenderLine(basic::Vector3(0.0f, 0.0f, 0.0f),
                    basic::Vector3(_Size.X, 0.0f, 0.0f));

                matrix.SetFromYRotation(basic::Angle(Pi/2.0f));
                matrix.Translate(basic::Vector3(_Size.X, 0.0f, 0.0f));
                matrix *= _LocalToWorldMatrix;

                renderer.SetLocalToWorldMatrix(matrix);
                graphics::GeometricRenderer::RenderArrow(_ArrowSize, 12);
            } break;

            case GIZMO_AXIS_Y:
            {
                renderer.SetLocalToWorldMatrix(_LocalToWorldMatrix);
                renderer.SetColor(GetAxisColor(_Axis,_SelectedAxis==_Axis));
                
                graphics::GeometricRenderer::RenderLine(basic::Vector3(0.0f, 0.0f, 0.0f),
                    basic::Vector3(0.0f, _Size.Y, 0.0f));

                matrix.SetFromXRotation(basic::Angle(-Pi/2.0f));
                matrix.Translate(basic::Vector3(0.0f, _Size.Y, 0.0f));
                matrix *= _LocalToWorldMatrix;

                renderer.SetLocalToWorldMatrix(matrix);
                graphics::GeometricRenderer::RenderArrow(_ArrowSize, 12);
            } break;

            case GIZMO_AXIS_Z:
            {
                renderer.SetLocalToWorldMatrix(_LocalToWorldMatrix);
                renderer.SetColor(GetAxisColor(_Axis,_SelectedAxis==_Axis));
                
                graphics::GeometricRenderer::RenderLine(basic::Vector3(0.0f, 0.0f, 0.0f),
                    basic::Vector3(0.0f, 0.0f, _Size.Z));
                
                matrix.SetFromYRotation(basic::Angle(-Pi));
                matrix.Translate(basic::Vector3(0.0f, 0.0f, _Size.Z));
                matrix *= _LocalToWorldMatrix;

                renderer.SetLocalToWorldMatrix(matrix);
                graphics::GeometricRenderer::RenderArrow(_ArrowSize, 12);
            } break;

            case GIZMO_AXIS_XY:
            {
                renderer.SetLocalToWorldMatrix(_LocalToWorldMatrix);
                renderer.SetColor(GetAxisColor(GIZMO_AXIS_X,_SelectedAxis==_Axis));
                graphics::GeometricRenderer::RenderLine(basic::Vector3(_Size.X * 0.7f, 0.0f, 0.0f),
                    basic::Vector3(_Size.X * 0.7f * center, _Size.Y * 0.7f * center, 0.0f));
                renderer.SetColor(GetAxisColor(GIZMO_AXIS_Y,_SelectedAxis==_Axis));
                graphics::GeometricRenderer::RenderLine(basic::Vector3(0.0f, _Size.Y * 0.7f, 0.0f),
                    basic::Vector3(_Size.X * 0.7f * center, _Size.Y * 0.7f * center, 0.0f));
            
                if (_ItIsPicking ||_SelectedAxis==_Axis)
                {
                    renderer.SetColor(GetAxisColor(_Axis, true));

                    graphics::GeometricRenderer::RenderQuad(
                        basic::Vector3(_Size.X * 0.7f, 0.0f, 0.0f),
                        basic::Vector3(0.0f, _Size.Y * 0.7f, 0.0f),
                        basic::Vector3(0.0f, _Size.Y * 0.5f, 0.0f),
                        basic::Vector3(_Size.X * 0.5f, 0.0f, 0.0f));
                }
            } break;

            case GIZMO_AXIS_XZ:
            {
                renderer.SetLocalToWorldMatrix(_LocalToWorldMatrix);
                renderer.SetColor(GetAxisColor(GIZMO_AXIS_X,_SelectedAxis==_Axis));
                graphics::GeometricRenderer::RenderLine(basic::Vector3(_Size.X * 0.7f, 0.0f, 0.0f),
                    basic::Vector3(_Size.X * 0.7f * center, 0.0f, _Size.Z * 0.7f * center ));
                renderer.SetColor(GetAxisColor(GIZMO_AXIS_Z,_SelectedAxis==_Axis));
                graphics::GeometricRenderer::RenderLine(basic::Vector3(0.0f, 0.0f, _Size.Z * 0.7f),
                    basic::Vector3(_Size.X * 0.7f * center, 0.0f, _Size.Z * 0.7f * center));
                
                if (_ItIsPicking ||_SelectedAxis==_Axis)
                {
                    renderer.SetColor(GetAxisColor(_Axis, true));

                    graphics::GeometricRenderer::RenderQuad(
                        basic::Vector3(_Size.X * 0.7f, 0.0f, 0.0f),
                        basic::Vector3(0.0f, 0.0f, _Size.Z * 0.7f),
                        basic::Vector3(0.0f, 0.0f, _Size.Z * 0.5f),
                        basic::Vector3(_Size.X * 0.5f, 0.0f, 0.0f));
                }
            } break;

            case GIZMO_AXIS_YZ:
            {
                renderer.SetLocalToWorldMatrix(_LocalToWorldMatrix);
                renderer.SetColor(GetAxisColor(GIZMO_AXIS_Y,_SelectedAxis==_Axis));
                graphics::GeometricRenderer::RenderLine(basic::Vector3(0.0f, _Size.Y * 0.7f, 0.0f),
                    basic::Vector3(0.0f, _Size.Y * 0.7f * center, _Size.Z * 0.7f * center));
                renderer.SetColor(GetAxisColor(GIZMO_AXIS_Z,_SelectedAxis==_Axis));
                graphics::GeometricRenderer::RenderLine(basic::Vector3(0.0f, 0.0f, _Size.Z * 0.7f),
                    basic::Vector3(0.0f, _Size.Y * 0.7f * center, _Size.Z * 0.7f * center));

                if (_ItIsPicking ||_SelectedAxis==_Axis)
                {
                    renderer.SetColor(GetAxisColor(_Axis, true));

                    graphics::GeometricRenderer::RenderQuad(
                        basic::Vector3(0.0f, _Size.Y * 0.7f, 0.0f),
                        basic::Vector3(0.0f, 0.0f, _Size.Z * 0.7f),
                        basic::Vector3(0.0f, 0.0f, _Size.Z * 0.5f),
                        basic::Vector3(0.0f, _Size.Y * 0.5f, 0.0f));
                }
            } break;

            case GIZMO_AXIS_XYZ:
            {
                renderer.SetLocalToWorldMatrix(_LocalToWorldMatrix);
                
                renderer.SetColor(GetAxisColor(GIZMO_AXIS_X,_SelectedAxis==_Axis ||_SelectedAxis==GIZMO_AXIS_XZ));
                graphics::GeometricRenderer::RenderLine(basic::Vector3(_Size.X * 0.5f, 0.0f, 0.0f),
                    basic::Vector3(_Size.X * 0.5f * center, 0.0f, _Size.Z * 0.5f * center ));
                renderer.SetColor(GetAxisColor(GIZMO_AXIS_X,_SelectedAxis==_Axis ||_SelectedAxis==GIZMO_AXIS_XY));
                graphics::GeometricRenderer::RenderLine(basic::Vector3(_Size.X * 0.5f, 0.0f, 0.0f),
                    basic::Vector3(_Size.X * 0.5f * center, _Size.Y * 0.5f * center, 0.0f));

                renderer.SetColor(GetAxisColor(GIZMO_AXIS_Y,_SelectedAxis==_Axis ||_SelectedAxis==GIZMO_AXIS_XY));
                graphics::GeometricRenderer::RenderLine(basic::Vector3(0.0f, _Size.Y * 0.5f, 0.0f),
                    basic::Vector3(_Size.X * 0.5f * center, _Size.Y * 0.5f * center, 0.0f));
                renderer.SetColor(GetAxisColor(GIZMO_AXIS_Y,_SelectedAxis==_Axis ||_SelectedAxis==GIZMO_AXIS_YZ));
                graphics::GeometricRenderer::RenderLine(basic::Vector3(0.0f, _Size.Y * 0.5f, 0.0f),
                    basic::Vector3(0.0f, _Size.Y * 0.5f * center, _Size.Z * 0.5f * center));

                renderer.SetColor(GetAxisColor(GIZMO_AXIS_Z,_SelectedAxis==_Axis ||_SelectedAxis==GIZMO_AXIS_XZ));
                graphics::GeometricRenderer::RenderLine(basic::Vector3(0.0f, 0.0f, _Size.Z * 0.5f),
                    basic::Vector3(_Size.X * 0.5f * center, 0.0f, _Size.Z * 0.5f * center));
                renderer.SetColor(GetAxisColor(GIZMO_AXIS_Z,_SelectedAxis==_Axis ||_SelectedAxis==GIZMO_AXIS_YZ));
                graphics::GeometricRenderer::RenderLine(basic::Vector3(0.0f, 0.0f, _Size.Z * 0.5f),
                    basic::Vector3(0.0f, _Size.Y * 0.5f * center, _Size.Z * 0.5f * center));
            
                if (_ItIsPicking ||_SelectedAxis==_Axis)
                {
                    renderer.SetColor(GetAxisColor(_Axis, true));

                    graphics::GeometricRenderer::RenderTriangle(
                        basic::Vector3(0.0f, 0.0f, 0.0f),
                        basic::Vector3(_Size.X * 0.5f, 0.0f, 0.0f),
                        basic::Vector3(0.0f, _Size.Y * 0.5f, 0.0f));

                    graphics::GeometricRenderer::RenderTriangle(
                        basic::Vector3(0.0f, 0.0f, 0.0f),
                        basic::Vector3(_Size.X * 0.5f, 0.0f, 0.0f),
                        basic::Vector3(0.0f, 0.0f, _Size.Z * 0.5f));

                    graphics::GeometricRenderer::RenderTriangle(
                        basic::Vector3(0.0f, 0.0f, 0.0f),
                        basic::Vector3(0.0f, _Size.Y * 0.5f, 0.0f),
                        basic::Vector3(0.0f, 0.0f, _Size.Z * 0.5f));
                }
            } break;
        }
    }

}
}
