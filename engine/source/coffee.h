#ifndef _COFFEE_H_
#define _COFFEE_H_

#include "coffee_includes.h"
#include "coffee_mode.h"
#include "coffee_externals.h"
#include "kernel/kernel.h"
#include "system/system.h"
#include "wide/wide.h"

//------------------------------------------------------------------------------------------------//
/// Coffee engine API
//------------------------------------------------------------------------------------------------//
namespace coffee
{
    //--------------------------------------------------------------------------------------------//
    /// Main class wrapping the whole engine and the application
    ///
    /// This is an internal class, use COFFEE_RegisterApplication to create a custom application.
    /// As a singleton, there may be only one Engine per process.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Engine
    {
        COFFEE_DeclareSingleton(Engine);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Engine(const char* command_line, uint32 modes=RUN_MODE_None);
        ~Engine();

        //-ACCESSORS------------------------------------------------------------------------------//

        /// Get the application name, based on the running executable
        const char* GetApplicationName() const { return _ApplicationName; }

        /// Get the application path, based on the running executable
        const char* GetApplicationPath() const { return _ApplicationPath; }
        
        //-QUERIES--------------------------------------------------------------------------------//

        /// Retrieve if a particular coffee::RUN_MODE is active
        bool HasMode(const RUN_MODE& mode) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        /// Update the registered modules through the coffee::shell::ModuleManager
        bool Update();

        /// Safely ask to quit the application
        void Quit();
        
    private:

        //-OPERATIONS-----------------------------------------------------------------------------//

        /// Parse application parameters from the command line
        void _ParseApplicationParameters(const char* command_line);

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        char _ApplicationName[64];
        char _ApplicationPath[2048];
        uint32 _Modes;
        bool _ItHasToQuit;
        core::Log* _Log;
        core::ErrorHandler _ErrorHandler;
        core::Platform* _Platform;
        core::Processor* _Processor;
        core::MemoryManager* _MemoryManager;
        meta::Types* _Meta;
        storage::PhysicalSystem* _PhysicalSystem;
        storage::System* _System;
        shell::ModuleManager* _ModuleManager;
    };
}
#endif
