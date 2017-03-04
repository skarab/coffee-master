#include "system/graphics/component/mesh/graphics_component_mesh.h"
#include "system/graphics/renderer/graphics_renderer.h"
#include "system/scene/node/scene_node.h"
#include "system/graphics/device/graphics_device.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::ComponentMesh);
        COFFEE_Ancestor(graphics::Component);
        COFFEE_Attribute(graphics::Mesh, _Mesh, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ComponentMesh::ComponentMesh() :
        _ItIsUpToDate(false)
    {
        EnableFlag(COMPONENT_FLAG_Pickable, true);
        EnableFlag(COMPONENT_FLAG_CastShadows, true);
    }

    //--------------------------------------------------------------------------------------------//

    ComponentMesh::~ComponentMesh()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void ComponentMesh::SetMesh(Mesh mesh)
    {
        _Mesh = mesh;
        _ItIsUpToDate = false;
    }

    //--------------------------------------------------------------------------------------------//

    const Mesh& ComponentMesh::GetMesh() const
    {
        return _Mesh;
    }

    //--------------------------------------------------------------------------------------------//

    Mesh& ComponentMesh::GetMesh()
    {
        return _Mesh;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//
     
    void ComponentMesh::Render(uint32 surface_index, Viewport& viewport)
    {
        COFFEE_GRAPHICS_Debug();
        Renderer::Get().SetLocalToWorldMatrix(
            GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World));
        _Mesh.Render(surface_index);
        COFFEE_GRAPHICS_Debug();
    }

    //--------------------------------------------------------------------------------------------//

    void ComponentMesh::RenderShadows(uint32 surface_index, Viewport& viewport, graphics::Material& material)
    {
        Renderer::Get().SetLocalToWorldMatrix(
            GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World));
        _Mesh.RenderShadows(surface_index, material);
    }
       
    //--------------------------------------------------------------------------------------------//

    void ComponentMesh::RenderPicker(Viewport& viewport)
    {
        Renderer::Get().SetLocalToWorldMatrix(
            GetNode().GetTransform().GetMatrix(scene::TRS_Local, scene::TRS_World));
        _Mesh.RenderPicker();
    }
    
    //-HANDLERS-------------------------------------------------------------------------------//

    void ComponentMesh::OnStart()
    {
        if (_Mesh.GetFilePath().IsEmpty())
        {
            SetMesh(resource::Manager::Get().Load(
                storage::Path("/coffee/import/meshes/cube.mesh")));
        }
    }

    //--------------------------------------------------------------------------------------------//

    void ComponentMesh::OnUpdate(const basic::Time& time_step)
    {
        if (!_ItIsUpToDate && _Mesh.IsAvailable(0))
        {
            if (GetNode().HasBounding())
                GetNode().GetBounding().SetLocalBox(_Mesh.GetBoundingBox());
            _ItIsUpToDate = true;
        }
    }

    //--------------------------------------------------------------------------------------------//

    void ComponentMesh::OnPropertyModified(const void* prop)
    {
        if (prop==&_Mesh)
            _ItIsUpToDate = false;
    }

}
}
