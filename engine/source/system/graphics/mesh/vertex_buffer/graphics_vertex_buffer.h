#ifndef _COFFEE_GRAPHICS_VERTEX_BUFFER_H_
#define _COFFEE_GRAPHICS_VERTEX_BUFFER_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "system/graphics/mesh/vertex_buffer/graphics_vertex_buffer_type.h"
#include "system/graphics/mesh/vertex_buffer/graphics_vertex_buffer_mode.h"

namespace coffee
{
namespace graphics
{
    //--------------------------------------------------------------------------------------------//
    /// Graphics Vertex Buffer
    ///
    /// A vertex buffer is a container for some kind of vertex parameter, used by the Mesh class.
    /// Internally, it'll use VBO or VertexArrays depending of the required access mode.
    ///
    /// @see coffee::graphics::MeshChunk
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API VertexBuffer : public meta::Object
    {
        COFFEE_Type(VertexBuffer);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        VertexBuffer();
        virtual ~VertexBuffer();

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetType(const VERTEX_BUFFER_TYPE& type) { _Type = type; }
        VERTEX_BUFFER_TYPE GetType() const { return _Type; }
        void EnableMode(VERTEX_BUFFER_MODE mode, bool it_has_to_enable) { COFFEE_EnableFlag(_Mode, mode, it_has_to_enable); }
        bool IsModeEnabled(VERTEX_BUFFER_MODE mode) { return COFFEE_IsFlagEnabled(_Mode, mode); }
        void SetComponentType(meta::SCALAR_FORMAT scalar_format);
        meta::SCALAR_FORMAT GetComponentType() const { return _ComponentType; }
        void SetComponentCount(uint32 component_count);
        uint32 GetComponentCount() const { return _ComponentCount; }
        void SetObjectCount(uint32 object_count);
        uint32 GetObjectCount() const { return _ObjectCount; }
        const void* GetObject(uint32 object_index) const;
        void* GetObject(uint32 object_index);
        const void* GetData() const { return _Data.GetLinearBuffer(); }
        void* GetData() { return _Data.GetLinearBuffer(); }

        //-QUERIES--------------------------------------------------------------------------------//

        bool IsEmpty() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void Create();
        void Destroy();
        void Bind();
        void UnBind();

    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _UpdateData();
        void _UpdateComponentType();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        bool _ItIsCreated;
        VERTEX_BUFFER_TYPE _Type;
        uint32 _Mode;
        meta::SCALAR_FORMAT _ComponentType;
        uint32 _ComponentSize;
        uint32 _ComponentCount;
        uint32 _ObjectCount;
        uint32 _ObjectSize;
        basic::Array<int8> _Data;
        uint32 _Index;
        uint32 _GLComponentType;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, VertexBuffer);
}
}
#endif
