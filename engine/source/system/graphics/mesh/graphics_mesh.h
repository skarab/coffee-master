#ifndef _COFFEE_GRAPHICS_MESH_H_
#define _COFFEE_GRAPHICS_MESH_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "kernel/resource/resources.h"
#include "system/graphics/mesh/graphics_mesh_surface.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Mesh
    ///
    /// Mesh contains vertex buffers and multiple surfaces.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Mesh : public resource::Object
    {
        COFFEE_Resource(Mesh);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Mesh();
        ~Mesh();

        //-ACCESSORS------------------------------------------------------------------------------//

        const VertexBuffer& GetVertexBuffer(const VERTEX_BUFFER_TYPE& vertex_buffer_type) const;
        VertexBuffer& GetVertexBuffer(const VERTEX_BUFFER_TYPE& vertex_buffer_type);
        uint32 GetSurfaceCount() const { return _Surfaces.Get().GetSize(); }
        const MeshSurface& GetSurface(uint32 surface_index) const { return *_Surfaces.Get()[surface_index]; }
        MeshSurface& GetSurface(uint32 surface_index) { return *_Surfaces.Get()[surface_index]; }
        const Material& GetMaterial(uint32 surface_index) const { return *_Materials.Get()[surface_index]; }
        const basic::Box& GetBoundingBox() const { return _BoundingBox.Get(); }

        //-QUERIES--------------------------------------------------------------------------------//

        bool HasVertexBuffer(const VERTEX_BUFFER_TYPE& vertex_buffer_type) const;
        
        //-OPERATIONS-----------------------------------------------------------------------------//

        bool Initialize();
        bool Finalize();
        void Render(uint32 surface_index);
        void RenderShadows(uint32 surface_index, graphics::Material& material);
        void RenderPicker();
        uint32 AddSurface(Material material);
        void AddVertexBuffer(VertexBuffer& buffer);
        bool RemoveVertexBuffer(const VERTEX_BUFFER_TYPE& vertex_buffer_type);
        void ComputeBoundingBox();

        //-HANDLERS-------------------------------------------------------------------------------//

        bool OnInstantiateProperty(resource::PropertyBase& property, resource::PropertyBase& source_property, bool it_is_instantiating);

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _BindBuffers(const graphics::Material& material);
        void _UnBindBuffers(const graphics::Material& material);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        resource::Property< basic::Prow<VertexBuffer*, true> > _VertexBuffers;
        resource::Property< basic::Prow<MeshSurface*, true> > _Surfaces;
        resource::Property< basic::Prow<Material*, true> > _Materials;
        resource::Property< basic::Box > _BoundingBox;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Mesh);
}
}
#endif
