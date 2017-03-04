#include "kernel/meta/serializer/meta_serializer.h"
#include "kernel/core/core.h"
#include "kernel/meta/meta_object.h"
#include "kernel/meta/meta_types.h"
#include "kernel/meta/type/class/meta_class.h"
#include "kernel/meta/type/scalar/meta_scalar.h"
#include "kernel/meta/array/meta_array.h"
#include "kernel/basic/container/basic_containers.h"
#include "kernel/basic/alpha/basic_alpha.h"
#include "kernel/storage/storage.h"
#include "kernel/shell/shell.h"

namespace coffee
{
namespace meta
{
    //-TYPES--------------------------------------------------------------------------------------//

    //--------------------------------------------------------------------------------------------//
    /// Serialized object identifiers
    //--------------------------------------------------------------------------------------------//
    struct Serializer::SObject
    {
        Type* _Type;
        void* _Object;
        uint32 _Identifier;
        
        SObject() :
            _Type(NULL),
            _Object(NULL),
            _Identifier(NONE)
        {
        }
    };

    //--------------------------------------------------------------------------------------------//
    /// Serialized pointer identifiers
    //--------------------------------------------------------------------------------------------//
    struct Serializer::SPointer
    {
        void** _Address;
        uint32 _Identifier;

        SPointer() :
            _Address(NULL),
            _Identifier(NONE)
        {
        }
    };

    //--------------------------------------------------------------------------------------------//
    /// Serialized weak pointer identifiers
    //--------------------------------------------------------------------------------------------//
    struct Serializer::SWeakPointer
    {
        SWeakPointer() {};
        size_t _Offset;
        void* _Object;
    };

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Serializer::Serializer() :
        _ItIsProcessing(false),
        _Objects(COFFEE_New(basic::Rope<Object*>)),
        _ProcessingObjects(COFFEE_New(basic::Rope<SObject*>)),
        _ProcessedObjects(COFFEE_New(basic::Rope<SObject*>)),
        _Pointers(COFFEE_New(basic::Rope<SPointer*>)),
        _WeakPointers(COFFEE_New(basic::Rope<SWeakPointer*>))
    {
    }

    //--------------------------------------------------------------------------------------------//

