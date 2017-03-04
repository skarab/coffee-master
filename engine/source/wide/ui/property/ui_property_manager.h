#ifndef _COFFEE_UI_PROPERTY_MANAGER_H_
#define _COFFEE_UI_PROPERTY_MANAGER_H_

#include "coffee_includes.h"
#include "kernel/kernel.h"
#include "wide/ui/property/ui_property.h"
#include "wide/ui/property/ui_property_flag.h"
#include "wide/ui/property/ui_property_list.h"
#include "wide/ui/property/ui_property_undo.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// Property custom widget manager
    ///
    /// A ui::Property is a specific widget for a particular meta type.
    /// Class inheriting of ui::Property declare what they edit according to the meta type,
    /// the meta param type, and if its specific to arrays, using COFFEE_PropertyInterface.
    /// They are automatically registered to this manager using COFFEE_RegisterPropertyInterface.
    ///
    /// In Coffee, an edited object always go through the ui::PropertyList which parses the meta
    /// type using meta::ObjectInfo and create various widgets through this manager,
    /// using CreatePropertyInterface. 
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PropertyManager
    {
        COFFEE_DeclareSingleton(PropertyManager);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyManager();
        ~PropertyManager();

        //-OPERATIONS-----------------------------------------------------------------------------//

        Property* CreatePropertyInterface(Window& parent_window, meta::ObjectInfo& object_info,
            const meta::Type* meta_type, const meta::Param* meta_param, uint32 flags);
    
        /// Register the custom widget
        template<class T> void Register()
        {
            _PropertyInterface* inter = COFFEE_New(_PropertyInterface);
            inter->_HandledType = T::GetHandledTypeName();
            inter->_HandledParams = T::GetHandledParamName();
            inter->_ItIsHandlingArray = T::IsHandlingArray();
            inter->_MetaType = &meta::TYPE<T>().Get();
            _Interfaces.AddItem(inter);
        }

        /// Unregister the custom widget
        template<class T> void Unregister()
        {
            for (uint32 index=0 ; index<_Interfaces.GetSize() ; ++index)
            {
                if (_Interfaces[index]->_MetaType==&meta::TYPE<T>().Get())
                {
                    _Interfaces.Remove(index);
                    return;
                }
            }
            COFFEE_Error(core::ERROR_CODE_IncorrectUsage, "Property interface doesnt exist");
        }
        
    private:

        //-TYPES----------------------------------------------------------------------------------//

        struct _PropertyInterface
        {
            basic::String _HandledType;
            basic::String _HandledParams;
            bool _ItIsHandlingArray;
            meta::Type* _MetaType;
        };

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        basic::Prow<_PropertyInterface*, true> _Interfaces;
    };

}
}
#endif
