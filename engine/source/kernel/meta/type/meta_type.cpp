#include "kernel/meta/type/meta_type.h"
#include "kernel/core/core.h"
#include "kernel/meta/meta_object.h"
#include "kernel/basic/container/basic_containers.h"
#include "kernel/basic/alpha/basic_alpha.h"

namespace coffee
{
namespace meta
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Type::Type(TYPE_INFO info) :
        _Name(COFFEE_New(basic::String)),
        _Size(0),
        _CreationMethod(NULL),
        _Info(info)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Type::~Type()
    {
        COFFEE_Delete(_Name);
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Type::SetName(const basic::String & name)
    {
        *_Name = name;
    }

    //--------------------------------------------------------------------------------------------//

    void Type::SetName(const char * name)
    {
        *_Name = name;
    }

    //--------------------------------------------------------------------------------------------//

    const basic::String & Type::GetName() const
    {
        return *_Name;
    }

    //--------------------------------------------------------------------------------------------//

    void Type::SetSize(ulong size)
    {
        _Size = size;
    }

    //--------------------------------------------------------------------------------------------//

    ulong Type::GetSize() const
    {
        return _Size;
    }

    //--------------------------------------------------------------------------------------------//

    const TYPE_INFO & Type::GetInfo() const
    {
        return _Info;
    }

    //--------------------------------------------------------------------------------------------//

    void Type::SetCreationMethod(Object * (* creation_method) ())
    {
        _CreationMethod = creation_method;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    Object * Type::CreateObject() const
    {
        COFFEE_Assert(_CreationMethod != NULL, core::ERROR_CODE_MetaSystem,
            "Failed to call meta::Type::CreateObject()");

        return _CreationMethod();
    }

    //--------------------------------------------------------------------------------------------//

    void Type::Serialize(Stream& stream)
    {
        COFFEE_Error(core::ERROR_CODE_MetaSystem, "Failed to serialize object");
    }

}
}
