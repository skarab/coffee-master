#ifndef _COFFEE_GRAPHICS_COMPONENT_MESH_H_
#define _COFFEE_GRAPHICS_COMPONENT_MESH_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/component/graphics_component.h"
#include "system/graphics/mesh/graphics_mesh.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Graphic mesh component
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ComponentMesh : public Component
    {
        COFFEE_Component(ComponentMesh, "Mesh", "Graphics/");

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ComponentMesh();
        ~ComponentMesh();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetMesh(Mesh mesh);
        const Mesh& GetMesh() const;
        Mesh& GetMesh();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Render(uint32 surface_index, Viewport& viewport);
        void RenderShadows(uint32 surface_index, Viewport& viewport, graphics::Material& material);
        void RenderPicker(Viewport& viewport);
        
        //-HANDLERS-------------------------------------------------------------------------------//

        void OnStart();
        void OnUpdate(const basic::Time& time_step);
        void OnPropertyModified(const void* prop);

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Mesh _Mesh;
        bool _ItIsUpToDate;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ComponentMesh);
}
}
#endif
