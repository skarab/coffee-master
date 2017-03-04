#include "kernel/basic/time/basic_time.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(basic::Time);
        COFFEE_Attribute(real, _SecondCount, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace basic
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Time::Time() :
        _SecondCount(0.0f)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Time::Time(const Time & time) :
        _SecondCount(time.GetSecondCount())
    {
    }

    //--------------------------------------------------------------------------------------------//

    Time::Time(real second_count) :
        _SecondCount(second_count)
    {
    }

    //--------------------------------------------------------------------------------------------//

    Time::~Time()
    {
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    Time& Time::operator = (const Time& time)
    {
        SetSecondCount(time.GetSecondCount());
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Time& Time::operator = (real second_count)
    {
        SetSecondCount(second_count);
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Time& Time::operator += (const Time& time)
    {
        SetSecondCount(GetSecondCount() + time.GetSecondCount());
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Time& Time::operator -= (const Time& time)
    {
        SetSecondCount(GetSecondCount() - time.GetSecondCount());
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Time& Time::operator *= (real factor)
    {
        SetSecondCount(GetSecondCount() * factor);
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Time& Time::operator /= (real factor)
    {
        SetSecondCount(GetSecondCount() / factor);

        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    Time Time::operator + (const Time& time) const
    {
        Time result(*this);
        result += time;
        return result;
    }

    //--------------------------------------------------------------------------------------------//

    Time Time::operator - (const Time& time) const
    {
        Time result(*this);
        result -= time;
        return result;
    }

    //--------------------------------------------------------------------------------------------//

    Time Time::operator * (real factor) const
    {
        Time result(*this);
        result *= factor;
        return result;
    }

    //--------------------------------------------------------------------------------------------//

    Time Time::operator / (real factor) const
    {
        Time result(*this);
        result /= factor;
        return result;
    }

    //--------------------------------------------------------------------------------------------//

    bool Time::operator == (const Time & time) const
    {
        return (_SecondCount == time._SecondCount);
    }

    //-ACCESSORS----------------------------------------------------------------------------------//

    void Time::SetSecondCount(real second_count)
    {
        _SecondCount = second_count;
    }

    //--------------------------------------------------------------------------------------------//

    real Time::GetSecondCount() const
    {
        return _SecondCount;
    }

    //--------------------------------------------------------------------------------------------//

    real Time::GetMilliSecondCount() const
    {
        return _SecondCount * 1000.0f;
    }

}
}
