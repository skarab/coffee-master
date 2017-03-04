//------------------------------------------------------------------------------------------------//
/// @file kernel/meta/type/class/meta_class.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "kernel/meta/type/class/meta_class.h"
#include "kernel/meta/type/class/meta_class_serializer.h"
#include "kernel/meta/meta_types.h"
#include "kernel/meta/array/meta_array.h"
#include "kernel/basic/container/basic_containers.h"
#include "kernel/basic/alpha/basic_alpha.h"
#include "kernel/meta/param/meta_params.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
namespace meta
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Class::Class() :
        Type(TYPE_INFO_Class),
        _Ancestor(NULL)
    {
        _Attributes = new basic::Prow<Attribute*, true>();
    }

    //--------------------------------------------------------------------------------------------//

    Class::~Class()
    {
        delete _Attributes;
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const Class* Class::GetAncestor() const
    {
        return _Ancestor;
    }

    //--------------------------------------------------------------------------------------------//

    Class* Class::GetAncestor()
    {
        return _Ancestor;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::Prow< Attribute *, true > & Class::GetAttributes() const
    {
        return *_Attributes;
    }

    //--------------------------------------------------------------------------------------------//

    basic::Prow< Attribute *, true > & Class::GetAttributes()
    {
        return *_Attributes;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool Class::IsKindOf(const Class& meta_type) const
    {
        if (this==&meta_type)
            return true;
        if (_Ancestor!=NULL)
            return _Ancestor->IsKindOf(meta_type);
        return false;
    }

    //----------------------------------------------------------------------------------------//

    const Attribute* Class::FindAttribute(const basic::String& name, bool it_has_to_check_ancestors) const
    {
        for (uint32 i=0 ; i<_Attributes->GetSize() ; ++i)
        {
            if (name==*(*_Attributes)[i]->_Name)
                return (*_Attributes)[i];
        }
        if (it_has_to_check_ancestors && _Ancestor!=NULL)
            return _Ancestor->FindAttribute(name);
        return NULL;
    }

    //--------------------------------------------------------------------------------------------//

    bool Class::FindNextAttribute(uint32& ancestor_index, uint32& attribute_index,
        Attribute** attribute, ulong_ptr& attribute_offset)
    {
        if (ancestor_index==0 && GetAttributes().GetSize()==0)
            ++ancestor_index;

        if (ancestor_index==0)
        {
            *attribute = GetAttributes()[attribute_index];
            attribute_offset = (*attribute)->_Offset;
            ++attribute_index;

            if(attribute_index>=GetAttributes().GetSize())
            {
                ++ancestor_index;
                attribute_index = 0;
            }
        }
        else
        {
            Class* ancestor;
            uint32 index(1);

            if (_Ancestor==NULL)
                return false;

            ancestor = _Ancestor;

            while (index<ancestor_index || ancestor->GetAttributes().GetSize()==0)
            {
                if (ancestor->GetAncestor()==NULL)
                    return false;
                ancestor = ancestor->GetAncestor();
                ++index;
            }

            *attribute = ancestor->GetAttributes()[attribute_index];
            attribute_offset = (*attribute)->_Offset;
            ++attribute_index;

            if(attribute_index>=ancestor->GetAttributes().GetSize())
            {
                ++ancestor_index;
                attribute_index = 0;
            }
        }

        return true;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Class::SetAncestor(const char* type_name)
    {
        basic::String type_string(type_name);
        _ParseTypeName(type_string);        
        Types::Get()._RequireType(type_string);
        _Ancestor = static_cast<Class*>(Types::Get().FindType(type_string));
    }

    //--------------------------------------------------------------------------------------------//

    void Class::SetAncestor(Class& meta_type)
    {
        _Ancestor = &meta_type;
    }
        
    //--------------------------------------------------------------------------------------------//

    void Class::AddAttribute(const char * name, const char * type_name, ulong_ptr offset,
        uint32 mode, Param * param)
    {
        basic::String name_string(name);
        basic::String type_string(type_name);

        // remove private prefix '_'
        if (name_string.IsPrefixed('_'))
            name_string.CutLeft(1);
        
        // remove boolean prefixes
        if (name_string.IsPrefixed("ItIs"))
            name_string.CutLeft(4);
        else if (name_string.IsPrefixed("ItHasTo"))
            name_string.CutLeft(7);
        else if (name_string.IsPrefixed("ItHas"))
            name_string.CutLeft(5);
            
        if (_ParseTypeName(type_string))
        {
            AddAttributeArray(
                name_string.GetBuffer(),
                type_string.GetBuffer(),
                offset,
                (param == NULL) ? COFFEE_New(ParamArray, mode, basic::String()) : param);
        }
        else
        {
            Attribute* attribute = COFFEE_New(Attribute);
            *attribute->_Name = name_string.GetBuffer();
            attribute->_Offset = offset;
            attribute->_Param = (param==NULL)? COFFEE_New(Param, mode) : param;

            if (type_string.IsContaining('*'))
            {
                attribute->_ItIsPointer = true;
                if (type_string.IsContaining('~'))
                    attribute->_ItIsWeak = true;
                _ParsePointerName(type_string);
            }

            Types::Get()._RequireType(type_string);
            attribute->_Type = Types::Get().FindType(type_string);
            _Attributes->AddItem(attribute);
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Class::AddAttributeArray(const char * name, const char * type_name, ulong_ptr offset,
        Param * param)
    {
        basic::String type_string(type_name);
        _ParseTypeName(type_string);
        Attribute* attribute = COFFEE_New(Attribute);
        *attribute->_Name = name;
        attribute->_Offset = offset;
        attribute->_Param = param;
        attribute->_ItIsArray = true;

        if (type_string.IsContaining('*'))
        {
            attribute->_ItIsPointer = true;
            attribute->_ItIsWeak = type_string.IsContaining('~');        
            _ParsePointerName(type_string);
        }

        Types::Get()._RequireType(type_string);
        attribute->_Type = Types::Get().FindType(type_string);
        _Attributes->AddItem(attribute);
    }

    //--------------------------------------------------------------------------------------------//

    void Class::Serialize(Stream& stream)
    {
        ClassSerializer serializer;
        serializer.Serialize(*this, stream);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    bool Class::_ParseTypeName(basic::String& type_name)
    {
        uint32 array_token;
        bool it_is_array(false);

        // parse tokens

        array_token = type_name.Find('<');

        if(array_token != NONE)
        {
            while(type_name[ ++ array_token ] == ' ');
            type_name.CutLeft(array_token);
            array_token = type_name.Find('>');
            COFFEE_Assert(array_token != NONE, core::ERROR_CODE_Unexpected, "Unexpected error");
            while(type_name[ -- array_token ] == ' ');
            type_name.CutRight(type_name.GetLength() - array_token - 1);
            it_is_array = true;
        }

        // remove namespace
        if (type_name.GetLength()>8 && type_name.GetLeft(8)=="coffee::")
        {
            type_name.CutLeft(8);
        }

        return it_is_array;
    }

    //--------------------------------------------------------------------------------------------//

    void Class::_ParsePointerName(basic::String& pointer_name)
    {
        basic::String type_name;
        int32 word_index = NONE;
        basic::Vector< basic::String > token_array;

        token_array.AddItem(' ');
        token_array.AddItem('*');
        token_array.AddItem('~');

        pointer_name.GetNextWord(type_name, word_index, token_array);
        pointer_name = type_name;
    }

}
}
//------------------------------------------------------------------------------------------------//
