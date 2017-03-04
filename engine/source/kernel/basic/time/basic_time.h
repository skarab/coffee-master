#ifndef _COFFEE_BASIC_TIME_H_
#define _COFFEE_BASIC_TIME_H_

#include "coffee_includes.h"
#include "kernel/meta/meta.h"

namespace coffee
{
namespace basic
{
    //--------------------------------------------------------------------------------------------//
    /// Time class
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Time : public meta::Object
    {
        COFFEE_Type(Time);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Time();
        Time(const Time& time);
        Time(real second_count);
        ~Time();

        //-OPERATORS------------------------------------------------------------------------------//

        Time& operator = (const Time& time);
        Time& operator = (real second_count);
        Time& operator += (const Time& time);
        Time& operator -= (const Time& time);
        Time& operator *= (real factor);
        Time& operator /= (real factor);
        Time operator + (const Time& time) const;
        Time operator - (const Time& time) const;
        Time operator * (real factor) const;
        Time operator / (real factor) const;
        bool operator == (const Time & time) const;

        //-ACCESSORS------------------------------------------------------------------------------//

        void SetSecondCount(real second_count);
        real GetSecondCount() const;
        real GetMilliSecondCount() const;

    private:

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        real _SecondCount;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Time);
}
}
#endif
