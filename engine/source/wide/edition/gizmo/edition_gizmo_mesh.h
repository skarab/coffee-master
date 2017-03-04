#ifndef _COFFEE_EDITION_GIZMO_MESH_H_
#define _COFFEE_EDITION_GIZMO_MESH_H_

#include "coffee_includes.h"
#include "system/graphics/graphics.h"
#include "wide/edition/gizmo/edition_gizmo_axis.h"
#include "wide/edition/gizmo/edition_gizmo_mode.h"

namespace coffee
{
namespace edition
{
    //--------------------------------------------------------------------------------------------//
    /// Gizmo mesh
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API GizmoMesh
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        GizmoMesh();
        ~GizmoMesh();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Render(graphics::Viewport& viewport, const basic::Matrix& local_to_world_matrix, basic::Vector3 size,
            basic::Vector3 arrow_size, const GIZMO_MODE& mode, const GIZMO_AXIS& selected_axis);
        GIZMO_AXIS Pick(graphics::Viewport& viewport, const basic::Vector2i& point, const basic::Matrix& local_to_world_matrix,
            basic::Vector3 size, basic::Vector3 arrow_size, const GIZMO_MODE& mode);

    private:

        //-QUERIES--------------------------------------------------------------------------------//

        basic::Color GetAxisColor(const GIZMO_AXIS& axis, bool it_is_selected);

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _RenderAxis(graphics::Viewport& viewport, const GIZMO_AXIS& axis);
        void _RenderTranslation(graphics::Viewport& viewport);
        void _RenderRotation(graphics::Viewport& viewport);
        void _RenderScale(graphics::Viewport& viewport);

        //-ATTRIBUTES-----------------------------------------------------------------------------//
        
        basic::Matrix _LocalToWorldMatrix;
        basic::Vector3 _Size;
        basic::Vector3 _ArrowSize;
        GIZMO_MODE _Mode;
        GIZMO_AXIS _SelectedAxis;
        GIZMO_AXIS _Axis;
        bool _ItIsPicking;
    };
}
}
#endif
