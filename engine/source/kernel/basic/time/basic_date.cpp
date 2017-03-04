#include "kernel/basic/time/basic_date.h"

namespace coffee
{
    //-META---------------------------------------------------------------------------------------//

    COFFEE_BeginType(basic::Date);
        COFFEE_Attribute(uint16, _Year, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(uint16, _Month, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(uint16, _DayOfWeek, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(uint16, _Day, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(uint16, _Hour, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(uint16, _Minute, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(uint16, _Second, meta::MODE_Serializeable | meta::MODE_Editable);
        COFFEE_Attribute(uint16, _Millisecond, meta::MODE_Serializeable | meta::MODE_Editable);
    COFFEE_EndType();

namespace basic
{
    //-CONSTRUCTORS-------------------------------------------------------------------------------//

    Date::Date()
    {
        core::Platform::Get().GetDate(*this);
    }

    //--------------------------------------------------------------------------------------------//

    Date::Date(const Date& date)
    {
        operator =(date);
    }

    //--------------------------------------------------------------------------------------------//

    Date::~Date()
    {
    }

    //-OPERATORS----------------------------------------------------------------------------------//

    Date& Date::operator = (const Date& date)
    {
        _Year = date._Year;
        _Month = date._Month;
        _DayOfWeek = date._DayOfWeek;
        _Day = date._Day;
        _Hour = date._Hour;
        _Minute = date._Minute;
        _Second = date._Second;
        _Millisecond = date._Millisecond;
        return *this;
    }

    //--------------------------------------------------------------------------------------------//

    bool Date::operator == (const Date& date) const
    {
        return _Year==date._Year
            && _Month==date._Month
            && _DayOfWeek==date._DayOfWeek
            && _Day==date._Day
            && _Hour==date._Hour
            && _Minute==date._Minute
            && _Second==date._Second
            && _Millisecond==date._Millisecond;
    }
    
    //--------------------------------------------------------------------------------------------//

    bool Date::operator != (const Date& date) const
    {
        return !(*this==date);
    }

    //--------------------------------------------------------------------------------------------//

    #define CHECK_DATE(_i_) if (_i_>date._i_) return false; if (_i_<date._i_) return true; \

    bool Date::operator < (const Date& date) const
    {
        CHECK_DATE(_Year);
        CHECK_DATE(_Month);
        CHECK_DATE(_Day);
        CHECK_DATE(_Hour);
        CHECK_DATE(_Minute);
        CHECK_DATE(_Second);
        CHECK_DATE(_Millisecond);
        return false;
    }

    #undef COFFEE_CHECK_DATE
    
    //--------------------------------------------------------------------------------------------//

    bool Date::operator > (const Date& date) const
    {
        return !(*this<date);
    }

    //-OPERATIONS---------------------------------------------------------------------------------//


}
}
