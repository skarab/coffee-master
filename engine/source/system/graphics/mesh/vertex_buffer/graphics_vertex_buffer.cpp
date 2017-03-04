#include "system/graphics/mesh/vertex_buffer/graphics_vertex_buffer.h"
#include "system/graphics/device/graphics_device.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(graphics::VertexBuffer);
        COFFEE_Attribute(uint32, _Type, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(uint32, _Mode, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(uint32, _ComponentType, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(uint32, _ComponentCount, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(uint32, _ObjectCount, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(basic::Array<int8>, _Data, meta::MODE_Serializeable);
    COFFEE_EndType();

namespace graphics
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    VertexBuffer::VertexBuffer() :
        _Type(VERTEX_BUFFER_TYPE_None),
        _Mode(VERTEX_BUFFER_MODE_Read),
        _ComponentType(meta::SCALAR_FORMAT_Real),
        _ComponentCount(0),
        _ComponentSize(0),
        _ObjectCount(0),
        _ObjectSize(0),
        _ItIsCreated(false)
    {
    }

    //--------------------------------------------------------------------------------------------//

    VertexBuffer::~VertexBuffer()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void VertexBuffer::SetComponentType(meta::SCALAR_FORMAT scalar_format)
    {
        _ComponentType = scalar_format;
        _UpdateData();
    }

    //--------------------------------------------------------------------------------------------//

    void VertexBuffer::SetComponentCount(uint32 component_count)
    {
        _ComponentCount = component_count;
        _UpdateData();
    }

    //--------------------------------------------------------------------------------------------//

    void VertexBuffer::SetObjectCount(uint32 object_count)
    {
        _ObjectCount = object_count;
        _UpdateData();
    }

    //--------------------------------------------------------------------------------------------//

    const void* VertexBuffer::GetObject(uint32 object_index) const
    {
        return (const void*)((ulong_ptr) _Data.GetLinearBuffer() + object_index * _ObjectSize);
    }

    //--------------------------------------------------------------------------------------------//

    void* VertexBuffer::GetObject(uint32 object_index)
    {
        return (void*)((ulong_ptr) _Data.GetLinearBuffer() + object_index * _ObjectSize);
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool VertexBuffer::IsEmpty() const
    {
        return _Data.GetSize()==0;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void VertexBuffer::Create()
    {
        if (!IsEmpty())
        {
            _UpdateComponentType();
            EnableMode(VERTEX_BUFFER_MODE_Write, false);

            if (!IsModeEnabled(VERTEX_BUFFER_MODE_Write))
            {
                glGenBuffersARB(1, &_Index);
                glBindBufferARB(GL_ARRAY_BUFFER_ARB, _Index);
                glBufferDataARB(GL_ARRAY_BUFFER_ARB, _ObjectCount * _ObjectSize, GetData(), GL_STATIC_DRAW_ARB);
                glBindBufferARB(GL_ARRAY_BUFFER_ARB, 0);
            }
            _ItIsCreated = true;
        }
    }

    //--------------------------------------------------------------------------------------------//

    void VertexBuffer::Destroy()
    {
        if (!IsEmpty())
        {
            if (!IsModeEnabled(VERTEX_BUFFER_MODE_Write))
                glDeleteBuffersARB(1, &_Index);
            _ItIsCreated = false;
        }
    }

    //--------------------------------------------------------------------------------------------//

    void VertexBuffer::Bind()
    {
        if (IsEmpty())
            return;

        switch(_Type)
        {
            case VERTEX_BUFFER_TYPE_Index:
            {
                if (!IsModeEnabled(VERTEX_BUFFER_MODE_Write))
                {
                    COFFEE_GRAPHICS_Debug();
                    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, _Index);
                    glDrawElements(GL_TRIANGLES, _ObjectCount*_ComponentCount, _GLComponentType, 0);
                    COFFEE_GRAPHICS_Debug();
                }
                else
                {
                    COFFEE_GRAPHICS_Debug();
                    glDrawElements(GL_TRIANGLES, _ObjectCount*_ComponentCount, _GLComponentType, GetData());
                    COFFEE_GRAPHICS_Debug();
                }
            } break;

            case VERTEX_BUFFER_TYPE_Position:
            {
                glEnableClientState(GL_VERTEX_ARRAY);

                if (!IsModeEnabled(VERTEX_BUFFER_MODE_Write))
                {
                    glBindBufferARB(GL_ARRAY_BUFFER_ARB, _Index);
                    glVertexPointer(_ComponentCount, _GLComponentType, 0, 0);
                }
                else
                {
                    glVertexPointer(_ComponentCount, _GLComponentType, 0, GetData());
                }
            } break;

            case VERTEX_BUFFER_TYPE_Color:
            {
                glEnableClientState(GL_COLOR_ARRAY);

                if (!IsModeEnabled(VERTEX_BUFFER_MODE_Write))
                {
                    glBindBufferARB(GL_ARRAY_BUFFER_ARB, _Index);
                    glColorPointer(_ComponentCount, _GLComponentType, 0, 0);
                }
                else
                {
                    glColorPointer(_ComponentCount, _GLComponentType, 0, GetData());
                }
            } break;

            case VERTEX_BUFFER_TYPE_Normal:
            {
                glEnableClientState(GL_NORMAL_ARRAY);

                if (!IsModeEnabled(VERTEX_BUFFER_MODE_Write))
                {
                    glBindBufferARB(GL_ARRAY_BUFFER_ARB, _Index);
                    glNormalPointer(_GLComponentType, _ObjectSize, 0);
                }
                else
                {
                    glNormalPointer(_GLComponentType, _ObjectSize, GetData());
                }
            } break;

            case VERTEX_BUFFER_TYPE_STangent:
            {
                glClientActiveTexture(GL_TEXTURE1);
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);

                if (!IsModeEnabled(VERTEX_BUFFER_MODE_Write))
                {
                    glBindBufferARB(GL_ARRAY_BUFFER_ARB, _Index);
                    glTexCoordPointer(_ComponentCount, _GLComponentType, 0, 0);
                }
                else
                {
                    glTexCoordPointer(_ComponentCount, _GLComponentType, 0, GetData());
                }
            } break;

            case VERTEX_BUFFER_TYPE_TTangent:
            {
                glClientActiveTexture(GL_TEXTURE2);
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);

                if (!IsModeEnabled(VERTEX_BUFFER_MODE_Write))
                {
                    glBindBufferARB(GL_ARRAY_BUFFER_ARB, _Index);
                    glTexCoordPointer(_ComponentCount, _GLComponentType, 0, 0);
                }
                else
                {
                    glTexCoordPointer(_ComponentCount, _GLComponentType, 0, GetData());
                }
            } break;

            case VERTEX_BUFFER_TYPE_TexCoord:
            {
                glClientActiveTexture(GL_TEXTURE0);
                glEnableClientState(GL_TEXTURE_COORD_ARRAY);

                if (!IsModeEnabled(VERTEX_BUFFER_MODE_Write))
                {
                    glBindBufferARB(GL_ARRAY_BUFFER_ARB, _Index);
                    glTexCoordPointer(_ComponentCount, _GLComponentType, 0, 0);
                }
                else
                {
                    glTexCoordPointer(_ComponentCount, _GLComponentType, 0, GetData());
                }
            } break;

            case VERTEX_BUFFER_TYPE_Adjacency:
            {
                if (!IsModeEnabled(VERTEX_BUFFER_MODE_Write))
                {
                    glBindBufferARB(GL_ELEMENT_ARRAY_BUFFER_ARB, _Index);
                    glDrawElements(GL_TRIANGLES_ADJACENCY_EXT, _ObjectCount*_ComponentCount, _GLComponentType, 0);
                }
                else
                {
                    glDrawElements(GL_TRIANGLES_ADJACENCY_EXT, _ObjectCount*_ComponentCount, _GLComponentType, GetData());
                }
            } break;

            default:
                break;
        };
    }

    //--------------------------------------------------------------------------------------------//

    void VertexBuffer::UnBind()
    {
        if (IsEmpty())
            return;

        switch(_Type)
        {
            case VERTEX_BUFFER_TYPE_Index:
            case VERTEX_BUFFER_TYPE_Adjacency:
                break;

            case VERTEX_BUFFER_TYPE_Position:
                glDisableClientState(GL_VERTEX_ARRAY);
                break;

            case VERTEX_BUFFER_TYPE_Color:
                glDisableClientState(GL_COLOR_ARRAY);
                break;

            case VERTEX_BUFFER_TYPE_Normal:
                glDisableClientState(GL_NORMAL_ARRAY);
                break;

            case VERTEX_BUFFER_TYPE_STangent:
                glClientActiveTexture(GL_TEXTURE1);
                glDisableClientState(GL_TEXTURE_COORD_ARRAY);
                break;

            case VERTEX_BUFFER_TYPE_TTangent:
                glClientActiveTexture(GL_TEXTURE2);
                glDisableClientState(GL_TEXTURE_COORD_ARRAY);
                break;

            case VERTEX_BUFFER_TYPE_TexCoord:
                glClientActiveTexture(GL_TEXTURE0);
                glDisableClientState(GL_TEXTURE_COORD_ARRAY);
                break;

            default:
                break;
        }
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void VertexBuffer::_UpdateData()
    {
        _ComponentSize = meta::SCALAR_FORMAT_GetFormatSize(_ComponentType);
        _ObjectSize = _ComponentSize * _ComponentCount;
        _Data.Resize(_ObjectCount * _ObjectSize);
    }
    
    //--------------------------------------------------------------------------------------------//

    void VertexBuffer::_UpdateComponentType()
    {
        switch(_ComponentType)
        {
            case meta::SCALAR_FORMAT_Real:
                _GLComponentType = GL_FLOAT;
                break;

            case meta::SCALAR_FORMAT_UInt8:
                _GLComponentType = GL_UNSIGNED_BYTE;
                break;

            case meta::SCALAR_FORMAT_UInt16:
                _GLComponentType = GL_UNSIGNED_SHORT;
                break;

            case meta::SCALAR_FORMAT_UInt32:
                _GLComponentType = GL_UNSIGNED_INT;
                break;

            case meta::SCALAR_FORMAT_Int8:
                _GLComponentType = GL_BYTE;
                break;

            case meta::SCALAR_FORMAT_Int16:
                _GLComponentType = GL_SHORT;
                break;

            case meta::SCALAR_FORMAT_Int32:
                _GLComponentType = GL_INT;
                break;

            default:
                COFFEE_Error(core::ERROR_CODE_GraphicsDriver, "Failed to initialize vertex buffer object");
        };

        _ComponentSize = meta::SCALAR_FORMAT_GetFormatSize(_ComponentType);
        _ObjectSize = _ComponentSize * _ComponentCount;
    }

}
}
