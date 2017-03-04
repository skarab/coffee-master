#include "system/graphics/mesh/graphics_mesh_surface.h"
#include "system/graphics/device/graphics_device.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::MeshSurface);
        COFFEE_Attribute(basic::Prow<graphics::VertexBuffer*>, _IndexBuffers, meta::MODE_Serializeable);
    COFFEE_EndType();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    MeshSurface::MeshSurface()
    {
    }

    //--------------------------------------------------------------------------------------------//

    MeshSurface::~MeshSurface()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//
    
    const VertexBuffer& MeshSurface::GetIndexBuffer(const VERTEX_BUFFER_TYPE& index_buffer_type) const
    {
        for (uint32 index=0 ; index<_IndexBuffers.GetSize() ; ++index)
        {
            if (_IndexBuffers[index]->GetType()==index_buffer_type)
                return *_IndexBuffers[index];
        }
        COFFEE_Error(core::ERROR_CODE_GraphicsDriver, "Failed to find index buffer");
        return *_IndexBuffers[0];
    }

    //--------------------------------------------------------------------------------------------//

    VertexBuffer& MeshSurface::GetIndexBuffer(const VERTEX_BUFFER_TYPE& index_buffer_type)
    {
        for (uint32 index=0 ; index<_IndexBuffers.GetSize() ; ++index)
        {
            if (_IndexBuffers[index]->GetType()==index_buffer_type)
                return *_IndexBuffers[index];
        }
        COFFEE_Error(core::ERROR_CODE_GraphicsDriver, "Failed to find index buffer");
        return *_IndexBuffers[0];
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool MeshSurface::HasIndexBuffer(const VERTEX_BUFFER_TYPE& index_buffer_type) const
    {
        for (uint32 index=0 ; index<_IndexBuffers.GetSize() ; ++index)
        {
            if (_IndexBuffers[index]->GetType()==index_buffer_type)
                return true;
        }
        return false;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void MeshSurface::Create()
    {
        for (uint32 index=0 ; index<_IndexBuffers.GetSize() ; ++index)
            _IndexBuffers[index]->Create();
    }

    //--------------------------------------------------------------------------------------------//

    void MeshSurface::Destroy()
    {
        for (uint32 index=0 ; index<_IndexBuffers.GetSize() ; ++index)
            _IndexBuffers[index]->Destroy();
    }

    //--------------------------------------------------------------------------------------------//

    void MeshSurface::Render(const Material& material)
    {
        for (uint32 index=0 ; index<_IndexBuffers.GetSize() ; ++index)
        {
            if (material.GetShader().IsVertexBufferEnabled(_IndexBuffers[index]->GetType()))
            {
                COFFEE_GRAPHICS_Debug();
                _IndexBuffers[index]->Bind();
                COFFEE_GRAPHICS_Debug();
                _IndexBuffers[index]->UnBind();
                COFFEE_GRAPHICS_Debug();
            }
        }
    }

    //--------------------------------------------------------------------------------------------//
    
    void MeshSurface::AddIndexBuffer(VertexBuffer& index_buffer)
    {
        COFFEE_Assert(!HasIndexBuffer(index_buffer.GetType()), core::ERROR_CODE_GraphicsDriver,
            "Surface already contains an index buffer of this type");
        _IndexBuffers.AddItem(&index_buffer);
    }

    //--------------------------------------------------------------------------------------------//

    bool MeshSurface::RemoveIndexBuffer(const VERTEX_BUFFER_TYPE& index_buffer_type)
    {
        for (uint32 index=0 ; index<_IndexBuffers.GetSize() ; ++index)
        {
            if (_IndexBuffers[index]->GetType()==index_buffer_type)
            {
                COFFEE_Delete(_IndexBuffers[index]);
                _IndexBuffers.Remove(index);
                return true;
            }
        }
        return false;
    }

}
}
