#ifndef _COFFEE_INPUT_DEVICE_BUTTON_H_
#define _COFFEE_INPUT_DEVICE_BUTTON_H_

#include "coffee_includes.h"
#include "kernel/basic/time/basic_time.h"

namespace coffee
{
namespace input
{
    class Device;

    //--------------------------------------------------------------------------------------------//
    /// Input device button
    //--------------------------------------------------------------------------------------------//
    class COFFEE_API DeviceButton
    {
    public:

        //-CONSTRUCTORS---------------------------------------------------------------------------//

        DeviceButton();
        virtual ~DeviceButton();

        //-QUERIES--------------------------------------------------------------------------------//

        virtual real GetPressure() const;
        virtual bool IsPressed() const;
        virtual bool WasPressed() const;
        virtual bool IsJustPressed() const;
        virtual bool IsJustReleased() const;
        bool IsRepeatPressed() const;
        bool IsRepeating() const;

        //-OPERATIONS-----------------------------------------------------------------------------//

        virtual void Update(const basic::Time& time_step);

    protected:

        //-ACCESSORS------------------------------------------------------------------------------//

        bool _ItIsPressed, _ItWasPressed;
        basic::Time _PressTime;
    };
}
}
#endif
