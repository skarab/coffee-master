//------------------------------------------------------------------------------------------------//
/// @file kernel/meta/type/class/meta_class_serializer.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "kernel/meta/type/class/meta_class_serializer.h"
#include "kernel/meta/type/meta_type_templates.h"
#include "kernel/basic/alpha/basic_alpha.h"
#include "kernel/basic/container/prow/basic_prow.h"
#include "kernel/meta/serializer/meta_serializer.h"
#include "kernel/storage/storage.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
namespace meta
{
    //-TYPES--------------------------------------------------------------------------------------//

    struct ClassSerializer::Class
    {
        basic::String _TypeName;
        ulong _Size;
        ulong _SizePtr;
        meta::Class* _Ancestor;
        ulong_ptr _AncestorOffset;
    };

    //--------------------------------------------------------------------------------------------//

    struct ClassSerializer::Attribute
    {
        basic::String _Name;
        basic::String _TypeName;
        bool _ItIsAnArray;
        bool _ItIsAPointer;
        bool _ItIsWeak;
        ulong _Size;
        ulong _SizePtr;
        meta::Attribute* _Attribute;
    };

    //--------------------------------------------------------------------------------------------//

    struct ClassSerializer::Dictionnary
    {
        Class _Class;
        Class* _Ancestor;
        basic::Prow< Attribute*, true > _AttributeArray;

        Dictionnary() :
            _Ancestor(NULL)
        {
        }

        ~Dictionnary()
        {
            if (_Ancestor!=NULL)
                COFFEE_Delete(_Ancestor);
        }
    };

    //--------------------------------------------------------------------------------------------//

    ClassSerializer::ClassSerializer()
    {
    }

    //--------------------------------------------------------------------------------------------//

