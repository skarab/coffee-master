#include "wide/edition/gizmo/edition_gizmo.h"
#include "wide/edition/gizmo/edition_gizmo_controller.h"

namespace coffee
{
namespace edition
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Gizmo::Gizmo() :
        _Mode(GIZMO_MODE_Select),
        _Axis(GIZMO_AXIS_None),
        _Scale(1.0f),
        _ItIsEnabled(false),
        _ViewScale(1.0f),
        _TransformScale(1.0f),
        _ItIsActive(false)
    {
        _UpdateMatrices();
    }

    //--------------------------------------------------------------------------------------------//

    Gizmo::~Gizmo()
    {
    }

    //-ACCESSORS------------------------------------------------------------------------------//

    void Gizmo::SetMode(GIZMO_MODE mode)
    {
        _Mode = mode;
        _Axis = GIZMO_AXIS_None;
    }

    //--------------------------------------------------------------------------------------------//

    GIZMO_MODE Gizmo::GetMode() const
    {
        return _Mode;
    }
    
    //--------------------------------------------------------------------------------------------//

    void Gizmo::SetIsEnabled(bool it_is_enabled)
    {
        _ItIsEnabled = it_is_enabled;
        _ItIsActive = false;
    }
    
    //--------------------------------------------------------------------------------------------//
    
    bool Gizmo::IsEnabled() const
    {
        return _ItIsEnabled;
    }

    //--------------------------------------------------------------------------------------------//
    
    void Gizmo::SetPosition(const basic::Vector3& translation, const basic::Quaternion& rotation,
        const basic::Vector3& scale)
    {
        _Translation = translation;
        _Rotation = rotation;
        _Scale = scale;
        _UpdateMatrices();
    }
        
    //-OPERATIONS---------------------------------------------------------------------------------//
        
    void Gizmo::Render()
    {
        if (_ItIsEnabled)
        {
            basic::Vector3 size(1.6f);
            basic::Vector3 arrow_size(0.1f, 0.1f, 0.4f);

            if (!_ItIsActive)
            {
                _ViewScale = _GetViewportScale();
            }

            size *= _TransformScale * _ViewScale;
            arrow_size *= _TransformScale * _ViewScale;

            _Mesh.Render(_Controller->GetParentViewport(), _UnscaledMatrix, size*0.1f, arrow_size*0.1f, _Mode, _Axis);
        }
    }

    //--------------------------------------------------------------------------------------------//

    GIZMO_AXIS Gizmo::Pick(const basic::Vector2i& point)
    {
        basic::Vector3 size(1.6f);
        basic::Vector3 arrow_size(0.1f, 0.1f, 0.4f);

        if (!_ItIsActive)
        {
            _ViewScale = _GetViewportScale();
        }

        size *= _TransformScale * _ViewScale;
        arrow_size *= _TransformScale * _ViewScale;

        return _Mesh.Pick(_Controller->GetParentViewport(), point, _UnscaledMatrix, size*0.1f, arrow_size*0.1f, _Mode);
    }

    //-HANDLERS-----------------------------------------------------------------------------------//
        
