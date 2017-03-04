#ifndef _COFFEE_EDITION_GIZMO_H_
#define _COFFEE_EDITION_GIZMO_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "wide/edition/gizmo/edition_gizmo_mode.h"
#include "wide/edition/gizmo/edition_gizmo_axis.h"
#include "wide/edition/gizmo/edition_gizmo_mesh.h"
#include "system/input/input.h"

namespace coffee
{
namespace edition
{
    //-FORWARDS-----------------------------------------------------------------------------------//
    class GizmoController;

    //--------------------------------------------------------------------------------------------//
    /// Gizmo
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Gizmo
    {
        friend class GizmoController;

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Gizmo();
        ~Gizmo();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetMode(GIZMO_MODE mode);
        GIZMO_MODE GetMode() const;
        void SetIsEnabled(bool it_is_enabled);
        bool IsEnabled() const;
        void SetPosition(const basic::Vector3& translation, const basic::Quaternion& rotation,
            const basic::Vector3& scale);
        
        //-OPERATIONS-----------------------------------------------------------------------------//
        
        void Render();
        GIZMO_AXIS Pick(const basic::Vector2i& point);

        //-HANDLERS-------------------------------------------------------------------------------//
        
        bool OnKeyPressed(const input::KEY& key_code, bool it_is_repeating);
        bool OnMouseMove(const basic::Vector2i& point);
        bool OnMouseLeftButtonPressed(const basic::Vector2i& point);
        bool OnMouseLeftButtonReleased(const basic::Vector2i& point);
        
    private:

        //-QUERIES--------------------------------------------------------------------------------//
        
        real _GetViewportScale() const;
            
        //-OPERATIONS-----------------------------------------------------------------------------//
        
        void _UpdateMatrices();
        void _ApplyTranslation();
        void _ApplyRotation();
        void _ApplyScale();
        bool _ComputeTranslationAxis();
        bool _ComputeTranslation(basic::Vector3& vector);
        bool _ComputeRotationAxis();
        bool _ComputeRotation(basic::Vector3& vector);
        void _ComputePlaneAxis(basic::Plane& plane);
        basic::Line3 _ComputeRayFromCursor(const basic::Vector2i& cursor_position);
        void _ComputePlane(basic::Vector3& vector, const basic::Plane& plane);
        
        //-ATTRIBUTES-----------------------------------------------------------------------------//
        
        GIZMO_MODE _Mode;
        GIZMO_AXIS _Axis;
        GizmoMesh _Mesh;
        basic::Vector3 _Translation;
        basic::Quaternion _Rotation;
        basic::Vector3 _Scale;
        basic::Matrix _Matrix;
        basic::Matrix _UnscaledMatrix;
        GizmoController* _Controller;
        bool _ItIsEnabled;
        real _ViewScale;
        bool _ItIsActive;
        basic::Vector3 _StartTranslation;
        basic::Quaternion _StartRotation;
        basic::Vector3 _StartScale;
        basic::Vector3 _StartTransform;
        basic::Vector2i _CursorPosition;
        basic::Vector2 _Transform;
        basic::Vector2 _TransformAxis;
        basic::Vector3 _TransformScale;
        basic::Plane _TransformPlane;
    };
}
}
#endif
