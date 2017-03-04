#ifndef _COFFEE_CORE_PLATFORM_H_
#define _COFFEE_CORE_PLATFORM_H_

#include "coffee_includes.h"
#include "kernel/core/platform/core_platform_types.h"

namespace coffee
{
    //-FORWARDS-----------------------------------------------------------------------------------//
namespace basic
{
    class String;
    class Text;
    class Date;
}
namespace shell
{
    class Thread;
    class Mutex;
}
namespace meta
{
    class Object;
}

namespace core
{
    //--------------------------------------------------------------------------------------------//
    /// Access to core platform functions
    ///
    /// This class hide usefull OS specific functionalities needed to the engine.
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Platform
    {
        COFFEE_DeclareSingleton(Platform);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Platform();
        ~Platform();

        //-QUERIES--------------------------------------------------------------------------------//

        /// @brief Get time in seconds, elapsed since engine start
        real GetTime() const;

        /// @brief Get system date
        void GetDate(basic::Date& date) const;
        
        bool GetBuildTargets(basic::String& platform, basic::String& compiler, basic::String& mode) const;
        basic::String GetBuildPlatform() const;
        basic::String GetBuildCompiler() const;
        basic::String GetBuildMode() const;
        
        /// Launch a command, and don't wait the exit, best way to execute an external soft...
        bool Launch(const basic::String& executable_path, const basic::String& parameters,
            const basic::String& work_folder);

        /// Run a command, using pipe, and wait till finished
        bool Run(const basic::String& command, const basic::String& work_folder);
        
        /// Run a command, using pipe and having asynchronous access to the output
        bool RunPipe(const basic::String& command, const basic::String& work_folder,
            bool it_has_to_wait=true, bool it_has_to_show=false);
        bool IsPipeRunning() const;
        basic::String GetPipeOutput();
        uint32 GetPipeReturnCode();
        void StopPipe();

        /// Ask an existing file path, extensions looks like: [ "All", "*.*", "Others", "*.other" ]
        bool AskForFile(basic::String& path, const basic::Text& extensions);

    private:

        //-FUNCTIONS------------------------------------------------------------------------------//

        static void _PipeUpdate(meta::Object* platform);
        
        //-OPERATIONS-----------------------------------------------------------------------------//

        void _Initialize();
        void _Finalize();

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        shell::Thread* _PipeThread;
        shell::Mutex* _PipeMutex;
        basic::String* _PipeOutput;
        uint32 _PipeCode;

        //-PLATFORMS------------------------------------------------------------------------------//

        #include "kernel/core/platform/core_platform_windows.h"
        #include "kernel/core/platform/core_platform_unix.h"
    };
}
}
#endif
