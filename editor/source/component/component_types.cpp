#include "component/component_types.h"

namespace coffee_editor
{
namespace component
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_ImplementSingleton(Types);

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Types::Types()
    {
        COFFEE_CreateSingleton(Types);
        #include "component/component_registration.hpp"
    }

    //--------------------------------------------------------------------------------------------//

    Types::~Types()
    {
        COFFEE_DestroySingleton(Types);
    }

    //-QUERIES------------------------------------------------------------------------------------//

    uint32 Types::GetCount() const
    {
        return _Types.GetSize();
    }
    
    //--------------------------------------------------------------------------------------------//

    const basic::String& Types::GetName(uint32 index) const
    {
        COFFEE_Assert(index<_Types.GetSize(), core::ERROR_CODE_IncorrectUsage, "Component doesnt exist");
        return _Types[index]->Name;
    }
    
    //--------------------------------------------------------------------------------------------//

    const basic::String& Types::GetClassification(uint32 index) const
    {
        COFFEE_Assert(index<_Types.GetSize(), core::ERROR_CODE_IncorrectUsage, "Component doesnt exist");
        return _Types[index]->Classification;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    scene::Component* Types::Create(uint32 index) const
    {
        COFFEE_Assert(index<_Types.GetSize(), core::ERROR_CODE_IncorrectUsage, "Component doesnt exist");
        return static_cast<scene::Component*>(_Types[index]->MetaType->CreateObject());
    }

}
}