    bool Gizmo::OnKeyPressed(const input::KEY& key_code, bool it_is_repeating)
    {
        if (key_code==input::KEY_Escape && IsEnabled() && _ItIsActive)
        {
            _ItIsActive = false;
            _Translation = _StartTranslation;
            _Rotation = _StartRotation;
            _Scale = _StartScale;
            _TransformScale = _Scale;
            _UpdateMatrices();
            _Controller->OnCancelTransform();
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Gizmo::OnMouseMove(const basic::Vector2i& point)
    {
        if (IsEnabled())
        {
            if (_ItIsActive)
            {
                basic::Vector2i cursor_position(point);
                basic::Vector2 cursor_movement(
                    (float)(cursor_position.X-_CursorPosition.X),
                    (float)(cursor_position.Y-_CursorPosition.Y));
                _CursorPosition = cursor_position;
                cursor_movement *= 0.3f * input::Module::Get().GetTimeStep().GetSecondCount();
                _Transform += cursor_movement;
                _Translation = _StartTranslation;
                _Rotation = _StartRotation;
                _Scale = _StartScale;
                _TransformScale = 1.0f;

                switch (_Mode)
                {
                    case GIZMO_MODE_Translate:  _ApplyTranslation();    break;
                    case GIZMO_MODE_Rotate:     _ApplyRotation();       break;
                    case GIZMO_MODE_Scale:      _ApplyScale();          break;
                }
                return true;
            }
            else
            {
                _Axis = Pick(point);
            }            
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Gizmo::OnMouseLeftButtonPressed(const basic::Vector2i& point)
    {
        if (IsEnabled())
        {
            if (_Axis!=GIZMO_AXIS_None)
            {
                _ItIsActive = true;
                _StartTranslation = _Translation;
                _StartRotation = _Rotation;
                _StartScale = _Scale;
                _CursorPosition = point;
                _Transform = 0;
                
                _Controller->OnQueryTransform();
            
                if (_Mode==GIZMO_MODE_Scale)
                    _TransformScale = 1.0f;
                if (_Mode==GIZMO_MODE_Translate || _Mode==GIZMO_MODE_Scale)
                    _ComputeTranslationAxis();
                if (_Mode==GIZMO_MODE_Rotate)
                    _ComputeRotationAxis();

                _ComputePlaneAxis(_TransformPlane );
                _ComputePlane(_StartTransform, _TransformPlane);
                return true;
            }
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    bool Gizmo::OnMouseLeftButtonReleased(const basic::Vector2i& point)
    {
        if (IsEnabled() && _ItIsActive)
        {
            _ItIsActive = false;
            _TransformScale = 1.0f;
            _Controller->OnAcceptTransform();
            return true;
        }
        return false;
    }
    
    //-QUERIES------------------------------------------------------------------------------------//
        
    real Gizmo::_GetViewportScale() const
    {
        basic::Vector4 position;
        position = _Translation * _Controller->GetParentViewport().GetCamera().GetComponent().GetNode().GetTransform().GetMatrix(scene::TRS_World, scene::TRS_Local);
        position *= _Controller->GetParentViewport().GetCamera().GetComponent().GetLocalToViewportMatrix();
        return position.W*1.5f;
    }
        
    //-OPERATIONS---------------------------------------------------------------------------------//
        
    void Gizmo::_UpdateMatrices()
    {
        _UnscaledMatrix.Set(_Translation, _Rotation);
        _Matrix = _UnscaledMatrix;
        _Matrix.Scale(_Scale);
    }

    //--------------------------------------------------------------------------------------------//

    void Gizmo::_ApplyTranslation()
    {
        basic::Vector3 translation;        
        if (!_ComputeTranslation(translation))
        {
            _ComputePlane(translation, _TransformPlane);
            translation -= _StartTransform;
        }
            
        _Translation += translation;
        _UpdateMatrices();
        _Controller->OnTranslate(translation);
    }

    //--------------------------------------------------------------------------------------------//

    void Gizmo::_ApplyRotation()
    {
        basic::Vector3 transform;
        basic::Quaternion rotation;
        if (_ComputeRotation(transform))
        {
            basic::Vector3 axis(transform);
            if (axis.IsZero())
                return;
            axis.Normalize();           
            rotation.SetFromAxisAndAngle(axis, transform.GetNorm());
        }
        else
        {
            _ComputePlane(transform, _TransformPlane);
        
            if (_Axis==GIZMO_AXIS_Free)
            {
                rotation = basic::Euler(transform.X, transform.Y, transform.Z);
            }
            else
            {
                basic::Quaternion world_to_local_rotation(~_Rotation);
                transform = (_TransformPlane.GetNormal()+basic::Vector3(0.0001f, 0.0f, 0.0f))
                    *_TransformAxis.GetDotProduct(_Transform)*_ViewScale;
                rotation.SetFromAxisAndAngle(
                    _TransformPlane.GetNormal()*world_to_local_rotation, transform.GetNorm());
            }
        }

        _Rotation *= rotation;
        _UpdateMatrices();
        _Controller->OnRotate(rotation);
    }

    //--------------------------------------------------------------------------------------------//

    void Gizmo::_ApplyScale()
    {
        basic::Vector3 scale;        
        if (!_ComputeTranslation(scale))
        {
            _ComputePlane(scale, _TransformPlane);
            scale -= _StartTransform;
        }

        basic::Matrix matrix;
        matrix.SetInversed(_StartRotation);
        scale *= matrix;

        if (_Axis==GIZMO_AXIS_XYZ)
            scale = (scale.GetMinimum()+scale.GetMaximum())/2.0f;
            
        _Scale += scale;

        if (_Scale.X<1.0f) _Scale.X = -1.0f/(_Scale.X-2.0f);
        if (_Scale.Y<1.0f) _Scale.Y = -1.0f/(_Scale.Y-2.0f);
        if (_Scale.Z<1.0f) _Scale.Z = -1.0f/(_Scale.Z-2.0f);

        _TransformScale += scale;

        if (_TransformScale.X<1.0f) _TransformScale.X = -1.0f/(_TransformScale.X-2.0f);
        if (_TransformScale.Y<1.0f) _TransformScale.Y = -1.0f/(_TransformScale.Y-2.0f);
        if (_TransformScale.Z<1.0f) _TransformScale.Z = -1.0f/(_TransformScale.Z-2.0f);

        _UpdateMatrices();
        _Controller->OnScale(_Scale);
    }

    //--------------------------------------------------------------------------------------------//

    bool Gizmo::_ComputeTranslationAxis()
    {
        basic::Vector3 axis;
        switch (_Axis)
        {
            case GIZMO_AXIS_X:    axis = basic::Vector3::XAxis*_Rotation;    break;
            case GIZMO_AXIS_Y:    axis = basic::Vector3::YAxis*_Rotation;    break;
            case GIZMO_AXIS_Z:    axis = basic::Vector3::ZAxis*_Rotation;    break;
            default: return false;
        }

        basic::Vector3 transform_axis;
        transform_axis = axis * _Controller->GetParentViewport().GetCamera().GetComponent().GetNode().GetTransform().GetMatrix(scene::TRS_World, scene::TRS_Local).GetRotation();
        _TransformAxis.Set(transform_axis.X, transform_axis.Y);
        
        if (_TransformAxis.IsZero())
            return false;

        _TransformAxis.Normalize();
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Gizmo::_ComputeTranslation(basic::Vector3& vector)
    {
        switch (_Axis)
        {
            case GIZMO_AXIS_X: vector = _UnscaledMatrix.GetXAxis()*_TransformAxis.GetDotProduct(_Transform)*_ViewScale;     break;
            case GIZMO_AXIS_Y: vector = _UnscaledMatrix.GetYAxis()*_TransformAxis.GetDotProduct(_Transform)*_ViewScale;     vector.Y = -vector.Y;   break;
            case GIZMO_AXIS_Z: vector = _UnscaledMatrix.GetZAxis()*_TransformAxis.GetDotProduct(_Transform)*_ViewScale;     break;
            default: return false;
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Gizmo::_ComputeRotationAxis()
    {
        basic::Vector3 axis;
        switch (_Axis)
        {
            case GIZMO_AXIS_X: axis = basic::Vector3::XAxis*_Rotation;    break;
            case GIZMO_AXIS_Y: axis = basic::Vector3::YAxis*_Rotation;    break;
            case GIZMO_AXIS_Z: axis = basic::Vector3::ZAxis*_Rotation;    break;
            case GIZMO_AXIS_Camera: axis = _TransformPlane.GetNormal()+basic::Vector3(0.0001f, 0.0f, 0.0f);    break;
            default: return false;
        }
        axis.Normalize();

        basic::Plane plane;
        plane.Set(_Translation, axis);
        
        basic::Vector3 radial_axis;
        radial_axis = _Controller->GetParentViewport().GetCamera().GetComponent().GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World).GetZAxis();
        
        basic::Line3 line;
        line.Set(
            _Controller->GetParentViewport().GetCamera().GetComponent().GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World).GetTranslation(),
            radial_axis);

        if (!IsRoughlyEqual(axis.GetDotProduct(-radial_axis), 0.0f, 0.1f))
        {
            basic::Vector3 intersection_point;
            if (plane.FindLineIntersection(intersection_point, line))
            {
                radial_axis = intersection_point - _Translation;
                radial_axis.Normalize();
            }
        }

        basic::Vector3 cursor_axis;
        basic::Vector3 transform_axis;
        
        cursor_axis = axis.GetCrossProduct(radial_axis);
        if (cursor_axis.IsZero())
            return false;
        cursor_axis.Normalize();

        transform_axis = cursor_axis
            * _Controller->GetParentViewport().GetCamera().GetComponent().GetNode().GetTransform().GetMatrix(scene::TRS_World, scene::TRS_Local).GetRotation();

        _TransformAxis.Set(transform_axis.X, transform_axis.Y);

        if (_TransformAxis.IsZero())
            return false;

        _TransformAxis.Normalize();
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Gizmo::_ComputeRotation(basic::Vector3& vector)
    {
        switch (_Axis )
        {
            case GIZMO_AXIS_X: vector = basic::Vector3::XAxis*_TransformAxis.GetDotProduct(_Transform)*_ViewScale; break;
            case GIZMO_AXIS_Y: vector = basic::Vector3::YAxis*_TransformAxis.GetDotProduct(_Transform)*_ViewScale; break;
            case GIZMO_AXIS_Z: vector = basic::Vector3::ZAxis*_TransformAxis.GetDotProduct(_Transform)*_ViewScale; break;
            default: return false;
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    void Gizmo::_ComputePlaneAxis(basic::Plane& plane)
    {
        basic::Vector3 plane_normal;
        switch (_Axis)
        {
            case GIZMO_AXIS_X:
            case GIZMO_AXIS_YZ:
                plane_normal = _UnscaledMatrix.GetXAxis();
                break;
            case GIZMO_AXIS_Y:
            case GIZMO_AXIS_XZ:
                plane_normal = _UnscaledMatrix.GetYAxis();
                break;
            case GIZMO_AXIS_Z:
            case GIZMO_AXIS_XY:
                plane_normal = _UnscaledMatrix.GetZAxis();
                break;
            case GIZMO_AXIS_Camera:
            case GIZMO_AXIS_Free:
            case GIZMO_AXIS_XYZ:
                plane_normal = -_Controller->GetParentViewport().GetCamera().GetComponent().GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World).GetZAxis();
                break;
        }

        plane.Set(_Translation, plane_normal);
    }

    //--------------------------------------------------------------------------------------------//

    basic::Line3 Gizmo::_ComputeRayFromCursor(const basic::Vector2i& cursor_position)
    {
        basic::Line3 ray;
        basic::Vector3 point_a, point_b;        
        point_a = _Controller->GetParentViewport().GetCamera().GetComponent().GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World).GetTranslation();
        point_b = _Controller->GetParentViewport().GetCamera().ComputeViewportToWorldPoint(
            basic::Vector2((real)cursor_position.X, (real)cursor_position.Y));
        ray.SetFromPoints(point_a, point_b);
        return ray;
    }

    //--------------------------------------------------------------------------------------------//

    void Gizmo::_ComputePlane(basic::Vector3& vector, const basic::Plane& plane)
    {
        basic::Line3 ray = _ComputeRayFromCursor(_CursorPosition);        
        plane.FindLineIntersection(vector, ray);
        vector -= _Translation;        
    }
    
}
}
