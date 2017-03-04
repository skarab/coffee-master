#ifndef _COFFEE_GRAPHICS_MESH_SURFACE_H_
#define _COFFEE_GRAPHICS_MESH_SURFACE_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/material/graphics_material.h"
#include "system/graphics/mesh/vertex_buffer/graphics_vertex_buffer.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Graphics mesh surface
    ///
    /// Surface containing its own index buffers and material.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API MeshSurface : public meta::Object
    {
        COFFEE_Type(MeshSurface);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        MeshSurface();
        ~MeshSurface();

        //-ACCESSORS------------------------------------------------------------------------------//

        const VertexBuffer& GetIndexBuffer(const VERTEX_BUFFER_TYPE& index_buffer_type) const;
        VertexBuffer& GetIndexBuffer(const VERTEX_BUFFER_TYPE& index_buffer_type);
        
        //-QUERIES--------------------------------------------------------------------------------//

        bool HasIndexBuffer(const VERTEX_BUFFER_TYPE& index_buffer_type) const;
        
        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create();
        void Destroy();
        void Render(const Material& material);
        void AddIndexBuffer(VertexBuffer& index_buffer);
        bool RemoveIndexBuffer(const VERTEX_BUFFER_TYPE& index_buffer_type);
        
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Prow<graphics::VertexBuffer*, true> _IndexBuffers;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, MeshSurface);
}
}
#endif
