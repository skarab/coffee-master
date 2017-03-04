#include "kernel/meta/info/meta_object_info.h"
#include "kernel/basic/container/basic_containers.h"
#include "kernel/resource/property/resource_property_base.h"

namespace coffee
{
namespace meta
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    ObjectInfo::ObjectInfo(Object* object) :
        _Data((void*)object),
        _Type(&object->GetMetaType()),
        _Attribute(NULL),
        _Ancestor(NULL),
        _ItIsArray(false),
        _ResourceProperty(NULL)
    {
        BuildTree();
    }

    //--------------------------------------------------------------------------------------------//

    ObjectInfo::ObjectInfo(void* object_data, Type* object_type,
        Attribute* attribute, Class* ancestor) :
            _Data(object_data),
            _Type(object_type),
            _Attribute(attribute),
            _Ancestor(ancestor),
            _ItIsArray(false),
            _ResourceProperty(NULL)
    {
        BuildTree();
    }

    //--------------------------------------------------------------------------------------------//

    ObjectInfo::~ObjectInfo()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void ObjectInfo::SetName(const basic::String & name)
    {
        _Name = name;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::String & ObjectInfo::GetName() const
    {
        if(!_Name.IsEmpty())
            return _Name;

        if(IsAttribute())
            return *_Attribute->_Name;

        return _Type->GetName();
    }

    //--------------------------------------------------------------------------------------------//

    const void * ObjectInfo::GetData() const
    {
        return _Data;
    }

    //--------------------------------------------------------------------------------------------//

    void * ObjectInfo::GetData()
    {
        return _Data;
    }

    //--------------------------------------------------------------------------------------------//

    const Type & ObjectInfo::GetType() const
    {
        return *_Type;
    }

    //--------------------------------------------------------------------------------------------//

    Type & ObjectInfo::GetType()
    {
        return *_Type;
    }

    //--------------------------------------------------------------------------------------------//

    void ObjectInfo::SetAttribute(Attribute & attribute)
    {
        _Attribute = &attribute;
    }

    //--------------------------------------------------------------------------------------------//

    const Attribute & ObjectInfo::GetAttribute() const
    {
        return *_Attribute;
    }

    //--------------------------------------------------------------------------------------------//

    void ObjectInfo::SetAncestor(Class& ancestor)
    {
        _Ancestor = &ancestor;
    }

    //--------------------------------------------------------------------------------------------//

    const Class& ObjectInfo::GetAncestor() const
    {
        return *_Ancestor;
    }

    //--------------------------------------------------------------------------------------------//

    void ObjectInfo::SetResourceProperty(resource::PropertyBase * resource_property)
    {
        _ResourceProperty = resource_property;
    }

    //--------------------------------------------------------------------------------------------//

    resource::PropertyBase * ObjectInfo::GetResourceProperty()
    {
        return _ResourceProperty;
    }

    //--------------------------------------------------------------------------------------------//

    const resource::PropertyBase * ObjectInfo::GetResourceProperty() const
    {
        return _ResourceProperty;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool ObjectInfo::IsScalar() const
    {
        return GetType().GetInfo() == meta::TYPE_INFO_Scalar;
    }

    //--------------------------------------------------------------------------------------------//

    bool ObjectInfo::IsClass() const
    {
        return GetType().GetInfo() == meta::TYPE_INFO_Class;
    }

    //--------------------------------------------------------------------------------------------//

    bool ObjectInfo::IsAttribute() const
    {
        return (_Attribute != NULL);
    }

    //--------------------------------------------------------------------------------------------//

    bool ObjectInfo::IsAncestor() const
    {
        return (_Ancestor != NULL);
    }

    //--------------------------------------------------------------------------------------------//

    bool ObjectInfo::IsArray() const
    {
        return _ItIsArray;
    }

    //--------------------------------------------------------------------------------------------//

    bool ObjectInfo::IsResourceProperty() const
    {
        return (_ResourceProperty != NULL);
    }

    //--------------------------------------------------------------------------------------------//

    ObjectInfo * ObjectInfo::FindByNameAndType(const basic::String & name, const Type & type)
    {
        if (IsAttribute() && *GetAttribute()._Name==name && &GetType()==&type)
            return this;

        for (uint32 i=0 ; i<GetChildCount() ; ++i)
        {
            ObjectInfo* object = GetChild(i).FindByNameAndType(name, type);
            if (object != NULL)
                return object;
        }
        return NULL;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ObjectInfo::BuildTree(bool it_is_rebuilding)
    {
        if (IsAttribute())
        {
            if (GetAttribute()._ItIsPointer && !GetAttribute()._ItIsArray && !it_is_rebuilding)
            {
                _Data = (void*) *(Object**)_Data;
            }

            if (GetAttribute()._ItIsArray)
            {
                Array* object_array = (Array*)_Data;

                for (uint32 index=0 ; index<object_array->GetSize() ; ++index)
                {
                    ObjectInfo* object_info;

                    if (!GetAttribute()._ItIsPointer)
                    {
                        object_info = COFFEE_New(ObjectInfo, 
                            object_array->GetItemPointer(index),
                            &GetType());
                    }
                    else
                    {
                        if (object_array->GetItemPointer(index)==NULL)
                            continue;

                        if (GetType().GetInfo()==TYPE_INFO_Scalar)
                        {
                            object_info = COFFEE_New(ObjectInfo, 
                                *((void **) object_array->GetItemPointer(index)),
                                &GetType());
                        }
                        else
                        {
                            Object* object = *((Object **) object_array->GetItemPointer(index));
                            if (object==NULL)
                                continue;

                            object_info = COFFEE_New(ObjectInfo, 
                                *((void **) object_array->GetItemPointer(index)),
                                &object->GetMetaType());
                        }
                    }

                    object_info->SetName(basic::String("%s[ %i ]",
                        GetName().GetBuffer(), index));

                    ParamArray* param = (ParamArray*)GetAttribute()._Param;

                    if(!param->GetAttributeName().IsEmpty())
                    {
                        ObjectInfo* element_object = object_info->FindByNameAndType(
                            param->GetAttributeName(),
                            basic::String::GetClassMetaType());

                        if (element_object!=NULL)
                        {
                            object_info->SetName(*(basic::String*) element_object->GetData());
                        }
                        else
                        {
                            uint32 ancestor_index(0);
                            uint32 attribute_index(0);
                            Attribute * attribute;
                            ulong_ptr attribute_offset;

                            while(((Class &) object_info->GetType()).FindNextAttribute(
                                ancestor_index,
                                attribute_index,
                                &attribute,
                                attribute_offset))
                            {
                                if(attribute->_Type==&basic::String::GetClassMetaType()
                                    && *attribute->_Name==param->GetAttributeName())
                                {
                                    object_info->SetName(
                                        *(basic::String *)((ulong_ptr) object_info->GetData() + attribute_offset));

                                    break;
                                }
                            }
                        }
                    }

                    Attach(*object_info);
                }

                _ItIsArray = true;
            }
        }

        if(_Type->GetInfo() == TYPE_INFO_Class
            && !(IsAttribute() && GetAttribute()._ItIsArray))
        {
            _BuildTreeClass();
        }
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ObjectInfo::_BuildTreeClass()
    {
        uint32 index;
        ObjectInfo * object_info;
        uint32 ancestor_offset = 0;
        Class & object_type = (Class &) *_Type;

        if (object_type.GetAncestor()!=NULL)
        {
            object_info = COFFEE_New(ObjectInfo, 
                (void *) ((ulong_ptr) _Data + ancestor_offset),
                object_type.GetAncestor(),
                (coffee::meta::Attribute*)NULL,
                object_type.GetAncestor());

            Attach(*object_info);
            ancestor_offset += object_type.GetAncestor()->GetSize();
        }

        resource::PropertyBase * resource_property(NULL);
        
        for (index = 0 ; index < object_type.GetAttributes().GetSize() ; ++index)
        {
            if (object_type.GetAttributes()[index]->_Param!=NULL
                && object_type.GetAttributes()[index]->_Param->IsEditable())
            {
                if (object_type.GetAttributes()[index]->_ItIsPointer
                    && *(void **)((ulong_ptr)_Data + object_type.GetAttributes()[index]->_Offset)==NULL)
                {
                    resource_property = NULL;
                    continue;
                }

                Type* type = object_type.GetAttributes()[index]->_Type;

                if (object_type.GetAttributes()[index]->_ItIsPointer
                    && !object_type.GetAttributes()[index]->_ItIsArray
                    && object_type.GetAttributes()[index]->_Type->GetInfo()==TYPE_INFO_Class)
                {
                    Object* object = *((Object **) ((ulong_ptr) _Data + object_type.GetAttributes()[index]->_Offset));
                    if (object!=NULL)
                        type = &object->GetMetaType();
                }

                object_info = COFFEE_New(ObjectInfo, 
                    (void *)((ulong_ptr) _Data + object_type.GetAttributes()[index]->_Offset),
                    type,
                    object_type.GetAttributes()[index]);

                object_info->SetResourceProperty(resource_property);

                Attach(*object_info);
            }
            else if (object_type.GetAttributes()[index]->_Type==&resource::PropertyBase::GetClassMetaType())
            {
                resource_property = (resource::PropertyBase *)((ulong_ptr) _Data
                    + object_type.GetAttributes()[index]->_Offset);
                continue;
            }

            resource_property = NULL;
        }
    }

}
}
