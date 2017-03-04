#ifndef _COFFEE_BASIC_TIME_CLOCK_H_
#define _COFFEE_BASIC_TIME_CLOCK_H_

#include "coffee_includes.h"
#include "kernel/basic/time/basic_time.h"

namespace coffee
{
namespace basic
{
    //--------------------------------------------------------------------------------------------//
    /// Clock
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Clock
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Clock();
        ~Clock();

        //-ACCESSORS------------------------------------------------------------------------------//

        const Time& GetTime() const;
        const Time& GetTimeStep() const;

        //-OPERATORS------------------------------------------------------------------------------//

        void Update();

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        Time _StartTime;
        Time _Time;
        Time _TimeStep;
        Time _TimeStepTime;
    };
}
}
#endif
