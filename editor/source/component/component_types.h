#ifndef _EDITOR_COMPONENT_TYPES_H_
#define _EDITOR_COMPONENT_TYPES_H_

#include "coffee_editor_includes.h"

namespace coffee_editor
{
namespace component
{
    //--------------------------------------------------------------------------------------------//
    /// Register GUI exposed components
    //--------------------------------------------------------------------------------------------//
    class COFFEE_EDITOR_API Types
    {
        COFFEE_DeclareSingleton(Types);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Types();
        ~Types();

        //-QUERIES--------------------------------------------------------------------------------//

        uint32 GetCount() const;
        const basic::String& GetName(uint32 index) const;
        const basic::String& GetClassification(uint32 index) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        scene::Component* Create(uint32 index) const;

        template<class T> void Register()
        {
            _ComponentType* type = COFFEE_New(_ComponentType);
            type->Name = T::GetStaticName();
            type->Classification = T::GetStaticClassification();
            type->MetaType = &meta::TYPE<T>().Get();
            _Types.AddItem(type);
        }
        
        template<class T> void Unregister()
        {
            for (uint32 index=0 ; index<_Types.GetSize() ; ++index)
            {
                if (_Types[index]->MetaType==&meta::TYPE<T>().Get())
                {
                    _Types.Remove(index);
                    return;
                }
            }
            COFFEE_Error(core::ERROR_CODE_IncorrectUsage, "Component doesn't exist");    
        }

    private:

        //-TYPES----------------------------------------------------------------------------------//

        struct _ComponentType
        {
            basic::String Name;
            basic::String Classification;
            meta::Type* MetaType;
        };

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Prow<_ComponentType*, true> _Types;
    };

}
}
#endif
