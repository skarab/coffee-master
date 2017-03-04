#include "asset/mesh/asset_mesh_obj_file.h"
#include "coffee_editor.h"

namespace coffee_editor
{
namespace asset
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    MeshOBJFile::MeshOBJFile()
    {
    }

    //--------------------------------------------------------------------------------------------//

    MeshOBJFile::~MeshOBJFile()
    {
        for (uint32 i=0 ; i<IndexArray.GetSize() ; ++i)
            COFFEE_Delete(IndexArray[i].Refs);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool MeshOBJFile::Load(storage::Stream& data_stream)
    {
        basic::String line;
        _CurrentObject = NULL;
        _CurrentSurface = NULL;
        while(data_stream.PopLine(line))
        {
            Application::Get().GetEditorFrame().SetSubProgress(data_stream.GetPercentage());

            if (line.GetLength()==0)
                continue;

            while (line.GetLength()>0 && (line[line.GetLength()-1]==' '
                || line[line.GetLength()-1]=='/n' || line[line.GetLength()-1]=='/t'
                || line[line.GetLength()-1]==13))
            {
                --line;
            }

            if (line.GetLength()==0)
                continue;

            switch (line[0])
            {
                case 'v':   if (!_ParseVertex(line))    return false;   break;
                case 'f':   if (!_ParseFace(line))      return false;   break;
                case 'o':   if (!_ParseObject(line))    return false;   break;
                case 'g':   if (!_ParseGroup(line))     return false;   break;
                case 'u':   if (!_ParseMaterial(line))  return false;   break;
                default:    break;
            }
        }
        _PushObject();
        return ObjectArray.GetSize()>0;
    }

    //-OPERATIONS-----------------------------------------------------------------------------//

    void MeshOBJFile::_RequireObject(basic::String name)
    {
        if (_CurrentObject==NULL)
        {
            _CurrentObject = COFFEE_New(Object);
            _CurrentObject->Name = name;
        }
    }

    //--------------------------------------------------------------------------------------------//

    void MeshOBJFile::_PushObject()
    {
        if (_CurrentObject!=NULL)
        {
            _PushSurface();
            if (_CurrentObject->SurfaceArray.GetSize()>0)
            {
                ObjectArray.AddItem(_CurrentObject);
            }
            else
            {
                COFFEE_Delete(_CurrentObject);
            }
            _CurrentObject = NULL;
        }
    }
     
    //--------------------------------------------------------------------------------------------//

    void MeshOBJFile::_RequireSurface(basic::String material)
    {
        _RequireObject();
        if (_CurrentSurface==NULL)
        {
            _CurrentSurface = COFFEE_New(Surface);
            _CurrentSurface->Material = material;
        }
    }

    //--------------------------------------------------------------------------------------------//

    void MeshOBJFile::_PushSurface()
    {
        if (_CurrentSurface!=NULL)
        {
            if (_CurrentSurface->FaceArray.GetSize()>0)
            {
                _CurrentObject->SurfaceArray.AddItem(_CurrentSurface);
            }
            else
            {
                COFFEE_Delete(_CurrentSurface);
            }
            _CurrentSurface = NULL;
        }
    }

    //--------------------------------------------------------------------------------------------//

    bool MeshOBJFile::_ParseVertex(basic::String& line)
    {
        if (line.GetLength()<3)
            return true;
        
        if (line.IsPrefixed("v ") || line.IsPrefixed("v/t"))
        {
            basic::Vector3 vertex;
            if (sscanf(line.GetBuffer()+2, "%f %f %f", &vertex.X, &vertex.Y, &vertex.Z)!=3)
                return false;
            VertexArray.AddItem(vertex);
            GenIndex ri;
            ri.Refs = COFFEE_New(basic::Rope<VertexRef>);
            IndexArray.AddItem(ri);
        }
        else if (line.IsPrefixed("vt ") || line.IsPrefixed("vt/t"))
        {
            basic::Vector2 texcoord;
            if (sscanf(line.GetBuffer()+3, "%f %f", &texcoord.X, &texcoord.Y)!=2)
                return false;
            TexCoordArray.AddItem(texcoord);
        }
        else if (line.IsPrefixed("vn ") || line.IsPrefixed("vn/t"))        
        {
            basic::Vector3 normal;
            if (sscanf(line.GetBuffer()+3, "%f %f %f", &normal.X, &normal.Y, &normal.Z)!=3)
                return false;
            NormalArray.AddItem(normal);
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool MeshOBJFile::_ParseFace(basic::String& line)
    {
        if ((line.IsPrefixed("f ") || line.IsPrefixed("f/t")) && line.GetLength()>2)
        {
            _RequireSurface();
            Face* face = COFFEE_New(Face);
            basic::String data(line.GetBuffer()+2);
            uint32 count = data.GetOccurencesCount(' ')+1;
            uint32 component_count = data.GetOccurencesCount('/')/count+1;
            bool it_has_error = component_count>3;
            int32 offset = NONE;
            basic::String value;
            basic::Vector<basic::String> tokens;
            tokens.AddItem(" ");
            tokens.AddItem("/");
            if (!it_has_error)
            {
                face->IndexArray.Resize(count);
                for (uint32 i=0;i<count;++i)
                {
                    Index& index = face->IndexArray[i];
                    index.VertexIndex = 0;
                    index.TexCoordIndex = 0;
                    index.NormalIndex = 0;

                    if (data.GetNextWord(value, offset, tokens)
                        && value.GetLength()>0)
                    {
                        index.VertexIndex = value.GetInteger();
                    }
                    else
                    {
                        it_has_error = true;
                    }

                    if (component_count>1 && offset>0 && offset<(int32)data.GetLength()
                        && (data[offset]!='/' || data[offset-1]!='/'))
                    {
                        if (data.GetNextWord(value, offset, tokens))
                        {
                            if (value.GetLength()>0)
                            {
                                index.TexCoordIndex = value.GetInteger();
                            }
                        }
                        else
                        {
                            it_has_error = true;
                        }
                    }

                    if (component_count>2)
                    {
                        if (data.GetNextWord(value, offset, tokens))
                        {
                            if (value.GetLength()>0)
                            {
                                index.NormalIndex = value.GetInteger();
                            }
                        }
                        else
                        {
                            it_has_error = true;
                        }
                    }
                }
            }
            for (uint32 i=0 ; i<count ; ++i)
            {
                if (face->IndexArray[i].VertexIndex<0)
                    face->IndexArray[i].VertexIndex = (int32)VertexArray.GetSize() + face->IndexArray[i].VertexIndex + 1;
                if (component_count>1 && face->IndexArray[i].TexCoordIndex<0)
                    face->IndexArray[i].TexCoordIndex = (int32)TexCoordArray.GetSize() + face->IndexArray[i].TexCoordIndex + 1;
                if (component_count>2 && face->IndexArray[i].NormalIndex<0)
                    face->IndexArray[i].NormalIndex = (int32)NormalArray.GetSize() + face->IndexArray[i].NormalIndex + 1;
            }
            if (count<3 || it_has_error)
            {
                COFFEE_Delete(face);
            }
            else if (count==3)
            {
                _CurrentSurface->FaceArray.AddItem(face);
            }
            else
            {
                for (uint32 i=0 ; i<count-2 ; ++i)
                {
                    Face* new_face = COFFEE_New(Face);
                    new_face->IndexArray.Resize(3);
                    new_face->IndexArray[0] = face->IndexArray[0];
                    new_face->IndexArray[1] = face->IndexArray[i+1];
                    new_face->IndexArray[2] = face->IndexArray[i+2];
                    _CurrentSurface->FaceArray.AddItem(new_face);
                }
                COFFEE_Delete(face);
            }
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool MeshOBJFile::_ParseObject(basic::String& line)
    {
        if (line.IsPrefixed("o ") && line.GetLength()>2)
        {
            _PushObject();
            _RequireObject(line.GetBuffer()+2);
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool MeshOBJFile::_ParseGroup(basic::String& line)
    {
        if (line.IsPrefixed("g ") && line.GetLength()>2)
        {
            _PushObject();
            _RequireObject(line.GetBuffer()+2);
        }
        else if (line.IsPrefixed("g"))
        {
            _PushObject();
            _RequireObject();
        }
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    bool MeshOBJFile::_ParseMaterial(basic::String& line)
    {
        if (line.IsPrefixed("usemtl") && line.GetLength()>7)
        {
            basic::String material(line.GetBuffer()+7);
            _PushSurface();
            _RequireSurface(material);
        }
        return true;
    }

}
}
