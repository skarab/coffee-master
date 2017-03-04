#ifndef _COFFEE_UI_PROPERTY_UINT32_ENUM_MULTI_H_
#define _COFFEE_UI_PROPERTY_UINT32_ENUM_MULTI_H_

#include "coffee_includes.h"
#include "kernel/basic/basic.h"
#include "wide/ui/property/ui_property_manager.h"
#include "wide/ui/widget/widgets.h"

namespace coffee
{
namespace ui
{
    //--------------------------------------------------------------------------------------------//
    /// uint32 property, based on enum
    ///
    /// Active when coffee::meta::ParamEnumMulti is set in COFFEE_Attribute on an uint32,
    /// it binds the uint32 to an enum in SINGLE mode, using a MULTI mode approach.
    ///
    /// @see coffee::meta::ParamEnumMulti
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API PropertyUInt32EnumMulti : public Property
    {
        //-META-----------------------------------------------------------------------------------//

        COFFEE_PropertyInterface(PropertyUInt32EnumMulti, "uint32", "meta::ParamEnumMulti", false);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        PropertyUInt32EnumMulti();
        virtual ~PropertyUInt32EnumMulti();

        //-OPERATIONS-----------------------------------------------------------------------------//

        void CreateContent();

        //-EVENTS---------------------------------------------------------------------------------//

        COFFEE_DeclareEventHandler(PropertyUInt32EnumMulti);
        COFFEE_Event bool OnCheckItem(shell::Event& event);

    private:

        //-ACCESSORS------------------------------------------------------------------------------//

        void _EnableFlag(uint32 flag_index, bool it_has_to_enable);
        bool _IsFlagEnabled(uint32 flag_index) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        void _InitializeContent();
        void _CreateHierarchy(uint32 item_index);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        widget::Group* _Group;
    };

    //-META---------------------------------------------------------------------------------------//

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, PropertyUInt32EnumMulti);
}
}
#endif
