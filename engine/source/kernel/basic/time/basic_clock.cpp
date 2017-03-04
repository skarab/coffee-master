#include "kernel/basic/time/basic_clock.h"
#include "kernel/core/platform/core_platform.h"

namespace coffee
{
namespace basic
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Clock::Clock() :
        _Time(0.0f),
        _TimeStep(0.0f),
        _TimeStepTime(0.0f)
    {
        _StartTime.SetSecondCount(core::Platform::Get().GetTime());
    }

    //--------------------------------------------------------------------------------------------//

    Clock::~Clock()
    {
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    const Time& Clock::GetTime() const
    {
        return _Time;
    }

    //--------------------------------------------------------------------------------------------//

    const Time& Clock::GetTimeStep() const
    {
        return _TimeStep;
    }

    //-OPERATIONS---------------------------------------------------------------------------------//

    void Clock::Update()
    {
        Time current_time(core::Platform::Get().GetTime());
        if (current_time.GetSecondCount()<_StartTime.GetSecondCount())
        {
            _StartTime = current_time;
            _TimeStepTime = 0.0f;
        }
        _Time = current_time-_StartTime;
        _TimeStep = _Time-_TimeStepTime;
        if (_TimeStep.GetSecondCount()<0.0f)
        {
            _TimeStep = 0.0f;
            _TimeStepTime = _Time;
        }
        _TimeStepTime += _TimeStep;
    }

}
}
