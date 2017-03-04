#include "asset/mesh/asset_mesh_modifier.h"
#include "coffee_editor.h"

namespace coffee_editor
{
namespace asset
{
    //-FUNCTIONS----------------------------------------------------------------------------------//

    bool MeshModifierComputeTBN(graphics::Mesh& mesh)
    {
        // Check position
        if (!mesh.HasVertexBuffer(graphics::VERTEX_BUFFER_TYPE_Position)
            || mesh.GetVertexBuffer(graphics::VERTEX_BUFFER_TYPE_Position).GetObjectCount()==0)
        {
            return false;
        }
        graphics::VertexBuffer& vertex_buffer(mesh.GetVertexBuffer(graphics::VERTEX_BUFFER_TYPE_Position));
        
        // Check texcoord
        bool it_has_texcoords = mesh.HasVertexBuffer(graphics::VERTEX_BUFFER_TYPE_TexCoord);
        graphics::VertexBuffer* texcoord_buffer;
        if (it_has_texcoords)
            texcoord_buffer = &mesh.GetVertexBuffer(graphics::VERTEX_BUFFER_TYPE_TexCoord);
        
        // Check normals
        graphics::VertexBuffer* normal_buffer;
        bool it_has_normals = mesh.HasVertexBuffer(graphics::VERTEX_BUFFER_TYPE_Normal);
        real* normal_data = NULL;
        if (it_has_normals)
        {
            normal_buffer = &mesh.GetVertexBuffer(graphics::VERTEX_BUFFER_TYPE_Normal);
        }
        else
        {
            normal_buffer = COFFEE_New(graphics::VertexBuffer);
            normal_buffer->SetType(graphics::VERTEX_BUFFER_TYPE_Normal);
            normal_buffer->EnableMode(graphics::VERTEX_BUFFER_MODE_Write, true);
            normal_buffer->SetComponentCount(3);
            normal_buffer->SetComponentType(meta::SCALAR_FORMAT_Real);
            normal_buffer->SetObjectCount(vertex_buffer.GetObjectCount());
            normal_data = (real*)normal_buffer->GetData();
            COFFEE_Set(normal_data, 0, sizeof(real)*3*vertex_buffer.GetObjectCount());
        }

        // Check stangent
        if (mesh.HasVertexBuffer(graphics::VERTEX_BUFFER_TYPE_STangent))
            mesh.RemoveVertexBuffer(graphics::VERTEX_BUFFER_TYPE_STangent);
        graphics::VertexBuffer* stangent_buffer(NULL);
        real* stangent_data(NULL);
        if (it_has_texcoords)
        {
            stangent_buffer = COFFEE_New(graphics::VertexBuffer);
            stangent_buffer->SetType(graphics::VERTEX_BUFFER_TYPE_STangent);
            stangent_buffer->EnableMode(graphics::VERTEX_BUFFER_MODE_Write, true);
            stangent_buffer->SetComponentCount(3);
            stangent_buffer->SetComponentType(meta::SCALAR_FORMAT_Real);
            stangent_buffer->SetObjectCount(vertex_buffer.GetObjectCount());
            stangent_data = (real*)stangent_buffer->GetData();
            COFFEE_Set(stangent_data, 0, sizeof(real)*3*vertex_buffer.GetObjectCount());
        }

        // Check ttangent
        if (mesh.HasVertexBuffer(graphics::VERTEX_BUFFER_TYPE_TTangent))
            mesh.RemoveVertexBuffer(graphics::VERTEX_BUFFER_TYPE_TTangent);
        graphics::VertexBuffer* ttangent_buffer(NULL);
        real* ttangent_data(NULL);
        if (it_has_texcoords)
        {
            ttangent_buffer = COFFEE_New(graphics::VertexBuffer);
            ttangent_buffer->SetType(graphics::VERTEX_BUFFER_TYPE_TTangent);
            ttangent_buffer->EnableMode(graphics::VERTEX_BUFFER_MODE_Write, true);
            ttangent_buffer->SetComponentCount(3);
            ttangent_buffer->SetComponentType(meta::SCALAR_FORMAT_Real);
            ttangent_buffer->SetObjectCount(vertex_buffer.GetObjectCount());
            ttangent_data = (real*)ttangent_buffer->GetData();
            COFFEE_Set(ttangent_data, 0, sizeof(real)*3*vertex_buffer.GetObjectCount());
        }

        uint32 polygon_count = 0;
        for (uint32 surface_index=0 ; surface_index<mesh.GetSurfaceCount() ; ++surface_index)
        {
            graphics::MeshSurface& surface = mesh.GetSurface(surface_index);
            if (surface.HasIndexBuffer(graphics::VERTEX_BUFFER_TYPE_Index))
                polygon_count += surface.GetIndexBuffer(graphics::VERTEX_BUFFER_TYPE_Index).GetObjectCount();
        }

        // Generate polygons TBN and add it to vertice TBN
        uint32 progress = 0;
        for (uint32 surface_index=0 ; surface_index<mesh.GetSurfaceCount() ; ++surface_index)
        {
            graphics::MeshSurface& surface = mesh.GetSurface(surface_index);
            if (surface.HasIndexBuffer(graphics::VERTEX_BUFFER_TYPE_Index))
            {
                graphics::VertexBuffer& index_buffer(surface.GetIndexBuffer(graphics::VERTEX_BUFFER_TYPE_Index));
            
                for (uint32 polygon_index=0 ; polygon_index<index_buffer.GetObjectCount() ; ++polygon_index)
                {
                    Application::Get().GetEditorFrame().SetSubProgress(progress/(real)polygon_count);
                    ++progress;

                    uint32* p_data = (uint32*)index_buffer.GetObject(polygon_index);
                    basic::Vector3 vertex[3];
                    basic::Vector3 normal;
                    basic::Vector2 texcoord[3];
                    
                    for (uint32 i=0 ; i<3 ; ++i)
                    {
                        real* v_data = (real*)vertex_buffer.GetObject(p_data[i]);
                        vertex[i].X = v_data[0];
                        vertex[i].Y = v_data[1];
                        vertex[i].Z = v_data[2];

                        if (it_has_normals)
                        {
                            real* n_data = (real*)normal_buffer->GetObject(p_data[i]);
                            normal.X += n_data[0];
                            normal.Y += n_data[1];
                            normal.Z += n_data[2];
                        }

                        if (it_has_texcoords)
                        {
                            real* uv_data = (real*)texcoord_buffer->GetObject(p_data[i]);
                            texcoord[i].X = uv_data[0];
                            texcoord[i].Y = uv_data[1];
                        }
                    }

                    basic::Vector3 v[2];
                    v[0] = vertex[1]-vertex[0];
                    v[1] = vertex[2]-vertex[0];
                    
                    if (!it_has_normals)
                        normal = v[0].GetCrossProduct(v[1]);
                    if (normal.IsZero()) normal = basic::Vector3::XAxis;
                    else normal.Normalize();
                    
                    basic::Vector3 stangent, ttangent;
                    if (it_has_texcoords)
                    {
                        basic::Vector2 uv[2];
                        uv[0] = texcoord[1]-texcoord[0];
                        uv[1] = texcoord[2]-texcoord[0];

                        stangent = v[0]*uv[1].Y - v[1]*uv[0].Y;
                        if (stangent.IsZero()) stangent = basic::Vector3::XAxis;
                        else stangent.Normalize();

                        ttangent = v[0]*uv[1].X - v[1]*uv[0].X;
                        if (ttangent.IsZero()) ttangent = basic::Vector3::XAxis;
                        else ttangent.Normalize();
                        
                        basic::Vector3 cross = stangent.GetCrossProduct(ttangent);
                        if (cross.GetDotProduct(normal)<0.0f)
                        {
                            stangent = -stangent;
                            ttangent = -ttangent;
                        }
                    }

                    // Add polygon TBN to vertice TBN
                    for (uint32 index_index=0 ; index_index<3 ; ++index_index)
                    {
                        if (!it_has_normals)
                        {
                            normal_data[p_data[index_index]*3+0] += normal.X;
                            normal_data[p_data[index_index]*3+1] += normal.Y;
                            normal_data[p_data[index_index]*3+2] += normal.Z;
                        }

                        if (it_has_texcoords)
                        {
                            stangent_data[p_data[index_index]*3+0] += stangent.X;
                            stangent_data[p_data[index_index]*3+1] += stangent.Y;
                            stangent_data[p_data[index_index]*3+2] += stangent.Z;

                            ttangent_data[p_data[index_index]*3+0] += ttangent.X;
                            ttangent_data[p_data[index_index]*3+1] += ttangent.Y;
                            ttangent_data[p_data[index_index]*3+2] += ttangent.Z;
                        }
                    }
                }
            }
        }

        // Normalize vertice TBN
        for (uint32 vertex_index=0 ; vertex_index<vertex_buffer.GetObjectCount() ; ++vertex_index)
        {
            if (!it_has_normals)
            {
                basic::Vector3 normal(normal_data[vertex_index*3+0], normal_data[vertex_index*3+1], normal_data[vertex_index*3+2]);
                if (normal.IsZero()) normal = basic::Vector3::XAxis;
                else normal.Normalize();
                normal_data[vertex_index*3+0] = normal.X;
                normal_data[vertex_index*3+1] = normal.Y;
                normal_data[vertex_index*3+2] = normal.Z;
            }

            if (it_has_texcoords)
            {
                basic::Vector3 stangent(stangent_data[vertex_index*3+0], stangent_data[vertex_index*3+1], stangent_data[vertex_index*3+2]);
                if (stangent.IsZero()) stangent = basic::Vector3::XAxis;
                else stangent.Normalize();
                stangent_data[vertex_index*3+0] = stangent.X;
                stangent_data[vertex_index*3+1] = stangent.Y;
                stangent_data[vertex_index*3+2] = stangent.Z;

                basic::Vector3 ttangent(ttangent_data[vertex_index*3+0], ttangent_data[vertex_index*3+1], ttangent_data[vertex_index*3+2]);
                if (ttangent.IsZero()) ttangent = basic::Vector3::XAxis;
                else ttangent.Normalize();
                ttangent_data[vertex_index*3+0] = -ttangent.X;
                ttangent_data[vertex_index*3+1] = -ttangent.Y;
                ttangent_data[vertex_index*3+2] = -ttangent.Z;
            }
        }

        if (!it_has_normals)
            mesh.AddVertexBuffer(*normal_buffer);

        if (it_has_texcoords)
        {
            mesh.AddVertexBuffer(*stangent_buffer);
            mesh.AddVertexBuffer(*ttangent_buffer);
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//
    
    bool MeshModifierComputeAdjacency(graphics::Mesh& mesh)
    {
        // Check position
        if (!mesh.HasVertexBuffer(graphics::VERTEX_BUFFER_TYPE_Position)
            || mesh.GetVertexBuffer(graphics::VERTEX_BUFFER_TYPE_Position).GetObjectCount()==0)
        {
            return false;
        }
        graphics::VertexBuffer& vertex_buffer(mesh.GetVertexBuffer(graphics::VERTEX_BUFFER_TYPE_Position));
        
        // Add vertex considered as the NULL index (W=0)
        vertex_buffer.SetObjectCount(vertex_buffer.GetObjectCount()+1);
        real* null_vertex = (real*)vertex_buffer.GetObject(vertex_buffer.GetObjectCount()-1);
        COFFEE_Copy(null_vertex, vertex_buffer.GetObject(0), sizeof(real)*3);
        null_vertex[3] = 0.0f;
        uint32 null_index = vertex_buffer.GetObjectCount()-1;
    
        uint32 polygon_count = 0;
        for (uint32 surface_index=0 ; surface_index<mesh.GetSurfaceCount() ; ++surface_index)
        {
            graphics::MeshSurface& surface = mesh.GetSurface(surface_index);
            if (surface.HasIndexBuffer(graphics::VERTEX_BUFFER_TYPE_Index))
                polygon_count += surface.GetIndexBuffer(graphics::VERTEX_BUFFER_TYPE_Index).GetObjectCount();
        }

        uint32 progress = 0;
        for (uint32 surface_index=0 ; surface_index<mesh.GetSurfaceCount() ; ++surface_index)
        {
            graphics::MeshSurface& surface = mesh.GetSurface(surface_index);
            if (surface.HasIndexBuffer(graphics::VERTEX_BUFFER_TYPE_Index)
                && surface.GetIndexBuffer(graphics::VERTEX_BUFFER_TYPE_Index).GetObjectCount()>0)
            {
                graphics::VertexBuffer& index_buffer(surface.GetIndexBuffer(graphics::VERTEX_BUFFER_TYPE_Index));
        
                // Use edges tokens to speed up
                basic::Array<uint32> edges;
                edges.Resize(index_buffer.GetObjectCount()*3);
                memset(edges.GetLinearBuffer(), 0, index_buffer.GetObjectCount()*3*sizeof(uint32));

                // Create adjacency buffer
                graphics::VertexBuffer* adjacency = COFFEE_New(graphics::VertexBuffer);
                adjacency->SetType(graphics::VERTEX_BUFFER_TYPE_Adjacency);
                adjacency->EnableMode(graphics::VERTEX_BUFFER_MODE_Write, true);
                adjacency->SetComponentCount(6);
                adjacency->SetComponentType(meta::SCALAR_FORMAT_UInt32);
                adjacency->SetObjectCount(index_buffer.GetObjectCount());
                
                for (uint32 i=0 ; i<index_buffer.GetObjectCount() ; ++i)
                {
                    Application::Get().GetEditorFrame().SetSubProgress(progress/(real)polygon_count);
                    ++progress;

                    uint32* surface_indice = (uint32*)index_buffer.GetObject(i);
                    uint32* indice = (uint32*)adjacency->GetObject(i);
                    indice[0] = surface_indice[0];
                    indice[1] = null_index;
                    indice[2] = surface_indice[1];
                    indice[3] = null_index;
                    indice[4] = surface_indice[2];
                    indice[5] = null_index;

                    if (edges[i*3+0]!=0) indice[1] = edges[i*3+0]-1;
                    if (edges[i*3+1]!=0) indice[3] = edges[i*3+1]-1;
                    if (edges[i*3+2]!=0) indice[5] = edges[i*3+2]-1;
                    
                    bool finish = (indice[1]!=null_index) && (indice[3]!=null_index) && (indice[5]!=null_index);
                    for (uint32 j=i+1 ; j<index_buffer.GetObjectCount() && !finish ; ++j)
                    {
                        const uint32* ind = (uint32*)index_buffer.GetObject(j);
                        
                        for (uint32 k=0 ; k<3 ; ++k)
                        {
                            if (edges[j*3+k]==0)
                            {
                                uint32 i0 = k;
                                uint32 i1 = (k+1)%3;
                                uint32 i2 = (k+2)%3;

                                for (uint32 p=0 ; p<3 ; ++p)
                                {
                                    uint32 ii = 1+p*2;
                                    uint32 si0 = p;
                                    uint32 si1 = (p+1)%3;
                                    uint32 si2 = (p+2)%3;

                                    if (indice[ii]==null_index
                                        && ((ind[i0]==surface_indice[si0] && ind[i1]==surface_indice[si1])
                                        || (ind[i1]==surface_indice[si0] && ind[i0]==surface_indice[si1])))
                                    {
                                        edges[j*3+k] = surface_indice[si2]+1;
                                        indice[ii] = ind[i2];
                                    }                                    
                                }
                            }
                        }

                        finish = (indice[1]!=null_index) && (indice[3]!=null_index) && (indice[5]!=null_index);
                    }
                }
                
                surface.AddIndexBuffer(*adjacency);
            }
        }
        return true;
    }

}
}