    ClassSerializer::~ClassSerializer()
    {
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ClassSerializer::Serialize(meta::Class& meta_type, Stream& stream)
    {
        ulong_ptr offset = stream.GetObjectOffset();
        _Dictionnary = COFFEE_New(Dictionnary);
        _PreSerializeDictionnary(meta_type, stream);
        _SerializeAncestors(stream);
        _SerializeAttributes(stream);
        _PostSerializeDictionnary(meta_type, stream);
        stream.SetObjectOffset(offset);
        COFFEE_Delete(_Dictionnary);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void ClassSerializer::_PreSerializeDictionnary(meta::Class& meta_type, Stream& stream)
    {
        ulong object_size(0);
        uint32 array_size(0);
        uint32 index;
        
        if (stream.GetMode()==storage::MODE_Output)
        {
            _ClassSize = stream.GetStream().GetSize();
            _BuildDictionnary(meta_type, stream);

            stream.GetStream().PushString(_Dictionnary->_Class._TypeName);
            _Dictionnary->_Class._SizePtr = stream.GetStream().GetSize();
            stream.GetStream().Push(&object_size, sizeof(ulong));

            bool it_has_ancestor = _Dictionnary->_Ancestor!=NULL;
            stream.GetStream().Push(&it_has_ancestor, sizeof(bool));
            if (it_has_ancestor)
            {
                stream.GetStream().PushString(_Dictionnary->_Ancestor->_TypeName);
                _Dictionnary->_Ancestor->_SizePtr = stream.GetStream().GetData().GetSize();
                stream.GetStream().Push(&object_size, sizeof(ulong));
            }

            array_size = _Dictionnary->_AttributeArray.GetSize();
            stream.GetStream().Push(&array_size, sizeof(uint32));

            for(index=0 ; index<_Dictionnary->_AttributeArray.GetSize() ; ++index)
            {
                stream.GetStream().PushString(_Dictionnary->_AttributeArray[index]->_Name);
                stream.GetStream().PushString(_Dictionnary->_AttributeArray[index]->_TypeName);
                stream.GetStream().Push(&_Dictionnary->_AttributeArray[index]->_ItIsAnArray, sizeof(bool));
                stream.GetStream().Push(&_Dictionnary->_AttributeArray[index]->_ItIsAPointer, sizeof(bool));
                stream.GetStream().Push(&_Dictionnary->_AttributeArray[index]->_ItIsWeak, sizeof(bool));
                _Dictionnary->_AttributeArray[index]->_SizePtr = stream.GetStream().GetData().GetSize();
                stream.GetStream().Push(&object_size, sizeof(ulong));
            }
        }
        else
        {
            stream.GetStream().PopString(_Dictionnary->_Class._TypeName);
            stream.GetStream().Pop(&_Dictionnary->_Class._Size, sizeof(ulong));

            bool it_has_ancestor;
            stream.GetStream().Pop(&it_has_ancestor, sizeof(bool));
            if (it_has_ancestor)
            {
                Class* ancestor = COFFEE_New(Class);
                stream.GetStream().PopString(ancestor->_TypeName);
                stream.GetStream().Pop(&ancestor->_Size, sizeof(ulong));
                _Dictionnary->_Ancestor = ancestor;
            }

            stream.GetStream().Pop(&array_size, sizeof(uint32));
            _Dictionnary->_AttributeArray.Resize(array_size);

            for(index=0 ; index<_Dictionnary->_AttributeArray.GetSize() ; ++index)
            {
                Attribute* attribute = COFFEE_New(Attribute);
                stream.GetStream().PopString(attribute->_Name);
                stream.GetStream().PopString(attribute->_TypeName);
                stream.GetStream().Pop(&attribute->_ItIsAnArray, sizeof(bool));
                stream.GetStream().Pop(&attribute->_ItIsAPointer, sizeof(bool));
                stream.GetStream().Pop(&attribute->_ItIsWeak, sizeof(bool));
                stream.GetStream().Pop(&attribute->_Size, sizeof(ulong));
                _Dictionnary->_AttributeArray[index] = attribute;
            }

            _BuildDictionnary(meta_type, stream);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void ClassSerializer::_BuildDictionnary(meta::Class& meta_type, Stream& stream)
    {
        uint32 index;

        if (stream.GetMode()==storage::MODE_Output)
        {
            ulong_ptr offset = stream.GetObjectOffset();
            ulong_ptr ancestor_offset = offset;

            static int count = 0;
            _Dictionnary->_Class._TypeName = meta_type.GetName();
            _Dictionnary->_Class._Size = 0;
            ++count;

            if (meta_type.GetAncestor()!=NULL)
            {
                Class* ancestor = COFFEE_New(Class);
                ancestor->_TypeName = meta_type.GetAncestor()->GetName();
                ancestor->_Size = 0;
                ancestor->_Ancestor = meta_type.GetAncestor();
                ancestor->_AncestorOffset = ancestor_offset;
                _Dictionnary->_Ancestor = ancestor;
                ancestor_offset += meta_type.GetAncestor()->GetSize();
            }

            for (index=0 ; index<meta_type.GetAttributes().GetSize() ; ++index)
            {
                if (meta_type.GetAttributes()[index]->_Param!=NULL
                    && meta_type.GetAttributes()[index]->_Param->IsSerializeable())
                {
                    Attribute* attribute = COFFEE_New(Attribute);
                    attribute->_Name = *meta_type.GetAttributes()[index]->_Name;
                    attribute->_TypeName = meta_type.GetAttributes()[index]->_Type->GetName();
                    attribute->_ItIsAnArray = meta_type.GetAttributes()[index]->_ItIsArray;
                    attribute->_ItIsAPointer = meta_type.GetAttributes()[index]->_ItIsPointer;
                    attribute->_ItIsWeak = meta_type.GetAttributes()[index]->_ItIsWeak;
                    attribute->_Size = 0;
                    attribute->_Attribute = meta_type.GetAttributes()[index];
                    _Dictionnary->_AttributeArray.AddItem(attribute);
                }
            }
        }
        else
        {
            ulong_ptr offset = stream.GetObjectOffset();

            if (_Dictionnary->_Ancestor!=NULL)
                _SearchAncestor(meta_type, _Dictionnary->_Ancestor, offset);
            
            for (index=0 ; index<_Dictionnary->_AttributeArray.GetSize() ; ++index)
                _SearchAttribute(meta_type, _Dictionnary->_AttributeArray[index]);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void ClassSerializer::_PostSerializeDictionnary(meta::Class& meta_type, Stream& stream)
    {
        if (stream.GetMode()==storage::MODE_Output)
        {
            _ClassSize = stream.GetStream().GetData().GetSize() - _ClassSize;
            _Dictionnary->_Class._Size = _ClassSize;
            *((ulong *)(stream.GetStream().GetData().GetBuffer() + _Dictionnary->_Class._SizePtr)) =
                _Dictionnary->_Class._Size;
        }
    }

    //--------------------------------------------------------------------------------------------//

    void ClassSerializer::_SerializeAncestors(Stream& stream)
    {
        ulong_ptr offset = stream.GetObjectOffset();

        if (_Dictionnary->_Ancestor!=NULL)
        {
            Class& ancestor = *_Dictionnary->_Ancestor;
            if (ancestor._Ancestor!=NULL)
            {
                if (stream.GetMode()==storage::MODE_Output)
                    _ObjectSize = stream.GetStream().GetData().GetSize();

                stream.SetObjectOffset(ancestor._AncestorOffset);
                stream.GetSerializer().SerializeObjectFromType(stream, *ancestor._Ancestor);
            
                if (stream.GetMode()==storage::MODE_Output)
                {
                    _ObjectSize = stream.GetStream().GetData().GetSize()-_ObjectSize;
                    *((ulong*)(stream.GetStream().GetData().GetBuffer()+ancestor._SizePtr)) = _ObjectSize;
                }
            }
            else
            {
                stream.GetStream().Pop(ancestor._Size);
            }
        }

        stream.SetObjectOffset(offset);
    }

    //--------------------------------------------------------------------------------------------//

    void ClassSerializer::_SerializeAttributes(Stream& stream)
    {
        uint32 index;
        ulong_ptr offset = stream.GetObjectOffset();

        for (index=0 ; index<_Dictionnary->_AttributeArray.GetSize() ; ++index)
        {
            Attribute& attribute = *_Dictionnary->_AttributeArray[index];

            if (attribute._Attribute!=NULL)
            {
                if (stream.GetMode()==storage::MODE_Output)
                    _ObjectSize = stream.GetStream().GetData().GetSize();

                stream.SetObjectOffset(offset + attribute._Attribute->_Offset);
                _SerializeAttribute(*attribute._Attribute, stream);

                if (stream.GetMode()==storage::MODE_Output)
                {
                    _ObjectSize = stream.GetStream().GetData().GetSize() - _ObjectSize;
                    *((ulong *)(stream.GetStream().GetData().GetBuffer() + attribute._SizePtr)) = _ObjectSize;
                }
            }
            else
            {
                stream.GetStream().Pop(attribute._Size);
            }
        }

        stream.SetObjectOffset(offset);
    }

    //--------------------------------------------------------------------------------------------//

    void ClassSerializer::_SerializeAttribute(meta::Attribute& attribute, Stream& stream)
    {
        if (!attribute._ItIsPointer && !attribute._ItIsArray)
        {
            if (attribute._Type->GetInfo()==TYPE_INFO_Scalar)
            {
                stream.GetSerializer().SerializeObjectFromType(stream, *attribute._Type);
            }
            else
            {
                stream.GetSerializer().SerializeObject(stream, *(Object*)stream.GetObject());            
            }
        }
        else if (attribute._ItIsArray)
        {
            stream.GetSerializer().SerializeArray(stream, attribute);
        }
        else if(attribute._ItIsPointer)
        {
            stream.GetSerializer().SerializePointer(stream, attribute);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void ClassSerializer::_SearchAncestor(meta::Class& meta_type, Class* ancestor, ulong_ptr offset)
    {
        ulong_ptr ancestor_offset = offset;

        ancestor->_Ancestor = NULL;

        if (meta_type.GetAncestor()!=NULL)
        {
            meta::Class& meta_ancestor = *meta_type.GetAncestor();

            if (ancestor->_TypeName==meta_ancestor.GetName())
            {
                ancestor->_Ancestor = &meta_ancestor;
                ancestor->_AncestorOffset = ancestor_offset;
                return;
            }

            _SearchAncestor(meta_ancestor, ancestor, ancestor_offset);

            if (ancestor->_Ancestor!=NULL)
                return;

            ancestor_offset += meta_ancestor.GetSize();
        }
    }

    //--------------------------------------------------------------------------------------------//

    void ClassSerializer::_SearchAttribute(meta::Class& meta_type, Attribute* attribute)
    {
        attribute->_Attribute = NULL;

        for (uint32 index=0 ; index<meta_type.GetAttributes().GetSize() ; ++index)
        {
            meta::Attribute& meta_attribute = *meta_type.GetAttributes()[index];

            if(attribute->_ItIsAPointer==meta_attribute._ItIsPointer
                && attribute->_ItIsWeak==meta_attribute._ItIsWeak
                && attribute->_ItIsAnArray==meta_attribute._ItIsArray
                && attribute->_Name==*meta_attribute._Name
                && attribute->_TypeName==meta_attribute._Type->GetName())
            {
                attribute->_Attribute = &meta_attribute;
                return;
            }
        }
    }

}
}
//------------------------------------------------------------------------------------------------//
