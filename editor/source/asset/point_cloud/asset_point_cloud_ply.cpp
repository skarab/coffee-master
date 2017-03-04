#include "asset/point_cloud/asset_point_cloud_ply.h"

namespace coffee_editor
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(asset::PointCloudPLY);
        COFFEE_Ancestor(asset::Importer);
        COFFEE_Attribute(graphics::TEXTURE_PARAMETER, _Parameters, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace asset
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    PointCloudPLY::PointCloudPLY() :
        _Parameters(graphics::TEXTURE_PARAMETER_BilinearFiltering
            | graphics::TEXTURE_PARAMETER_AnisotropicFiltering)
    {
    }

    //--------------------------------------------------------------------------------------------//

    PointCloudPLY::~PointCloudPLY()
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool PointCloudPLY::IsSupporting(const basic::String& file_extension)
    {
        return file_extension=="ply";
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool PointCloudPLY::Import()
    {
        storage::Data* file_data = storage::System::Get().GetFileData(GetAssetPath());
        if (file_data==NULL)
            return false;
        if (file_data->GetSize()==0)
        {
            COFFEE_Delete(file_data);
            return false;
        }

        basic::Vector<basic::Vector3> points;
        basic::Vector<basic::Vector3> colors;
        basic::Vector3 minimum;
        basic::Vector3 maximum;

        storage::Stream stream;
        stream.SetData(file_data);
        basic::String line;
        basic::String vertex_count_token = "element vertex ";
        basic::String begin_vertex_token = "end_header";
        uint32 point_count = 0;

        while (stream.PopLine(line))
        {
            if (line.IsPrefixed(vertex_count_token))
            {
                point_count = line.GetRight(line.GetLength()-vertex_count_token.GetLength()).GetInteger();
                break;
            }
        }

        if (point_count==0)
            return false;

        while (stream.PopLine(line))
        {
            if (line.IsPrefixed(begin_vertex_token))
                break;
        }

        if (stream.IsOver())
            return false;

        points.Resize(point_count);
        colors.Resize(point_count);

        for (uint32 i=0 ; i<point_count ; ++i)
        {
            if (!stream.PopLine(line))
                return false;

            int32 id = NONE;
            basic::String component;
            if (!line.GetNextWord(component, id)) return false;
            points[i].X = component.GetReal();
            if (!line.GetNextWord(component, id)) return false;
            points[i].Y = component.GetReal();
            if (!line.GetNextWord(component, id)) return false;
            points[i].Z = component.GetReal();

            if (i==0)
            {
                minimum = points[i];
                maximum = points[i];
            }
            else
            {
                minimum.X = Minimum(minimum.X, points[i].X);
                minimum.Y = Minimum(minimum.Y, points[i].Y);
                minimum.Z = Minimum(minimum.Z, points[i].Z);
                maximum.X = Maximum(maximum.X, points[i].X);
                maximum.Y = Maximum(maximum.Y, points[i].Y);
                maximum.Z = Maximum(maximum.Z, points[i].Z);
            }

            if (!line.GetNextWord(component, id)) return false;
            colors[i].X = component.GetReal();
            if (!line.GetNextWord(component, id)) return false;
            colors[i].Y = component.GetReal();
            colors[i].Z = 0.0f;
        }

        basic::Vector3 border = (maximum-minimum)*0.1f;
        minimum -= border;
        maximum += border;
        
        uint32 width = 48;
        uint32 height = 48;
        uint32 depth = 48;
        uint32 component_count = 4;
        meta::SCALAR_FORMAT component_type = meta::SCALAR_FORMAT_UInt8;
        
        storage::Path albedo_file_path = Manager::Get().GetResourcePath(GetAssetPath())
            + "/" + GetAssetPath().GetFileNameWithoutExtension() + "_albedo.texture";
        
        basic::Image* albedo_image = COFFEE_New(basic::Image);
        albedo_image->Create(width, height, depth, component_type, component_count, false);
        
        uint8* data = (uint8*)albedo_image->GetData();
        for (uint32 i=0 ; i<points.GetSize() ; ++i)
        {
            basic::Vector3 p = (points[i]-minimum)/(maximum-minimum);
            int32 x = (int32)(p.X*width);   Clamp(x, 1, (int32)width-2);
            int32 y = (int32)(p.Y*height);  Clamp(y, 1, (int32)height-2);
            int32 z = (int32)(p.Z*depth);   Clamp(z, 1, (int32)depth-2);
            uint32 d = (z*width*height+y*width+x)*4;
            data[d] = colors[i].X*255;
            data[d+1] = colors[i].Y*255;
            data[d+2] = colors[i].Z*255;
            data[d+3] = 255;
        }

        storage::Path normal_file_path = Manager::Get().GetResourcePath(GetAssetPath())
            + "/" + GetAssetPath().GetFileNameWithoutExtension() + "_normal.texture";
    
        basic::Image* normal_image = COFFEE_New(basic::Image);
        normal_image->Create(width, height, depth, component_type, 3, false);
        
        uint8* normal_data = (uint8*)normal_image->GetData();
        for (uint32 z=1 ; z<depth-1 ; ++z)
        for (uint32 y=1 ; y<height-1 ; ++y)
        for (uint32 x=1 ; x<width-1 ; ++x)
        {
            basic::Vector3 normal;
            
            for (int32 k=-1 ; k<2 ; k++)
            for (int32 j=-1 ; j<2 ; j++)
            for (int32 i=-1 ; i<2 ; i++)
            {
                uint32 d = ((z+k)*width*height+(y+j)*width+x+i)*4;
                if (data[d+3]==0)
                {
                    basic::Vector3 v = basic::Vector3(i, j, k);
                    if (!v.IsZero())
                    {
                        v.Normalize();
                        normal += v;
                    }
                }
            }

            if (!normal.IsZero())
            {
                normal.Normalize();
                uint32 d = (z*width*height+y*width+x)*3;
                normal_data[d] = (normal.X/2.0f+0.5f)*255;
                normal_data[d+1] = (normal.Y/2.0f+0.5f)*255;
                normal_data[d+2] = (normal.Z/2.0f+0.5f)*255;                
            }
        }

        DeleteImportedResources();
        AddThumbnail(Manager::Get().GenerateThumbnail(GetImportPath(), *albedo_image));
        AddThumbnail(Manager::Get().GenerateThumbnail(albedo_file_path, *albedo_image));
        AddThumbnail(Manager::Get().GenerateThumbnail(normal_file_path, *normal_image));

        // Create albedo
        {
            graphics::Texture3D* texture;
            texture = COFFEE_New(graphics::Texture3D);
            texture->SetImage(*albedo_image);
            texture->SetParameters(_Parameters);
            texture->Initialize();
            texture->PreCreateLOD(0);

            resource::Chunk* resource_chunk;
            resource_chunk = resource::Manager::Get().Create(albedo_file_path);
            resource_chunk->AddLOD(*texture);
            AddImportedResource(resource_chunk);
        }

        // Create normal
        {
            graphics::Texture3D* texture;
            texture = COFFEE_New(graphics::Texture3D);
            texture->SetImage(*normal_image);
            texture->SetParameters(_Parameters | graphics::TEXTURE_PARAMETER_LinearSpace);
            texture->Initialize();
            texture->PreCreateLOD(0);

            resource::Chunk* resource_chunk;
            resource_chunk = resource::Manager::Get().Create(normal_file_path);
            resource_chunk->AddLOD(*texture);
            AddImportedResource(resource_chunk);
        }

        // Create mesh
        {
            storage::Path file_path = Manager::Get().GetResourcePath(GetAssetPath())
                + "/" + GetAssetPath().GetFileNameWithoutExtension() + ".mesh";

            graphics::Mesh* mesh = COFFEE_New(graphics::Mesh);

            graphics::VertexBuffer* vertex_buffer = COFFEE_New(graphics::VertexBuffer);
            vertex_buffer->SetType(graphics::VERTEX_BUFFER_TYPE_Position);
            vertex_buffer->EnableMode(graphics::VERTEX_BUFFER_MODE_Write, true);
            vertex_buffer->SetComponentCount(3);
            vertex_buffer->SetComponentType(meta::SCALAR_FORMAT_Real);
            mesh->AddVertexBuffer(*vertex_buffer);
    
            graphics::VertexBuffer* surface = COFFEE_New(graphics::VertexBuffer);
            surface->SetType(graphics::VERTEX_BUFFER_TYPE_Index);
            surface->EnableMode(graphics::VERTEX_BUFFER_MODE_Write, true);
            surface->SetComponentCount(3);
            surface->SetComponentType(meta::SCALAR_FORMAT_UInt32);
            
            float s = 0.6f;
            uint32 depth = 128;
            vertex_buffer->SetObjectCount(depth*4);
            surface->SetObjectCount(depth*2);

            for (uint32 p=0 ; p<depth ; ++p)
            {
                real* vertice = (real*)vertex_buffer->GetObject(p*4);
                float d = p*(s*2.0f)/(depth-1.0f)-s;
                vertice[0] = -s;   vertice[1] = s;      vertice[2] = d;
                vertice[3] = s;    vertice[4] = s;      vertice[5] = d;
                vertice[6] = s;    vertice[7] = -s;     vertice[8] = d;
                vertice[9] = -s;   vertice[10] = -s;    vertice[11] = d;
                
                uint32* indices = (uint32*)surface->GetObject(p*2);
                indices[0] = p*4;
                indices[1] = p*4+1;
                indices[2] = p*4+2;
                indices[3] = p*4;
                indices[4] = p*4+2;
                indices[5] = p*4+3;
            }

            mesh->AddSurface(resource::Manager::Get().Load(
                "/coffee/import/shaders/point_cloud.material"));
            mesh->GetSurface(0).AddIndexBuffer(*surface);

            mesh->ComputeBoundingBox();
            mesh->Initialize();
            mesh->PreCreateLOD(0);
            resource::Chunk* resource_chunk;
            resource_chunk = resource::Manager::Get().Create(file_path);
            resource_chunk->AddLOD(*mesh);

            AddImportedResource(resource_chunk);
        }
        return true;
    }

}
}
