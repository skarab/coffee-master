#include "coffee.h"
#include "kernel/meta/meta_types.h"
#include "kernel/core/core.h"
#include "kernel/meta/meta_object.h"
#include "kernel/meta/type/meta_type.h"
#include "kernel/meta/type/class/meta_class.h"
#include "kernel/meta/type/scalar/meta_scalar.h"
#include "kernel/meta/array/meta_array.h"
#include "kernel/basic/container/basic_containers.h"
#include "kernel/basic/alpha/basic_alpha.h"
#include "kernel/shell/thread/shell_locker.h"

namespace coffee
{
namespace meta
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_ImplementSingleton(Types);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Types::Types() :
        _NullClassType(COFFEE_New(Class)),
        _Types(COFFEE_New(basic::Prow<Type*>)),
        _RequiredTypes(COFFEE_New(basic::Prow<Type*>))
    {
        COFFEE_CreateSingleton(Types);
        _RegisterTypes();
    }

    //--------------------------------------------------------------------------------------------//

    Types::~Types()
    {
        _UnregisterTypes();
        COFFEE_Delete(_RequiredTypes);
        COFFEE_Delete(_Types);
        COFFEE_DestroySingleton(Types);
        COFFEE_Delete(_NullClassType);
    }

    //-ACCESSORS------------------------------------------------------------------------------//

    const Class& Types::GetNullClassType() const
    {
        return *_NullClassType;
    }

    //--------------------------------------------------------------------------------------------//

