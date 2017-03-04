#ifndef _COFFEE_PLUGINS_COMPONENT_LIBRARY_H_
#define _COFFEE_PLUGINS_COMPONENT_LIBRARY_H_

#include "coffee_includes.h"
#include "wide/plugins/plugins_library.h"

namespace coffee
{
namespace plugins
{
    //--------------------------------------------------------------------------------------------//
    /// Plugin library dedicated to component creation
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API ComponentLibrary : public Library
    {
        COFFEE_Type(ComponentLibrary);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        ComponentLibrary();
        ~ComponentLibrary();

        //-OPERATIONS-----------------------------------------------------------------------------//

        template<class T> T* CreateComponent()
        {
            if (_ComponentType==NULL)
                return NULL;
            T* component = static_cast<T*>(_ComponentType->CreateObject());
            _Components.AddItem(component);
            return component;
        }

        //----------------------------------------------------------------------------------------//

        template<class T> void Register()
        {
            _ComponentType = &meta::TYPE<T>().Get();
        }
        
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        meta::Type* _ComponentType;
        basic::Prow<meta::Object*, true> _Components;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, ComponentLibrary);
}
}
#endif
