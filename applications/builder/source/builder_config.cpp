#include "builder_config.h"

namespace builder
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(Config);
        COFFEE_Attribute(builder::OPERATION, _Operation, meta::MODE_Serializeable|meta::MODE_Editable);
        COFFEE_Attribute(builder::TARGET, _Target, meta::MODE_Serializeable|meta::MODE_Editable);
        COFFEE_Attribute(builder::PLATFORM, _Platform, meta::MODE_Serializeable|meta::MODE_Editable);
        COFFEE_Attribute(builder::COMPILER, _Compiler, meta::MODE_Serializeable|meta::MODE_Editable);
        COFFEE_Attribute(builder::MODE, _Mode, meta::MODE_Serializeable|meta::MODE_Editable);
    COFFEE_EndType();

    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Config::Config() :
        _Operation(OPERATION_build),
        _Target(TARGET_all),
        _Platform(PLATFORM_win32),
        _Compiler(COMPILER_vs2008),
        _Mode(MODE_release)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Config::~Config()
    {
    }

    //-QUERIES------------------------------------------------------------------------------------//

    OPERATION Config::GetOperation() const
    {
        return _Operation;
    }

    //--------------------------------------------------------------------------------------------//

    basic::String Config::GetTarget() const
    {
        meta::Enum& enum_type = ((meta::Enum&)*COFFEE_FindType("builder::TARGET"));
        return enum_type.GetName((uint32)_Target);
    }
       
    //--------------------------------------------------------------------------------------------//

    basic::String Config::GetPlatform() const
    {
        meta::Enum& enum_type = ((meta::Enum&)*COFFEE_FindType("builder::PLATFORM"));
        return enum_type.GetName((uint32)_Platform);
    }
    
    //--------------------------------------------------------------------------------------------//

    basic::String Config::GetCompiler() const
    {
        meta::Enum& enum_type = ((meta::Enum&)*COFFEE_FindType("builder::COMPILER"));
        return enum_type.GetName((uint32)_Compiler);
    }
    
    //--------------------------------------------------------------------------------------------//

    basic::String Config::GetMode() const
    {
        meta::Enum& enum_type = ((meta::Enum&)*COFFEE_FindType("builder::MODE"));
        return enum_type.GetName((uint32)_Mode);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//


}
