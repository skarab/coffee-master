#ifndef _BUILDER_CONFIG_H_
#define _BUILDER_CONFIG_H_

#include "builder_includes.h"
#include "builder_modes.h"

namespace builder
{
    //--------------------------------------------------------------------------------------------//
    /// Configuration
    //--------------------------------------------------------------------------------------------//
    class Config : public meta::Object
    {
        COFFEE_Type(Config);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Config();
        ~Config();

        //-QUERIES--------------------------------------------------------------------------------//
    
        OPERATION GetOperation() const;
        basic::String GetTarget() const;
        basic::String GetPlatform() const;
        basic::String GetCompiler() const;
        basic::String GetMode() const;
        
    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        OPERATION _Operation;
        TARGET _Target;
        PLATFORM _Platform;
        COMPILER _Compiler;
        MODE _Mode;
    };

    COFFEE_RegisterType(BUILDER_EXPORT_STATICS, Config);
}
#endif
