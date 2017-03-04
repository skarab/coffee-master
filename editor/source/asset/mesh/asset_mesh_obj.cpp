#include "asset/mesh/asset_mesh_obj.h"
#include "asset/mesh/asset_mesh_modifier.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(asset::MeshOBJ);
        COFFEE_Ancestor(asset::Importer);
        COFFEE_Attribute(real, _Scale, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(asset::MESH_MAP_MODE, _TexCoords, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(asset::MESH_MAP_MODE, _Normals, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(bool, _GenerateAdjacency, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(bool, _FlipPolygons, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(asset::MESH_MAP_COMPONENT, _X, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(asset::MESH_MAP_COMPONENT, _Y, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(asset::MESH_MAP_COMPONENT, _Z, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace asset
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

	MeshOBJ::MeshOBJ() :
        _Scale(1.0f),
        _TexCoords(MESH_MAP_MODE_Keep),
        _Normals(MESH_MAP_MODE_KeepOrGenerate),
        _GenerateAdjacency(true),
        _FlipPolygons(false),
        _X(MESH_MAP_COMPONENT_X),
        _Y(MESH_MAP_COMPONENT_Y),
        _Z(MESH_MAP_COMPONENT_Z)
    {
    }

    //--------------------------------------------------------------------------------------------//

    MeshOBJ::~MeshOBJ()
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool MeshOBJ::IsSupporting(const basic::String& file_extension)
    {
        return file_extension=="obj";
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    real _GetMapping(uint32 index, const basic::Rope<basic::Vector3, 64>& v,  MESH_MAP_COMPONENT mapping)
    {
        if (index<v.GetSize())
        {
            switch (mapping)
            {
                case MESH_MAP_COMPONENT_X:          return v[index].X;
                case MESH_MAP_COMPONENT_Y:          return v[index].Y;
                case MESH_MAP_COMPONENT_Z:          return v[index].Z;
                case MESH_MAP_COMPONENT_InverseX:   return -v[index].X;
                case MESH_MAP_COMPONENT_InverseY:   return -v[index].Y;
                case MESH_MAP_COMPONENT_InverseZ:   return -v[index].Z;
                default: break;
            }
        }
        return 0.0f;
    }

    //--------------------------------------------------------------------------------------------//

    bool MeshOBJ::Import()
    {
        storage::Data* file_data = storage::System::Get().GetFileData(GetAssetPath());
        if (file_data==NULL)
            return false;
        if (file_data->GetSize()==0)
        {
            COFFEE_Delete(file_data);
            return false;
        }

        storage::Stream data_stream;
        data_stream.SetData(file_data);
        MeshOBJFile obj;
        if (!obj.Load(data_stream))
            return false;

        SetProgress(0.10f);

        storage::Path file_path = Manager::Get().GetResourcePath(GetAssetPath())
            + "/" + GetAssetPath().GetFileNameWithoutExtension() + ".mesh";

        graphics::Mesh* mesh = COFFEE_New(graphics::Mesh);

        graphics::VertexBuffer* vertex_buffer = COFFEE_New(graphics::VertexBuffer);
        vertex_buffer->SetType(graphics::VERTEX_BUFFER_TYPE_Position);
        vertex_buffer->EnableMode(graphics::VERTEX_BUFFER_MODE_Write, true);
        vertex_buffer->SetComponentCount(_GenerateAdjacency?4:3);
        vertex_buffer->SetComponentType(meta::SCALAR_FORMAT_Real);
        mesh->AddVertexBuffer(*vertex_buffer);

        bool use_input_texcoords = obj.TexCoordArray.GetSize()>0 && _TexCoords==MESH_MAP_MODE_Keep;
        graphics::VertexBuffer* texcoord_buffer(NULL);
        if (use_input_texcoords)
        {
            texcoord_buffer = COFFEE_New(graphics::VertexBuffer);
            texcoord_buffer->SetType(graphics::VERTEX_BUFFER_TYPE_TexCoord);
            texcoord_buffer->EnableMode(graphics::VERTEX_BUFFER_MODE_Write, true);
            texcoord_buffer->SetComponentCount(2);
            texcoord_buffer->SetComponentType(meta::SCALAR_FORMAT_Real);
            mesh->AddVertexBuffer(*texcoord_buffer);
        }

        bool use_input_normals = obj.NormalArray.GetSize()>0
            && (_Normals==MESH_MAP_MODE_Keep || _Normals==MESH_MAP_MODE_KeepOrGenerate);
        graphics::VertexBuffer* normal_buffer(NULL);
        if (use_input_normals)
        {
            normal_buffer = COFFEE_New(graphics::VertexBuffer);
            normal_buffer->SetType(graphics::VERTEX_BUFFER_TYPE_Normal);
            normal_buffer->EnableMode(graphics::VERTEX_BUFFER_MODE_Write, true);
            normal_buffer->SetComponentCount(3);
            normal_buffer->SetComponentType(meta::SCALAR_FORMAT_Real);
            mesh->AddVertexBuffer(*normal_buffer);
        }

        uint32 face_count(0);
        for (uint32 object_index=0 ; object_index<obj.ObjectArray.GetSize() ; ++object_index)
        for (uint32 surface_index=0 ; surface_index<obj.ObjectArray[object_index]->SurfaceArray.GetSize() ; ++surface_index)
            face_count += obj.ObjectArray[object_index]->SurfaceArray[surface_index]->FaceArray.GetSize();

        uint32 findex(0);
        for (uint32 object_index=0 ; object_index<obj.ObjectArray.GetSize() ; ++object_index)
        for (uint32 surface_index=0 ; surface_index<obj.ObjectArray[object_index]->SurfaceArray.GetSize() ; ++surface_index)
        {
            MeshOBJFile::Surface& obj_surface = *obj.ObjectArray[object_index]->SurfaceArray[surface_index];
            if (obj_surface.FaceArray.GetSize()==0)
                continue;

            graphics::VertexBuffer* surface = COFFEE_New(graphics::VertexBuffer);
            surface->SetType(graphics::VERTEX_BUFFER_TYPE_Index);
            surface->EnableMode(graphics::VERTEX_BUFFER_MODE_Write, true);
            surface->SetComponentCount(3);
            surface->SetComponentType(meta::SCALAR_FORMAT_UInt32);
            surface->SetObjectCount(obj_surface.FaceArray.GetSize());

            for (uint32 face_index=0 ; face_index<surface->GetObjectCount() ; ++face_index)
            {
                SetProgress(0.10f+((real)findex/(face_count-1.0f))/2.0f);
                ++findex;

                uint32* surface_data = (uint32*)surface->GetObject(face_index);
                MeshOBJFile::Face& face = *obj_surface.FaceArray[face_index];
                for (uint32 index=0 ; index<3 ; ++index)
                {
                    uint32 iindex = _FlipPolygons?2-index:index;
                    uint32 vertex_index = face.IndexArray[iindex].VertexIndex-1;
                    uint32 texcoord_index = face.IndexArray[iindex].TexCoordIndex-1;
                    uint32 normal_index = face.IndexArray[iindex].NormalIndex-1;

                    // Check if its broken
                    if (vertex_index>=0 && vertex_index<obj.VertexArray.GetSize()
                        && (!use_input_texcoords || (texcoord_index>=0 && texcoord_index<obj.TexCoordArray.GetSize()))
                        && (!use_input_normals || (normal_index>=0 && normal_index<obj.NormalArray.GetSize())))
                    {
                        // Find if vertex is already created
                        uint32 id = NONE;
                        if (obj.IndexArray[vertex_index].Refs->GetSize()>0)
                        {
                            for (uint32 ri=0 ; ri<obj.IndexArray[vertex_index].Refs->GetSize() ; ++ri)
                            {
                                if ((!use_input_texcoords || texcoord_index==(*obj.IndexArray[vertex_index].Refs)[ri].TexCoordIndex)
                                    && (!use_input_normals || normal_index==(*obj.IndexArray[vertex_index].Refs)[ri].NormalIndex))
                                {
                                    id = (*obj.IndexArray[vertex_index].Refs)[ri].ID;
                                    break;
                                }
                            }
                        }

                        if (id!=NONE)
                        {
                            // Already created
                            surface_data[index] = id;
                        }
                        else
                        {
                            // Add a new vertex
                            uint32 new_index = vertex_buffer->GetObjectCount();

                            MeshOBJFile::VertexRef ref;
                            ref.ID = new_index;
                            ref.TexCoordIndex = texcoord_index;
                            ref.NormalIndex = normal_index;
                            obj.IndexArray[vertex_index].Refs->AddItem(ref);


                            surface_data[index] = new_index;
                            vertex_buffer->SetObjectCount(vertex_buffer->GetObjectCount()+1);
                            real* vertex = (real*)vertex_buffer->GetObject(new_index);
                            vertex[0] = _GetMapping(vertex_index, obj.VertexArray, _X) * _Scale;
                            vertex[1] = _GetMapping(vertex_index, obj.VertexArray, _Y) * _Scale;
                            vertex[2] = _GetMapping(vertex_index, obj.VertexArray, _Z) * _Scale;
                            if (_GenerateAdjacency)
                                vertex[3] = 1.0f;

                            if (texcoord_buffer!=NULL)
                            {
                                texcoord_buffer->SetObjectCount(texcoord_buffer->GetObjectCount()+1);
                                real* texcoord = (real*)texcoord_buffer->GetObject(new_index);
                                texcoord[0] = obj.TexCoordArray[texcoord_index].X;
                                texcoord[1] = obj.TexCoordArray[texcoord_index].Y;
                            }

                            if (normal_buffer!=NULL)
                            {
                                normal_buffer->SetObjectCount(normal_buffer->GetObjectCount()+1);
                                real* normal = (real*)normal_buffer->GetObject(new_index);
                                normal[0] = _GetMapping(normal_index, obj.NormalArray, _X);
                                normal[1] = _GetMapping(normal_index, obj.NormalArray, _Y);
                                normal[2] = _GetMapping(normal_index, obj.NormalArray, _Z);
                            }
                        }
                    }
                    else
                    {
                        // Broken mesh
                        surface_data[index] = 0;
                    }
                }
            }

            uint32 i = mesh->AddSurface(resource::Manager::Get().Load(
                "/coffee/import/shaders/default.material"));
            mesh->GetSurface(i).AddIndexBuffer(*surface);
        }

        if (_Normals!=MESH_MAP_MODE_Discard)
            MeshModifierComputeTBN(*mesh);

        SetProgress(0.80f);

        if (_GenerateAdjacency)
            MeshModifierComputeAdjacency(*mesh);

        SetProgress(1.0f);

        mesh->ComputeBoundingBox();
        mesh->Initialize();
        mesh->PreCreateLOD(0);
        resource::Chunk* resource_chunk;
        resource_chunk = resource::Manager::Get().Create(file_path);
        resource_chunk->AddLOD(*mesh);

        DeleteImportedResources();
        AddImportedResource(resource_chunk);
        return true;
    }

}
}