    Serializer::~Serializer()
    {
        for(uint32 index=0 ; index<_WeakPointers->GetSize() ; ++index)
            COFFEE_Delete((*_WeakPointers)[index]);
        COFFEE_Delete(_WeakPointers);
        for(uint32 index=0 ; index<_Pointers->GetSize() ; ++index)
            COFFEE_Delete((*_Pointers)[index]);
        COFFEE_Delete(_Pointers);
        for(uint32 index=0 ; index<_ProcessedObjects->GetSize() ; ++index)
            COFFEE_Delete((*_ProcessedObjects)[index]);
        COFFEE_Delete(_ProcessedObjects);
        for(uint32 index=0 ; index<_ProcessingObjects->GetSize() ; ++index)
            COFFEE_Delete((*_ProcessingObjects)[index]);
        COFFEE_Delete(_ProcessingObjects);
        COFFEE_Delete(_Objects);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Serializer::Serialize(meta::Object& object, Stream& stream)
    {
        COFFEE_Assert(!_ItIsProcessing, core::ERROR_CODE_IncorrectUsage,
            "Can't be called during serialization");
        _ItIsProcessing = true;

        stream._Serializer = this;
        _RootObject = &object;
        _RegisterPointer(stream, &object, object.GetMetaType());

        while (_ProcessingObjects->GetSize()>0 && _Process(stream));
        
        _ProcessPointers(stream);
        
        for (int32 i=((int32)_Objects->GetSize())-1 ; i>=0 ; --i)
            (*_Objects)[i]->PostSerialize(stream.GetMode());
    }

    //--------------------------------------------------------------------------------------------//

    void Serializer::SerializeObject(Stream& stream, Object& object)
    {
        _RegisterObject(stream, &object, object.GetMetaType());
        _Objects->AddItem(&object);
        void* root_object = stream.GetRootObject();
        ulong_ptr offset = stream.GetObjectOffset();
        stream.SetObject(&object);
        object.PreSerialize(stream.GetMode());
        object.Serialize(stream);
        stream.SetObject(root_object);
        stream.SetObjectOffset(offset);
    }

    //--------------------------------------------------------------------------------------------//

    void Serializer::SerializeObjectFromType(Stream& stream, Type& type)
    {
        _RegisterObject(stream, stream.GetObject(), type);
        type.Serialize(stream);
    }
    
    //--------------------------------------------------------------------------------------------//

    void Serializer::SerializePointer(Stream& stream, Attribute& attribute)
    {
        uint32 identifier;
        void** address = (void**)stream.GetObject();

        switch(stream.GetMode())
        {
            case storage::MODE_Input:
            {
                stream.GetStream().Pop(&identifier, sizeof(uint32));

                if (!attribute._ItIsWeak)
                {
                    COFFEE_Assert(*address==NULL, core::ERROR_CODE_MetaSystem,
                        "Loading into a non-empty pointer !");
                }

                if (identifier==NONE)
                {
                    *address = NULL;
                }
                else
                {
                    _RegisterPointer(stream, NULL, *attribute._Type, identifier,
                        address, attribute._ItIsWeak);
                }
            } break;

            case storage::MODE_Output:
            {
                if (*address==NULL)
                {
                    identifier = NONE;
                }
                else
                {
                    identifier = _RegisterPointer(stream, *address,
                        ((meta::Object*)*address)->GetMetaType(), NONE, NULL, attribute._ItIsWeak);
                }
                stream.GetStream().Push(&identifier, sizeof(uint32));
            } break;
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Serializer::SerializeArray(Stream& stream, meta::Attribute& attribute)
    {
        void* object = stream.GetRootObject();
        ulong_ptr offset = stream.GetObjectOffset();
        Array* array = (Array*) stream.GetObject();
        uint32 size;
        
        if (stream.GetMode()==storage::MODE_Output)
            size = array->GetSize();
        
        stream.SetObject(&size);
        TYPE<uint32>().Get().Serialize(stream);
        stream.SetObject(object);
        stream.SetObjectOffset(offset);

        if (stream.GetMode()==storage::MODE_Input)
        {
            COFFEE_Assert(array->IsEmpty() || !attribute._ItIsPointer,
                core::ERROR_CODE_Unexpected, "Loading into a non-empty array !");

            if (array->GetSize()!=size)
                array->Resize(size);
        }

        void* array_buffer = array->GetLinearBuffer();
        stream.SetObject(array_buffer);

        if (array_buffer!=NULL && attribute._Type->GetInfo()==TYPE_INFO_Scalar)
        {
            Scalar& meta_type = *static_cast<Scalar*>(attribute._Type);

            if (stream.GetMode()==storage::MODE_Output)
            {
                stream.GetStream().Push(stream.GetObject(), meta_type.GetSize()*array->GetSize());
            }
            else
            {
                stream.GetStream().Pop(stream.GetObject(), meta_type.GetSize()*array->GetSize());
            }
        }
        else
        {
            for (uint32 item_index=0 ; item_index<array->GetSize() ; ++item_index)
            {
                stream.SetObject(array->GetItemPointer(item_index));
                if (attribute._ItIsPointer)
                {
                    SerializePointer(stream, attribute);
                }
                else if (attribute._Type->GetInfo()==TYPE_INFO_Class)
                {
                    _RegisterObject(stream, stream.GetObject(), *attribute._Type);
                    SerializeObject(stream, *(Object*)stream.GetObject());
                }
                else if (attribute._Type->GetInfo()==TYPE_INFO_Scalar)
                {
                    SerializeObjectFromType(stream, *attribute._Type);
                }
            }
        }

        stream.SetObject(object);
        stream.SetObjectOffset(offset);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Serializer::_RegisterObject(Stream& stream, void* object, Type& type)
    {
        if (_ProcessedObjects->GetSize()>0 && (*_ProcessedObjects)[_ProcessedObjects->GetSize()-1]->_Object==object)
            return;

        SObject* processed_object = COFFEE_New(SObject);
        processed_object->_Type = &type;
        processed_object->_Object = object;

        if (stream.GetMode()==storage::MODE_Output)
            processed_object->_Identifier = _ProcessingObjects->GetSize()+_ProcessedObjects->GetSize()+1;
        
        COFFEE_SerializeScalar(&processed_object->_Identifier, uint32);
        _ProcessedObjects->AddItem(processed_object);
    }
       
    //--------------------------------------------------------------------------------------------//

    uint32 Serializer::_RegisterPointer(Stream& stream, void* object, Type& type, uint32 identifier,
        void** address, bool it_is_weak)
    {
        COFFEE_Assert((object!=NULL) || (identifier!=NONE), core::ERROR_CODE_MetaSystem,
            "Unexpected error");

        if (object==NULL)
        {
            COFFEE_Assert(stream.GetMode()==storage::MODE_Input, core::ERROR_CODE_MetaSystem,
                "Unexpected error");

            SPointer* pointer = COFFEE_New(SPointer);
            pointer->_Address = address;
            pointer->_Identifier = identifier;
            _Pointers->AddItem(pointer);

            for (uint32 index=0 ; index<_ProcessingObjects->GetSize() ; ++index)
                if (identifier==(*_ProcessingObjects)[index]->_Identifier)
                    return identifier;
            
            for (uint32 index=0 ; index<_ProcessedObjects->GetSize() ; ++index)
                if (identifier==(*_ProcessedObjects)[index]->_Identifier)
                    return identifier;
        }
        else
        {
            for (uint32 index=0 ; index<_ProcessingObjects->GetSize() ; ++index)
                if (object==(*_ProcessingObjects)[index]->_Object)
                    return (*_ProcessingObjects)[index]->_Identifier;
            
            for (uint32 index=0 ; index<_ProcessedObjects->GetSize() ; ++index)
                if (object==(*_ProcessedObjects)[index]->_Object)
                    return (*_ProcessedObjects)[index]->_Identifier;
        }            
        
        if (!it_is_weak)
        {
            SObject* processing_object = COFFEE_New(SObject);
            processing_object->_Type = &type;
            processing_object->_Object = object;
            processing_object->_Identifier = identifier!=NONE?identifier
                :_ProcessingObjects->GetSize()+_ProcessedObjects->GetSize()+1;
            _ProcessingObjects->AddItem(processing_object);
            return processing_object->_Identifier;
        }

        if (stream.GetMode()==storage::MODE_Output)
        {
            SWeakPointer* pointer = COFFEE_New(SWeakPointer);
            pointer->_Offset = (size_t)stream.GetStream().GetData().GetSize();
            pointer->_Object = object;
            _WeakPointers->AddItem(pointer);
        }
        return identifier;
    }

    //--------------------------------------------------------------------------------------------//

    bool Serializer::_Process(Stream& stream)
    {
        void* object = stream.GetRootObject();
        ulong_ptr offset = stream.GetObjectOffset();
        uint32 identifier = NONE;
        uint32 size = 0;
        size_t size_offset;

        SObject* sobject = (*_ProcessingObjects)[0];

        if (stream.GetMode()==storage::MODE_Output)
            identifier = sobject->_Identifier;

        COFFEE_SerializeScalar(&identifier, uint32);
        COFFEE_SerializeScalar(&size, uint32);

        if (stream.GetMode()==storage::MODE_Output)
        {
            size_offset = (size_t)stream.GetStream().GetData().GetSize()-sizeof(uint32);
        }
        else
        {
            // Skip objects till correct identifier is found
            // Note it means those objects need to be removed (ex: pointer attribute removed)
            while (identifier!=sobject->_Identifier)
            {
                if (stream.GetStream().Pop(size)==NULL
                    || stream.GetStream().IsOver())
                {
                    COFFEE_Error(core::ERROR_CODE_MetaSystem, "File is corrupted");
                    return false;
                }
                COFFEE_SerializeScalar(&identifier, uint32);
                COFFEE_SerializeScalar(&size, uint32);
            }            
        }
        
        _ProcessingObjects->Remove(0);
        _ProcessedObjects->AddItem(sobject);

        if (stream.GetMode()==storage::MODE_Output)
        {
            if (sobject->_Type->GetInfo()==TYPE_INFO_Scalar)
            {
                stream.SetObject(sobject->_Object);
                sobject->_Type->Serialize(stream);
            }
            else
            {
                stream.GetStream().PushString(sobject->_Type->GetName());
                SerializeObject(stream, *(Object*)sobject->_Object);
            }
        }

        if (stream.GetMode()==storage::MODE_Input)
        {
            if (sobject->_Type->GetInfo()==TYPE_INFO_Scalar)
            {
                Object* new_object = sobject->_Type->CreateObject();
                stream.SetObject((void*)new_object);
                sobject->_Object = (void*)new_object;
                sobject->_Type->Serialize(stream);
            }
            else
            {
                basic::String type_name;
                stream.GetStream().PopString(type_name);

                meta::Type* type = COFFEE_FindType(type_name);
                COFFEE_Assert(type!=NULL, core::ERROR_CODE_MetaSystem, "Invalid meta type");
                Object* new_object;
                if (sobject->_Object!=NULL)
                {
                    COFFEE_Assert(sobject->_Identifier==1, core::ERROR_CODE_MetaSystem, "Failed to serialize objects");
                    COFFEE_Assert(sobject->_Object==(void*)_RootObject, core::ERROR_CODE_MetaSystem, "Failed to serialize objects");
                    new_object = _RootObject;
                }
                else
                {
                    new_object = type->CreateObject();
                    sobject->_Object = (void*)new_object;
                }
                SerializeObject(stream, *new_object);
            }
        }
        
        if (stream.GetMode()==storage::MODE_Output)
        {
            // Update object size in the stream
            *(uint32*)(stream.GetStream().GetData().GetBuffer()+size_offset) =
                (uint32)((size_t)stream.GetStream().GetData().GetSize()-size_offset-sizeof(uint32));
        }
        
        stream.SetObject(object);
        stream.SetObjectOffset(offset);
        return true;
    }

    //--------------------------------------------------------------------------------------------//

    void Serializer::_ProcessPointers(Stream& stream)
    {
        // Assign processed objects to pointers, when stream is in input mode
        for (uint32 index=0 ; index<_Pointers->GetSize() ; ++index)
        {
            bool found(false);
            for (uint32 i=0 ; i<_ProcessedObjects->GetSize() ; ++i)
            {
                COFFEE_Assert((*_ProcessedObjects)[i]->_Object!=NULL, core::ERROR_CODE_MetaSystem,
                    "Unexpected error");
                if ((*_Pointers)[index]->_Identifier==(*_ProcessedObjects)[i]->_Identifier)
                {
                    *(*_Pointers)[index]->_Address = (*_ProcessedObjects)[i]->_Object;
                    found = true;
                    break;
                }
            }
            COFFEE_Assert(found, core::ERROR_CODE_MetaSystem, "Unexpected error");
        }

        // Write pointed objects identifier, when stream is in output mode
        for (uint32 index=0 ; index<_WeakPointers->GetSize() ; ++index)
        {
            uint32 identifier = NONE;
            for (uint32 i=0 ; i<_ProcessedObjects->GetSize() ; ++i)
            {
                COFFEE_Assert((*_ProcessedObjects)[i]->_Object!=NULL, core::ERROR_CODE_MetaSystem,
                    "Unexpected error");
                if ((*_WeakPointers)[index]->_Object==(*_ProcessedObjects)[i]->_Object)
                {
                    identifier = (*_ProcessedObjects)[i]->_Identifier;
                    break;
                }
            }
            *(uint32*)(stream.GetStream().GetData().GetBuffer()+(*_WeakPointers)[index]->_Offset) = identifier;
        }
    }

}
}
