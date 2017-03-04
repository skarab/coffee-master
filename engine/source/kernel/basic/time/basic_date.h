#ifndef _COFFEE_BASIC_DATE_H_
#define _COFFEE_BASIC_DATE_H_

#include "coffee_includes.h"
#include "kernel/meta/meta.h"

namespace coffee
{
namespace basic
{
    //--------------------------------------------------------------------------------------------//
    /// Contains date information, retrievable using coffee::core::Platform
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API Date : public meta::Object
    {
        COFFEE_Type(Date);

    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        Date();
        Date(const Date& date);
        ~Date();

        //-OPERATORS------------------------------------------------------------------------------//

        Date& operator = (const Date& date);
        bool operator == (const Date& date) const;
        bool operator != (const Date& date) const;
        bool operator < (const Date& date) const;
        bool operator > (const Date& date) const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        

        //-ATTRIBUTES-----------------------------------------------------------------------------//

        uint16 _Year;
        uint16 _Month;
        uint16 _DayOfWeek;
        uint16 _Day;
        uint16 _Hour;
        uint16 _Minute;
        uint16 _Second;
        uint16 _Millisecond;
    };

    COFFEE_RegisterType(COFFEE_EXPORT_STATICS, Date);
}
}
#endif
