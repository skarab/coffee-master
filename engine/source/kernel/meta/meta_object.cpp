#include "kernel/meta/meta_object.h"
#include "kernel/meta/meta_types.h"
#include "kernel/core/core.h"
#include "kernel/storage/logical/storage_path.h"
#include "kernel/basic/container/array/basic_array.h"

namespace coffee
{
namespace meta
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Object::Object()
    {
    }

    //--------------------------------------------------------------------------------------------//

    Object::~Object()
    {
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    bool Object::operator == (const Object& object) const
    {
        return false;
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const Class& Object::GetMetaType() const
    {
        COFFEE_Assert(Types::IsInstantiated(), core::ERROR_CODE_MetaSystem, "Null type isnt available");
        return Types::Get().GetNullClassType();
    }

    //--------------------------------------------------------------------------------------------//

    Class& Object::GetMetaType()
    {
        COFFEE_Assert(Types::IsInstantiated(), core::ERROR_CODE_MetaSystem, "Null type isnt available");
        return Types::Get().GetNullClassType();
    }

    //--------------------------------------------------------------------------------------------//

    Class& Object::GetClassMetaType()
    {
        COFFEE_Assert(Types::IsInstantiated(), core::ERROR_CODE_MetaSystem, "Null type isnt available");
        return Types::Get().GetNullClassType();
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool Object::Serialize(storage::Path file_path, storage::MODE mode)
    {
        coffee::meta::Stream stream;
        if (stream.Open(file_path, mode))
        {
            Serializer* serializer = COFFEE_New(Serializer);
            serializer->Serialize(*this, stream);
            COFFEE_Delete(serializer);
            stream.Close();
            return true;
        }
        return false;
    }

    //--------------------------------------------------------------------------------------------//

    void Object::Serialize(Stream& stream)
    {
        GetMetaType().Serialize(stream);
    }

    //--------------------------------------------------------------------------------------------//

    Object* Object::Clone()
    {
        Object* object = GetMetaType().CreateObject();
        object->Copy(*this);
        return object;
    }
    
    //--------------------------------------------------------------------------------------------//

    void Object::Copy(Object& object)
    {
        COFFEE_Assert(&object.GetMetaType()==&GetMetaType(),
            coffee::core::ERROR_CODE_IncorrectUsage, "Cant copy objects of different types."); \
    
        meta::Stream stream;
        stream.DisableEncoder();

        stream.Open(storage::MODE_Output);
        meta::Serializer* serializer = COFFEE_New(Serializer);
        serializer->Serialize(object, stream);
        COFFEE_Delete(serializer);
        stream.Close();

        stream.Open(storage::MODE_Input);
        serializer = COFFEE_New(Serializer);
        serializer->Serialize(*this, stream);
        COFFEE_Delete(serializer);
        stream.Close();
    }

    //--------------------------------------------------------------------------------------------//

    Object* Object::CastObject(void* object) const
    {
        return (Object*)object;
    }

    //--------------------------------------------------------------------------------------------//

    void Object::SerializeToArray(basic::Array<uint8>& array, storage::MODE mode)
    {
        meta::Stream stream;

        if (mode==storage::MODE_Input)
        {
            if (array.GetSize()==0)
                return;

            stream.GetStream().SetData(COFFEE_New(storage::Data));
            stream.GetStream().GetData().Resize(array.GetSize());
            COFFEE_Copy(stream.GetStream().GetData().GetBuffer(), array.GetLinearBuffer(), array.GetSize());
        }
        
        stream.Open(mode);
        meta::Serializer* serializer = COFFEE_New(meta::Serializer);
        serializer->Serialize(*this, stream);
        COFFEE_Delete(serializer);
        stream.Close();

        if (mode==storage::MODE_Output)
        {
            array.Resize(stream.GetStream().GetData().GetSize());
            COFFEE_Copy(array.GetLinearBuffer(), stream.GetStream().GetData().GetBuffer(), array.GetSize());
        }
    }

}
}
