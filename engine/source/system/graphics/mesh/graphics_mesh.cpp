#include "system/graphics/mesh/graphics_mesh.h"
#include "system/graphics/frame/picker/graphics_frame_picker.h"
#include "system/graphics/device/graphics_device.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginResource(graphics, Mesh, "Mesh", "mesh", 0);
        COFFEE_Ancestor(resource::Object);
        COFFEE_ResourceProperty(basic::Prow<graphics::VertexBuffer*>, _VertexBuffers, meta::MODE_Serializeable, 0);
        COFFEE_ResourceProperty(< graphics::MeshSurface* >, _Surfaces, meta::MODE_Serializeable, 0);
        COFFEE_ResourceProperty(< graphics::Material* >, _Materials, meta::MODE_Serializeable | meta::MODE_Editable,
            resource::PROPERTY_FLAG_Instantiable);
        COFFEE_ResourceProperty(basic::Box, _BoundingBox, meta::MODE_Serializeable, 0);
    COFFEE_EndResource();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Mesh::Mesh()
    {
    }

    //--------------------------------------------------------------------------------------------//

    Mesh::~Mesh()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const VertexBuffer& Mesh::GetVertexBuffer(const VERTEX_BUFFER_TYPE& vertex_buffer_type) const
    {
        for (uint32 index=0 ; index<_VertexBuffers.Get().GetSize() ; ++index)
        {
            if(_VertexBuffers.Get()[index]->GetType()==vertex_buffer_type)
                return *_VertexBuffers.Get()[index];
        }
        COFFEE_Error(core::ERROR_CODE_GraphicsDriver, "Failed to find vertex buffer");
        return *_VertexBuffers.Get()[0];
    }

    //--------------------------------------------------------------------------------------------//

    VertexBuffer& Mesh::GetVertexBuffer(const VERTEX_BUFFER_TYPE& vertex_buffer_type)
    {
        for (uint32 index=0 ; index<_VertexBuffers.Get().GetSize() ; ++index)
        {
            if (_VertexBuffers.Get()[index]->GetType()==vertex_buffer_type)
                return *_VertexBuffers.Grab()[index];
        }
        COFFEE_Error(core::ERROR_CODE_GraphicsDriver, "Failed to find vertex buffer");
        return *_VertexBuffers.Grab()[0];
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool Mesh::HasVertexBuffer(const VERTEX_BUFFER_TYPE& vertex_buffer_type) const
    {
        for (uint32 index=0 ; index<_VertexBuffers.Get().GetSize() ; ++index)
        {
            if (_VertexBuffers.Get()[index]->GetType()==vertex_buffer_type)
                return true;
        }
        return false;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool Mesh::Initialize()
    {
        for (uint32 index=0 ; index<_VertexBuffers.GrabValue().GetSize() ; ++index)
            _VertexBuffers.GrabValue()[index]->Create();
        for (uint32 index=0 ; index<_Surfaces.Get().GetSize() ; ++index)
            _Surfaces.GrabValue()[index]->Create();
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool Mesh::Finalize()
    {
        for (uint32 index=0 ; index<_VertexBuffers.GrabValue().GetSize() ; ++index)
            _VertexBuffers.GrabValue()[index]->Destroy();
        for (uint32 index=0 ; index<_Surfaces.Get().GetSize() ; ++index)
            _Surfaces.GrabValue()[index]->Destroy();
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    void Mesh::Render(uint32 surface_index)
    {
        COFFEE_GRAPHICS_Debug();
        Material* material = _Materials.Grab()[surface_index];
        if (material->IsAvailable() && material->GetShader().IsAvailable())
        {
            material->Bind();
            COFFEE_GRAPHICS_Debug();
            _BindBuffers(*material);
            COFFEE_GRAPHICS_Debug();
            _Surfaces.Grab()[surface_index]->Render(*material);
            COFFEE_GRAPHICS_Debug();
            _UnBindBuffers(*material);
            COFFEE_GRAPHICS_Debug();
            material->UnBind();
            COFFEE_GRAPHICS_Debug();
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Mesh::RenderShadows(uint32 surface_index, graphics::Material& material)
    {
        material.Bind();
        _BindBuffers(material);
        _Surfaces.Grab()[surface_index]->Render(material);
        _UnBindBuffers(material);
        material.UnBind();
    }

    //--------------------------------------------------------------------------------------------//

    void Mesh::RenderPicker()
    {
        Material* material = &FramePicker::Get().GetMaterial();
        material->Bind();
        _BindBuffers(*material);
        for (uint32 i=0 ; i<_Surfaces.Get().GetSize() ; ++i)
            _Surfaces.Grab()[i]->Render(*material);
        _UnBindBuffers(*material);
        material->UnBind();
    }

    //--------------------------------------------------------------------------------------------//

    uint32 Mesh::AddSurface(Material material)
    {
        MeshSurface* surface = COFFEE_New(MeshSurface);
        uint32 index = _Surfaces.Grab().AddItem(surface);
        uint32 material_index = _Materials.Grab().AddItem(COFFEE_New(Material, material));
        COFFEE_Assert(index==material_index, core::ERROR_CODE_IncorrectUsage, "Mesh synchronization failed.");
        return index;
    }

    //--------------------------------------------------------------------------------------------//

    void Mesh::AddVertexBuffer(VertexBuffer& buffer)
    {
        COFFEE_Assert(!HasVertexBuffer(buffer.GetType()), core::ERROR_CODE_GraphicsDriver,
            "Mesh already contains a buffer of this type");
        _VertexBuffers.Grab().AddItem(&buffer);
    }

    //--------------------------------------------------------------------------------------------//

    bool Mesh::RemoveVertexBuffer(const VERTEX_BUFFER_TYPE& vertex_buffer_type)
    {
        for(uint32 index=0 ; index<_VertexBuffers.Get().GetSize() ; ++index)
        {
            if(_VertexBuffers.Get()[index]->GetType()==vertex_buffer_type)
            {
                COFFEE_Delete(_VertexBuffers.Grab()[index]);
                _VertexBuffers.Grab().Remove(index);
                return true;
            }
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    void Mesh::ComputeBoundingBox()
    {
        _BoundingBox.GrabValue().SetEmpty();
        if (HasVertexBuffer(VERTEX_BUFFER_TYPE_Position))
        {
            const VertexBuffer& buffer = GetVertexBuffer(VERTEX_BUFFER_TYPE_Position);
            for (uint32 i=0 ; i<buffer.GetObjectCount() ; i++)
            {
                _BoundingBox.GrabValue().AddPoint(basic::Vector3(
                    ((float*)buffer.GetObject(i))[0],
                    ((float*)buffer.GetObject(i))[1],
                    ((float*)buffer.GetObject(i))[2]),
                    i==0);
            }
        }
    }

    //-HANDLERS-----------------------------------------------------------------------------------//

    bool Mesh::OnInstantiateProperty(resource::PropertyBase& property, resource::PropertyBase& source_property, bool it_is_instantiating)
    {
        if (&property==&_Materials)
        {
            basic::Prow<Material*, true>& materials = _Materials.GrabValue();
            materials.Erase();

            if (it_is_instantiating)
            {
                basic::Prow<Material*, true>& source_materials =
                    static_cast<resource::Property< basic::Prow<Material*, true> >& >(source_property).Grab();
                for (uint32 index=0 ; index<source_materials.GetSize() ; ++index)
                    materials.AddItem(COFFEE_New(Material, *source_materials[index]));
            }
            return true;
        }
        return false;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Mesh::_BindBuffers(const graphics::Material& material)
    {
        for (uint32 index=0 ; index<_VertexBuffers.Get().GetSize() ; ++index)
        {
            if (material.GetShader().IsVertexBufferEnabled(_VertexBuffers.Grab()[index]->GetType()))
                _VertexBuffers.Grab()[index]->Bind();
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Mesh::_UnBindBuffers(const graphics::Material& material)
    {
        for (uint32 index=0 ; index<_VertexBuffers.Get().GetSize() ; ++index)
        {
            if (material.GetShader().IsVertexBufferEnabled(_VertexBuffers.Grab()[index]->GetType()))
                _VertexBuffers.Grab()[index]->UnBind();
        }
    }

}
}
