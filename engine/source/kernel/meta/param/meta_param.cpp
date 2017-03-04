//------------------------------------------------------------------------------------------------//
/// @file kernel/meta/param/meta_param.cpp
//------------------------------------------------------------------------------------------------//

//-INCLUDES---------------------------------------------------------------------------------------//
#include "kernel/meta/param/meta_param.h"
//------------------------------------------------------------------------------------------------//

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(meta::Param);
    COFFEE_EndType();

namespace meta
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Param::Param() :
        _Mode(MODE_None)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Param::Param(uint32 mode) :
        _Mode(mode)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Param::~Param()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    uint32 Param::GetMode() const
    {
        return _Mode;
    }

    //--------------------------------------------------------------------------------------------//

    void Param::SetMode(uint32 mode)
    {
        _Mode = mode;
    }

    //-QUERIES------------------------------------------------------------------------------------//

    bool Param::IsSerializeable() const
    {
        return (_Mode & MODE_Serializeable) > 0;
    }

    //--------------------------------------------------------------------------------------------//

    bool Param::IsEditable() const
    {
        return (_Mode & MODE_Editable) > 0;
    }

}
}
//------------------------------------------------------------------------------------------------//