    Class& Types::GetNullClassType()
    {
        return *_NullClassType;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    const Type* Types::FindType(const basic::String type_name) const
    {
        shell::Locker lock(((Types*)this)->_Mutex);
        for (uint32 index=0 ; index<_Types->GetSize() ; ++index)
        {
            if ((*_Types)[index]->GetName()==type_name)
                return (*_Types)[index];
        }
        return NULL;
    }

    //--------------------------------------------------------------------------------------------//

    Type* Types::FindType(const basic::String type_name)
    {
        shell::Locker lock(_Mutex);
        for (uint32 index=0 ; index<_Types->GetSize() ; ++index)
        {
            Type* type = (*_Types)[index];
            if (type->GetName()==type_name)
                return type;
        }
        return NULL;
    }

    //--------------------------------------------------------------------------------------------//

    bool Types::HasType(const basic::String type_name) const
    {
        return FindType(type_name)!=NULL;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Types::_RegisterTypes(basic::Prow<Type*>& registered_types)
    {
        shell::Locker lock(_Mutex);
        registered_types.Clear();
        registered_types.Resize(_TypeRegistrationCount);
        for (uint32 index=0 ; index<_TypeRegistrationCount ; ++index)
        {
            _TypeRegistrationArray[index].Register(_TypeRegistrationArray[index]);
            registered_types[index] = (*_Types)[_Types->GetSize()-1];
        }

        free(_TypeRegistrationArray);
        _TypeRegistrationArray = NULL;
        _TypeRegistrationCount = 0;

        if (_RequiredTypes->GetSize()>0 && Engine::Get().HasMode(RUN_MODE_MetaType))
        {
            for (uint32 index=0 ; index<_RequiredTypes->GetSize() ; ++index)
            {
                COFFEE_Log(core::Log::Debug, "[RUN_MODE_MetaType] Types : Failed to register %s",
                    (*_RequiredTypes)[index]->GetName().GetBuffer());
            }

            COFFEE_Error(core::ERROR_CODE_MetaSystem, "Failed to register all needed types");
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Types::_UnregisterTypes(basic::Prow<Type*>& registered_types)
    {
        shell::Locker lock(_Mutex);
        for (uint32 index=0 ; index<registered_types.GetSize() ; ++index)
        {
            if (Engine::Get().HasMode(RUN_MODE_MetaType))
            {
                COFFEE_Log(core::Log::Debug, "[RUN_MODE_MetaType] Unregistering %s",
                    registered_types[index]->GetName().GetBuffer());
            }
        
            uint32 type_index = _Types->FindItem(registered_types[index]);
            COFFEE_Assert(type_index!=NONE, core::ERROR_CODE_MetaSystem, "Type is not registered");
            COFFEE_Delete((*_Types)[type_index]);
            (*_Types)[type_index] = NULL;
        }

        basic::Prow<Type *>* types = _Types;
        _Types = COFFEE_New(basic::Prow<Type*>);
        _Types->Reserve(types->GetSize());
        for (uint32 index=0 ; index<types->GetSize() ; ++index)
        {
            if ((*types)[index]!=NULL)
                _Types->AddItem((*types)[index]);
        }
        COFFEE_Delete(types);
    }
        
    //--------------------------------------------------------------------------------------------//

    void Types::_RegisterType(Type& type)
    {
        if (Engine::Get().HasMode(RUN_MODE_MetaType))
            COFFEE_Log(core::Log::Debug, "[RUN_MODE_MetaType] Registering %s", type.GetName().GetBuffer());
        
        _RemoveRequiredType(_Types->AddItem(&type));

        int count=0;
        for (uint32 index=0 ; index<_Types->GetSize() ; ++index)
        {
            if ((*_Types)[index]->GetName()==type.GetName())
                ++ count;
        }

        if (count!=1)
        {
            COFFEE_Log(core::Log::Error, "meta::Type %s is already registered",
                type.GetName().GetBuffer());
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Types::_RequireType(const basic::String& type_name)
    {
        if (!HasType(type_name))
        {
            Type* type = COFFEE_New(Type, TYPE_INFO_None);
            type->SetName(type_name);
            _RequiredTypes->AddItem(type);
            _Types->AddItem(type);
        }
    }

    //-FUNCTIONS----------------------------------------------------------------------------------//

    void Types::_AddTypeRegistration(
        void (*registeration_method)(_TypeRegistration&),
        Object* (*creation_method) ())
    {
        if (_TypeRegistrationArray==NULL)
        {
            _TypeRegistrationArray = (_TypeRegistration*)malloc(sizeof(_TypeRegistration));
        }
        else
        {
            for (uint32 index=0 ; index<_TypeRegistrationCount ; ++index)
                if (registeration_method==_TypeRegistrationArray[index].Register)
                    return;

            _TypeRegistrationArray = (_TypeRegistration*)realloc(_TypeRegistrationArray,
                sizeof(_TypeRegistration)*(_TypeRegistrationCount+1));
        }

        _TypeRegistrationArray[_TypeRegistrationCount].Register = registeration_method;
        _TypeRegistrationArray[_TypeRegistrationCount].Create = creation_method;
        ++_TypeRegistrationCount;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Types::_RegisterTypes()
    {
        Class* type;

        type = COFFEE_New(Class);
        type->SetName("meta::Object");
        _RegisterType(*type);

        SCALAR_FORMAT_Register();

        for (uint32 index=0 ; index<_TypeRegistrationCount ; ++index)
            _TypeRegistrationArray[index].Register(_TypeRegistrationArray[index]);

        free(_TypeRegistrationArray);
        _TypeRegistrationArray = NULL;
        _TypeRegistrationCount = 0;

        if (_RequiredTypes->GetSize()>0 && Engine::Get().HasMode(RUN_MODE_MetaType))
        {
            for (uint32 index=0 ; index<_RequiredTypes->GetSize() ; ++index)
            {
                COFFEE_Log(core::Log::Debug, "[RUN_MODE_MetaType] Types : Failed to register %s",
                    (*_RequiredTypes)[index]->GetName().GetBuffer());
            }

            COFFEE_Error(core::ERROR_CODE_MetaSystem, "Failed to register all needed types");
        }
    }

    //--------------------------------------------------------------------------------------------//

    void Types::_UnregisterTypes()
    {
        for (uint32 index=0 ; index<_Types->GetSize() ; ++index)
        {
            if (Engine::Get().HasMode(RUN_MODE_MetaType))
            {
                COFFEE_Log(core::Log::Debug, "[RUN_MODE_MetaType] Unregistering %s",
                    (*_Types)[index]->GetName().GetBuffer());
            }

            COFFEE_Delete((*_Types)[index]);
            (*_Types)[index] = NULL;
        }

        _Types->Erase();
    }

    //--------------------------------------------------------------------------------------------//

    void Types::_RemoveRequiredType(uint32 type_index)
    {
        // Check if its a required type
        uint32 index;
        for (index=0 ; index<_RequiredTypes->GetSize() ; ++index)
            if ((*_RequiredTypes)[index]->GetName()==(*_Types)[type_index]->GetName())
                break;
        if(index==_RequiredTypes->GetSize())
            return;

        // Update ancestor & attribute pointing on the required type
        for (uint32 tindex=0 ; tindex<_Types->GetSize() ; ++tindex)
        {
            if ((*_Types)[tindex]->GetInfo()==TYPE_INFO_Class)
            {
                Class* object = (Class*)(*_Types)[tindex];

                if (object->GetAncestor()!=NULL && object->GetAncestor()->GetName()==(*_Types)[type_index]->GetName())
                    object->SetAncestor(*(Class *)((*_Types)[type_index]));
            
                for (uint32 attribute=0 ; attribute<object->GetAttributes().GetSize() ; ++attribute)
                {
                    if (object->GetAttributes()[attribute]->_Type->GetName()==(*_Types)[type_index]->GetName())
                        object->GetAttributes()[attribute]->_Type = (*_Types)[type_index];
                }
            }
        }

        // Remove required type
        for (int32 tindex=0 ; tindex<(int32)_Types->GetSize() ; ++tindex)
        {
            if (tindex!=(int32)type_index && (*_Types)[tindex]->GetName()==(*_Types)[type_index]->GetName())
            {
                COFFEE_Delete((*_Types)[tindex]);
                (*_Types)[tindex] = NULL;
                _Types->Remove(tindex);
                break;
            }
        }
        _RequiredTypes->Remove(index);
    }

    //-VARIABLES----------------------------------------------------------------------------------//

    Types::_TypeRegistration* Types::_TypeRegistrationArray = NULL;
    uint32 Types::_TypeRegistrationCount = 0;
}
}
