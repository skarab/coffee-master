#ifndef _EDITOR_ASSET_MESH_OBJ_FILE_H_
#define _EDITOR_ASSET_MESH_OBJ_FILE_H_

#include "coffee_editor_includes.h"

namespace coffee_editor
{
namespace asset
{
    //--------------------------------------------------------------------------------------------//
    /// OBJ file
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API MeshOBJFile
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        MeshOBJFile();
        ~MeshOBJFile();

        //-OPERATIONS-----------------------------------------------------------------------------//

        bool Load(storage::Stream& data_stream);

        //-TYPES----------------------------------------------------------------------------------//

        class Index
        {
        public:
            Index() {}
            bool operator==(const Index&) const { return false; }
            int32 VertexIndex;
            int32 TexCoordIndex;
            int32 NormalIndex;
            uint32 ID;
        };

        class Face
        {
        public:
            bool operator==(const Face&) const { return false; }
            basic::Vector<Index> IndexArray;
        };

        struct Surface
        {
            basic::String Material;
            basic::Prow<Face*, true> FaceArray;
        };

        struct Object
        {
            basic::String Name;
            basic::Prow<Surface*, true> SurfaceArray;
        };

        class VertexRef
        {
        public:
            VertexRef() {}
            bool operator==(const VertexRef&) const { return false; }
            int32 TexCoordIndex;
            int32 NormalIndex;
            uint32 ID;
        };

        class GenIndex
        {
        public:
            GenIndex() {}
            bool operator==(const GenIndex&) const { return false; }
            basic::Rope<VertexRef> *Refs;
        };

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Rope<GenIndex> IndexArray;
        basic::Rope<basic::Vector3, 64> VertexArray;
        basic::Rope<basic::Vector2, 64> TexCoordArray;
        basic::Rope<basic::Vector3, 64> NormalArray;
        basic::Prow<Object*, true> ObjectArray;
        
    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _RequireObject(basic::String name="object");
        void _PushObject();
        void _RequireSurface(basic::String material="default");
        void _PushSurface();
        bool _ParseVertex(basic::String& line);
        bool _ParseFace(basic::String& line);
        bool _ParseObject(basic::String& line);
        bool _ParseGroup(basic::String& line);
        bool _ParseMaterial(basic::String& line);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Object* _CurrentObject;
        Surface* _CurrentSurface;
    };
}
}
#endif
